#include <Arduino.h>
#include <vector>
#include <cstring>
#include <esp_now.h>
#include <cmath>
#include <WiFi.h>
#include <esp_dmx.h>

#include "Types.h"
#include "MovingHead.h"
#include "ConfigManager.h"
#include "WebServerManager.h"

// ===== DMX PIN KONFIGURATION =====
const int transmitPin = 17;     
const int enablePin = 21;       
const dmx_port_t dmxOutputPort = DMX_NUM_2; 
const int receivePin = 16;      
const int receiveEnablePin = 15;
const dmx_port_t dmxInputPort = DMX_NUM_1;  

uint8_t dmxUniverse[513];

// ===== GLOBALER STATUS =====
OperatingMode currentMode = MODE_UWB_TRACKING;
unsigned long modeStartTime = 0;
const unsigned long TEST_DURATION = 10000; 
const unsigned long TRACKING_UPDATE_INTERVAL = 200; 
unsigned long lastTrackingCalc = 0;

PositionData currentPosition;
unsigned long lastPositionUpdate = 0;
const unsigned long POSITION_TIMEOUT = 5000;

// ===== DYNAMIC CONFIGURATION =====
std::vector<MovingHeadProfile> fixtureProfiles; // Available profiles
std::vector<MovingHead> movingHeads;           // Active fixtures

// ===== WEB SERVER =====
WebServerManager* webServer = nullptr;

// ===== MANUELLE STEUERUNG =====
enum ManualInputState { 
    IDLE,                 
    WAITING_FOR_FIXTURE,  
    WAITING_FOR_CHANNEL,  
    WAITING_FOR_VALUE     
};
static ManualInputState manualState = IDLE;
static int manualFixtureIdx = -1; 
static int manualRelativeChannel = -1; 

// --- Forward Declarations ---
void changeMode(OperatingMode newMode);
void onPositionDataReceived(const uint8_t* mac, const uint8_t* data, int len);
void sendDMXData();
void createDefaultConfiguration();
void loadOrCreateDefaultConfig();
void initializeWebServer();

// ===== CALLBACKS & HELPERS =====

void onPositionDataReceived(const uint8_t* mac, const uint8_t* data, int len) {
    if (len == sizeof(PositionData)) {
        memcpy(&currentPosition, data, sizeof(PositionData));
        currentPosition.valid = true;
        lastPositionUpdate = millis();
        Serial.printf("UWB Position empfangen: X=%.2fm, Y=%.2fm, Z=%.2fm, RMSE=%.3f\n",
                     currentPosition.x, currentPosition.y, currentPosition.z, currentPosition.rmse);
    }
}

void initializeDMX() {
    Serial.println("Initialisiere DMX...");
    pinMode(receiveEnablePin, OUTPUT);
    digitalWrite(receiveEnablePin, HIGH); 
    
    dmx_config_t config = DMX_CONFIG_DEFAULT;
    dmx_driver_install(dmxOutputPort, &config, NULL, 0);
    dmx_set_pin(dmxOutputPort, transmitPin, DMX_PIN_NO_CHANGE, enablePin);

    dmx_driver_install(dmxInputPort, &config, NULL, 0);
    dmx_set_pin(dmxInputPort, DMX_PIN_NO_CHANGE, receivePin, receiveEnablePin);
    
    memset(dmxUniverse, 0, sizeof(dmxUniverse));
    dmxUniverse[0] = 0;
    Serial.println("DMX initialisiert (Output=Port 2, Input=Port 1)");
}

void initializeESPNOW() {
    WiFi.mode(WIFI_AP_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Fehler bei ESP-NOW Initialisierung!");
        return;
    }
    esp_now_register_recv_cb(onPositionDataReceived);
    Serial.println("ESP-NOW initialisiert - Warte auf Positionsdaten...");
}

