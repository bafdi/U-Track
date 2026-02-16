# U-Track DMX Controller - Web GUI Documentation

## 🎯 Overview

The U-Track DMX Controller now features a **fully dynamic, web-based configuration system**. You can configure the entire stage setup (fixture profiles and active fixtures) via a modern Web Dashboard without recompiling code.

## 🚀 Key Features

### ✅ Dynamic Configuration
- **No hardcoded fixtures** - all configuration is stored in `config.json` on LittleFS
- Add/Edit/Delete fixtures and profiles via Web GUI
- Download/Upload configuration as JSON files
- Automatic persistence across reboots

### 🌐 Web Dashboard
- **Real-time monitoring** of UWB position and fixture status
- **Profile Manager** - Create custom fixture profiles (channel mappings, limits, calibration)
- **Fixture Manager** - Add lights with 3D position calibration
- **Operating Mode Control** - Switch between tracking, testing, manual, and passthrough modes
- **Emergency Stop** button for instant blackout

### 🔧 Technical Stack
- **Backend**: ESPAsyncWebServer, ArduinoJson, LittleFS
- **Frontend**: Single-page HTML5/CSS3/JavaScript (embedded in PROGMEM)
- **Performance**: Non-blocking DMX loop, async file operations

---

## 📡 Getting Started

### 1. First Boot

On first boot, the system will:
1. Initialize LittleFS
2. Create a default `config.json` with your existing fixtures
3. Start WiFi Access Point: **SSID: `U-Track-DMX`** / **Password: `utrack123`**
4. Launch Web Server on port 80

### 2. Connect to Dashboard

1. Connect your device (phone/laptop) to WiFi network `U-Track-DMX`
2. Open browser and navigate to: `http://192.168.4.1/`
3. You should see the U-Track Dashboard

### 3. Configure Your Stage

#### **Add a Fixture Profile**

A profile defines the DMX channel layout and physical capabilities of a fixture type.

1. Go to **Profiles** tab
2. Click "Create New Profile"
3. Fill in:
   - **Name**: e.g., "Robe Robin MegaPointe"
   - **Channel Mapping**: Pan Coarse/Fine, Tilt, Dimmer, Zoom, Focus, etc.
   - **Physical Limits**: Pan/Tilt ranges in degrees
   - **Flags**: Invert Pan/Tilt, Hanging/Floor mount
4. Click "Create Profile"

#### **Add a Fixture**

Once you have profiles, add actual lights:

1. Go to **Fixtures** tab
2. Fill in:
   - **Name**: e.g., "Front Spot 1"
   - **DMX Address**: Starting DMX channel (1-512)
   - **Profile**: Select from dropdown
   - **Position X, Y, Z**: Physical location in meters (for tracking)
3. Click "Add Fixture"

#### **Calibrate Position**

Use a measuring tape or laser distance meter to determine the X, Y, Z coordinates of each fixture relative to your UWB coordinate system.

**Tip**: Place the UWB tag at a known position and use the Dashboard to verify the tracking is accurate before adding fixtures.

---

## 🎮 Operating Modes

The system supports multiple operating modes, selectable from the **Control** tab:

| Mode | Description |
|------|-------------|
| **UWB Tracking** | Fixtures follow the UWB tag in real-time |
| **Pan Test** | Sweeps pan left/right across full range |
| **Tilt Test** | Sweeps tilt up/down across full range |
| **Dimmer Test** | Fades dimmer 0-100% |
| **Manual** | Full manual control via serial commands |
| **DMX Passthrough** | Passes DMX input directly to output |

---

## 💾 Configuration Management

### Save Configuration
Click **"Save Configuration"** in the Configuration tab to persist changes to LittleFS.

### Download Config
Download the current `config.json` file to your computer for backup.

### Upload Config
Upload a previously saved `config.json` file to restore a configuration.

### Manual Editing
You can manually edit `config.json` on your computer and upload it. See example below.

---

## 📄 Example config.json

