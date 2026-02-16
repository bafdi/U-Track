#include "ConfigManager.h"

const char* ConfigManager::CONFIG_FILE = "/config.json";

bool ConfigManager::begin() {
    if (!LittleFS.begin(true)) {
        Serial.println("❌ LittleFS Mount Failed");
        return false;
    }
    Serial.println("✓ LittleFS Mounted");
    return true;
}

bool ConfigManager::loadConfig(std::vector<MovingHeadProfile>& profiles, std::vector<MovingHead>& fixtures) {
    if (!LittleFS.exists(CONFIG_FILE)) {
        Serial.println("⚠️  config.json not found - using empty configuration");
        return false;
    }
    
    File file = LittleFS.open(CONFIG_FILE, "r");
    if (!file) {
        Serial.println("❌ Failed to open config.json");
        return false;
    }
    
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, file);
    file.close();
    
    if (error) {
        Serial.printf("❌ JSON Parse Error: %s\n", error.c_str());
        return false;
    }
    
    // Clear existing data
    profiles.clear();
    fixtures.clear();
    
    // Load profiles
    JsonArray profilesArray = doc["profiles"].as<JsonArray>();
    for (JsonObject profileObj : profilesArray) {
        MovingHeadProfile profile;
        profileFromJson(profileObj, profile);
        profiles.push_back(profile);
    }
    
    // Load fixtures
    JsonArray fixturesArray = doc["fixtures"].as<JsonArray>();
    for (JsonObject fixtureObj : fixturesArray) {
        MovingHead fixture = fixtureFromJson(fixtureObj, profiles);
        fixtures.push_back(fixture);
    }
    
    Serial.printf("✓ Loaded %d profiles and %d fixtures from config\n", profiles.size(), fixtures.size());
    return true;
}

bool ConfigManager::saveConfig(const std::vector<MovingHeadProfile>& profiles, const std::vector<MovingHead>& fixtures) {
    JsonDocument doc;
    
    doc["version"] = "1.0";
    doc["system"]["name"] = "U-Track DMX Controller";
    
    // Save profiles
    JsonArray profilesArray = doc["profiles"].to<JsonArray>();
    for (const auto& profile : profiles) {
        JsonObject profileObj = profilesArray.add<JsonObject>();
        profileToJson(profile, profileObj);
    }
    
    // Save fixtures
    JsonArray fixturesArray = doc["fixtures"].to<JsonArray>();
    for (const auto& fixture : fixtures) {
        JsonObject fixtureObj = fixturesArray.add<JsonObject>();
        fixtureToJson(fixture, fixtureObj);
    }
    
    File file = LittleFS.open(CONFIG_FILE, "w");
    if (!file) {
        Serial.println("❌ Failed to create config.json");
        return false;
    }
    
    if (serializeJson(doc, file) == 0) {
        Serial.println("❌ Failed to write config.json");
        file.close();
        return false;
    }
    
    file.close();
    Serial.printf("✓ Saved %d profiles and %d fixtures to config\n", profiles.size(), fixtures.size());
    return true;
}

String ConfigManager::getConfigAsJson() {
    if (!LittleFS.exists(CONFIG_FILE)) {
        return "{}";
    }
    
    File file = LittleFS.open(CONFIG_FILE, "r");
    if (!file) return "{}";
    
    String content = file.readString();
    file.close();
    return content;
}

bool ConfigManager::loadConfigFromJson(const String& json, std::vector<MovingHeadProfile>& profiles, std::vector<MovingHead>& fixtures) {
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, json);
    
    if (error) {
        Serial.printf("❌ JSON Parse Error: %s\n", error.c_str());
        return false;
    }
    
    profiles.clear();
    fixtures.clear();
    
    JsonArray profilesArray = doc["profiles"].as<JsonArray>();
    for (JsonObject profileObj : profilesArray) {
        MovingHeadProfile profile;
        profileFromJson(profileObj, profile);
        profiles.push_back(profile);
    }
    
    JsonArray fixturesArray = doc["fixtures"].as<JsonArray>();
    for (JsonObject fixtureObj : fixturesArray) {
        MovingHead fixture = fixtureFromJson(fixtureObj, profiles);
        fixtures.push_back(fixture);
    }
    
    return true;
}

int ConfigManager::findProfileByName(const std::vector<MovingHeadProfile>& profiles, const String& name) {
    for (size_t i = 0; i < profiles.size(); i++) {
        if (profiles[i].name == name) return i;
    }
    return -1;
}

