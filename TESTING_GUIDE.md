# 🧪 Testing & Validation Guide

## Pre-Deployment Testing Checklist

### 1. Firmware Upload Test
```bash
# Clean build
pio run --target clean

# Build and upload
pio run --target upload

# Expected Serial Output:
# ✓ LittleFS Mounted
# ✓ Loaded X profiles and Y fixtures from config
# ✓ DMX initialisiert
# ✓ WiFi Access Point Started
# ✓ Web Server started on port 80
# ✓✓✓ System Ready ✓✓✓
```

**Pass Criteria:**
- [ ] Firmware uploads without errors
- [ ] Serial console shows all "✓" messages
- [ ] No error messages in serial output

---

### 2. WiFi Connectivity Test

**Steps:**
1. Scan for WiFi networks
2. Find "U-Track-DMX"
3. Connect with password: `utrack123`
4. Check assigned IP (should be 192.168.4.x)

**Pass Criteria:**
- [ ] Network visible
- [ ] Connection successful
- [ ] Valid IP assigned

---

### 3. Web Dashboard Access Test

**URL:** `http://192.168.4.1/`

**Expected Elements:**
- [ ] Header with "🎭 U-Track DMX Controller"
- [ ] Five tabs: Dashboard, Fixtures, Profiles, Settings
- [ ] Emergency Stop button (top-right)
- [ ] Live position display (4 boxes: X, Y, Z, RMSE)
- [ ] Operating mode selector (8 buttons)

**Browser Console:**
- [ ] No JavaScript errors
- [ ] Network requests successful (200 OK)

---

### 4. Configuration Load Test

**Verify Default Config:**

Navigate to **Profiles** tab:
- [ ] "Robin MegaPointe" profile exists
- [ ] Shows channel mappings (Pan: 1/2, Tilt: 3/4)
- [ ] Physical limits displayed

Navigate to **Fixtures** tab:
- [ ] Default fixtures loaded (MH4, MH5)
- [ ] DMX addresses shown (1, 40)
- [ ] Positions displayed

**Serial Console Check:**
Type `C` to view configuration:
```
=== CONFIGURATION ===
Fixture Profiles (1):
  - Robin MegaPointe (Pan:1-2 Tilt:3-4)

Active Fixtures (2):
  - MH4 (MegaPointe) @ DMX 1 [Robin MegaPointe] Pos:(7.95,24.84,0.35)
  - MH5 (MegaPointe) @ DMX 40 [Robin MegaPointe] Pos:(3.30,24.23,0.25)
```

---

### 5. Add Fixture Test

**Steps:**
1. Click "Fixtures" tab
2. Click "➕ Add Fixture"
3. Fill form:
   - Name: `Test Fixture`
   - DMX Address: `100`
   - Profile: `Robin MegaPointe`
   - Position: X=5.0, Y=10.0, Z=2.5
4. Click "✓ Add"

**Pass Criteria:**
- [ ] Modal closes
- [ ] New fixture appears in list
- [ ] Dashboard shows 3 fixtures
- [ ] Serial console confirms save: `✓ Saved 1 profiles and 3 fixtures to config`

**Verification:**
```bash
# Reboot ESP32 (press EN button)
# Check serial: Should load 3 fixtures
```

---

### 6. Add Profile Test

**Steps:**
1. Click "Profiles" tab
2. Click "➕ Add Profile"
3. Fill form:
   - Name: `Test Profile`
   - Pan Coarse: 1
   - Pan Fine: 2
   - Tilt Coarse: 3
   - Tilt Fine: 4
   - Pan Range: 540
   - Tilt Range: 270
   - Tilt Home: 135
4. Click "✓ Add"

**Pass Criteria:**
- [ ] Modal closes
- [ ] New profile appears in list
- [ ] Can select in fixture creation modal
- [ ] Persists after reboot

---

### 7. Delete Operations Test

**Delete Fixture:**
1. Navigate to Fixtures tab
2. Click 🗑️ on "Test Fixture"
3. Confirm deletion

**Pass Criteria:**
- [ ] Confirmation dialog appears
- [ ] Fixture removed from list
- [ ] Fixture count updates
- [ ] Serial shows save confirmation

**Delete Profile:**
1. Navigate to Profiles tab
2. Click 🗑️ on "Test Profile"
3. Confirm deletion

**Pass Criteria:**
- [ ] Warning about fixtures using it
- [ ] Profile removed after confirmation

---

### 8. Configuration Export/Import Test

**Export:**
1. Navigate to Settings tab
2. Click "📥 Download Config"
3. Save file as `backup-config.json`

**Pass Criteria:**
- [ ] File downloads successfully
- [ ] JSON is valid (check with validator)
- [ ] Contains all profiles and fixtures

