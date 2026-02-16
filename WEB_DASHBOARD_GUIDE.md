# U-Track DMX Controller v2.0 - Web Dashboard Guide

## 🎯 Overview

The U-Track DMX Controller v2.0 features a **fully dynamic, web-based configuration system**. Gone are the days of recompiling code to add fixtures or change settings. Everything can now be configured through a modern, responsive Web GUI.

## 🚀 Key Features

### ✨ Dynamic Configuration
- **No Code Changes Required**: Add, edit, and remove fixtures and profiles entirely through the Web GUI
- **Persistent Storage**: All configurations saved to LittleFS (config.json)
- **Live Reload**: Changes take effect immediately without restarting the ESP32
- **Import/Export**: Download and upload configuration files for backup or sharing

### 🎨 Modern Web Dashboard
- **Real-time Monitoring**: Live UWB position data (X, Y, Z, RMSE)
- **Operating Mode Control**: Switch between tracking, test modes, manual, and passthrough
- **Emergency Stop**: Instant blackout button for safety
- **Fixture Management**: Add, delete, and configure moving head fixtures
- **Profile Editor**: Create custom fixture profiles with channel mappings
- **Responsive Design**: Works on desktop, tablet, and mobile

### 🔧 Technical Architecture

#### File Structure
```
U-Track/
├── data/
│   └── config.json          # Configuration storage (LittleFS)
├── include/
│   ├── ConfigManager.h      # JSON config persistence
│   ├── WebServerManager.h   # Web server & API endpoints
│   ├── WebContent.h         # Embedded HTML dashboard
│   ├── MovingHead.h         # Fixture control logic
│   └── Types.h              # Data structures
├── src/
│   ├── main.cpp             # Main application loop
│   ├── ConfigManager.cpp    # Config load/save implementation
│   ├── WebServerManager.cpp # REST API handlers
│   └── MovingHead.cpp       # DMX output logic
└── platformio.ini           # Build configuration
```

#### Libraries Used
- **ESPAsyncWebServer**: High-performance async web server
- **AsyncTCP**: Asynchronous TCP library
- **ArduinoJson v7**: JSON parsing and generation
- **LittleFS**: Flash filesystem for config storage
- **esp_dmx**: DMX512 driver for ESP32

## 📱 Web Dashboard Guide

### Accessing the Dashboard

1. **Connect to WiFi**: 
   - SSID: `U-Track-DMX`
   - Password: `utrack123`

2. **Open Browser**:
   - URL: `http://192.168.4.1/` (default AP IP)
   - Compatible with all modern browsers

### Dashboard Tabs

#### 📊 Dashboard (Home)
- **Live Position Display**: Real-time UWB tag coordinates
- **Operating Mode Selector**: Quick mode switching
- **Active Fixtures List**: Overview of all configured fixtures
- **System Info**: Uptime, fixture count, position validity

#### 💡 Fixtures
- **Add New Fixture**: 
  1. Click "➕ Add Fixture"
  2. Enter fixture name (e.g., "Front Spot 1")
  3. Set DMX start address (1-512)
  4. Select fixture profile
  5. Enter 3D position (X, Y, Z in meters)
  
- **Delete Fixture**: Click 🗑️ button on any fixture

#### ⚙️ Profiles
- **Add New Profile**:
  1. Click "➕ Add Profile"
  2. Enter profile name (e.g., "MAC 250 Krypton")
  3. Configure DMX channels:
     - Pan Coarse/Fine
     - Tilt Coarse/Fine
     - Zoom, Focus, Dimmer, etc.
  4. Set physical limits:
     - Pan range (degrees)
     - Tilt range (degrees)
     - Tilt home position
  5. Configure inversion flags:
     - Invert Pan
     - Invert Tilt
     - Is Hanging (ceiling mount)

- **Delete Profile**: Click 🗑️ (warning: fixtures using it may malfunction)

#### 🔧 Settings
- **Download Config**: Export configuration as JSON file
- **Upload Config**: Import previously saved configuration
- **Factory Reset**: Clear all settings (future feature)

## 🛠️ Configuration JSON Structure

### Sample config.json

```json
{
  "version": "1.0",
  "system": {
    "name": "U-Track DMX Controller"
  },
  "profiles": [
    {
      "name": "Robin MegaPointe",
      "panCoarse": 1,
      "panFine": 2,
      "tiltCoarse": 3,
      "tiltFine": 4,
      "dimmer": 0,
      "shutter": 0,
      "zoom": 32,
      "focus": 34,
      "panMin": 0.0,
      "panMax": 540.0,
      "tiltMin": 0.0,
      "tiltMax": 265.0,
      "tiltHome": 41.5,
      "panHomeOffset": 180.0,
      "zoomMinAngle": 1.8,
      "zoomMaxAngle": 42.0,
      "invertPan": true,
      "invertTilt": false,
      "isHanging": false,
      "panDeadZone": 2.0,
      "tiltDeadZone": 2.0
    }
  ],
  "fixtures": [
    {
      "name": "MH4 (MegaPointe)",
      "dmxAddress": 1,
      "profileName": "Robin MegaPointe",
      "position": {
        "x": 7.95,
        "y": 24.84,
        "z": 0.35
      }
    }
  ]
}
```

### Profile Parameters Explained

