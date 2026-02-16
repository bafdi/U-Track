#include "WebServerManager.h"
#include "ConfigManager.h"
#include "WebContent.h"
#include <ArduinoJson.h>

WebServerManager::WebServerManager(std::vector<MovingHeadProfile>& profiles, std::vector<MovingHead>& fixtures)
    : server(80), profiles(profiles), fixtures(fixtures), currentMode(MODE_UWB_TRACKING) {
    lastPosition.valid = false;
    lastPosition.x = lastPosition.y = lastPosition.z = lastPosition.rmse = 0.0f;
}

void WebServerManager::begin() {
    setupRoutes();
    server.begin();
    Serial.println("✓ Web Server started on port 80");
    Serial.println("Access dashboard at: http://<ESP32_IP>/");
}

void WebServerManager::handleClient() {
    // AsyncWebServer handles requests automatically
}

void WebServerManager::updatePositionData(const PositionData& pos) {
    lastPosition = pos;
}

void WebServerManager::updateCurrentMode(OperatingMode mode) {
    currentMode = mode;
}

void WebServerManager::setupRoutes() {
    // Serve main dashboard
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", HTML_DASHBOARD);
    });
    
    // API: Get full configuration
    server.on("/api/config", HTTP_GET, [this](AsyncWebServerRequest *request){
        handleGetConfig(request);
    });
    
    // API: Save configuration
    server.on("/api/config/save", HTTP_POST, 
        [](AsyncWebServerRequest *request){
            request->send(200, "text/plain", "OK");
        },
        NULL,
        [this](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
            handleSaveConfig(request, data, len);
        }
    );
    
    // API: Get live status
    server.on("/api/status", HTTP_GET, [this](AsyncWebServerRequest *request){
        handleGetStatus(request);
    });
    
    // API: Set operating mode
    server.on("/api/mode", HTTP_GET, [this](AsyncWebServerRequest *request){
        handleSetMode(request);
    });
    
    // API: Emergency stop
    server.on("/api/emergency", HTTP_GET, [this](AsyncWebServerRequest *request){
        handleEmergencyStop(request);
    });
    
    // API: Get profiles only
    server.on("/api/profiles", HTTP_GET, [this](AsyncWebServerRequest *request){
        handleGetProfiles(request);
    });
    
    // API: Get fixtures only
    server.on("/api/fixtures", HTTP_GET, [this](AsyncWebServerRequest *request){
        handleGetFixtures(request);
    });
    
    // API: Set DMX channel value (for manual control)
    server.on("/api/dmx/set", HTTP_GET, [this](AsyncWebServerRequest *request){
        handleSetDMXChannel(request);
    });
    
    // API: WiFi configuration
    server.on("/api/wifi/config", HTTP_POST, 
        [](AsyncWebServerRequest *request){
            request->send(200, "text/plain", "OK");
        },
        NULL,
        [this](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
            handleWiFiConfig(request, data, len);
        }
    );
    
    // 404 handler
    server.onNotFound([](AsyncWebServerRequest *request){
        request->send(404, "text/plain", "Not Found");
    });
}

void WebServerManager::handleGetConfig(AsyncWebServerRequest *request) {
    JsonDocument doc;
    
    doc["version"] = "1.0";
    
    // Add profiles
    JsonArray profilesArray = doc["profiles"].to<JsonArray>();
    for (const auto& profile : profiles) {
        JsonObject profileObj = profilesArray.add<JsonObject>();
        ConfigManager::profileToJson(profile, profileObj);
    }
    
    // Add fixtures
    JsonArray fixturesArray = doc["fixtures"].to<JsonArray>();
    for (const auto& fixture : fixtures) {
        JsonObject fixtureObj = fixturesArray.add<JsonObject>();
        ConfigManager::fixtureToJson(fixture, fixtureObj);
    }
    
    String response;
    serializeJson(doc, response);
    request->send(200, "application/json", response);
}

void WebServerManager::handleSaveConfig(AsyncWebServerRequest *request, uint8_t *data, size_t len) {
    String json;
    for (size_t i = 0; i < len; i++) {
        json += (char)data[i];
    }
    
    // Parse and reload configuration
    if (ConfigManager::loadConfigFromJson(json, profiles, fixtures)) {
        // Save to filesystem
        if (ConfigManager::saveConfig(profiles, fixtures)) {
            Serial.println("✓ Configuration saved via Web UI");
            if (onConfigChanged) onConfigChanged();
        }
    }
}