**Modify & Import:**
1. Edit downloaded JSON (change a fixture name)
2. Click "📤 Upload Config"
3. Select modified file

**Pass Criteria:**
- [ ] Upload successful
- [ ] Changes reflected in dashboard
- [ ] Serial confirms save

---

### 9. Operating Mode Test

**Test Each Mode:**

| Mode | Button | Expected Behavior |
|------|--------|-------------------|
| 0 | 🎯 Tracking | "UWB-TRACKING" displayed, button highlighted |
| 1 | ↔️ Pan | "PAN-TEST" displayed |
| 2 | ↕️ Tilt | "TILT-TEST" displayed |
| 3 | 💡 Dimmer | "SHUTTER-DIMMER" displayed |
| 4 | 🎨 Color | "COLOR-TEST" displayed |
| 5 | 🔄 Gobo | "GOBO-TEST" displayed |
| 6 | ✋ Manual | "MANUAL" displayed |
| 7 | 🔁 Pass | "DMX-PASSTHROUGH" displayed |

**Pass Criteria:**
- [ ] Each mode activates correctly
- [ ] Current mode badge updates
- [ ] Active button highlighted
- [ ] Serial console confirms mode change

---

### 10. Live Position Data Test

**Without UWB Tag (Simulated):**
- [ ] Position shows 0.00 for X, Y, Z
- [ ] RMSE shows 0.000
- [ ] "Position Valid" shows "No"

**With UWB Tag (Real):**
Send test position via ESP-NOW:
```cpp
PositionData testPos = {5.5, 10.2, 1.5, 0.025, true};
esp_now_send(MAC, (uint8_t*)&testPos, sizeof(testPos));
```

**Pass Criteria:**
- [ ] Dashboard updates within 1 second
- [ ] Position values match sent data
- [ ] "Position Valid" shows "Yes"
- [ ] Serial console logs position

---

### 11. Emergency Stop Test

**Steps:**
1. Set mode to "UWB Tracking"
2. Wait for fixtures to move
3. Click "⚠️ EMERGENCY STOP"
4. Confirm dialog

**Pass Criteria:**
- [ ] Confirmation dialog appears
- [ ] All DMX channels set to 0
- [ ] Fixtures stop moving immediately
- [ ] Mode changes to MANUAL
- [ ] Serial logs: `🛑 EMERGENCY STOP triggered via Web UI`

---

### 12. Serial Console Commands Test

**Type Each Command:**

| Key | Expected Output |
|-----|----------------|
| `H` or `?` | Help menu with all commands |
| `S` | System status (mode, fixtures, position) |
| `C` | Configuration details (profiles, fixtures) |
| `0-7` | Mode change confirmation |
| `M` | Manual control prompt |

**Pass Criteria:**
- [ ] All commands respond correctly
- [ ] No crashes or errors
- [ ] Output formatted properly

---

### 13. DMX Output Test

**Equipment Needed:**
- DMX tester OR
- Moving head fixture

**Test Without Fixtures:**
1. Connect DMX analyzer to output
2. Set mode to "Pan Test"
3. Observe channels 1-4 (if using default config)

**Expected:**
- [ ] Channels 1-2 sweep through 0-255
- [ ] DMX signal stable, no dropouts
- [ ] Update rate ~30 Hz

**Test With Fixtures:**
1. Connect moving head at DMX 1
2. Set mode to "Tilt Test"
3. Watch fixture movement

**Pass Criteria:**
- [ ] Fixture responds to commands
- [ ] Movement smooth, no jitter
- [ ] Fixture stops when mode changed

---

### 14. Tracking Accuracy Test

**Equipment:**
- UWB positioning system
- Tagged object
- Measuring tape

**Steps:**
1. Place fixture at known position (e.g., X=0, Y=0, Z=2.5)
2. Update config with exact position
3. Place UWB tag at test point (e.g., X=5, Y=5, Z=1)
4. Measure actual beam center
5. Compare to tag position

**Pass Criteria:**
- [ ] Pan angle calculated correctly (±2°)
- [ ] Tilt angle calculated correctly (±2°)
- [ ] Beam center within 20cm of tag
- [ ] Tracking smooth during movement

---

### 15. Stress Test

**Many Fixtures:**
1. Add 10+ fixtures via Web GUI
2. Set all to tracking mode
3. Move UWB tag rapidly

**Pass Criteria:**
- [ ] Web dashboard remains responsive
- [ ] DMX output stable
- [ ] No crashes or resets
- [ ] Position updates maintain 5 Hz

**Rapid Configuration Changes:**
1. Add 5 fixtures quickly
2. Delete 3 fixtures
3. Edit positions multiple times
4. Download/upload config

