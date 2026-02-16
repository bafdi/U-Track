# 🎭 U-Track DMX Controller v2.0

> **Real-time UWB Position Tracking → DMX Control System**  
> **Now with Dynamic Web-Based Configuration**

[![PlatformIO](https://img.shields.io/badge/PlatformIO-ESP32-blue)](https://platformio.org/)
[![License](https://img.shields.io/badge/License-MIT-green)]()
[![Version](https://img.shields.io/badge/Version-2.0-orange)]()

---

## 🌟 Overview

The U-Track DMX Controller is a **professional-grade lighting control system** that uses Ultra-Wideband (UWB) position tracking to automatically aim moving head fixtures at a tracked target. Version 2.0 introduces **complete dynamic configuration via Web GUI** - no code changes required!

### ✨ Key Features

- 🎯 **Real-time UWB Tracking**: Fixtures follow a moving target with high precision
- 🌐 **Web Dashboard**: Modern, responsive interface for complete system control
- 💾 **Dynamic Configuration**: Add/edit fixtures and profiles without recompiling
- 🔄 **Persistent Storage**: Configuration saved to LittleFS, survives reboots
- 🎛️ **Multiple Operating Modes**: Tracking, Testing, Manual, DMX Passthrough
- 🚨 **Emergency Controls**: Instant blackout capability
- 📡 **REST API**: Programmatic access for automation
- 🔧 **Profile Manager**: Create custom fixture types with calibration
- 📱 **Mobile Friendly**: Works on phone, tablet, desktop

---

## 🚀 Quick Start

### 1️⃣ **Upload Firmware**
```bash
# In VS Code with PlatformIO
pio run --target upload
```

### 2️⃣ **Connect to WiFi**
```
SSID: U-Track-DMX
Password: utrack123
```

### 3️⃣ **Open Dashboard**
```
http://192.168.4.1/
```

### 4️⃣ **Configure & Track!**
See [QUICKSTART.md](QUICKSTART.md) for detailed setup.

---

## 📚 Documentation

| Document | Description |
|----------|-------------|
| [📖 QUICKSTART.md](QUICKSTART.md) | 5-minute setup guide |
| [📘 WEB_GUI_README.md](WEB_GUI_README.md) | Complete user manual |
| [🔧 CONFIG_REFERENCE.txt](CONFIG_REFERENCE.txt) | JSON configuration guide |
| [🔨 BUILD_GUIDE.md](BUILD_GUIDE.md) | Compilation & deployment |
| [📊 IMPLEMENTATION_SUMMARY.md](IMPLEMENTATION_SUMMARY.md) | Technical architecture |

---

## 🎨 Web Dashboard

<p align="center">
  <img src="https://via.placeholder.com/800x400/1e1e2e/00d4ff?text=U-Track+Dashboard+Screenshot" alt="Dashboard Screenshot">
</p>

### Dashboard Features

| Tab | Features |
|-----|----------|
| **📊 Dashboard** | Real-time UWB position, fixture status, system health |
| **💡 Fixtures** | Add/edit/delete fixtures, 3D position calibration |
| **⚙️ Profiles** | Create custom fixture types (channel mapping + limits) |
| **🎮 Control** | Operating mode selection, emergency stop |
| **🔧 Configuration** | Save/load/backup system configuration |

---

## 🛠️ Hardware Requirements

### Required Components
- **ESP32 DevKit C v4** (or compatible)
- **DMX512 Interface** (e.g., RS485 transceiver)
- **UWB Positioning System** (e.g., Pozyx, Qorvo DWM1001)
- **Moving Head Fixtures** (any DMX-controlled fixtures)
- **Power Supply** (5V for ESP32, 12-48V for fixtures)

### Wiring

```
ESP32 Pin 17 → DMX Transceiver TX (DMX Output)
ESP32 Pin 21 → DMX Transceiver DE/RE (Enable)
ESP32 Pin 16 → DMX Transceiver RX (DMX Input - optional)
ESP32 Pin 15 → DMX Transceiver DE/RE (Input Enable)
ESP32 GND   → Common Ground
```

---

## 📦 Software Dependencies

Automatically installed via PlatformIO:

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
lib_deps = 
    https://github.com/someweisguy/esp_dmx.git
    https://github.com/me-no-dev/ESPAsyncWebServer.git
    https://github.com/me-no-dev/AsyncTCP.git
    bblanchon/ArduinoJson@^7.0.0
```

---

## 🎯 Use Cases

### 🎭 **Theater & Stage Productions**
Automatically spotlight actors as they move around the stage.

### 🎪 **Events & Concerts**
Follow performers with dynamic lighting effects.

### 🎬 **TV & Film Production**
Automated camera-following spotlights for live broadcasts.

### 🏀 **Sports Arenas**
Track athletes during games for instant replays and highlights.

### 🎨 **Interactive Installations**
Create immersive experiences with responsive lighting.

---

## 🔧 Configuration Example

### Add a Fixture via Web GUI

```
1. Navigate to "Fixtures" tab
2. Fill in:
   - Name: "Front Spot 1"
   - DMX Address: 1
   - Profile: "Robin MegaPointe"
   - Position: X=5.0, Y=10.0, Z=2.5 meters
3. Click "Add Fixture"
4. Click "Save Configuration"
```

### Or via JSON

```json
{
  "profiles": [
    {
      "name": "Robin MegaPointe",
      "panCoarse": 1,
      "panFine": 2,
      "tiltCoarse": 3,
      "tiltFine": 4,
      "panMax": 540.0,
      "tiltMax": 265.0
    }
  ],
  "fixtures": [
    {
      "name": "Front Spot 1",
      "dmxAddress": 1,
      "profileName": "Robin MegaPointe",
      "position": { "x": 5.0, "y": 10.0, "z": 2.5 }
    }
  ]
}
```

---

## 🎮 Operating Modes

| Mode | Description | Use Case |
|------|-------------|----------|
| **UWB Tracking** | Follow UWB tag position | Live performance |
| **Pan Test** | Sweep pan L/R | Calibration |
| **Tilt Test** | Sweep tilt U/D | Calibration |
| **Dimmer Test** | Fade intensity | Testing |
| **Manual** | Direct DMX control | Programming |
| **DMX Passthrough** | Relay input to output | Integration |

---

## 📊 Performance

- **Tracking Update Rate**: 5 Hz (200ms default, configurable to 10Hz)
- **DMX Frame Rate**: 30 Hz (33ms loop)
- **Position Accuracy**: < 10cm (RMSE with good UWB setup)
- **Web Server**: Async, non-blocking
- **Max Fixtures**: Limited by ESP32 memory (~50+ fixtures supported)

---

## 🌐 API Reference

### REST Endpoints

```
GET  /                      → Web Dashboard
GET  /api/config            → Get configuration
POST /api/config/save       → Save configuration
GET  /api/status            → Live system status
GET  /api/mode?mode=X       → Set operating mode
GET  /api/emergency         → Emergency stop
GET  /api/profiles          → Get all profiles
GET  /api/fixtures          → Get all fixtures
```

### Example API Call

```bash
# Get system status
curl http://192.168.4.1/api/status

# Change to tracking mode
curl http://192.168.4.1/api/mode?mode=0

# Emergency stop
curl http://192.168.4.1/api/emergency
```

---

## 🐛 Troubleshooting

### Can't connect to WiFi?
- Check ESP32 is powered on
- Look for "U-Track-DMX" network
- Password: `utrack123`

### Fixtures not responding?
- Verify DMX wiring (TX=pin 17, Enable=pin 21)
- Check DMX addresses in config
- Use Serial Monitor for debug output

### Configuration not saving?
- Click "Save Configuration" button
- Check Serial Monitor for filesystem errors
- Reflash if LittleFS corrupted

See [BUILD_GUIDE.md](BUILD_GUIDE.md) for detailed troubleshooting.

---

## 🔒 Security

⚠️ **Default configuration is NOT secure for production use!**

### Recommended for Production:
1. **Change WiFi Password** (default: `utrack123`)
2. **Enable HTTP Authentication**
3. **Use HTTPS** (requires SSL certificates)
4. **Restrict WiFi to specific MAC addresses**

See [WEB_GUI_README.md](WEB_GUI_README.md#security) for details.

---

## 🛣️ Roadmap

### Version 2.1 (Planned)
- [ ] 3D Stage Visualizer (Three.js)
- [ ] Scene Memory (save/recall positions)
- [ ] Automated Position Calibration
- [ ] Multi-Universe DMX Support

### Version 2.2 (Future)
- [ ] OTA Firmware Updates
- [ ] Mobile App (iOS/Android)
- [ ] Cloud Configuration Backup
- [ ] Advanced Effects Engine

---

## 🤝 Contributing

Contributions welcome! Please:
1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Submit a pull request

---

## 📄 License

This project is licensed under the MIT License.

```
Copyright (c) 2026 U-Track Project

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software.
```

---

## 🙏 Acknowledgments

- **esp_dmx** by someweisguy - DMX512 library
- **ESPAsyncWebServer** by me-no-dev - Async web server
- **ArduinoJson** by Benoit Blanchon - JSON parsing
- **PlatformIO** - Development platform

---

## 📞 Support

- 📧 Email: support@u-track.example.com
- 💬 Discord: [Join our community](#)
- 📚 Documentation: [WEB_GUI_README.md](WEB_GUI_README.md)
- 🐛 Issues: [GitHub Issues](#)

---

## 🎉 Get Started Now!

```bash
# Clone the repository
git clone https://github.com/yourusername/U-Track.git

# Open in VS Code with PlatformIO
code U-Track

# Upload firmware
pio run --target upload

# Open Serial Monitor
pio device monitor

# Connect to WiFi and enjoy! 🎭
```

---

<p align="center">
  <strong>Made with ❤️ for the lighting community</strong><br>
  <sub>Illuminate the world, one tracked fixture at a time ✨</sub>
</p>
