# 🌐 REST API Reference - U-Track DMX v2.0

## Base URL

```
http://192.168.4.1/
```

## Overview

The U-Track DMX Controller provides a RESTful API for programmatic access to configuration, status monitoring, and control. All endpoints return JSON unless otherwise specified.

---

## Endpoints

### 🏠 GET /

**Description:** Serves the main Web Dashboard (HTML)

**Response:** HTML page

**Example:**
```bash
curl http://192.168.4.1/
```

---

### 📊 GET /api/status

**Description:** Get current system status and live data

**Response:**
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

**Fields:**
- `mode` (string): Current operating mode
- `position` (object): UWB position data
  - `x` (float): X coordinate in meters
  - `y` (float): Y coordinate in meters
  - `z` (float): Z coordinate (height) in meters
  - `rmse` (float): Root Mean Square Error (accuracy)
  - `valid` (boolean): Position data is current
- `fixtureCount` (integer): Number of active fixtures
- `uptime` (integer): System uptime in seconds

**Example:**
```bash
curl http://192.168.4.1/api/status
```

**JavaScript:**
```javascript
fetch('/api/status')
  .then(r => r.json())
  .then(data => {
    console.log('Mode:', data.mode);
    console.log('Position:', data.position);
  });
```

**Update Frequency:** Poll at 1-2 Hz recommended

---

### ⚙️ GET /api/config

**Description:** Get complete system configuration

**Response:**
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
      "dimmer": 0,
      "shutter": 0,
      "colorWheel": 0,
      "goboWheel": 0,
      "goboRotation": 0,
      "focus": 34,
      "zoom": 32,
      "control": 0,
      "panMin": 0.0,
      "panMax": 540.0,
      "tiltMin": 0.0,
      "tiltMax": 265.0,
      "tiltHome": 41.5,
      "panHomeOffset": 180.0,
      "zoomMinAngle": 1.8,
      "zoomMaxAngle": 42.0,
      "zoomCalibDist1": 17.0,
      "zoomCalibAngle1": 25.0,
      "focusDMX1": 51,
      "zoomCalibDist2": 6.0,
      "zoomCalibAngle2": 35.0,
      "focusDMX2": 45,
      "invertPan": true,
      "invertTilt": false,
      "invertZoom": true,
      "invertFocus": true,
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

**Example:**
```bash
curl http://192.168.4.1/api/config
```

**JavaScript:**
```javascript
const config = await fetch('/api/config').then(r => r.json());
console.log('Profiles:', config.profiles.length);
console.log('Fixtures:', config.fixtures.length);
```

---

### 💾 POST /api/config/save

**Description:** Save new configuration to LittleFS

**Content-Type:** `application/json`

**Request Body:** Complete configuration object (same structure as GET /api/config)

**Response:** 
```
200 OK - Configuration saved
400 Bad Request - Invalid JSON
500 Internal Server Error - Save failed
```

**Example:**
```bash
curl -X POST http://192.168.4.1/api/config/save \
  -H "Content-Type: application/json" \
  -d @config.json
```

**JavaScript:**
```javascript
const newConfig = {
  version: "1.0",
  profiles: [...],
  fixtures: [...]
};

await fetch('/api/config/save', {
  method: 'POST',
  headers: { 'Content-Type': 'application/json' },
  body: JSON.stringify(newConfig)
});
```

**Notes:**
- Configuration is validated before saving
- Invalid JSON returns 400 error
- Changes take effect immediately
- System does not reboot

---

### 📡 GET /api/profiles

**Description:** Get list of available fixture profiles

**Response:**
```json
[
  {
    "name": "Robin MegaPointe",
    "panCoarse": 1,
    "panFine": 2,
    ...
  },
  {
    "name": "Generic Moving Head",
    "panCoarse": 1,
    "panFine": 2,
    ...
  }
]
```

**Example:**
```bash
curl http://192.168.4.1/api/profiles
```

**JavaScript:**
```javascript
const profiles = await fetch('/api/profiles').then(r => r.json());
profiles.forEach(p => console.log(p.name));
```

---

### 💡 GET /api/fixtures

**Description:** Get list of active fixtures

**Response:**
```json
[
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
```