void initializeWebServer() {
    // Start WiFi Access Point for Web GUI
    WiFi.mode(WIFI_AP_STA); // Both AP and STA mode for ESP-NOW + Web
    WiFi.softAP("U-Track-DMX", "utrack123"); // Change password as needed
    
    IPAddress IP = WiFi.softAPIP();
    Serial.println("\n=== WiFi Access Point Started ===");
    Serial.print("SSID: U-Track-DMX\n");
    Serial.print("Password: utrack123\n");
    Serial.print("Dashboard URL: http://");
    Serial.print(IP);
    Serial.println("/\n");
    
    webServer = new WebServerManager(fixtureProfiles, movingHeads);
    
    // Set callbacks
    webServer->onConfigChanged = []() {
        Serial.println("🔄 Configuration changed via Web UI - reloading...");
        // Reload is handled by ConfigManager
    };
    
    webServer->onModeChange = [](OperatingMode newMode) {
        changeMode(newMode);
    };
    
    webServer->onEmergencyStop = []() {
        // Emergency stop: blackout all fixtures
        memset(dmxUniverse, 0, sizeof(dmxUniverse));
        sendDMXData();
        changeMode(MODE_MANUAL);
    };
    
    webServer->begin();
}

void loadOrCreateDefaultConfig() {
    Serial.println("\n=== Loading Configuration ===");
    
    if (ConfigManager::loadConfig(fixtureProfiles, movingHeads)) {
        Serial.printf("✓ Loaded %d profiles and %d fixtures from LittleFS\n", 
                     fixtureProfiles.size(), movingHeads.size());
    } else {
        Serial.println("⚠️  No config found - creating default configuration");
        createDefaultConfiguration();
        ConfigManager::saveConfig(fixtureProfiles, movingHeads);
    }
}

void createDefaultConfiguration() {
    // Create default profile: Robin MegaPointe
    MovingHeadProfile megaPointeProfile;
    megaPointeProfile.name = "Robin MegaPointe";
    megaPointeProfile.panCoarseChannel = 1;
    megaPointeProfile.panFineChannel = 2;
    megaPointeProfile.tiltCoarseChannel = 3;
    megaPointeProfile.tiltFineChannel = 4;
    megaPointeProfile.zoomChannel = 32;
    megaPointeProfile.focusChannel = 34;
    megaPointeProfile.zoomPhysicalMinAngle = 1.8f;
    megaPointeProfile.zoomPhysicalMaxAngle = 42.0f;
    megaPointeProfile.panMinDegrees = 0.0f;
    megaPointeProfile.panMaxDegrees = 540.0f;
    megaPointeProfile.tiltMinDegrees = 0.0f;
    megaPointeProfile.tiltMaxDegrees = 265.0f;
    megaPointeProfile.tiltHomeDegrees = 41.5f;
    megaPointeProfile.zoomCalibDist1 = 17.0f;
    megaPointeProfile.zoomCalibAngle1 = 25.0f;
    megaPointeProfile.focusDMX1 = 51;
    megaPointeProfile.zoomCalibDist2 = 6.0f;
    megaPointeProfile.zoomCalibAngle2 = 35.0f;
    megaPointeProfile.focusDMX2 = 45;
    megaPointeProfile.invertTilt = false;
    megaPointeProfile.invertPan = true;
    megaPointeProfile.invertZoom = true;
    megaPointeProfile.invertFocus = true;
    megaPointeProfile.isHanging = false;
    megaPointeProfile.panHomeOffsetDegrees = 180.0f;
    
    fixtureProfiles.push_back(megaPointeProfile);
    
    // Create default fixtures (your existing setup)
    movingHeads.push_back(MovingHead("MH4 (MegaPointe)", 1, Point3D(7.95, 24.84, 0.35), megaPointeProfile));
    movingHeads.push_back(MovingHead("MH5 (MegaPointe)", 40, Point3D(3.3, 24.23, 0.25), megaPointeProfile));
    
    Serial.println("✓ Default configuration created");
}

void initializeMovingHeads() {
    // This function is now replaced by loadOrCreateDefaultConfig()
    // Kept for compatibility but does nothing
    Serial.printf("Active Fixtures: %d\n", movingHeads.size());
}