void WebServerManager::handleGetStatus(AsyncWebServerRequest *request) {
    JsonDocument doc;
    
    const char* modeNames[] = {
        "UWB-TRACKING", "PAN-TEST", "TILT-TEST", "SHUTTER-DIMMER", 
        "COLOR-TEST", "GOBO-TEST", "MANUAL", "DMX-PASSTHROUGH"
    };
    
    doc["mode"] = modeNames[currentMode];
    doc["position"]["x"] = lastPosition.x;
    doc["position"]["y"] = lastPosition.y;
    doc["position"]["z"] = lastPosition.z;
    doc["position"]["rmse"] = lastPosition.rmse;
    doc["position"]["valid"] = lastPosition.valid;
    doc["fixtureCount"] = fixtures.size();
    doc["uptime"] = millis() / 1000;
    
    String response;
    serializeJson(doc, response);
    request->send(200, "application/json", response);
}

void WebServerManager::handleSetMode(AsyncWebServerRequest *request) {
    if (request->hasParam("mode")) {
        int mode = request->getParam("mode")->value().toInt();
        if (mode >= 0 && mode <= 7) {
            if (onModeChange) {
                onModeChange((OperatingMode)mode);
            }
            request->send(200, "text/plain", "Mode changed");
            return;
        }
    }
    request->send(400, "text/plain", "Invalid mode");
}

void WebServerManager::handleEmergencyStop(AsyncWebServerRequest *request) {
    Serial.println("🛑 EMERGENCY STOP triggered via Web UI");
    if (onEmergencyStop) {
        onEmergencyStop();
    }
    request->send(200, "text/plain", "Emergency stop activated");
}

void WebServerManager::handleGetProfiles(AsyncWebServerRequest *request) {
    JsonDocument doc;
    JsonArray profilesArray = doc.to<JsonArray>();
    
    for (const auto& profile : profiles) {
        JsonObject profileObj = profilesArray.add<JsonObject>();
        ConfigManager::profileToJson(profile, profileObj);
    }
    
    String response;
    serializeJson(doc, response);
    request->send(200, "application/json", response);
}

void WebServerManager::handleGetFixtures(AsyncWebServerRequest *request) {
    JsonDocument doc;
    JsonArray fixturesArray = doc.to<JsonArray>();
    
    for (const auto& fixture : fixtures) {
        JsonObject fixtureObj = fixturesArray.add<JsonObject>();
        ConfigManager::fixtureToJson(fixture, fixtureObj);
    }
    
    String response;
    serializeJson(doc, response);
    request->send(200, "application/json", response);
}

void WebServerManager::handleAddFixture(AsyncWebServerRequest *request, uint8_t *data, size_t len) {
    // Implemented in handleSaveConfig (full config save)
}

void WebServerManager::handleDeleteFixture(AsyncWebServerRequest *request) {
    // Implemented in handleSaveConfig (full config save)
}

void WebServerManager::handleAddProfile(AsyncWebServerRequest *request, uint8_t *data, size_t len) {
    // Implemented in handleSaveConfig (full config save)
}

void WebServerManager::handleDeleteProfile(AsyncWebServerRequest *request) {
    // Implemented in handleSaveConfig (full config save)
}

void WebServerManager::handleSetDMXChannel(AsyncWebServerRequest *request) {
    if (!request->hasParam("ch") || !request->hasParam("val")) {
        request->send(400, "text/plain", "Missing parameters");
        return;
    }
    
    int channel = request->getParam("ch")->value().toInt();
    int value = request->getParam("val")->value().toInt();
    
    // Validate parameters
    if (channel < 1 || channel > 512 || value < 0 || value > 255) {
        request->send(400, "text/plain", "Invalid channel or value");
        return;
    }
    
    // Call the callback to set DMX channel in main.cpp
    if (onDMXChannelSet) {
        onDMXChannelSet(channel, value);
    }
    
    request->send(200, "text/plain", "OK");
}

void WebServerManager::handleWiFiConfig(AsyncWebServerRequest *request, uint8_t *data, size_t len) {
    // Parse JSON
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, data, len);
    
    if (error) {
        request->send(400, "text/plain", "Invalid JSON");
        return;
    }
    
    const char* ssid = doc["ssid"];
    const char* password = doc["password"];
    
    if (!ssid || strlen(ssid) == 0) {
        request->send(400, "text/plain", "SSID required");
        return;
    }
    
    // Call callback to save WiFi config
    if (onWiFiConfig) {
        onWiFiConfig(ssid, password ? password : "");
    }
    
    request->send(200, "text/plain", "WiFi config saved");
}
