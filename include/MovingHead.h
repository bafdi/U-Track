#pragma once
#include <Arduino.h>
#include "Types.h"

class MovingHead {
public:
    String name;
    uint16_t dmxAddress;
    Point3D position;
    MovingHeadProfile profile;
    
    float currentPan = 0.0f;
    float currentTilt = 0.0f;
    uint8_t currentZoomDMX = 0;
    uint8_t currentFocusDMX = 127;
    
    float testPanAngle = 0.0f;
    float testTiltAngle = 0.0f;
    uint8_t testDimmer = 0;
    uint8_t testColor = 0;
    uint8_t testGobo = 0;
    int8_t testGoboRotation = 0;
    uint8_t testShutter = 20;
    uint8_t testZoom = 127;
    
    MovingHead(const String& name, uint16_t address, const Point3D& pos, const MovingHeadProfile& prof);
    
    // Berechnungen
    float calculatePanAngle(const Point3D& target) const;
    float calculateTiltAngle(const Point3D& target) const;
    void calculateZoom(const Point3D& target);
    void calculateFocus(float distance);
    
    // DMX Helper
    void anglesToDMX(float pan, float tilt, uint8_t& panCoarse, uint8_t& panFine, 
                     uint8_t& tiltCoarse, uint8_t& tiltFine) const;
    
    // Hauptfunktion zum Schreiben in den Buffer
    // ACHTUNG: 'currentMode' wird jetzt übergeben!
    void writeToDMXUniverse(uint8_t universe[], OperatingMode mode) const;
    
    void updateTarget(const Point3D& target);
    
    // Testprogramme
    void updatePanTest(unsigned long elapsedTime);
    void updateTiltTest(unsigned long elapsedTime);
    void updateShutterDimmerTest(unsigned long elapsedTime);
    void updateColorTest(unsigned long elapsedTime);
    void updateGoboTest(unsigned long elapsedTime);
    void updateZoomTest(unsigned long elapsedTime);
    
    // Debug
    void printStatus(OperatingMode mode) const;
};