void changeMode(OperatingMode newMode) {
    if (currentMode == MODE_DMX_PASSTHROUGH) {
        Serial.println("DMX Passthrough (Eingang) deaktiviert.");
    }
    currentMode = newMode;
    modeStartTime = millis();
    if (newMode != MODE_MANUAL) manualState = IDLE;
    
    Serial.printf("\n=== MODUS WECHSEL ===\n"); // Vereinfachte Ausgabe

    if (currentMode == MODE_DMX_PASSTHROUGH) {
        digitalWrite(receiveEnablePin, LOW); 
        memset(dmxUniverse, 0, sizeof(dmxUniverse));
    }
}

void handleDmxPassthrough() {
    dmx_packet_t packet; 
    if (dmx_receive(dmxInputPort, &packet, DMX_TIMEOUT_TICK)) {
        if (!packet.err) {
            dmxUniverse[0] = packet.sc;
            if (packet.size > 0) dmx_read(dmxInputPort, &dmxUniverse[1], packet.size);
        }
    }
}

void sendDMXData() {
    if (currentMode != MODE_MANUAL && currentMode != MODE_DMX_PASSTHROUGH) { 
        for (auto& head : movingHeads) {
            // WICHTIG: Hier übergeben wir jetzt 'currentMode'
            head.writeToDMXUniverse(dmxUniverse, currentMode);
        }
    }
    dmx_write(dmxOutputPort, dmxUniverse, 513); 
    dmx_send(dmxOutputPort);
    dmx_wait_sent(dmxOutputPort, DMX_TIMEOUT_TICK);
}

void updateMovingHeads() {
    if (currentMode == MODE_UWB_TRACKING && currentPosition.valid) {
        if (millis() - lastPositionUpdate > POSITION_TIMEOUT) {
            currentPosition.valid = false;
            Serial.println("Positionsdaten veraltet - pausiere Tracking");
            return;
        }
        
        unsigned long now = millis();
        if (now - lastTrackingCalc < TRACKING_UPDATE_INTERVAL) return;
        lastTrackingCalc = now;
        
        Point3D target(currentPosition.x, currentPosition.y, currentPosition.z);
        for (auto& head : movingHeads) {
            head.updateTarget(target);
        }
    }
}

void updateTestPrograms(){
    unsigned long elapsedTime = millis() - modeStartTime;
    for (auto& head : movingHeads) {
        switch(currentMode) {
            case MODE_PAN_TEST: head.updatePanTest(elapsedTime); break;
            case MODE_TILT_TEST: head.updateTiltTest(elapsedTime); break;
            case MODE_SHUTTER_DIMMER_TEST: head.updateShutterDimmerTest(elapsedTime); break;
            case MODE_COLOR_TEST: head.updateColorTest(elapsedTime); break;
            case MODE_GOBO_TEST: head.updateGoboTest(elapsedTime); break;
            default: break;
        }
    }
    if (elapsedTime > TEST_DURATION) {
        OperatingMode nextMode;
        if (currentMode == MODE_GOBO_TEST) nextMode = MODE_UWB_TRACKING;
        else nextMode = static_cast<OperatingMode>(currentMode + 1);
        changeMode(nextMode);
    }
}

void printStatus() {
    static unsigned long lastPrint = 0;
    if (millis() - lastPrint < 1000) return;
    lastPrint = millis();
    
    Serial.println("\n=== MOVING HEAD STATUS ===");
    for (const auto& head : movingHeads) {
        // Auch hier übergeben wir den Modus
        head.printStatus(currentMode);
    }
    
    if (currentMode == MODE_UWB_TRACKING) {
        if (currentPosition.valid) Serial.printf("Ziel: X=%.2fm, Y=%.2fm, Z=%.2fm\n", currentPosition.x, currentPosition.y, currentPosition.z);
        else Serial.println("Warte auf UWB-Positionsdaten...");
    }
    Serial.println("=========================================\n");
}

