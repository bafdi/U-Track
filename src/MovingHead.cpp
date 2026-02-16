#include "MovingHead.h"
#include <cmath>

MovingHead::MovingHead(const String& name, uint16_t address, const Point3D& pos, const MovingHeadProfile& prof)
    : name(name), dmxAddress(address), position(pos), profile(prof) {}

float MovingHead::calculatePanAngle(const Point3D& target) const {
    float dx = target.x - position.x;
    float dy = target.y - position.y;
    
    if (fabs(dx) < 0.001f && fabs(dy) < 0.001f) {
        return -999.0f; 
    }
    
    float angle = atan2f(dy, dx) * 180.0f / M_PI;
    if (angle < 0) angle += 360.0f;
    
    angle += profile.panHomeOffsetDegrees;
    
    while (angle >= 360.0f) angle -= 360.0f;
    while (angle < 0.0f) angle += 360.0f;
    
    return angle;
}

float MovingHead::calculateTiltAngle(const Point3D& target) const {
    float dx = target.x - position.x;
    float dy = target.y - position.y;
    float dz = target.z - position.z; 
    
    float horizontalDistance = sqrt(dx*dx + dy*dy);
    
    if (fabs(horizontalDistance) < 0.001f && fabs(dz) < 0.001f) {
        return currentTilt;
    }
    
    float physicalAngle = atan2f(dz, horizontalDistance) * 180.0f / M_PI;
    float fixtureAngle;
    
    if (profile.isHanging) {
        fixtureAngle = profile.tiltHomeDegrees - physicalAngle;
    } else {
        fixtureAngle = profile.tiltHomeDegrees + physicalAngle;
    }
    
    return constrain(fixtureAngle, profile.tiltMinDegrees, profile.tiltMaxDegrees);
}

void MovingHead::calculateZoom(const Point3D& target) {
    if (profile.zoomChannel == 0) return;

    float distance = position.distanceTo(target);
    float distRange = profile.zoomCalibDist2 - profile.zoomCalibDist1;
    float angleRange = profile.zoomCalibAngle2 - profile.zoomCalibAngle1;
    
    if (fabs(distRange) < 0.01f) return; 

    float targetAngle = profile.zoomCalibAngle1 + (distance - profile.zoomCalibDist1) * (angleRange / distRange);
    targetAngle = constrain(targetAngle, profile.zoomPhysicalMinAngle, profile.zoomPhysicalMaxAngle);

    float physicalRange = profile.zoomPhysicalMaxAngle - profile.zoomPhysicalMinAngle;
    if (fabs(physicalRange) < 0.01f) {
        currentZoomDMX = 0;
        return;
    }

    float zoomFactor = (targetAngle - profile.zoomPhysicalMinAngle) / physicalRange;
    zoomFactor = constrain(zoomFactor, 0.0f, 1.0f);

    if (profile.invertZoom) {
        zoomFactor = 1.0f - zoomFactor;
    }

    currentZoomDMX = static_cast<uint8_t>(zoomFactor * 255);
}

void MovingHead::calculateFocus(float distance) {
    if (profile.focusChannel == 0) return;
    
    float distRange = profile.zoomCalibDist2 - profile.zoomCalibDist1;
    float dmxRange = (float)profile.focusDMX2 - (float)profile.focusDMX1;

    if (fabs(distRange) < 0.01f) {
        currentFocusDMX = profile.focusDMX1;
        return;
    }

    float calculatedDMX = (float)profile.focusDMX1 + (distance - profile.zoomCalibDist1) * (dmxRange / distRange);
    int val = (int)round(calculatedDMX);
    val = constrain(val, 0, 255);

    if (profile.invertFocus) {
        val = 255 - val;
    }

    currentFocusDMX = (uint8_t)val;
}

void MovingHead::anglesToDMX(float pan, float tilt, uint8_t& panCoarse, uint8_t& panFine, 
                 uint8_t& tiltCoarse, uint8_t& tiltFine) const {
    
    float panRange = profile.panMaxDegrees - profile.panMinDegrees;
    float panNormalized = (pan - profile.panMinDegrees) / panRange;
    panNormalized = constrain(panNormalized, 0.0f, 1.0f);
    
    if (profile.invertPan) panNormalized = 1.0f - panNormalized;
    
    uint16_t panValue = static_cast<uint16_t>(panNormalized * 65535.0f);
    panCoarse = (panValue >> 8) & 0xFF;
    panFine = panValue & 0xFF;
    
    float tiltRange = profile.tiltMaxDegrees - profile.tiltMinDegrees;
    float tiltNormalized = (tilt - profile.tiltMinDegrees) / tiltRange;
    tiltNormalized = constrain(tiltNormalized, 0.0f, 1.0f);
    
    if (profile.invertTilt) tiltNormalized = 1.0f - tiltNormalized;
    
    uint16_t tiltValue = static_cast<uint16_t>(tiltNormalized * 65535.0f);
    tiltCoarse = (tiltValue >> 8) & 0xFF;
    tiltFine = tiltValue & 0xFF;
}