**Example:**
```bash
curl http://192.168.4.1/api/fixtures
```

**JavaScript:**
```javascript
const fixtures = await fetch('/api/fixtures').then(r => r.json());
console.log(`${fixtures.length} fixtures active`);
```

---

### 🎮 GET /api/mode

**Description:** Change operating mode

**Query Parameters:**
- `mode` (integer, required): Mode number 0-7

**Modes:**
```
0 = UWB_TRACKING
1 = PAN_TEST
2 = TILT_TEST
3 = SHUTTER_DIMMER_TEST
4 = COLOR_TEST
5 = GOBO_TEST
6 = MANUAL
7 = DMX_PASSTHROUGH
```

**Response:**
```
200 OK - Mode changed
400 Bad Request - Invalid mode number
```

**Example:**
```bash
# Switch to tracking mode
curl "http://192.168.4.1/api/mode?mode=0"

# Switch to manual mode
curl "http://192.168.4.1/api/mode?mode=6"
```

**JavaScript:**
```javascript
// Switch to Pan Test
await fetch('/api/mode?mode=1');

// Switch to Tracking
await fetch('/api/mode?mode=0');
```

---

### 🚨 GET /api/emergency

**Description:** Trigger emergency stop (blackout all fixtures)

**Response:**
```
200 OK - Emergency stop activated
```

**Side Effects:**
- All DMX channels set to 0
- Mode changes to MANUAL
- Fixtures stop immediately

**Example:**
```bash
curl http://192.168.4.1/api/emergency
```

**JavaScript:**
```javascript
// Emergency stop
await fetch('/api/emergency');
alert('Emergency stop activated!');
```

**⚠️ Warning:** This immediately cuts output to all fixtures. Use with caution!

---

## Advanced Usage

### Monitoring Position in Real-Time

**Polling Method:**
```javascript
// Poll every second
setInterval(async () => {
  const status = await fetch('/api/status').then(r => r.json());
  
  if (status.position.valid) {
    updatePositionDisplay(status.position);
  } else {
    console.warn('Position data invalid');
  }
}, 1000);
```

**Event-Driven Method:**
```javascript
// More efficient - only update when needed
let lastPosition = null;

setInterval(async () => {
  const status = await fetch('/api/status').then(r => r.json());
  
  if (JSON.stringify(status.position) !== lastPosition) {
    lastPosition = JSON.stringify(status.position);
    updatePositionDisplay(status.position);
  }
}, 500);
```

---

### Adding a Fixture Programmatically

```javascript
async function addFixture(name, dmxAddress, profileName, x, y, z) {
  // Get current config
  const config = await fetch('/api/config').then(r => r.json());
  
  // Add new fixture
  config.fixtures.push({
    name: name,
    dmxAddress: dmxAddress,
    profileName: profileName,
    position: { x, y, z }
  });
  
  // Save
  const response = await fetch('/api/config/save', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(config)
  });
  
  if (response.ok) {
    console.log('Fixture added successfully');
  } else {
    console.error('Failed to add fixture');
  }
}

// Usage
await addFixture("New Spot", 100, "Robin MegaPointe", 5.0, 10.0, 2.5);
```

---

### Deleting a Fixture

```javascript
async function deleteFixture(fixtureName) {
  const config = await fetch('/api/config').then(r => r.json());
  
  // Remove fixture by name
  config.fixtures = config.fixtures.filter(f => f.name !== fixtureName);
  
  await fetch('/api/config/save', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(config)
  });
}

await deleteFixture("Old Fixture");
```

---

### Creating a Custom Profile