void handleSerialCommands() {
    if (Serial.available() == 0) return;
    
    char cmd = Serial.read();
    
    // Mode switching commands (0-7)
    if (cmd >= '0' && cmd <= '7') {
        changeMode((OperatingMode)(cmd - '0'));
        return;
    }
    
    // Manual mode commands
    if (manualState == IDLE) {
        switch(cmd) {
            case 'm':
            case 'M':
                Serial.println("\n=== MANUAL CONTROL MODE ===");
                Serial.printf("Available fixtures (%d):\n", movingHeads.size());
                for(size_t i = 0; i < movingHeads.size(); i++) {
                    Serial.printf("  [%d] %s (DMX %d)\n", i, 
                                movingHeads[i].name.c_str(), 
                                movingHeads[i].dmxAddress);
                }
                Serial.println("\nEnter fixture index:");
                manualState = WAITING_FOR_FIXTURE;
                break;
                
            case 'h':
            case 'H':
            case '?':
                Serial.println("\n=== U-TRACK DMX CONTROLLER - COMMAND HELP ===");
                Serial.println("Operating Modes:");
                Serial.println("  0 = UWB Tracking Mode");
                Serial.println("  1 = Pan Test");
                Serial.println("  2 = Tilt Test");
                Serial.println("  3 = Shutter/Dimmer Test");
                Serial.println("  4 = Color Wheel Test");
                Serial.println("  5 = Gobo Test");
                Serial.println("  6 = Manual Control Mode");
                Serial.println("  7 = DMX Passthrough Mode");
                Serial.println("\nManual Control:");
                Serial.println("  M = Enter manual control");
                Serial.println("  H or ? = Show this help");
                Serial.println("  S = Show status");
                Serial.println("  C = Show configuration");
                Serial.println("\nWeb Interface:");
                Serial.print("  Access dashboard at: http://");
                Serial.print(WiFi.softAPIP());
                Serial.println("/");
                Serial.println("=========================================\n");
                break;
                
            case 's':
            case 'S':
                Serial.println("\n=== SYSTEM STATUS ===");
                Serial.printf("Current Mode: %d\n", currentMode);
                Serial.printf("Active Fixtures: %d\n", movingHeads.size());
                Serial.printf("Available Profiles: %d\n", fixtureProfiles.size());
                Serial.printf("Position Valid: %s\n", currentPosition.valid ? "Yes" : "No");
                if (currentPosition.valid) {
                    Serial.printf("UWB Position: X=%.2f Y=%.2f Z=%.2f RMSE=%.3f\n",
                                currentPosition.x, currentPosition.y, 
                                currentPosition.z, currentPosition.rmse);
                }
                Serial.print("Web Dashboard: http://");
                Serial.println(WiFi.softAPIP());
                Serial.println("=====================\n");
                break;
                
            case 'c':
            case 'C':
                Serial.println("\n=== CONFIGURATION ===");
                Serial.printf("Fixture Profiles (%d):\n", fixtureProfiles.size());
                for(const auto& profile : fixtureProfiles) {
                    Serial.printf("  - %s (Pan:%d-%d Tilt:%d-%d)\n", 
                                profile.name.c_str(),
                                profile.panCoarseChannel, profile.panFineChannel,
                                profile.tiltCoarseChannel, profile.tiltFineChannel);
                }
                Serial.printf("\nActive Fixtures (%d):\n", movingHeads.size());
                for(const auto& fixture : movingHeads) {
                    Serial.printf("  - %s @ DMX %d [%s] Pos:(%.2f,%.2f,%.2f)\n",
                                fixture.name.c_str(),
                                fixture.dmxAddress,
                                fixture.profile.name.c_str(),
                                fixture.position.x, fixture.position.y, fixture.position.z);
                }
                Serial.println("=====================\n");
                break;
        }
    }
    else if (manualState == WAITING_FOR_FIXTURE) {
        if (cmd >= '0' && cmd <= '9') {
            int idx = cmd - '0';
            if (idx >= 0 && idx < (int)movingHeads.size()) {
                manualFixtureIdx = idx;
                Serial.printf("Selected: %s\n", movingHeads[idx].name.c_str());
                Serial.println("Enter channel number (relative to fixture DMX address):");
                manualState = WAITING_FOR_CHANNEL;
            } else {
                Serial.println("Invalid fixture index. Try again:");
            }
        } else if (cmd == 27 || cmd == 'q') { // ESC or 'q' to cancel
            Serial.println("Cancelled.");
            manualState = IDLE;
        }
    }
    else if (manualState == WAITING_FOR_CHANNEL) {
        if (cmd >= '0' && cmd <= '9') {
            manualRelativeChannel = cmd - '0';
            Serial.printf("Channel %d selected. Enter DMX value (0-255):\n", manualRelativeChannel);
            manualState = WAITING_FOR_VALUE;
        } else if (cmd == 27 || cmd == 'q') {
            Serial.println("Cancelled.");
            manualState = IDLE;
            manualFixtureIdx = -1;
        }
    }
    else if (manualState == WAITING_FOR_VALUE) {
        // Simple 3-digit input (0-255)
        static String valueStr = "";
        if (cmd >= '0' && cmd <= '9') {
            valueStr += cmd;
            Serial.print(cmd);
            if (valueStr.length() >= 3) {
                int value = valueStr.toInt();
                if (value >= 0 && value <= 255) {
                    int absoluteChannel = movingHeads[manualFixtureIdx].dmxAddress + manualRelativeChannel;
                    if (absoluteChannel >= 1 && absoluteChannel <= 512) {
                        dmxUniverse[absoluteChannel] = (uint8_t)value;
                        Serial.printf("\n✓ Set DMX channel %d to %d\n", absoluteChannel, value);
                    } else {
                        Serial.println("\n❌ Channel out of range!");
                    }
                } else {
                    Serial.println("\n❌ Value must be 0-255!");
                }
                valueStr = "";
                manualState = IDLE;
                manualFixtureIdx = -1;
                manualRelativeChannel = -1;
            }
        } else if (cmd == '\n' || cmd == '\r') {
            if (valueStr.length() > 0) {
                int value = valueStr.toInt();
                if (value >= 0 && value <= 255) {
                    int absoluteChannel = movingHeads[manualFixtureIdx].dmxAddress + manualRelativeChannel;
                    if (absoluteChannel >= 1 && absoluteChannel <= 512) {
                        dmxUniverse[absoluteChannel] = (uint8_t)value;
                        Serial.printf("\n✓ Set DMX channel %d to %d\n", absoluteChannel, value);
                    } else {
                        Serial.println("\n❌ Channel out of range!");
                    }
                } else {
                    Serial.println("\n❌ Value must be 0-255!");
                }
            }
            valueStr = "";
            manualState = IDLE;
            manualFixtureIdx = -1;
            manualRelativeChannel = -1;
        } else if (cmd == 27 || cmd == 'q') {
            Serial.println("\nCancelled.");
            valueStr = "";
            manualState = IDLE;
            manualFixtureIdx = -1;
            manualRelativeChannel = -1;
        }
    }
}