| Parameter | Description | Example |
|-----------|-------------|---------|
| `name` | Profile identifier | "Robin MegaPointe" |
| `panCoarse` | DMX channel for pan MSB | 1 |
| `panFine` | DMX channel for pan LSB | 2 |
| `tiltCoarse` | DMX channel for tilt MSB | 3 |
| `tiltFine` | DMX channel for tilt LSB | 4 |
| `panMax` | Maximum pan rotation (degrees) | 540.0 |
| `tiltMax` | Maximum tilt rotation (degrees) | 265.0 |
| `tiltHome` | Tilt angle when horizontal | 135.0 |
| `panHomeOffset` | Pan offset from 0° | 180.0 |
| `invertPan` | Reverse pan direction | true/false |
| `invertTilt` | Reverse tilt direction | true/false |
| `isHanging` | Ceiling-mounted fixture | true/false |

### Fixture Parameters

| Parameter | Description | Example |
|-----------|-------------|---------|
| `name` | Fixture identifier | "Front Spot 1" |
| `dmxAddress` | DMX start address (1-512) | 1 |
| `profileName` | Reference to profile | "Robin MegaPointe" |
| `position.x` | X coordinate (meters) | 7.95 |
| `position.y` | Y coordinate (meters) | 24.84 |
| `position.z` | Z height (meters) | 0.35 |

## 🎮 Operating Modes

### 0️⃣ UWB Tracking (Default)
- Fixtures follow UWB tag position in real-time
- Automatic pan/tilt/zoom/focus calculation
- Position update rate: 5 Hz (configurable)

### 1️⃣-5️⃣ Test Modes
- Pan Test: Sweep pan left-right
- Tilt Test: Sweep tilt up-down
- Dimmer Test: Fade in/out
- Color Test: Cycle through color wheel
- Gobo Test: Rotate gobo wheel

### 6️⃣ Manual Mode
- Direct DMX channel control via serial console
- Web-based manual control (coming soon)

### 7️⃣ DMX Passthrough
- Forward incoming DMX signal to output
- Useful for backup control or testing

## 📡 REST API Reference

### GET /api/status
Returns current system status
```json
{
  "mode": "UWB-TRACKING",
  "position": {
    "x": 5.23,
    "y": 12.45,
    "z": 1.20,
    "rmse": 0.023,
    "valid": true
  },
  "fixtureCount": 2,
  "uptime": 3600
}
```

### GET /api/config
Returns complete configuration
```json
{
  "version": "1.0",
  "profiles": [...],
  "fixtures": [...]
}
```

### POST /api/config/save
Save new configuration (JSON body)

### GET /api/mode?mode=0
Set operating mode (0-7)

### GET /api/emergency
Trigger emergency stop (blackout)

## 🔒 Security Considerations

- **Default Password**: Change WiFi password in `main.cpp` before deployment
- **Network Isolation**: AP mode isolates controller from other networks
- **No Authentication**: Web interface currently has no login (suitable for trusted networks)

## 🚨 Troubleshooting

### Web Dashboard Won't Load
1. Check WiFi connection to "U-Track-DMX"
2. Verify IP address (should be 192.168.4.1)
3. Try different browser
4. Check serial console for errors

### Fixtures Not Responding
1. Verify DMX wiring (Data+, Data-, GND)
2. Check fixture DMX addresses match config
3. Ensure fixtures are powered on
4. Test with DMX Passthrough mode

### Configuration Won't Save
1. Check LittleFS is mounted (serial console shows "✓ LittleFS Mounted")
2. Verify JSON syntax in uploaded config
3. Check available flash space
4. Try factory reset and reconfigure

### UWB Position Not Updating
1. Check ESP-NOW initialization in serial
2. Verify UWB tag is powered and transmitting
3. Check position timeout (default 5 seconds)
4. Monitor "Position Valid" indicator

## 🎓 Best Practices

### Fixture Calibration
1. **Measure Precisely**: Use laser measurer for X, Y, Z coordinates
2. **Reference Point**: Establish venue origin (0, 0, 0)
3. **Test Position**: Point fixture at known location to verify
4. **Document**: Export config and save with venue photos

### Profile Creation
1. **Consult Manual**: Use manufacturer DMX chart
2. **Test Channels**: Verify each channel function before saving
3. **Inversion**: Test pan/tilt direction, invert if needed
4. **Name Clearly**: Include manufacturer and model

### Safety
1. **Emergency Stop**: Always accessible during operation
2. **Backup Config**: Download before major changes
3. **Test Mode**: Use test modes before live tracking
4. **Manual Override**: Keep serial console access available

## 📦 Deployment Checklist

- [ ] Flash firmware to ESP32
- [ ] Upload config.json to LittleFS (via PlatformIO)
- [ ] Change WiFi password in code
- [ ] Measure and record fixture positions
- [ ] Create/verify fixture profiles
- [ ] Test each fixture individually
- [ ] Test UWB tracking
- [ ] Configure emergency stop procedures
- [ ] Document configuration
- [ ] Train operators

## 🔮 Future Enhancements

- [ ] User authentication system
- [ ] Multi-universe DMX support
- [ ] 3D visualization of stage/fixtures
- [ ] Advanced manual control sliders
- [ ] Movement recording/playback
- [ ] WiFi client mode (connect to existing network)
- [ ] OTA firmware updates
- [ ] Event logging and diagnostics

## 📞 Support

For issues, questions, or contributions:
- Serial Console: 115200 baud, press 'H' for help
- GitHub Issues: [Project Repository]
- Documentation: See BUILD_GUIDE.md and IMPLEMENTATION_SUMMARY.md

---

**Version**: 2.0.0  
**Last Updated**: February 2026  
**License**: MIT (or your preferred license)
