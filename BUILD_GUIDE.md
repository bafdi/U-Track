# 🔨 BUILD & DEPLOYMENT GUIDE

## Prerequisites

### Required Software
- **VS Code**: Latest version
- **PlatformIO IDE Extension**: Install from VS Code marketplace
- **Git**: For version control (optional)

### Required Hardware
- **ESP32 DevKit C v4** (or compatible)
- **USB Cable**: Data cable (not charge-only)
- **DMX Interface**: Connected to pins 17 (TX) and 21 (Enable)
- **Power Supply**: 5V via USB or external

---

## 📥 Installation Steps

### Step 1: Install PlatformIO
```
1. Open VS Code
2. Go to Extensions (Ctrl+Shift+X)
3. Search "PlatformIO IDE"
4. Click Install
5. Reload VS Code
```

### Step 2: Open Project
```
1. File → Open Folder
2. Navigate to U-Track project directory
3. Wait for PlatformIO to initialize
4. Dependencies will auto-download
```

### Step 3: Connect ESP32
```
1. Connect ESP32 to computer via USB
2. Windows: Check Device Manager for COM port
3. macOS/Linux: Check /dev/ttyUSB* or /dev/cu.usbserial*
```

### Step 4: Configure Upload Port (if needed)
```
If PlatformIO can't find ESP32:

1. Open platformio.ini
2. Add this line under [env:esp32dev]:
   upload_port = COM3  ; Windows
   upload_port = /dev/ttyUSB0  ; Linux
   upload_port = /dev/cu.usbserial-*  ; macOS
```

---

## 🚀 Building & Uploading

### Method 1: PlatformIO Toolbar
```
1. Look for PlatformIO icons in bottom toolbar:
   ✓ (checkmark) = Build
   → (arrow)     = Upload
   🔌 (plug)     = Serial Monitor

2. Click → (Upload) to compile and flash
3. Wait for "SUCCESS" message
4. Click 🔌 to open Serial Monitor
```

### Method 2: Command Palette
```
1. Press Ctrl+Shift+P (Windows/Linux) or Cmd+Shift+P (macOS)
2. Type "PlatformIO: Upload"
3. Press Enter
```

### Method 3: Terminal
```bash
# Navigate to project directory
cd /path/to/U-Track

# Build only
pio run

# Build and upload
pio run --target upload

# Open serial monitor
pio device monitor
```

---

## 📊 Build Output

### Successful Build
```
RAM:   [====      ]  35.2% (used 115416 bytes from 327680 bytes)
Flash: [====      ]  42.8% (used 561234 bytes from 1310720 bytes)
=========================== [SUCCESS] Took 12.34 seconds ===========================
```

### Failed Build
```
Common errors:
1. "Library not found" → Check platformio.ini dependencies
2. "Serial port not found" → Check USB connection and port
3. "Compilation error" → Check code syntax
```

---

## 🔍 Serial Monitor

### Open Monitor
```
1. Click 🔌 icon in PlatformIO toolbar
2. Or: Terminal → pio device monitor
3. Baud rate: 115200 (set in platformio.ini)
```

### Expected Output
```
╔════════════════════════════════════════╗
║   U-TRACK DMX TRACKING SYSTEM v2.0    ║
║   With Dynamic Web Configuration      ║
╚════════════════════════════════════════╝

✓ LittleFS Mounted
✓ Loaded 2 profiles and 2 fixtures from config
✓ DMX initialisiert (Output=Port 2, Input=Port 1)

=== WiFi Access Point Started ===
SSID: U-Track-DMX
Password: utrack123
Dashboard URL: http://192.168.4.1/

✓ Web Server started on port 80
ESP-NOW initialisiert - Warte auf Positionsdaten...

✓✓✓ System Ready ✓✓✓
```

---

## 🐛 Troubleshooting Build Issues

### Issue 1: Library Dependencies Not Found
```
Error: Could not find the package with 'ESPAsyncWebServer' requirements

Solution:
1. Delete .pio folder in project root
2. File → Close Folder
3. File → Open Folder (reopen project)
4. PlatformIO will re-download dependencies
```

### Issue 2: ESP32 Not Detected
```
Error: Could not open COM3, the port doesn't exist

Solution:
1. Check USB cable (must be data cable)
2. Install CP2102 or CH340 drivers
3. Try different USB port
4. Check Device Manager (Windows) or ls /dev/tty* (Linux/Mac)
```

### Issue 3: Compilation Errors
```
Error: 'WebServerManager' was not declared in this scope

Solution:
1. Ensure all files are in correct directories:
   - include/ for .h files
   - src/ for .cpp files
2. Clean build: PlatformIO → Clean
3. Rebuild: PlatformIO → Build
```

### Issue 4: Upload Fails
```
Error: Failed to connect to ESP32: Timed out waiting for packet header

Solution:
1. Hold BOOT button on ESP32 while uploading
2. Press RESET button after upload starts
3. Try lower upload speed in platformio.ini:
   upload_speed = 115200
```

---