```json
{
  "version": "1.0",
  "profiles": [
    {
      "name": "Robin MegaPointe",
      "panCoarse": 1,
      "panFine": 2,
      "tiltCoarse": 3,
      "tiltFine": 4,
      "dimmer": 6,
      "shutter": 5,
      "zoom": 32,
      "focus": 34,
      "panMin": 0.0,
      "panMax": 540.0,
      "tiltMin": 0.0,
      "tiltMax": 265.0,
      "tiltHome": 41.5,
      "panHomeOffset": 180.0,
      "invertPan": true,
      "invertTilt": false,
      "isHanging": false
    }
  ],
  "fixtures": [
    {
      "name": "Front Spot 1",
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

### Profile Fields Explained

| Field | Type | Description |
|-------|------|-------------|
| `name` | String | Profile identifier |
| `panCoarse` | int | DMX channel for pan coarse (0 = unused) |
| `panFine` | int | DMX channel for pan fine (0 = unused) |
| `tiltCoarse` | int | DMX channel for tilt coarse |
| `tiltFine` | int | DMX channel for tilt fine |
| `dimmer` | int | DMX channel for dimmer |
| `shutter` | int | DMX channel for shutter/strobe |
| `zoom` | int | DMX channel for zoom |
| `focus` | int | DMX channel for focus |
| `panMin` | float | Minimum pan angle (degrees) |
| `panMax` | float | Maximum pan angle (degrees) |
| `tiltMin` | float | Minimum tilt angle (degrees) |
| `tiltMax` | float | Maximum tilt angle (degrees) |
| `tiltHome` | float | Tilt home position (degrees) |
| `panHomeOffset` | float | Pan offset for 0° reference |
| `invertPan` | bool | Reverse pan direction |
| `invertTilt` | bool | Reverse tilt direction |
| `isHanging` | bool | `true` for hanging, `false` for floor |
| `zoomMinAngle` | float | Narrowest beam angle (degrees) |
| `zoomMaxAngle` | float | Widest beam angle (degrees) |
| `zoomCalibDist1` | float | Calibration distance 1 (meters) |
| `zoomCalibAngle1` | float | Beam angle at distance 1 |
| `focusDMX1` | int | Focus DMX value at distance 1 |
| `zoomCalibDist2` | float | Calibration distance 2 (meters) |
| `zoomCalibAngle2` | float | Beam angle at distance 2 |
| `focusDMX2` | int | Focus DMX value at distance 2 |

---

## 🔌 API Reference

The Web Dashboard communicates with the ESP32 via REST API:

### GET `/api/config`
Returns the full configuration (profiles + fixtures) as JSON.

### POST `/api/config/save`
Saves the configuration to LittleFS.  
**Body**: Complete config JSON

### GET `/api/status`
Returns live system status:
```json
{
  "mode": "UWB-TRACKING",
  "position": { "x": 5.2, "y": 10.3, "z": 1.8, "rmse": 0.05, "valid": true },
  "fixtureCount": 2,
  "uptime": 12345
}
```

### GET `/api/mode?mode=0`
Sets operating mode (0-7).

### GET `/api/emergency`
Triggers emergency stop (blackout all DMX).

---

## 🛠️ Troubleshooting

### Can't connect to WiFi
- Ensure you're connected to `U-Track-DMX` network
- Default password: `utrack123`
- Check if ESP32 LED is on (indicates WiFi active)

### Configuration not saving
- Check Serial Monitor for filesystem errors
- LittleFS may need reformatting (happens automatically on first boot)

### Fixtures not responding
- Verify DMX address matches your console/fixtures
- Check DMX wiring (TX pin 17, Enable pin 21)
- Use Serial Monitor to see DMX output

### Position tracking not working
- Ensure ESP-NOW is receiving UWB data (check Serial Monitor)
- Verify fixture positions are correct in config
- Check RMSE value in Dashboard (should be < 0.1m for good tracking)

---

## 🎨 Customization

### Change WiFi Credentials
In `main.cpp`, modify:
```cpp
WiFi.softAP("U-Track-DMX", "utrack123");
```

### Add Custom Profiles
Use the Web GUI or manually edit `config.json`.

### Extend API
Add routes in `WebServerManager.cpp`:
```cpp
server.on("/api/custom", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Custom response");
});
```

---

## 📚 File Structure

```
U-Track/
├── src/
│   ├── main.cpp              # Main application logic
│   ├── MovingHead.cpp        # Fixture control algorithms
│   ├── ConfigManager.cpp     # JSON config persistence
│   └── WebServerManager.cpp  # Web server & API
├── include/
│   ├── Types.h               # Data structures
│   ├── MovingHead.h
│   ├── ConfigManager.h
│   ├── WebServerManager.h
│   └── WebContent.h          # Embedded HTML/JS/CSS
├── data/
│   └── config.json           # Example configuration
└── platformio.ini            # Build configuration
```

---

## 🔒 Security Note

The current implementation **does not include authentication**. For production use:
- Change WiFi password
- Add HTTP basic auth or token-based authentication
- Use HTTPS (requires SSL certificates)

---

## 📞 Support

For issues or questions:
- Check Serial Monitor output (115200 baud)
- Review this documentation
- Inspect `config.json` on the ESP32 filesystem

---

## 🎉 Summary

You now have a **fully dynamic DMX controller** that can be configured entirely via Web GUI. No more recompiling code to add fixtures or change settings!

**Key Benefits:**
- ✅ Live configuration updates
- ✅ Visual dashboard for monitoring
- ✅ Easy backup/restore via JSON
- ✅ No programming knowledge required for day-to-day use
- ✅ Professional-grade interface

**Happy Tracking! 🎭**
