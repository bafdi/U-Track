#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include <LittleFS.h>
#include <vector>
#include "Types.h"
#include "MovingHead.h"

/* 
 * ConfigManager - Handles persistent storage of fixture profiles and active fixtures
 * Uses LittleFS to store config.json with all system configuration
 */

class ConfigManager {
public:
    static bool begin();
    static bool loadConfig(std::vector<MovingHeadProfile>& profiles, std::vector<MovingHead>& fixtures);
    static bool saveConfig(const std::vector<MovingHeadProfile>& profiles, const std::vector<MovingHead>& fixtures);
    
    // Individual operations
    static String getConfigAsJson();
    static bool loadConfigFromJson(const String& json, std::vector<MovingHeadProfile>& profiles, std::vector<MovingHead>& fixtures);
    
    // Helper functions
    static int findProfileByName(const std::vector<MovingHeadProfile>& profiles, const String& name);
    
    // JSON conversion helpers (public for WebServerManager)
    static void profileToJson(const MovingHeadProfile& profile, JsonObject obj);
    static void profileFromJson(JsonObject obj, MovingHeadProfile& profile);
    static void fixtureToJson(const MovingHead& fixture, JsonObject obj);
    static MovingHead fixtureFromJson(JsonObject obj, const std::vector<MovingHeadProfile>& profiles);
    
private:
    static const char* CONFIG_FILE;
    static const size_t JSON_BUFFER_SIZE = 16384; // 16KB for large configs
};
