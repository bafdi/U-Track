#pragma once
#include <Arduino.h>

// ===== KONSTANTEN =====
const float MAX_PAN_STEP = 1.25f; 
const float MAX_TILT_STEP = 0.25f;

// ===== BETRIEBSMODI =====
enum OperatingMode {
    MODE_UWB_TRACKING,          // UWB Position verfolgen
    MODE_PAN_TEST,              // Pan Testprogramm
    MODE_TILT_TEST,             // Tilt Testprogramm  
    MODE_SHUTTER_DIMMER_TEST,   // Shutter + Dimmer Test
    MODE_COLOR_TEST,            // Farbrad Test
    MODE_GOBO_TEST,             // Gobo + Rotation Test
    MODE_MANUAL,                // Manuelle Steuerung
    MODE_DMX_PASSTHROUGH        // DMX Signal durchschleifen
};

// ===== MATHEMATISCHE HELFER =====
struct Point3D {
    float x, y, z;
    Point3D(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
    
    float distanceTo(const Point3D& other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        float dz = z - other.z;
        return sqrt(dx*dx + dy*dy + dz*dz);
    }
};

// ===== UWB POSITIONSDATEN =====
struct PositionData {
    float x;            
    float y;
    float z;     
    float rmse;
    bool valid = false;
};

// ===== MOVING HEAD PROFIL =====
struct MovingHeadProfile {
    String name;
    
    uint8_t panCoarseChannel = 0;       
    uint8_t panFineChannel = 0;         
    uint8_t tiltCoarseChannel = 0;      
    uint8_t tiltFineChannel = 0;        
    uint8_t dimmerChannel = 0;          
    uint8_t shutterChannel = 0;         
    uint8_t colorWheelChannel = 0;      
    uint8_t goboWheelChannel = 0;       
    uint8_t goboRotationChannel = 0;    
    uint8_t focusChannel = 0;           
    uint8_t controlChannel = 0;         
    uint8_t zoomChannel = 0;
    
    float zoomPhysicalMinAngle = 0.0f; 
    float zoomPhysicalMaxAngle = 0.0f; 
    float panMinDegrees = 0.0f;
    float panMaxDegrees = 0.0f;
    float tiltMinDegrees = 0.0f;
    float tiltMaxDegrees = 0.0f;
    
    bool invertPan = false;
    bool invertTilt = false;
    bool invertZoom = false;
    bool invertFocus = false;
    bool isHanging = true; 
    
    float panDeadZone = 2.0f;
    float tiltDeadZone = 2.0f;
    float tiltHomeDegrees = 135.0f; 
    float panHomeOffsetDegrees = 0.0f;

    float zoomCalibDist1 = 5.0f;    
    float zoomCalibAngle1 = 25.0f; 
    uint8_t focusDMX1 = 127; 
    
    float zoomCalibDist2 = 20.0f;
    float zoomCalibAngle2 = 5.0f;
    uint8_t focusDMX2 = 10;
};