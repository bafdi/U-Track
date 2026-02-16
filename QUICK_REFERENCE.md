# U-Track Web Dashboard - Quick Reference

## 🌐 Accessing the Dashboard

### Via Access Point (Default)
1. Connect to WiFi: **U-Track-DMX**
2. Password: **utrack123**
3. Open browser: **http://192.168.4.1**

### Via External WiFi (After Configuration)
1. Configure WiFi in Settings tab
2. Restart device
3. Check serial monitor for IP address
4. Access via that IP address

## 📑 Tabs Overview

### 📊 Dashboard
- Live position data (X, Y, Z, RMSE)
- Operating mode controls
- Active fixtures list
- System information

### 🗺️ Stage Map
**Controls:**
- Set stage dimensions (width/depth in meters)
- 🔍+ Zoom In
- 🔍- Zoom Out
- 📐 Fit to Screen

**Display:**
- 🎯 Orange = Tracked target position
- 💡 Green = Fixture locations
- Grey grid = 5m intervals

**Tips:**
- Zoom in for labels and coordinates
- Zoom out for overview
- Settings auto-save to browser

### 💡 Fixtures
- View all configured fixtures
- ✏️ **Edit** - Modify fixture settings
- 🗑️ **Delete** - Remove fixture
- ➕ **Add** - Create new fixture

**Edit Features:**
- Update name, DMX address, profile
- Adjust position (X, Y, Z)
- Changes reflect immediately on stage map

### ⚙️ Profiles
- Manage fixture profiles
- View channel mappings
- Create custom profiles
- Delete unused profiles

### 🎛️ Manual DMX
**Usage:**
1. Select a fixture from dropdown
2. Use vertical sliders to control channels
3. Values update in real-time

**Available Controls:**
- Pan Coarse/Fine
- Tilt Coarse/Fine
- Zoom
- Focus
- Dimmer
- Shutter

**Note:** Channel numbers shown are absolute DMX addresses

### 🔧 Settings
**WiFi Configuration:**
- Enter external WiFi SSID and password
- Device connects on next restart
- Both AP and Station mode active simultaneously

**Configuration Backup:**
- 📥 Download - Save config as JSON
- 📤 Upload - Restore config from file

## 🎮 Operating Modes

| Mode | Number | Description |
|------|--------|-------------|
| 🎯 Tracking | 0 | UWB position tracking active |
| ↔️ Pan Test | 1 | Pan movement test |
| ↕️ Tilt Test | 2 | Tilt movement test |
| 💡 Dimmer Test | 3 | Shutter/dimmer test |
| 🎨 Color Test | 4 | Color wheel test |
| 🔄 Gobo Test | 5 | Gobo wheel test |
| ✋ Manual | 6 | Manual DMX control mode |
| 🔁 Passthrough | 7 | DMX input passthrough |

## ⚠️ Emergency Controls

### Emergency Stop Button
- Always visible (top-right)
- Blackouts all fixtures
- Switches to Manual mode
- Requires confirmation

## 💾 Data Persistence

### Browser Storage (localStorage)
- Stage dimensions
- Zoom level
- Automatically saved

### Device Flash (Preferences)
- WiFi credentials
- Saved permanently
- Survives reboots

### LittleFS Configuration
- Fixture profiles
- Active fixtures
- System settings

## 🔧 Troubleshooting

### Can't Access Dashboard
1. Verify WiFi connection to U-Track-DMX
2. Try http://192.168.4.1
3. Check device is powered on
4. Clear browser cache

### Stage Map Not Updating
1. Check "Position Valid" on Dashboard
2. Verify UWB system is sending data
3. Refresh browser tab
4. Check serial monitor for errors

### Manual DMX Not Working
1. Ensure fixture is selected
2. Check operating mode (works in all modes)
3. Verify DMX addresses don't overlap
4. Check physical DMX connections

### WiFi Connection Failed
1. Verify SSID and password
2. Check WiFi signal strength
3. Ensure 2.4GHz WiFi (ESP32 doesn't support 5GHz)
4. Try shorter password (some routers have limits)

### Fixtures Not Appearing on Map
1. Check fixture positions are within stage bounds
2. Verify fixtures are saved in configuration
3. Zoom out to see entire stage
4. Refresh page

## 📱 Mobile Access

### Optimizations
- Responsive layout adapts to screen size
- Touch-friendly buttons
- Scrollable modals
- Large tap targets

### Best Practices
- Use landscape orientation for stage map
- Zoom with buttons (not pinch)
- Scroll within modals for long forms

## ⌨️ Keyboard Shortcuts
*Currently none - potential future enhancement*

## 🔐 Security Notes

### Current State
- ⚠️ No authentication
- ⚠️ Open WiFi AP (set password in code)
- ⚠️ Passwords stored in plain text

### Recommendations for Production
- Change default AP password in code
- Use strong passwords
- Consider adding HTTP basic auth
- Keep device on isolated network
- Regular firmware updates

## 🛠️ API Reference

### GET /api/status
Returns live system status
```json
{
  "position": {"x": 5.2, "y": 3.1, "z": 1.5, "rmse": 0.012, "valid": true},
  "mode": "UWB-TRACKING",
  "uptime": 3600,
  "fixtureCount": 2
}
```

### GET /api/config
Returns full configuration (profiles + fixtures)

### POST /api/config/save
Save complete configuration (JSON body)

### GET /api/mode?mode=0
Set operating mode (0-7)

### GET /api/dmx/set?ch=1&val=255
Set DMX channel value (manual control)

### POST /api/wifi/config
Configure external WiFi
```json
{
  "ssid": "YourNetwork",
  "password": "YourPassword"
}
```

### GET /api/emergency
Trigger emergency stop

## 📊 Performance Tips

1. **Reduce Update Frequency**: Lower refresh rate for battery devices
2. **Limit Active Tabs**: Close unused browser tabs
3. **Clear Old Configs**: Delete unused profiles/fixtures
4. **Use Wired Connection**: For critical shows, use Ethernet (if available)
5. **Monitor Serial Output**: Watch for errors and warnings

## 🎯 Pro Tips

1. **Test Before Show**: Always test all fixtures before live use
2. **Backup Config**: Download config before major changes
3. **Label Fixtures Clearly**: Use descriptive names (e.g., "Front Left Spot")
4. **Use Consistent Positions**: Measure accurately for best tracking
5. **Group by Type**: Keep similar fixtures together in the list
6. **Document Your Setup**: Take photos of physical layout matching stage map
7. **Keep Spare Config**: Email yourself backup configs
8. **Update During Downtime**: Don't make changes during active performance
9. **Use Manual Mode for Focus**: Perfect for fixture alignment
10. **Monitor Position RMSE**: Lower = better accuracy (< 0.1m ideal)

## 📞 Support

Check the following files for more info:
- `README.md` - General system overview
- `IMPLEMENTATION_SUMMARY.md` - Technical details
- `WEB_DASHBOARD_GUIDE.md` - Detailed web interface guide
- `CHANGELOG_WEB_V2.md` - Latest updates and features

Serial Monitor Output (115200 baud):
- System status
- Error messages
- WiFi connection info
- Configuration changes

---

**Version**: 2.0  
**Last Updated**: February 2026  
**Compatibility**: ESP32, Modern Browsers (Chrome, Firefox, Safari, Edge)
