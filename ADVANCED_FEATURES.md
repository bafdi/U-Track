# Advanced Features - Implementation Guide

This document describes the advanced features added to the U-Track DMX controller web interface.

## ✅ Implemented Features

### 1. 📋 Fixture Copy Button
**Location:** Fixture Manager tab  
**Description:** Quickly duplicate fixtures with automatic DMX address offset.

**How it works:**
- Click the "📋 Copy" button next to any fixture
- Creates a copy with name "(Copy)" suffix
- Automatically offsets DMX address by 32 channels
- If address exceeds 512, wraps to channel 1
- Position offset by +1 meter on X-axis

**Code:** `copyFixture()` function in WebContent.h

---

### 2. 💡 Beam Visualization
**Location:** Live Stage Map tab  
**Description:** Toggle visual beam lines from fixtures to tracked target.

**How it works:**
- Click "💡 Show Beams" button to enable
- SVG overlay draws semi-transparent orange lines
- Shows light path from each fixture to target position
- Only visible when position is valid
- Toggle button text changes to "💡 Hide Beams"

**Code:** `toggleBeams()` and `drawBeams()` functions in WebContent.h

---

### 3. 📊 Full DMX Monitor
**Location:** Dashboard tab (below Operating Modes)  
**Description:** Real-time visualization of all 512 DMX channels.

**Features:**
- 32-column grid layout showing all channels
- Vertical bars with gradient colors (green→yellow→orange)
- Channel numbers displayed above each bar
- Auto-updates every 100ms
- Bar height represents DMX value (0-255)
- Opacity indicates active channels

**Backend:** `/api/dmx/status` endpoint returns all channel values

**Code:** 
- Frontend: `updateDMXMonitor()` function
- Backend: `handleGetDMXStatus()` in WebServerManager.cpp

---

### 4. 🎛️ Enhanced Manual Control
**Location:** Manual DMX Control tab  
**Description:** Show all fixtures simultaneously instead of dropdown selection.

**How it works:**
- Enable "Show all fixtures and channels" checkbox
- Displays every fixture in grouped panels
- Each fixture shows all 8 DMX channels (Pan, Tilt, Zoom, Focus, etc.)
- Vertical sliders for each channel with real-time value display
- No need to switch between fixtures

**Code:** Updated `loadManualChannels()` function

---

### 5. 🔒 Password Protection
**Location:** Login overlay on page load  
**Description:** Prevent unauthorized access in multi-user networks.

**Features:**
- Login overlay blocks access until password entered
- Default password: "admin" (or empty for no password)
- Password stored in localStorage after successful login
- Press Enter to submit password
- Error message for incorrect passwords

**Future Enhancement:** Add password configuration in Settings tab

**Code:** `checkPassword()` and `checkLoginStatus()` functions

---

### 6. 🐔 C.O.C.K. Mode (Easter Egg)
**Location:** Hidden easter egg (click 🐔 in bottom-right corner)  
**Description:** "Coordinated Optical Circuit Kit" - a fun troll mode!

**Features:**
- Pink gradient theme with hot pink colors
- Changes header to "🐔 C.O.C.K. Control Panel 🍆"
- Replaces fixture icons (💡) with chickens (🐔)
- Eggplant emoji cursor (🍆)
- Buttons scale and rotate on hover
- Persistent via localStorage

**Activation:**
- Click tiny 🐔 emoji in bottom-right corner, or
- Add `?mode=cock` to URL

**Code:** `applyCockMode()` function and `.cock-mode` CSS

---

## ⏳ Pending Implementation

### 7. DMX-Controlled Operating Modes
**Status:** Not yet implemented  
**Description:** Control operating mode via specific DMX input channel.

**Proposed Implementation:**

**DMX Channel Mapping (e.g., Channel 1):**
- 0-50: Auto Track mode
- 51-100: Manual mode
- 101-150: Scan mode
- 151-200: Random mode
- 201-255: Emergency stop

**Backend Requirements:**
1. Add DMX input monitoring in main loop
2. Check assigned control channel value
3. Switch `currentMode` based on value ranges
4. Add debouncing to prevent mode flickering
5. Optional: Make control channel configurable in Settings

**Code Location:** Needs implementation in `src/main.cpp` loop()

**Example Implementation:**
```cpp
// In loop() after DMX receive
void checkDMXModeControl() {
    const int CONTROL_CHANNEL = 1; // Configurable
    uint8_t value = dmxReceive[CONTROL_CHANNEL]; // If using DMX input
    
    OperatingMode newMode;
    if (value <= 50) newMode = OperatingMode::AUTO_TRACK;
    else if (value <= 100) newMode = OperatingMode::MANUAL;
    else if (value <= 150) newMode = OperatingMode::SCAN;
    else if (value <= 200) newMode = OperatingMode::RANDOM;
    else newMode = OperatingMode::EMERGENCY_STOP;
    
    if (newMode != currentMode) {
        setOperatingMode(newMode);
        Serial.printf("🎛️ Mode changed via DMX: %d\n", (int)newMode);
    }
}
```

**Note:** This requires DMX input capability (ArtNet/sACN or DMX shield).

---

## 🎨 CSS Classes Reference

### DMX Monitor
- `.dmx-monitor` - Grid container (32 columns)
- `.dmx-channel` - Individual channel container
- `.dmx-channel-num` - Channel number label
- `.dmx-bar-container` - Bar wrapper
- `.dmx-bar` - Animated bar with gradient

### Manual Control
- `.fixture-control-group` - Fixture grouping panel
- `.dmx-control-panel` - Grid layout for sliders
- `.dmx-slider` - Vertical range input

### C.O.C.K. Mode
- `.cock-mode` - Body class for troll theme
- `.cock-easter-egg` - Hidden trigger button

### Beam Visualization
- `.beam-overlay` - SVG overlay layer
- `.stage-controls` - Contains toggle button

---

## 🔧 Configuration

### Default Password
To change default password, modify the `checkPassword()` function:
```javascript
if(pwd==='your-password'||pwd===localStorage.getItem('dmxPassword')){
```

### DMX Monitor Refresh Rate
Current: 100ms (10 updates/second)  
To change, modify line in `DOMContentLoaded`:
```javascript
setInterval(updateDMXMonitor, 100); // Change 100 to desired milliseconds
```

### Fixture Copy DMX Offset
Current: +32 channels  
To change, modify `copyFixture()` function:
```javascript
dmxAddress:f.dmxAddress+32, // Change 32 to desired offset
```

---

## 📡 API Endpoints

### GET `/api/dmx/status`
**Description:** Returns current values of all 512 DMX channels

**Response:**
```json
{
  "channels": [0, 0, 128, 255, ...] // 512 values
}
```

**Usage:** Called by DMX monitor every 100ms

---

## 🐛 Known Limitations

1. **Password Security:** Currently client-side only - not truly secure
2. **DMX Mode Control:** Not implemented yet - requires DMX input
3. **Beam Visualization:** Static lines only - no dynamic animation
4. **Login Persistence:** Logout button not added yet

---

## 🚀 Future Enhancements

1. Server-side password authentication
2. Configurable password in Settings tab
3. Logout button in header
4. DMX input for mode control
5. Animated beam effects (pulsing, color change)
6. DMX monitor filtering (show only active channels)
7. Fixture grouping in manual control
8. Export/import fixture configurations
9. More easter eggs! 🎉

---

**Last Updated:** Phase 2 Implementation  
**Version:** Web Dashboard V2.1  
**Author:** GitHub Copilot + Sebastian Pfleiderer
