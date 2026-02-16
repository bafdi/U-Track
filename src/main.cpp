#include <Arduino.h>
#include <vector>
#include <cstring>
#include <esp_now.h>
#include <cmath>
#include <WiFi.h>
#include <esp_dmx.h>

#include "Types.h"
#include "MovingHead.h"

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

std::vector<MovingHead> movingHeads;

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
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Fehler bei ESP-NOW Initialisierung!");
        return;
    }
    esp_now_register_recv_cb(onPositionDataReceived);
    Serial.println("ESP-NOW initialisiert - Warte auf Positionsdaten...");
}

void initializeMovingHeads() {
    Serial.println("Initialisiere Moving Head Fixtures...");

    // PROFIL 4: Robin MegaPointe
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

    // Fixture hinzufügen
    movingHeads.push_back(MovingHead("MH4 (MegaPointe)", 1, Point3D(7.95, 24.84, 0.35), megaPointeProfile));
    movingHeads.push_back(MovingHead("MH5 (MegaPointe)", 40, Point3D(3.3, 24.23, 0.25), megaPointeProfile));

    Serial.printf("\nInitialisiert: %d Moving Heads\n\n", movingHeads.size());
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
    // ... (Hier der restliche Serial-Code, 1:1 übernehmen aus deiner alten Datei, ist sehr lang) ...
    // HINWEIS: Kopiere hier die komplette Funktion 'handleSerialCommands' aus deinem originalen Code rein.
    // Ich habe sie hier gekürzt, um die Übersicht zu wahren.
    // Der wichtigste Teil ist, dass 'handleSerialCommands' Zugriff auf 'movingHeads' und 'currentMode' hat, was hier gegeben ist.
    
    // Quick Hack für den Beispielcode: Einfaches Umschalten zum Testen
    char cmd = Serial.read();
    if(cmd == '0') changeMode(MODE_UWB_TRACKING);
    if(cmd == '1') changeMode(MODE_PAN_TEST);
}

// ===== SETUP & LOOP =====
void setup() {
    Serial.begin(115200);
    delay(1000);
    WiFi.mode(WIFI_STA);
    
    Serial.println("\n=== UWB-DMX TRACKING SYSTEM ===");
    initializeDMX();
    initializeMovingHeads();
    initializeESPNOW();
    
    pinMode(2, OUTPUT);
    changeMode(MODE_PAN_TEST);
}

void loop() {
    digitalWrite(2, HIGH);
    
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