```javascript
async function createProfile(name, channels, limits) {
  const config = await fetch('/api/config').then(r => r.json());
  
  config.profiles.push({
    name: name,
    panCoarse: channels.panCoarse,
    panFine: channels.panFine,
    tiltCoarse: channels.tiltCoarse,
    tiltFine: channels.tiltFine,
    zoom: channels.zoom || 0,
    focus: channels.focus || 0,
    dimmer: channels.dimmer || 0,
    shutter: channels.shutter || 0,
    colorWheel: 0,
    goboWheel: 0,
    goboRotation: 0,
    control: 0,
    panMin: 0,
    panMax: limits.panMax,
    tiltMin: 0,
    tiltMax: limits.tiltMax,
    tiltHome: limits.tiltHome,
    panHomeOffset: 0,
    zoomMinAngle: 5,
    zoomMaxAngle: 50,
    zoomCalibDist1: 5,
    zoomCalibAngle1: 25,
    focusDMX1: 127,
    zoomCalibDist2: 20,
    zoomCalibAngle2: 5,
    focusDMX2: 10,
    invertPan: false,
    invertTilt: false,
    invertZoom: false,
    invertFocus: false,
    isHanging: true,
    panDeadZone: 2,
    tiltDeadZone: 2
  });
  
  await fetch('/api/config/save', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(config)
  });
}

// Usage
await createProfile("MAC 250", 
  { panCoarse: 1, panFine: 2, tiltCoarse: 3, tiltFine: 4, zoom: 10 },
  { panMax: 540, tiltMax: 270, tiltHome: 135 }
);
```

---

### Batch Operations

**Add Multiple Fixtures:**
```javascript
async function addMultipleFixtures(fixtures) {
  const config = await fetch('/api/config').then(r => r.json());
  
  fixtures.forEach(f => {
    config.fixtures.push({
      name: f.name,
      dmxAddress: f.dmx,
      profileName: f.profile,
      position: { x: f.x, y: f.y, z: f.z }
    });
  });
  
  await fetch('/api/config/save', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(config)
  });
}

// Usage
await addMultipleFixtures([
  { name: "Spot 1", dmx: 1, profile: "Robin MegaPointe", x: 0, y: 0, z: 2.5 },
  { name: "Spot 2", dmx: 40, profile: "Robin MegaPointe", x: 5, y: 0, z: 2.5 },
  { name: "Spot 3", dmx: 80, profile: "Robin MegaPointe", x: 10, y: 0, z: 2.5 }
]);
```

---

### Update Fixture Position

```javascript
async function updateFixturePosition(fixtureName, x, y, z) {
  const config = await fetch('/api/config').then(r => r.json());
  
  const fixture = config.fixtures.find(f => f.name === fixtureName);
  if (fixture) {
    fixture.position.x = x;
    fixture.position.y = y;
    fixture.position.z = z;
    
    await fetch('/api/config/save', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(config)
    });
  }
}

await updateFixturePosition("Front Spot", 7.5, 24.5, 0.4);
```

---

## Error Handling

### HTTP Status Codes

| Code | Meaning | Typical Cause |
|------|---------|---------------|
| 200 | OK | Request successful |
| 400 | Bad Request | Invalid parameters or JSON |
| 404 | Not Found | Endpoint doesn't exist |
| 500 | Internal Server Error | Server-side error (check serial) |

### Example Error Handling

```javascript
async function safeAPICall(url, options = {}) {
  try {
    const response = await fetch(url, options);
    
    if (!response.ok) {
      throw new Error(`HTTP ${response.status}: ${response.statusText}`);
    }
    
    return await response.json();
  } catch (error) {
    console.error('API Error:', error);
    alert('API request failed. Check console for details.');
    return null;
  }
}

// Usage
const status = await safeAPICall('/api/status');
if (status) {
  console.log('Position:', status.position);
}
```

---

## Rate Limiting

**Recommendations:**
- `/api/status`: Poll at 1-2 Hz maximum
- `/api/config`: Read once on page load
- `/api/config/save`: Only when user changes config
- `/api/mode`: Throttle to 1 call per second

**Example Throttling:**
```javascript
let lastModeChange = 0;

function changeMode(mode) {
  const now = Date.now();
  if (now - lastModeChange < 1000) {
    console.warn('Mode change throttled');
    return;
  }
  
  fetch(`/api/mode?mode=${mode}`);
  lastModeChange = now;
}
```

---

## WebSocket (Future)

**Note:** Current version uses polling. Future versions may implement WebSocket for real-time push updates.

**Planned API:**
```javascript
// Future implementation
const ws = new WebSocket('ws://192.168.4.1/ws');
ws.onmessage = (event) => {
  const data = JSON.parse(event.data);
  if (data.type === 'position') {
    updatePosition(data.position);
  }
};
```

---