void MovingHead::writeToDMXUniverse(uint8_t universe[], OperatingMode mode) const {
    uint8_t panCoarse, panFine, tiltCoarse, tiltFine;
    
    if (mode == MODE_UWB_TRACKING) {
        anglesToDMX(currentPan, currentTilt, panCoarse, panFine, tiltCoarse, tiltFine);
    } else {
        anglesToDMX(testPanAngle, testTiltAngle, panCoarse, panFine, tiltCoarse, tiltFine);
    }
    
    if (profile.panCoarseChannel > 0) universe[dmxAddress + profile.panCoarseChannel - 1] = panCoarse;
    if (profile.panFineChannel > 0) universe[dmxAddress + profile.panFineChannel - 1] = panFine;
    
    if (profile.tiltCoarseChannel > 0) universe[dmxAddress + profile.tiltCoarseChannel - 1] = tiltCoarse;
    if (profile.tiltFineChannel > 0) universe[dmxAddress + profile.tiltFineChannel - 1] = tiltFine;
    
    if (profile.shutterChannel > 0) universe[dmxAddress + profile.shutterChannel - 1] = testShutter;
    
    if (profile.dimmerChannel > 0) {
        if (mode == MODE_SHUTTER_DIMMER_TEST) {
            universe[dmxAddress + profile.dimmerChannel - 1] = testDimmer;
        } else {
            universe[dmxAddress + profile.dimmerChannel - 1] = 255; 
        }
    }
    
    if (profile.colorWheelChannel > 0) {
        universe[dmxAddress + profile.colorWheelChannel - 1] = (mode == MODE_COLOR_TEST) ? testColor : 0;
    }
    
    if (profile.goboWheelChannel > 0) {
        universe[dmxAddress + profile.goboWheelChannel - 1] = (mode == MODE_GOBO_TEST) ? testGobo : 0;
    }
    
    if (profile.goboRotationChannel > 0) {
        universe[dmxAddress + profile.goboRotationChannel - 1] = (mode == MODE_GOBO_TEST) ? testGoboRotation : 0;
    }
    
    if (profile.focusChannel > 0) {
        if (mode == MODE_UWB_TRACKING) {
            universe[dmxAddress + profile.focusChannel - 1] = currentFocusDMX;
        } else {
            universe[dmxAddress + profile.focusChannel - 1] = profile.focusDMX2; 
        }
    }

    if (profile.zoomChannel > 0) {
        if (mode == MODE_UWB_TRACKING) {
            universe[dmxAddress + profile.zoomChannel - 1] = currentZoomDMX;
        } else {
            universe[dmxAddress + profile.zoomChannel - 1] = testZoom; 
        }
    }
}

void MovingHead::updateTarget(const Point3D& target) {
    float goalPanAngle_0_360 = calculatePanAngle(target);
    float goalTilt = calculateTiltAngle(target); 
    float distance = position.distanceTo(target);
    
    if (goalPanAngle_0_360 != -999.0f) {
        float currentPan_0_360 = fmod(currentPan, 360.0f);
        if (currentPan_0_360 < 0) currentPan_0_360 += 360.0f;
        
        float deltaPan = goalPanAngle_0_360 - currentPan_0_360;
        
        if (deltaPan > 180.0f) deltaPan -= 360.0f;
        if (deltaPan < -180.0f) deltaPan += 360.0f;
        
        if (deltaPan > MAX_PAN_STEP) deltaPan = MAX_PAN_STEP;
        else if (deltaPan < -MAX_PAN_STEP) deltaPan = -MAX_PAN_STEP;
        
        float nextPan = currentPan + deltaPan;
        bool limitingActivePan = (fabs(deltaPan) >= MAX_PAN_STEP);
        
        if (limitingActivePan || fabs(deltaPan) > profile.panDeadZone) {
            currentPan = constrain(nextPan, profile.panMinDegrees, profile.panMaxDegrees);
        }
    }
    
    float deltaTilt = goalTilt - currentTilt;
    if (deltaTilt > MAX_TILT_STEP) deltaTilt = MAX_TILT_STEP;
    else if (deltaTilt < -MAX_TILT_STEP) deltaTilt = -MAX_TILT_STEP;
    
    float nextTilt = currentTilt + deltaTilt;
    bool limitingActiveTilt = (fabs(deltaTilt) >= MAX_TILT_STEP);

    if (limitingActiveTilt || fabs(deltaTilt) > profile.tiltDeadZone) {
        currentTilt = nextTilt;
    }

    calculateZoom(distance);
    calculateFocus(distance);
}