**Pass Criteria:**
- [ ] No data corruption
- [ ] Config saves successfully each time
- [ ] System remains stable

---

### 16. Power Cycle Test

**Steps:**
1. Configure system (add fixtures, profiles)
2. Power off ESP32
3. Wait 10 seconds
4. Power on ESP32
5. Check configuration

**Pass Criteria:**
- [ ] System boots successfully
- [ ] All fixtures loaded from config
- [ ] All profiles present
- [ ] Web dashboard accessible
- [ ] No data loss

---

### 17. Network Stability Test

**Long-term Connection:**
1. Connect to WiFi
2. Keep browser open for 1 hour
3. Monitor status updates

**Pass Criteria:**
- [ ] Connection remains stable
- [ ] Status updates every second
- [ ] No disconnections
- [ ] No memory leaks (check serial)

---

### 18. Browser Compatibility Test

**Test Browsers:**
- [ ] Chrome/Chromium (Desktop)
- [ ] Firefox (Desktop)
- [ ] Safari (Desktop/iOS)
- [ ] Edge (Desktop)
- [ ] Chrome (Android)

**Pass Criteria:**
- [ ] All tabs render correctly
- [ ] All buttons functional
- [ ] Modals display properly
- [ ] No console errors

---

### 19. Error Handling Test

**Invalid JSON Upload:**
1. Create malformed JSON file
2. Attempt to upload

**Expected:**
- [ ] Error message displayed
- [ ] System remains stable
- [ ] Previous config unchanged

**Out-of-Range DMX:**
1. Try to set DMX address to 600
2. Submit form

**Expected:**
- [ ] Form validation prevents
- [ ] Error message shown

**Duplicate Names:**
1. Add fixture with existing name
2. Save configuration

**Expected:**
- [ ] Allowed (names are identifiers, not unique keys)
- [ ] Both fixtures work independently

---

### 20. Performance Metrics

**Measure:**
```
Metric                Target       Actual      Pass/Fail
-----------------------------------------------------
Boot time            < 5 sec      _____       ☐
Web page load        < 2 sec      _____       ☐
Config save          < 500 ms     _____       ☐
Mode switch          < 100 ms     _____       ☐
DMX update rate      30 Hz        _____       ☐
Position update      5 Hz         _____       ☐
API response         < 200 ms     _____       ☐
Memory free (RAM)    > 50 KB      _____       ☐
Memory free (Flash)  > 500 KB     _____       ☐
```

---

## Regression Testing

After each firmware update, run:

**Quick Test (5 minutes):**
- [ ] Test 1: Firmware Upload
- [ ] Test 2: WiFi Connectivity
- [ ] Test 3: Web Dashboard Access
- [ ] Test 9: Operating Mode
- [ ] Test 11: Emergency Stop

**Full Test (30 minutes):**
- [ ] All tests 1-20

---

## Production Readiness Checklist

Before deploying to live event:

### Security
- [ ] WiFi password changed from default
- [ ] Web interface tested on production network
- [ ] Emergency stop procedure documented

### Configuration
- [ ] All fixture positions measured and verified
- [ ] All profiles tested with actual fixtures
- [ ] Config backed up to safe location
- [ ] Venue documentation created

### Testing
- [ ] All 20 tests passed
- [ ] Stress test completed (1+ hour runtime)
- [ ] Tracking accuracy verified on stage
- [ ] Operators trained on Web interface

### Documentation
- [ ] WEB_DASHBOARD_GUIDE.md reviewed
- [ ] QUICKSTART.md created for venue
- [ ] Emergency procedures posted
- [ ] Support contact information available

---

## Known Issues & Workarounds

### Issue: Config Won't Save
**Symptom:** "Save failed" alert

**Workaround:**
1. Check LittleFS space: Serial shows "Saved X profiles"
2. Try smaller config (remove some fixtures)
3. Reflash filesystem: `pio run --target uploadfs`

### Issue: Web Page Slow
**Symptom:** Dashboard takes >5 seconds to load

**Workaround:**
1. Reduce status update rate (edit HTML, change 1000 to 2000 ms)
2. Disable browser extensions
3. Clear browser cache

### Issue: Position Not Updating
**Symptom:** Dashboard shows stale position

**Workaround:**
1. Check UWB tag is transmitting (serial console)
2. Verify ESP-NOW initialization
3. Check `POSITION_TIMEOUT` hasn't expired

---

## Support Logs

When reporting issues, include:

```
1. Firmware version: [from serial console]
2. Browser: [Chrome/Firefox/etc + version]
3. Config size: [number of profiles/fixtures]
4. Serial console output: [last 50 lines]
5. Screenshot of error: [if applicable]
6. Steps to reproduce: [detailed]
```

---

**Last Updated:** February 2026  
**Version:** 2.0.0
