# 🔄 Migration Guide: v1.0 → v2.0

## Architecture Evolution

### Before (v1.0 - Hardcoded)

```cpp
// main.cpp - OLD WAY
void setup() {
    // Fixtures hardcoded in setup()
    movingHeads.push_back(
        MovingHead("MH1", 1, 
                   Point3D(7.95, 24.84, 0.35), 
                   robinMegaPointeProfile)
    );
    
    movingHeads.push_back(
        MovingHead("MH2", 40, 
                   Point3D(3.3, 24.23, 0.25), 
                   robinMegaPointeProfile)
    );
    
    // Any change = recompile & reflash
}
```

**Problems:**
- ❌ Adding a fixture = edit code, recompile, reflash
- ❌ Changing position = same workflow
- ❌ New fixture type = write C++ code
- ❌ No backup/restore capability
- ❌ Difficult for non-programmers

---

### After (v2.0 - Dynamic Web GUI)

```cpp
// main.cpp - NEW WAY
void setup() {
    // Load from LittleFS
    ConfigManager::loadConfig(fixtureProfiles, movingHeads);
    
    // Start Web Server
    initializeWebServer();
    
    // All done - configure via Web!
}
```

**Benefits:**
- ✅ Add fixtures via Web GUI (no code!)
- ✅ Edit positions in real-time
- ✅ Create profiles with forms
- ✅ Export/import JSON configs
- ✅ Anyone can configure it

---

## Key Code Changes

### 1. Configuration Management

#### New Files
```cpp
// ConfigManager.h/cpp
class ConfigManager {
    static bool loadConfig(profiles, fixtures);
    static bool saveConfig(profiles, fixtures);
    static String getConfigAsJson();
    // JSON serialization helpers
};
```

#### Usage
```cpp
// Load on startup
ConfigManager::loadConfig(fixtureProfiles, movingHeads);

// Save when changed
ConfigManager::saveConfig(fixtureProfiles, movingHeads);
```

### 2. Web Server Integration

#### New Files
```cpp
// WebServerManager.h/cpp
class WebServerManager {
    AsyncWebServer server;
    
    // REST API endpoints
    GET  /api/config       // Get full config
    POST /api/config/save  // Save config
    GET  /api/status       // Live data
    GET  /api/mode         // Change mode
    GET  /api/emergency    // E-stop
};

// WebContent.h
const char HTML_DASHBOARD[] PROGMEM = "...";
// Complete single-page app embedded
```

### 3. Dynamic Data Structures

#### Before
```cpp
// Fixed at compile time
MovingHead mh1("MH1", ...);
MovingHead mh2("MH2", ...);
```

#### After
```cpp
// Runtime-configurable vectors
std::vector<MovingHeadProfile> fixtureProfiles;
std::vector<MovingHead> movingHeads;

// Populated from JSON
```

---

## Configuration File Format

### Structure
```
U-Track/
├── data/
│   └── config.json  ← Main configuration
```

### Sample config.json
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
      "panMax": 540.0,
      "tiltMax": 265.0,
      "invertPan": true,
      "isHanging": false
    }
  ],
  "fixtures": [
    {
      "name": "Front Spot",
      "dmxAddress": 1,
      "profileName": "Robin MegaPointe",
      "position": { "x": 7.95, "y": 24.84, "z": 0.35 }
    }
  ]
}
```

---

## Migration Steps

### For Existing Users

#### Step 1: Backup Current Code
```bash
git commit -am "Backup before v2.0 upgrade"
```

#### Step 2: Update Firmware
```bash
pio run --target upload
```

#### Step 3: Upload Filesystem
```bash
# Upload data/ folder to LittleFS
pio run --target uploadfs
```

#### Step 4: Access Web Dashboard
1. Connect to WiFi: `U-Track-DMX`
2. Open: `http://192.168.4.1/`
3. Navigate to: **Fixtures** tab

#### Step 5: Recreate Configuration
**Option A: Via Web GUI**
1. Add your profiles
2. Add your fixtures
3. Set positions
4. Click Save

**Option B: Upload JSON**
1. Create config.json with your settings
2. Go to Settings tab
3. Click "📤 Upload Config"

---

## New Capabilities

### 1. Real-time Position Adjustment
```
Before: Edit code → Compile → Flash (5 minutes)
After:  Web GUI → Change X/Y/Z → Save (5 seconds)
```

### 2. Fixture Library
```
Before: One profile hardcoded
After:  Unlimited profiles stored
```

### 3. Backup/Restore
```
Before: Not possible
After:  Download JSON → Store → Upload later
```

### 4. Remote Configuration
```
Before: USB cable required
After:  WiFi from any device
```