// ===== SETUP & LOOP =====
void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("\n╔════════════════════════════════════════╗");
    Serial.println("║   U-TRACK DMX TRACKING SYSTEM v2.0     ║");
    Serial.println("║   With Dynamic Web Configuration       ║");
    Serial.println("╚════════════════════════════════════════╝\n");
    
    // Initialize LittleFS for config storage
    if (!ConfigManager::begin()) {
        Serial.println("❌ FATAL: LittleFS failed to mount!");
        while(1) delay(1000);
    }
    
    // Load configuration (or create defaults)
    loadOrCreateDefaultConfig();
    
    // Initialize hardware
    initializeDMX();

    // Initialize ESP-NOW for UWB position data
    initializeESPNOW();

    // Initialize WiFi and Web Server
    initializeWebServer();
    
    pinMode(2, OUTPUT);
    changeMode(MODE_UWB_TRACKING);
    
    Serial.println("\n✓✓✓ System Ready ✓✓✓\n");
}

void loop() {
    digitalWrite(2, HIGH);
    
    // Update web server position data
    if (webServer) {
        webServer->updatePositionData(currentPosition);
        webServer->updateCurrentMode(currentMode);
        webServer->handleClient();
    }
    
    handleSerialCommands();
    
    if (currentMode == MODE_DMX_PASSTHROUGH) {
        handleDmxPassthrough();
    } else if (currentMode == MODE_UWB_TRACKING) {
        updateMovingHeads();
    } else if (currentMode != MODE_MANUAL) {
        updateTestPrograms();
    }
    
    sendDMXData();
    printStatus();
    
    digitalWrite(2, LOW);
    delay(33); 
}