## Cross-Origin Requests (CORS)

**Status:** CORS is **not enabled** by default.

**Workaround for external apps:**
- Access API from same network only
- Or modify `WebServerManager.cpp` to add CORS headers

**Example CORS Header (if needed):**
```cpp
// In WebServerManager.cpp
server.on("/api/status", HTTP_GET, [this](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse(200, "application/json", jsonString);
    response->addHeader("Access-Control-Allow-Origin", "*");
    request->send(response);
});
```

---

## Security Considerations

### Current Status
- ⚠️ **No Authentication**: API is open to all WiFi clients
- ⚠️ **No HTTPS**: Data transmitted in plain text
- ⚠️ **No Rate Limiting**: Subject to abuse

### Recommendations
1. **Change WiFi Password**: Edit in `main.cpp`
2. **Isolate Network**: Use dedicated WiFi for controller
3. **Physical Security**: Secure ESP32 in locked enclosure
4. **Operator Training**: Limit access to trained personnel

### Future Enhancements
- User authentication (username/password)
- API keys for programmatic access
- HTTPS support
- Request rate limiting

---

## Testing API with cURL

### Get Status
```bash
curl -i http://192.168.4.1/api/status
```

### Get Config
```bash
curl http://192.168.4.1/api/config | jq .
```

### Save Config
```bash
curl -X POST http://192.168.4.1/api/config/save \
  -H "Content-Type: application/json" \
  -d @new-config.json
```

### Change Mode
```bash
curl "http://192.168.4.1/api/mode?mode=0"
```

### Emergency Stop
```bash
curl http://192.168.4.1/api/emergency
```

---

## Python Client Example

```python
import requests
import time

class UTrackAPI:
    def __init__(self, base_url="http://192.168.4.1"):
        self.base_url = base_url
    
    def get_status(self):
        return requests.get(f"{self.base_url}/api/status").json()
    
    def get_config(self):
        return requests.get(f"{self.base_url}/api/config").json()
    
    def save_config(self, config):
        return requests.post(
            f"{self.base_url}/api/config/save",
            json=config
        )
    
    def set_mode(self, mode):
        return requests.get(f"{self.base_url}/api/mode?mode={mode}")
    
    def emergency_stop(self):
        return requests.get(f"{self.base_url}/api/emergency")
    
    def add_fixture(self, name, dmx, profile, x, y, z):
        config = self.get_config()
        config['fixtures'].append({
            'name': name,
            'dmxAddress': dmx,
            'profileName': profile,
            'position': {'x': x, 'y': y, 'z': z}
        })
        return self.save_config(config)

# Usage
api = UTrackAPI()

# Monitor position
while True:
    status = api.get_status()
    if status['position']['valid']:
        print(f"Position: {status['position']}")
    time.sleep(1)
```

---

## Node.js Client Example

```javascript
const axios = require('axios');

class UTrackAPI {
  constructor(baseURL = 'http://192.168.4.1') {
    this.client = axios.create({ baseURL });
  }
  
  async getStatus() {
    const { data } = await this.client.get('/api/status');
    return data;
  }
  
  async getConfig() {
    const { data } = await this.client.get('/api/config');
    return data;
  }
  
  async saveConfig(config) {
    await this.client.post('/api/config/save', config);
  }
  
  async setMode(mode) {
    await this.client.get(`/api/mode?mode=${mode}`);
  }
  
  async emergencyStop() {
    await this.client.get('/api/emergency');
  }
  
  async addFixture(name, dmx, profile, x, y, z) {
    const config = await this.getConfig();
    config.fixtures.push({
      name, dmxAddress: dmx, profileName: profile,
      position: { x, y, z }
    });
    await this.saveConfig(config);
  }
}

// Usage
const api = new UTrackAPI();

// Monitor position
setInterval(async () => {
  const status = await api.getStatus();
  if (status.position.valid) {
    console.log('Position:', status.position);
  }
}, 1000);
```

---

## Support

For API questions or issues:
- 📖 See documentation: `WEB_DASHBOARD_GUIDE.md`
- 🐛 Report bugs on GitHub
- 💬 Serial console: Press 'H' for help

---

**Last Updated:** February 2026  
**API Version:** 2.0.0