### 5. Multi-Venue Support
```
Before: Different firmware per venue
After:  Different JSON per venue
```

---

## Performance Considerations

### Memory Usage
| Component | v1.0 | v2.0 | Change |
|-----------|------|------|--------|
| Flash (Code) | ~450KB | ~520KB | +70KB |
| Flash (Config) | 0KB | <10KB | +10KB |
| RAM (Static) | ~25KB | ~28KB | +3KB |
| RAM (Dynamic) | Varies | Varies | Same |

**Verdict:** Minimal overhead, well worth it!

### Tracking Performance
- ✅ No impact on DMX update rate (30 Hz)
- ✅ No impact on tracking calculations (5 Hz)
- ✅ Web server is non-blocking (async)

---

## Breaking Changes

### None!
The v2.0 architecture is **backward compatible**. 

If no `config.json` exists:
1. System creates default config
2. Same fixtures as v1.0 hardcoded version
3. Everything works as before

---

## API Usage Examples

### Get Current Status (JavaScript)
```javascript
fetch('http://192.168.4.1/api/status')
  .then(r => r.json())
  .then(data => {
    console.log('Position:', data.position);
    console.log('Mode:', data.mode);
  });
```

### Add Fixture Programmatically
```javascript
// Get current config
const config = await fetch('/api/config').then(r => r.json());

// Add fixture
config.fixtures.push({
  name: "New Spot",
  dmxAddress: 80,
  profileName: "Robin MegaPointe",
  position: { x: 5.0, y: 10.0, z: 2.5 }
});

// Save
await fetch('/api/config/save', {
  method: 'POST',
  headers: { 'Content-Type': 'application/json' },
  body: JSON.stringify(config)
});
```

### Change Mode
```javascript
// Switch to tracking mode
fetch('/api/mode?mode=0');

// Switch to manual mode
fetch('/api/mode?mode=6');
```

---

## Troubleshooting

### Config Not Loading
**Symptom:** System starts with 0 fixtures

**Solution:**
1. Check serial console: "✓ LittleFS Mounted"
2. If failed, reflash filesystem: `pio run --target uploadfs`
3. Check `data/config.json` exists

### Web Dashboard Blank
**Symptom:** Browser shows nothing

**Solution:**
1. Verify WiFi connection to "U-Track-DMX"
2. Check IP: Should be 192.168.4.1
3. Open browser console for errors
4. Reflash firmware

### Changes Not Saving
**Symptom:** Config resets after reboot

**Solution:**
1. Check LittleFS has free space
2. Verify JSON format (use validator)
3. Check serial console for save errors
4. Try smaller config first

---

## Advanced Configuration

### Custom WiFi Settings
Edit `main.cpp`:
```cpp
void initializeWebServer() {
    WiFi.softAP("YourSSID", "YourPassword");
    // ... rest of code
}
```

### Change Update Rates
Edit `main.cpp`:
```cpp
const unsigned long TRACKING_UPDATE_INTERVAL = 200; // ms (5 Hz)
const unsigned long POSITION_TIMEOUT = 5000; // ms
```

### Increase Config Size
Edit `ConfigManager.h`:
```cpp
static const size_t JSON_BUFFER_SIZE = 16384; // 16KB default
// Increase if you have many fixtures
```

---

## Performance Tuning

### Optimize for Many Fixtures
```cpp
// Reserve vector capacity in setup()
movingHeads.reserve(20); // Pre-allocate for 20 fixtures
```

### Reduce Web Server Load
```javascript
// In HTML, adjust polling rate
setInterval(loadStatus, 2000); // Every 2s instead of 1s
```

---

## Future Roadmap

### v2.1 (Planned)
- [ ] User authentication
- [ ] Multi-universe DMX
- [ ] 3D stage visualizer
- [ ] Movement recording/playback

### v2.2 (Planned)
- [ ] WiFi client mode
- [ ] OTA updates
- [ ] Advanced calibration wizard
- [ ] DMX input monitoring

---

## Support & Resources

- 📖 **Web Dashboard Guide**: See `WEB_DASHBOARD_GUIDE.md`
- 🔧 **Build Guide**: See `BUILD_GUIDE.md`
- 📝 **Quick Start**: See `QUICKSTART.md`
- 🐛 **Issues**: GitHub Issues
- 💬 **Serial Help**: Press 'H' in serial console

---

## Credits

**v2.0 Architecture by:** Sebastian Pfleiderer  
**Web Dashboard:** Single-page app with vanilla JS  
**Backend:** ESPAsyncWebServer + ArduinoJson  
**Storage:** LittleFS (ESP32 flash filesystem)

---

**Last Updated:** February 2026  
**Version:** 2.0.0