void MovingHead::updatePanTest(unsigned long elapsedTime) {
    testShutter = 20;
    float panRange = profile.panMaxDegrees - profile.panMinDegrees;
    float progress = fmod(elapsedTime / 10000.0f, 1.0f); 
    if (progress < 0.5f) {
        testPanAngle = profile.panMinDegrees + (progress * 2.0f * panRange);
    } else {  
        testPanAngle = profile.panMaxDegrees - ((progress - 0.5f) * 2.0f * panRange);
    }
    testTiltAngle = profile.tiltHomeDegrees;
}

void MovingHead::updateTiltTest(unsigned long elapsedTime) {
    testShutter = 20;
    float tiltRange = profile.tiltMaxDegrees - profile.tiltMinDegrees;
    float progress = fmod(elapsedTime / 10000.0f, 1.0f);
    if (progress < 0.5f) {
        testTiltAngle = profile.tiltMinDegrees + (progress * 2.0f * tiltRange);
    } else {
        testTiltAngle = profile.tiltMaxDegrees - ((progress - 0.5f) * 2.0f * tiltRange);
    }
    testPanAngle = profile.panMinDegrees + (profile.panMaxDegrees - profile.panMinDegrees) / 2.0f; 
}

void MovingHead::updateShutterDimmerTest(unsigned long elapsedTime) {
    testShutter = 20;
    float progress = fmod(elapsedTime / 10000.0f, 1.0f);
    if (progress < 0.5f) {
        testDimmer = static_cast<uint8_t>(progress * 2.0f * 255);
    } else {
        testDimmer = static_cast<uint8_t>((1.0f - (progress - 0.5f) * 2.0f) * 255);
    }
    testPanAngle = profile.panMinDegrees + (profile.panMaxDegrees - profile.panMinDegrees) / 2.0f; 
    testTiltAngle = profile.tiltHomeDegrees; 
}

void MovingHead::updateColorTest(unsigned long elapsedTime) {
    testShutter = 20;
    float progress = fmod(elapsedTime / 10000.0f, 1.0f);
    testColor = static_cast<uint8_t>(progress * 255);
    testPanAngle = profile.panMinDegrees + (profile.panMaxDegrees - profile.panMinDegrees) / 2.0f; 
    testTiltAngle = profile.tiltHomeDegrees; 
}

void MovingHead::updateGoboTest(unsigned long elapsedTime) {
    testShutter = 20;
    float progress = fmod(elapsedTime / 10000.0f, 1.0f);
    testGobo = static_cast<uint8_t>(progress * 16) * 16;
    
    float rotationProgress = fmod(elapsedTime / 5000.0f, 1.0f);
    if (rotationProgress < 0.5f) {
        testGoboRotation = static_cast<uint8_t>(rotationProgress * 2.0f * 255);
    } else { 
        testGoboRotation = 255 - static_cast<uint8_t>((rotationProgress - 0.5f) * 2.0f * 255);
    }
    testPanAngle = profile.panMinDegrees + (profile.panMaxDegrees - profile.panMinDegrees) / 2.0f; 
    testTiltAngle = profile.tiltHomeDegrees; 
}

void MovingHead::updateZoomTest(unsigned long elapsedTime) {
    testShutter = 20;
    float progress = fmod(elapsedTime / 5000.0f, 1.0f);
    if (progress < 0.5f) {
        testZoom = static_cast<uint8_t>(progress * 2.0f * 255);
    } else {
        testZoom = static_cast<uint8_t>((1.0f - (progress - 0.5f) * 2.0f) * 255);
    }
    testPanAngle = profile.panMinDegrees + (profile.panMaxDegrees - profile.panMinDegrees) / 2.0f;
    testTiltAngle = profile.tiltHomeDegrees;
}

void MovingHead::printStatus(OperatingMode mode) const {
    const char* modeNames[] = {
        "UWB-TRACKING", "PAN-TEST", "TILT-TEST", "SHUTTER-DIMMER", 
        "COLOR-TEST", "GOBO-TEST", "MANUAL", "DMX-PASSTHROUGH"
    };
    
    Serial.printf("| %-15s | %-12s | Pan: %6.1f° | Tilt: %6.1f° | DMX: %3d |\n", 
                 name.c_str(), modeNames[mode], 
                 (mode == MODE_UWB_TRACKING ? currentPan : testPanAngle),
                 (mode == MODE_UWB_TRACKING ? currentTilt : testTiltAngle), 
                 dmxAddress);
}