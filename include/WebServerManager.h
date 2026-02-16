#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <vector>
#include "Types.h"
#include "MovingHead.h"

/*
 * WebServerManager - Handles the Web GUI and REST API
 * Provides endpoints for configuration, live monitoring, and control
 */

class WebServerManager {
public:
    WebServerManager(std::vector<MovingHeadProfile>& profiles, std::vector<MovingHead>& fixtures);
    
    void begin();
    void handleClient(); // Call in loop
    
    // Callbacks - set these in main.cpp
    void (*onConfigChanged)() = nullptr;
    void (*onModeChange)(OperatingMode newMode) = nullptr;
    void (*onEmergencyStop)() = nullptr;
    
    // Update live data
    void updatePositionData(const PositionData& pos);
    void updateCurrentMode(OperatingMode mode);
    
private:
    AsyncWebServer server;
    std::vector<MovingHeadProfile>& profiles;
    std::vector<MovingHead>& fixtures;
    
    PositionData lastPosition;
    OperatingMode currentMode;
    
    // Route handlers
    void setupRoutes();
    void handleGetConfig(AsyncWebServerRequest *request);
    void handleSaveConfig(AsyncWebServerRequest *request, uint8_t *data, size_t len);
    void handleGetStatus(AsyncWebServerRequest *request);
    void handleSetMode(AsyncWebServerRequest *request);
    void handleEmergencyStop(AsyncWebServerRequest *request);
    void handleGetProfiles(AsyncWebServerRequest *request);
    void handleGetFixtures(AsyncWebServerRequest *request);
    void handleAddFixture(AsyncWebServerRequest *request, uint8_t *data, size_t len);
    void handleDeleteFixture(AsyncWebServerRequest *request);
    void handleAddProfile(AsyncWebServerRequest *request, uint8_t *data, size_t len);
    void handleDeleteProfile(AsyncWebServerRequest *request);
    
    // HTML content (stored in PROGMEM)
    static const char* HTML_DASHBOARD;
};