## 📦 Filesystem Upload (Optional)

If you want to pre-load config.json to ESP32:

### Step 1: Install Filesystem Uploader
```
1. PlatformIO Home → Platforms
2. Search "Espressif 32"
3. Install/Update platform
```

### Step 2: Upload Filesystem
```
1. Place config.json in /data folder
2. PlatformIO → Upload Filesystem Image
3. Wait for completion
4. Reset ESP32
```

---

## 🔄 OTA Updates (Future)

For wireless firmware updates:

### Enable OTA in platformio.ini
```ini
upload_protocol = espota
upload_port = 192.168.4.1  ; ESP32 IP address
upload_flags = 
    --port=3232
    --auth=your_password
```

### Upload via WiFi
```
pio run --target upload
```

---

## 📊 Memory Optimization

### If Build Fails Due to Memory
```
Error: region `iram0_0_seg' overflowed by 1234 bytes

Solutions:
1. Reduce HTML_DASHBOARD size (minimize HTML)
2. Enable PSRAM in platformio.ini:
   board_build.arduino.memory_type = qio_opi
3. Optimize code:
   - Use PROGMEM for constants
   - Reduce buffer sizes
```

### Check Memory Usage
```bash
pio run --target size
```

---

## 🧪 Testing Checklist

### Before Deployment
- [ ] Serial Monitor shows "System Ready"
- [ ] WiFi AP "U-Track-DMX" appears
- [ ] Dashboard loads at http://192.168.4.1/
- [ ] Can add/delete fixtures via Web GUI
- [ ] Configuration saves successfully
- [ ] DMX output verified with DMX tester
- [ ] UWB position updates in dashboard
- [ ] Emergency stop works

### Hardware Verification
- [ ] DMX output on pin 17
- [ ] DMX enable on pin 21
- [ ] DMX input on pin 16 (if using passthrough)
- [ ] All fixtures respond to DMX

---

## 📋 Deployment Checklist

### Pre-Deployment
1. **Backup existing config**: Download config.json from old system
2. **Test on bench**: Verify all features before installation
3. **Document setup**: Note DMX addresses, fixture positions
4. **Prepare tools**: DMX tester, multimeter, laptop

### Installation
1. **Power off stage**: Disconnect all DMX devices
2. **Install ESP32**: Mount in rack/enclosure
3. **Connect DMX**: TX to DMX+ (pin 17), Enable to DE/RE (pin 21)
4. **Power on**: Verify Serial Monitor output
5. **Configure WiFi**: Connect to AP and access dashboard

### Post-Installation
1. **Test DMX output**: Use DMX tester to verify signal
2. **Configure fixtures**: Add all lights via Web GUI
3. **Calibrate positions**: Measure and input X/Y/Z coordinates
4. **Test tracking**: Move UWB tag and verify following
5. **Save configuration**: Backup config.json to computer
6. **Document**: Note WiFi password, IP address, DMX addresses

---

## 🔒 Security Hardening

### Change Default Password
```cpp
// In src/main.cpp, initializeWebServer()
WiFi.softAP("U-Track-DMX", "YOUR_STRONG_PASSWORD");
```

### Add HTTP Authentication
```cpp
// In WebServerManager.cpp
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate("admin", "password"))
        return request->requestAuthentication();
    request->send_P(200, "text/html", HTML_DASHBOARD);
});
```

---

## 📈 Performance Tuning

### Optimize DMX Update Rate
```cpp
// In main.cpp
const unsigned long TRACKING_UPDATE_INTERVAL = 100; // 10Hz (default: 200ms)
```

### Reduce Web Polling
```javascript
// In WebContent.h
setInterval(updateStatus, 2000); // Update every 2 seconds (default: 1000ms)
```

### Disable Unused Features
```cpp
// In config.json, set unused channels to 0
"colorWheel": 0,
"goboWheel": 0,
"goboRotation": 0
```

---

## 🎯 Final Steps

1. ✅ **Build successful** → Green checkmark in PlatformIO
2. ✅ **Upload successful** → "SUCCESS" in terminal
3. ✅ **Serial Monitor** → Shows startup messages
4. ✅ **WiFi connected** → Can access dashboard
5. ✅ **DMX output** → Verified with tester
6. ✅ **Configuration saved** → Persists across reboots

**You're ready to deploy! 🎉**

---

## 📞 Support Resources

### Documentation
- `WEB_GUI_README.md` - Complete user guide
- `QUICKSTART.md` - 5-minute setup guide
- `CONFIG_REFERENCE.txt` - Configuration details
- `IMPLEMENTATION_SUMMARY.md` - Technical overview

### Debugging
- **Serial Monitor**: First place to look for errors
- **DMX Tester**: Verify output signal
- **Web Browser Console**: Check for JavaScript errors (F12)

### Common Commands
```bash
# Full clean rebuild
pio run --target clean
pio run

# Monitor serial output
pio device monitor

# Check library versions
pio lib list

# Update all libraries
pio lib update
```

---

**Happy Building! 🔨**
