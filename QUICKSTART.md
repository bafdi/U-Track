# 🚀 QUICK START GUIDE - U-Track DMX Web GUI

## 📋 Prerequisites
- ESP32 DevKit C v4
- PlatformIO IDE (VS Code extension)
- Required libraries (auto-installed via platformio.ini)

## ⚡ 5-Minute Setup

### Step 1: Flash the Firmware
```bash
# In VS Code with PlatformIO
1. Open this project folder
2. Press PlatformIO: Upload (→ icon)
3. Wait for compilation and upload
```

### Step 2: Connect to WiFi
```
1. ESP32 will create WiFi hotspot:
   SSID: U-Track-DMX
   Password: utrack123

2. Connect your phone/laptop to this network

3. Serial Monitor will show:
   Dashboard URL: http://192.168.4.1/
```

### Step 3: Open Dashboard
```
1. Open browser
2. Navigate to: http://192.168.4.1/
3. You'll see the U-Track Dashboard
```

### Step 4: Configure Fixtures
```
Go to "Fixtures" tab:

1. Click "Add New Fixture"
2. Fill in:
   - Name: "Front Spot 1"
   - DMX Address: 1
   - Profile: Select "Robin MegaPointe"
   - Position X: 5.0 (meters)
   - Position Y: 10.0 (meters)
   - Position Z: 2.5 (meters)
3. Click "Add Fixture"

4. Click "Save Configuration" in Config tab
```

### Step 5: Test Tracking
```
1. Go to "Control" tab
2. Click "UWB Tracking" mode
3. Move UWB tag - fixtures will follow!
```

## 🎛️ Dashboard Tabs

| Tab | Purpose |
|-----|---------|
| **📊 Dashboard** | Real-time status, position, fixtures |
| **💡 Fixtures** | Add/remove/edit fixtures |
| **⚙️ Profiles** | Create custom fixture profiles |
| **🎮 Control** | Switch operating modes |
| **🔧 Configuration** | Save/load/backup config |

## 🔧 Common Tasks

### Add a New Fixture Type
```
Profiles tab → Create New Profile:
- Name: "Martin MAC 250"
- Pan Coarse: 1
- Pan Fine: 2
- Tilt Coarse: 3
- Tilt Fine: 4
- Dimmer: 5
- Pan Max: 540
- Tilt Max: 270
→ Create Profile
```

### Backup Configuration
```
Configuration tab → Download Config JSON
→ Save file to computer
```

### Restore Configuration
```
Configuration tab → Upload Config
→ Select JSON file
→ System reloads automatically
```

### Emergency Stop
```
Click red "EMERGENCY STOP" button (top right)
→ All DMX channels set to 0
→ System enters Manual mode
```

## 🐛 Troubleshooting

### ❌ Can't connect to WiFi
```
1. Check ESP32 is powered on
2. Look for "U-Track-DMX" network
3. Password: utrack123
4. Reset ESP32 and try again
```

### ❌ Dashboard won't load
```
1. Verify IP: http://192.168.4.1/
2. Check Serial Monitor for errors
3. Try different browser (Chrome recommended)
```

### ❌ Configuration not saving
```
1. Click "Save Configuration" button
2. Check Serial Monitor for filesystem errors
3. If LittleFS fails, reflash firmware
```

### ❌ Fixtures not tracking
```
1. Verify UWB position is updating (Dashboard)
2. Check fixture positions in config
3. Ensure mode is "UWB Tracking"
4. Check DMX cables and addresses
```

## 📡 Serial Monitor Commands

Open Serial Monitor (115200 baud):

```
'0' = UWB Tracking Mode
'1' = Pan Test
'2' = Tilt Test
'3' = Dimmer Test
'6' = Manual Mode
'7' = DMX Passthrough
```

## 🌐 Network Configuration

### Change WiFi Credentials
Edit in `src/main.cpp`:
```cpp
WiFi.softAP("U-Track-DMX", "utrack123");
//           ^^^^^^^^^^^^  ^^^^^^^^^^
//           SSID          Password
```

### Use Existing WiFi Network
Replace this section:
```cpp
WiFi.mode(WIFI_AP_STA);
WiFi.softAP("U-Track-DMX", "utrack123");
```

With:
```cpp
WiFi.mode(WIFI_STA);
WiFi.begin("YourSSID", "YourPassword");
while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
}
Serial.println(WiFi.localIP()); // Use this IP
```

## 📊 Performance Tips

### Optimize for Many Fixtures
```
1. Reduce TRACKING_UPDATE_INTERVAL in main.cpp
   (default: 200ms)

2. Use 8-bit pan/tilt (set Fine channels to 0)
   for faster DMX updates

3. Disable unused features (zoom, focus)
   in profiles
```

### Reduce Web Traffic
```
1. Dashboard auto-updates every 1 second
2. Edit JavaScript in WebContent.h:
   setInterval(updateStatus, 1000);
                              ^^^^ milliseconds
```

## 🎯 Next Steps

1. ✅ **Calibrate Positions**: Measure exact fixture locations
2. ✅ **Create Custom Profiles**: Add your fixture types
3. ✅ **Test Tracking**: Verify UWB accuracy
4. ✅ **Backup Config**: Download JSON for safety
5. ✅ **Experiment**: Try different modes and settings

## 📚 Full Documentation

See `WEB_GUI_README.md` for complete documentation including:
- API Reference
- Config.json structure
- Calibration guide
- Advanced customization

## 🎉 You're Ready!

Your U-Track DMX Controller is now fully configured and ready to use.

**Pro Tip**: Keep a backup of your `config.json` file in case you need to restore settings later!

---

**Need Help?** Check Serial Monitor output (115200 baud) for debug info.