void ConfigManager::profileToJson(const MovingHeadProfile& profile, JsonObject obj) {
    obj["name"] = profile.name;
    
    // Channel mapping
    obj["panCoarse"] = profile.panCoarseChannel;
    obj["panFine"] = profile.panFineChannel;
    obj["tiltCoarse"] = profile.tiltCoarseChannel;
    obj["tiltFine"] = profile.tiltFineChannel;
    obj["dimmer"] = profile.dimmerChannel;
    obj["shutter"] = profile.shutterChannel;
    obj["colorWheel"] = profile.colorWheelChannel;
    obj["goboWheel"] = profile.goboWheelChannel;
    obj["goboRotation"] = profile.goboRotationChannel;
    obj["focus"] = profile.focusChannel;
    obj["zoom"] = profile.zoomChannel;
    obj["control"] = profile.controlChannel;
    
    // Physical limits
    obj["panMin"] = profile.panMinDegrees;
    obj["panMax"] = profile.panMaxDegrees;
    obj["tiltMin"] = profile.tiltMinDegrees;
    obj["tiltMax"] = profile.tiltMaxDegrees;
    obj["tiltHome"] = profile.tiltHomeDegrees;
    obj["panHomeOffset"] = profile.panHomeOffsetDegrees;
    
    // Zoom/Focus calibration
    obj["zoomMinAngle"] = profile.zoomPhysicalMinAngle;
    obj["zoomMaxAngle"] = profile.zoomPhysicalMaxAngle;
    obj["zoomCalibDist1"] = profile.zoomCalibDist1;
    obj["zoomCalibAngle1"] = profile.zoomCalibAngle1;
    obj["focusDMX1"] = profile.focusDMX1;
    obj["zoomCalibDist2"] = profile.zoomCalibDist2;
    obj["zoomCalibAngle2"] = profile.zoomCalibAngle2;
    obj["focusDMX2"] = profile.focusDMX2;
    
    // Inversion flags
    obj["invertPan"] = profile.invertPan;
    obj["invertTilt"] = profile.invertTilt;
    obj["invertZoom"] = profile.invertZoom;
    obj["invertFocus"] = profile.invertFocus;
    obj["isHanging"] = profile.isHanging;
    
    // Dead zones
    obj["panDeadZone"] = profile.panDeadZone;
    obj["tiltDeadZone"] = profile.tiltDeadZone;
}

void ConfigManager::profileFromJson(JsonObject obj, MovingHeadProfile& profile) {
    profile.name = obj["name"].as<String>();
    
    profile.panCoarseChannel = obj["panCoarse"] | 0;
    profile.panFineChannel = obj["panFine"] | 0;
    profile.tiltCoarseChannel = obj["tiltCoarse"] | 0;
    profile.tiltFineChannel = obj["tiltFine"] | 0;
    profile.dimmerChannel = obj["dimmer"] | 0;
    profile.shutterChannel = obj["shutter"] | 0;
    profile.colorWheelChannel = obj["colorWheel"] | 0;
    profile.goboWheelChannel = obj["goboWheel"] | 0;
    profile.goboRotationChannel = obj["goboRotation"] | 0;
    profile.focusChannel = obj["focus"] | 0;
    profile.zoomChannel = obj["zoom"] | 0;
    profile.controlChannel = obj["control"] | 0;
    
    profile.panMinDegrees = obj["panMin"] | 0.0f;
    profile.panMaxDegrees = obj["panMax"] | 540.0f;
    profile.tiltMinDegrees = obj["tiltMin"] | 0.0f;
    profile.tiltMaxDegrees = obj["tiltMax"] | 270.0f;
    profile.tiltHomeDegrees = obj["tiltHome"] | 135.0f;
    profile.panHomeOffsetDegrees = obj["panHomeOffset"] | 0.0f;
    
    profile.zoomPhysicalMinAngle = obj["zoomMinAngle"] | 0.0f;
    profile.zoomPhysicalMaxAngle = obj["zoomMaxAngle"] | 50.0f;
    profile.zoomCalibDist1 = obj["zoomCalibDist1"] | 5.0f;
    profile.zoomCalibAngle1 = obj["zoomCalibAngle1"] | 25.0f;
    profile.focusDMX1 = obj["focusDMX1"] | 127;
    profile.zoomCalibDist2 = obj["zoomCalibDist2"] | 20.0f;
    profile.zoomCalibAngle2 = obj["zoomCalibAngle2"] | 5.0f;
    profile.focusDMX2 = obj["focusDMX2"] | 10;
    
    profile.invertPan = obj["invertPan"] | false;
    profile.invertTilt = obj["invertTilt"] | false;
    profile.invertZoom = obj["invertZoom"] | false;
    profile.invertFocus = obj["invertFocus"] | false;
    profile.isHanging = obj["isHanging"] | true;
    
    profile.panDeadZone = obj["panDeadZone"] | 2.0f;
    profile.tiltDeadZone = obj["tiltDeadZone"] | 2.0f;
}

void ConfigManager::fixtureToJson(const MovingHead& fixture, JsonObject obj) {
    obj["name"] = fixture.name;
    obj["dmxAddress"] = fixture.dmxAddress;
    obj["profileName"] = fixture.profile.name;
    
    JsonObject pos = obj["position"].to<JsonObject>();
    pos["x"] = fixture.position.x;
    pos["y"] = fixture.position.y;
    pos["z"] = fixture.position.z;
}

MovingHead ConfigManager::fixtureFromJson(JsonObject obj, const std::vector<MovingHeadProfile>& profiles) {
    String name = obj["name"].as<String>();
    uint16_t dmxAddress = obj["dmxAddress"] | 1;
    String profileName = obj["profileName"].as<String>();
    
    Point3D position;
    if (obj["position"].is<JsonObject>()) {
        JsonObject pos = obj["position"];
        position.x = pos["x"] | 0.0f;
        position.y = pos["y"] | 0.0f;
        position.z = pos["z"] | 0.0f;
    }
    
    // Find matching profile
    int profileIdx = findProfileByName(profiles, profileName);
    MovingHeadProfile profile;
    if (profileIdx >= 0) {
        profile = profiles[profileIdx];
    } else {
        Serial.printf("⚠️  Profile '%s' not found for fixture '%s'\n", profileName.c_str(), name.c_str());
        profile.name = profileName; // Use minimal profile
    }
    
    return MovingHead(name, dmxAddress, position, profile);
}
