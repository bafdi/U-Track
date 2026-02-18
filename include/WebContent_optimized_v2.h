#pragma once

// ============================================================================
// U-TRACK DMX CONTROLLER - OPTIMIZED WEB DASHBOARD
// Removed: Beam visualization, Complex login system
// Simplified: CSS, Login (single password only)
// ============================================================================

const char HTML_DASHBOARD[] PROGMEM = R"===(
<!DOCTYPE html>
<html><head><meta charset="UTF-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>U-Track DMX v2.0</title>
<style>
*{margin:0;padding:0;box-sizing:border-box}
body{font-family:system-ui,sans-serif;background:#0f0f0f;color:#e8e8e8;min-height:100vh}
.container{max-width:1800px;margin:0 auto;padding:20px}
header{background:#2b2b2b;padding:20px 30px;border-radius:2px;margin-bottom:20px;border-left:4px solid #ff8c42}
h1{color:#ff8c42;font-size:2em;font-weight:700;margin-bottom:8px}
.subtitle{color:#b0b0b0;font-size:0.95em;display:flex;align-items:center;gap:10px}
.status-badge{display:inline-block;padding:4px 12px;border-radius:2px;font-size:0.8em;font-weight:700;background:#4caf50;color:#0f0f0f}
.emergency-controls{position:fixed;top:20px;right:20px;z-index:1000}
.btn-emergency{background:#ff1744;color:#fff;border:2px solid #ff1744;padding:14px 28px;border-radius:2px;font-size:15px;font-weight:700;cursor:pointer;transition:all 0.2s}
.btn-emergency:hover{background:transparent;color:#ff1744}
.tabs{display:flex;gap:0;margin-bottom:20px;background:#1a1a1a;border:1px solid #333}
.tab-btn{flex:1;padding:14px 20px;border:none;background:#1a1a1a;color:#808080;border-right:1px solid #333;cursor:pointer;transition:all 0.2s;font-size:13px;font-weight:600}
.tab-btn:hover{background:#2b2b2b;color:#ff8c42}
.tab-btn.active{background:#ff8c42;color:#0f0f0f;font-weight:700}
.tab-content{display:none}
.tab-content.active{display:block}
.card{background:#2b2b2b;border-radius:2px;padding:20px;margin-bottom:15px;border-left:3px solid #ff8c42}
.card-title{font-size:1.3em;margin-bottom:15px;color:#ff8c42;font-weight:700;border-bottom:1px solid #333;padding-bottom:8px;display:flex;align-items:center;gap:10px}
.grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(300px,1fr));gap:15px}
.grid-2{display:grid;grid-template-columns:1fr 1fr;gap:15px}
.position-display{display:grid;grid-template-columns:repeat(4,1fr);gap:12px;margin-top:12px}
.position-item{background:#1a1a1a;padding:12px;border-radius:2px;text-align:center;border:1px solid #333}
.position-label{font-size:0.75em;color:#808080;margin-bottom:4px}
.position-value{font-size:2em;font-weight:700;color:#ff8c42}
.position-unit{font-size:0.75em;color:#666}
.fixture-list{display:flex;flex-direction:column;gap:8px}
.fixture-item{background:#1a1a1a;padding:15px;border-radius:2px;display:flex;justify-content:space-between;align-items:center;border:1px solid #333}
.fixture-info{flex:1}
.fixture-name{font-size:1.1em;font-weight:700;color:#fff;margin-bottom:4px}
.fixture-details{font-size:0.85em;color:#808080}
.fixture-actions{display:flex;gap:8px}
.btn{padding:8px 16px;border:2px solid;border-radius:2px;cursor:pointer;font-size:13px;font-weight:700;transition:all 0.2s}
.btn-primary{background:#ff8c42;color:#0f0f0f;border-color:#ff8c42}
.btn-primary:hover{background:transparent;color:#ff8c42}
.btn-success{background:#4caf50;color:#0f0f0f;border-color:#4caf50}
.btn-success:hover{background:transparent;color:#4caf50}
.btn-danger{background:#ff1744;color:#fff;border-color:#ff1744}
.btn-danger:hover{background:transparent;color:#ff1744}
.btn-secondary{background:transparent;color:#808080;border-color:#555}
.btn-secondary:hover{border-color:#ff8c42;color:#ff8c42}
.btn-small{padding:6px 12px;font-size:11px}
.form-group{margin-bottom:15px}
.form-label{display:block;margin-bottom:6px;color:#b0b0b0;font-size:0.85em;font-weight:600}
.form-input,.form-select{width:100%;padding:10px 12px;background:#1a1a1a;border:1px solid #333;border-radius:2px;color:#fff;font-size:13px}
.form-input:focus,.form-select:focus{outline:none;border-color:#ff8c42}
.form-checkbox{margin-right:8px;accent-color:#ff8c42}
.form-row{display:grid;grid-template-columns:repeat(auto-fit,minmax(200px,1fr));gap:12px}
.modal{display:none;position:fixed;top:0;left:0;width:100%;height:100%;background:rgba(0,0,0,0.9);z-index:2000;overflow-y:auto}
.modal.active{display:flex;align-items:center;justify-content:center}
.modal-content{background:#2b2b2b;border-radius:2px;padding:25px;max-width:900px;width:90%;max-height:90vh;overflow-y:auto;border:2px solid #ff8c42}
.modal-header{display:flex;justify-content:space-between;align-items:center;margin-bottom:20px;border-bottom:1px solid #333;padding-bottom:12px}
.modal-title{font-size:1.5em;color:#ff8c42;font-weight:700}
.modal-close{background:transparent;border:2px solid #808080;color:#808080;font-size:1.5em;cursor:pointer;width:35px;height:35px;border-radius:2px}
.modal-close:hover{background:#ff1744;border-color:#ff1744;color:#fff}
.mode-controls{display:grid;grid-template-columns:repeat(auto-fit,minmax(140px,1fr));gap:8px;margin-top:12px}
.mode-btn{padding:12px;background:#1a1a1a;border:2px solid #333;border-radius:2px;color:#808080;cursor:pointer;font-weight:700;text-align:center;font-size:12px;transition:all 0.2s}
.mode-btn:hover{border-color:#ff8c42;color:#ff8c42}
.mode-btn.active{background:#ff8c42;border-color:#ff8c42;color:#0f0f0f}
.profile-list{display:grid;gap:12px;margin-top:15px}
.profile-card{background:#1a1a1a;padding:15px;border-radius:2px;border:1px solid #333}
.profile-header{display:flex;justify-content:space-between;align-items:center;margin-bottom:12px}
.profile-name{font-size:1.2em;font-weight:700;color:#fff}
.channel-grid{display:grid;grid-template-columns:repeat(auto-fill,minmax(110px,1fr));gap:8px;margin-top:12px}
.channel-item{background:#0f0f0f;padding:8px;border-radius:2px;text-align:center;border:1px solid #333}
.channel-label{font-size:0.7em;color:#808080;margin-bottom:3px}
.channel-value{font-size:1.1em;font-weight:700;color:#ff8c42}
.stage-container{position:relative;width:100%;background:#0f0f0f;border:2px solid #333;border-radius:2px;overflow:hidden}
.stage-canvas{width:100%;display:block;cursor:crosshair}
.stage-controls{display:flex;gap:8px;margin-bottom:12px;align-items:center;flex-wrap:wrap}
.zoom-btn{padding:8px 14px;background:#1a1a1a;border:2px solid #333;border-radius:2px;color:#808080;cursor:pointer;font-weight:700;font-size:12px;transition:all 0.2s}
.zoom-btn:hover{border-color:#ff8c42;color:#ff8c42}
.zoom-level{color:#808080;font-size:0.85em;font-weight:700;padding:8px 12px;background:#1a1a1a;border:1px solid #333;border-radius:2px}
.stage-legend{margin-top:12px;display:flex;gap:15px;flex-wrap:wrap;justify-content:center}
.legend-item{display:flex;align-items:center;gap:6px;color:#808080;font-size:0.85em;font-weight:600}
.legend-icon{width:16px;height:16px;border-radius:2px;border:1px solid #333}
.dmx-control-panel{display:grid;grid-template-columns:repeat(auto-fill,minmax(70px,1fr));gap:8px;margin-top:12px}
.dmx-channel{background:#1a1a1a;padding:8px;border-radius:2px;text-align:center;border:1px solid #333}
.dmx-channel-label{font-size:0.7em;color:#808080;margin-bottom:4px;font-weight:600}
.dmx-channel-value{font-size:1.1em;font-weight:700;color:#ff8c42;margin:4px 0}
.dmx-slider{width:100%;height:90px;writing-mode:bt-lr;-webkit-appearance:slider-vertical;background:#0f0f0f;outline:none;border:1px solid #333;border-radius:2px}
.dmx-slider::-webkit-slider-thumb{-webkit-appearance:none;width:100%;height:12px;background:#ff8c42;cursor:pointer;border-radius:2px}
.dmx-slider::-moz-range-thumb{width:100%;height:12px;background:#ff8c42;cursor:pointer;border-radius:2px;border:none}
.manual-fixture-select{margin-bottom:12px}
.fixture-control-group{margin-bottom:20px;padding:12px;background:#1a1a1a;border-radius:2px;border:1px solid #333}
.fixture-control-group h3{color:#ff8c42;margin:0 0 12px 0;font-size:1em;font-weight:700}
.fixture-copy-btn{background:#4a9eff;border-color:#4a9eff;margin-left:5px}
.fixture-copy-btn:hover{background:transparent;color:#4a9eff}
.dmx-monitor{display:grid;grid-template-columns:repeat(32,1fr);gap:2px;padding:8px;background:#1a1a1a;border-radius:2px;max-height:280px;overflow-y:auto;border:1px solid #333}
.dmx-channel-num{font-size:0.65em;color:#666;margin-bottom:2px;font-weight:700}
.dmx-bar-container{flex:1;display:flex;flex-direction:column;justify-content:flex-end;background:#000;border-radius:2px;overflow:hidden;border:1px solid #222}
.dmx-bar{width:100%;background:linear-gradient(to top,#4caf50 0%,#ff8c42 50%,#ff1744 100%);transition:height 0.05s;opacity:0.3}
.login-overlay{position:fixed;top:0;left:0;width:100%;height:100%;background:rgba(0,0,0,0.95);z-index:9999;display:none;align-items:center;justify-content:center}
.login-overlay.active{display:flex}
.login-box{background:#2b2b2b;border-radius:2px;padding:40px;max-width:400px;width:90%;border:3px solid #ff8c42;text-align:center}
.login-title{font-size:2em;color:#ff8c42;margin-bottom:30px;font-weight:700}
.login-input{width:100%;padding:12px 15px;background:#1a1a1a;border:2px solid #333;border-radius:2px;color:#fff;font-size:14px;margin-bottom:15px}
.login-input:focus{outline:none;border-color:#ff8c42}
.login-btn{width:100%;padding:14px;background:#ff8c42;border:2px solid #ff8c42;border-radius:2px;color:#0f0f0f;font-size:15px;font-weight:700;cursor:pointer;transition:all 0.2s}
.login-btn:hover{background:transparent;color:#ff8c42}
.login-error{color:#ff1744;margin-top:12px;display:none;font-weight:700;font-size:0.85em}
.logout-btn{position:fixed;top:20px;left:20px;padding:10px 18px;background:#1a1a1a;border:2px solid #333;border-radius:2px;color:#808080;cursor:pointer;z-index:1000;font-weight:700;font-size:12px;transition:all 0.2s}
.logout-btn:hover{background:#ff8c42;border-color:#ff8c42;color:#0f0f0f}
.cock-mode .container{background:linear-gradient(135deg,#ff69b4,#ff1493,#c71585)}
.cock-mode h1,.cock-mode h2{color:#fff;text-shadow:2px 2px 4px rgba(0,0,0,0.8)}
.cock-mode .card{background:rgba(255,255,255,0.95);border:2px solid #ff69b4}
.cock-mode .btn{background:#ff1493;border:2px solid #fff}
.cock-mode .btn:hover{background:#ff69b4;transform:scale(1.1) rotate(5deg)}
.cock-mode *{cursor:url('data:image/svg+xml;utf8,<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24"><text y="20" font-size="20">🍆</text></svg>'),auto!important}
.cock-easter-egg{position:fixed;bottom:10px;right:10px;font-size:10px;color:#555;cursor:pointer;opacity:0.3;transition:opacity 0.3s}
.cock-easter-egg:hover{opacity:1}
@media (max-width:768px){h1{font-size:1.8em}.grid-2{grid-template-columns:1fr}.position-display{grid-template-columns:repeat(2,1fr)}.emergency-controls{position:static;margin-bottom:15px}}
</style>
</head>
<body>
<div id="loginOverlay" class="login-overlay active">
<div class="login-box">
<div class="login-title">🔒 U-Track Access</div>
<input type="password" id="loginPasswordInput" class="login-input" placeholder="Enter Password">
<button class="login-btn" onclick="checkPassword()">Login</button>
<div id="loginError" class="login-error">Incorrect password</div>
</div>
</div>
<button id="logoutBtn" class="logout-btn" style="display:none" onclick="logout()">🚪 Logout</button>
<div class="emergency-controls"><button class="btn-emergency" onclick="emergencyStop()">⚠️ EMERGENCY STOP</button></div>
<div class="container">
<header><h1>🎭 U-Track DMX Controller</h1>
<div class="subtitle">UWB Position Tracking System v2.0<span class="status-badge" id="systemStatus">Online</span></div></header>

<div class="tabs">
<button class="tab-btn active" onclick="switchTab('dashboard')">📊 Dashboard</button>
<button class="tab-btn" onclick="switchTab('stagemap')">🗺️ Stage Map</button>
<button class="tab-btn" onclick="switchTab('fixtures')">💡 Fixtures</button>
<button class="tab-btn" onclick="switchTab('profiles')">⚙️ Profiles</button>
<button class="tab-btn" onclick="switchTab('manual')">🎛️ Manual DMX</button>
<button class="tab-btn" onclick="switchTab('settings')">🔧 Settings</button>
</div>

<div id="tab-dashboard" class="tab-content active">
<div class="grid-2">
<div class="card"><div class="card-title">📍 Live Position Data</div>
<div class="position-display">
<div class="position-item"><div class="position-label">X Position</div><div class="position-value" id="posX">0.00</div><div class="position-unit">m</div></div>
<div class="position-item"><div class="position-label">Y Position</div><div class="position-value" id="posY">0.00</div><div class="position-unit">m</div></div>
<div class="position-item"><div class="position-label">Z Position</div><div class="position-value" id="posZ">0.00</div><div class="position-unit">m</div></div>
<div class="position-item"><div class="position-label">RMSE</div><div class="position-value" id="posRMSE">0.000</div><div class="position-unit">accuracy</div></div>
</div></div>

<div class="card"><div class="card-title">🎮 Operating Mode</div>
<div style="margin-top:20px;text-align:center">
<div style="font-size:2em;font-weight:bold;color:#00d4ff;margin-bottom:20px" id="currentMode">UWB-TRACKING</div>
<div class="mode-controls">
<button class="mode-btn active" onclick="setMode(0)">🎯 Tracking</button>
<button class="mode-btn" onclick="setMode(1)">↔️ Pan</button>
<button class="mode-btn" onclick="setMode(2)">↕️ Tilt</button>
<button class="mode-btn" onclick="setMode(3)">💡 Dimmer</button>
<button class="mode-btn" onclick="setMode(4)">🎨 Color</button>
<button class="mode-btn" onclick="setMode(5)">🔄 Gobo</button>
<button class="mode-btn" onclick="setMode(6)">✋ Manual</button>
<button class="mode-btn" onclick="setMode(7)">🔁 Pass</button>
</div></div></div>
</div>

<div class="card"><div class="card-title">📊 DMX Monitor <span style="font-size:0.7em;color:#888">(512 channels)</span></div>
<div class="dmx-monitor" id="dmxMonitor"></div></div>

<div class="card"><div class="card-title">💡 Active Fixtures <span style="font-size:0.7em;color:#888" id="fixtureCount">(0)</span></div>
<div class="fixture-list" id="dashboardFixtureList"><div style="text-align:center;padding:40px;color:#666">No fixtures configured</div></div></div>

<div class="grid"><div class="card"><div class="card-title">📈 System Info</div>
<div style="line-height:2">
<div><strong>Uptime:</strong> <span id="uptime">0s</span></div>
<div><strong>Active Fixtures:</strong> <span id="activeFixtures">0</span></div>
<div><strong>Profiles:</strong> <span id="profileCount">0</span></div>
<div><strong>Position Valid:</strong> <span id="posValid">No</span></div>
</div></div></div>
</div>

<div id="tab-stagemap" class="tab-content">
<div class="card"><div class="card-title">🗺️ Live Stage Map</div>
<div class="form-row" style="margin-bottom:20px">
<div class="form-group"><label class="form-label">Stage Width (m)</label>
<input type="number" id="stageWidth" class="form-input" step="0.1" value="30" onchange="updateStageMap()"></div>
<div class="form-group"><label class="form-label">Stage Depth (m)</label>
<input type="number" id="stageDepth" class="form-input" step="0.1" value="25" onchange="updateStageMap()"></div>
</div>
<div class="stage-controls">
<button class="zoom-btn" onclick="zoomIn()">🔍+ Zoom In</button>
<button class="zoom-btn" onclick="zoomOut()">🔍- Zoom Out</button>
<button class="zoom-btn" onclick="zoomFit()">📐 Fit to Screen</button>
<span class="zoom-level" id="zoomLevel">100%</span>
</div>
<div class="stage-container">
<canvas id="stageCanvas" class="stage-canvas" width="1600" height="1200"></canvas>
</div>
<div class="stage-legend">
<div class="legend-item"><div class="legend-icon" style="background:#ff8c42"></div><span>Tracked Target</span></div>
<div class="legend-item"><div class="legend-icon" style="background:#66bb6a"></div><span>Fixture Position</span></div>
<div class="legend-item"><div class="legend-icon" style="background:#999"></div><span>Stage Boundary</span></div>
</div>
</div>
</div>

<div id="tab-fixtures" class="tab-content">
<div class="card"><div class="card-title">💡 Fixture Manager
<button class="btn btn-primary btn-small" onclick="openAddFixtureModal()" style="margin-left:auto">➕ Add</button></div>
<div class="fixture-list" id="fixtureList"><div style="text-align:center;padding:40px">Loading...</div></div></div>
</div>

<div id="tab-profiles" class="tab-content">
<div class="card"><div class="card-title">⚙️ Fixture Profiles
<button class="btn btn-primary btn-small" onclick="openAddProfileModal()" style="margin-left:auto">➕ Add</button></div>
<div class="profile-list" id="profileList"><div style="text-align:center;padding:40px">Loading...</div></div></div>
</div>

<div id="tab-manual" class="tab-content">
<div class="card"><div class="card-title">📊 Live DMX Monitor <span style="font-size:0.7em;color:#888">(512 channels)</span></div>
<div class="dmx-monitor" id="dmxMonitorManual"></div></div>

<div class="card"><div class="card-title">🎛️ Manual DMX Control</div>
<div style="margin-bottom:15px">
<label><input type="checkbox" id="showAllFixtures" class="form-checkbox" onchange="loadManualChannels()"> Show all fixtures and channels</label>
</div>
<div class="manual-fixture-select" id="manualFixtureSelectDiv">
<label class="form-label">Select Fixture:</label>
<select id="manualFixtureSelect" class="form-select" onchange="loadManualChannels()">
<option value="">-- Select a fixture --</option>
</select>
</div>
<div id="manualChannelPanel" style="text-align:center;padding:40px;color:#888">
Select a fixture to control DMX channels
</div>
</div>
</div>

<div id="tab-settings" class="tab-content">
<div class="card"><div class="card-title">🔧 System Settings</div>

<h3 style="color:#ff8c42;margin-bottom:15px">WiFi Configuration</h3>
<div class="form-group"><label class="form-label">Access Point SSID (Current)</label>
<input type="text" class="form-input" value="U-Track-DMX" disabled></div>

<div class="form-group"><label class="form-label">Connect to External WiFi</label></div>
<div class="form-row">
<div class="form-group"><label class="form-label">WiFi SSID</label>
<input type="text" id="wifiSSID" class="form-input" placeholder="Enter WiFi network name"></div>
<div class="form-group"><label class="form-label">WiFi Password</label>
<input type="password" id="wifiPassword" class="form-input" placeholder="Enter WiFi password"></div>
</div>
<button class="btn btn-primary" onclick="saveWiFiConfig()">💾 Save WiFi Config</button>

<hr style="border:1px solid #333;margin:30px 0">

<h3 style="color:#ff8c42;margin-bottom:15px">Password Protection</h3>
<div class="form-group"><label class="form-label">Change Access Password</label>
<input type="password" id="newPassword" class="form-input" placeholder="Enter new password"></div>
<button class="btn btn-success" onclick="changePassword()">🔒 Update Password</button>

<hr style="border:1px solid #333;margin:30px 0">

<h3 style="color:#ff8c42;margin-bottom:15px">Configuration Backup</h3>
<div class="form-group">
<div style="display:flex;gap:10px">
<button class="btn btn-primary" onclick="downloadConfig()">📥 Download Config</button>
<button class="btn btn-success" onclick="document.getElementById('uploadInput').click()">📤 Upload Config</button>
<input type="file" id="uploadInput" accept=".json" style="display:none" onchange="uploadConfig(event)">
</div>
</div>

<hr style="border:1px solid #333;margin:30px 0">

<h3 style="color:#ff8c42;margin-bottom:15px">System Actions</h3>
<button class="btn btn-danger" onclick="if(confirm('Restart ESP32?'))restartDevice()">🔄 Restart Device</button>

</div>
</div>
</div>

<div id="addFixtureModal" class="modal">
<div class="modal-content">
<div class="modal-header">
<div class="modal-title">➕ Add New Fixture</div>
<button class="modal-close" onclick="closeAddFixtureModal()">✕</button>
</div>
<div class="form-row">
<div class="form-group"><label class="form-label">Name</label>
<input type="text" id="fixtureName" class="form-input" placeholder="e.g., MH1"></div>
<div class="form-group"><label class="form-label">Profile</label>
<select id="fixtureProfile" class="form-select"><option value="">-- Select profile --</option></select></div>
</div>
<div class="form-row">
<div class="form-group"><label class="form-label">DMX Address</label>
<input type="number" id="fixtureDmxAddress" class="form-input" min="1" max="512" value="1"></div>
<div class="form-group"><label class="form-label"><input type="checkbox" id="fixtureEnabled" class="form-checkbox" checked> Enabled</label></div>
</div>
<h3 style="color:#ff8c42;margin:20px 0 10px 0">Position (meters)</h3>
<div class="form-row">
<div class="form-group"><label class="form-label">X</label>
<input type="number" id="fixtureX" class="form-input" step="0.1" value="0"></div>
<div class="form-group"><label class="form-label">Y</label>
<input type="number" id="fixtureY" class="form-input" step="0.1" value="0"></div>
<div class="form-group"><label class="form-label">Z</label>
<input type="number" id="fixtureZ" class="form-input" step="0.1" value="0"></div>
</div>
<button class="btn btn-success" onclick="addFixture()">✅ Add Fixture</button>
</div>
</div>

<div id="addProfileModal" class="modal">
<div class="modal-content">
<div class="modal-header">
<div class="modal-title">➕ Add New Profile</div>
<button class="modal-close" onclick="closeAddProfileModal()">✕</button>
</div>
<div class="form-group"><label class="form-label">Profile Name</label>
<input type="text" id="profileName" class="form-input" placeholder="e.g., Robe MegaPointe"></div>
<h3 style="color:#ff8c42;margin:20px 0 10px 0">DMX Channel Mapping</h3>
<div class="form-row">
<div class="form-group"><label class="form-label">Pan Coarse</label>
<input type="number" id="profilePanCoarse" class="form-input" min="0" max="32" value="0"></div>
<div class="form-group"><label class="form-label">Pan Fine</label>
<input type="number" id="profilePanFine" class="form-input" min="0" max="32" value="1"></div>
</div>
<div class="form-row">
<div class="form-group"><label class="form-label">Tilt Coarse</label>
<input type="number" id="profileTiltCoarse" class="form-input" min="0" max="32" value="2"></div>
<div class="form-group"><label class="form-label">Tilt Fine</label>
<input type="number" id="profileTiltFine" class="form-input" min="0" max="32" value="3"></div>
</div>
<div class="form-row">
<div class="form-group"><label class="form-label">Dimmer</label>
<input type="number" id="profileDimmer" class="form-input" min="0" max="32" value="4"></div>
<div class="form-group"><label class="form-label">Shutter</label>
<input type="number" id="profileShutter" class="form-input" min="0" max="32" value="5"></div>
</div>
<div class="form-row">
<div class="form-group"><label class="form-label">Color Wheel</label>
<input type="number" id="profileColor" class="form-input" min="0" max="32" value="6"></div>
<div class="form-group"><label class="form-label">Gobo Wheel</label>
<input type="number" id="profileGobo" class="form-input" min="0" max="32" value="7"></div>
</div>
<button class="btn btn-success" onclick="addProfile()">✅ Add Profile</button>
</div>
</div>

<div class="cock-easter-egg" onclick="toggleCockMode()">🐔</div>

<script>
let config={fixtures:[],profiles:[]};
let position={x:0,y:0,z:0,valid:false,rmse:0};
let stageZoom=1;
let dmxMonitorInterval=null;

function checkPassword(){
const input=document.getElementById('loginPasswordInput');
const error=document.getElementById('loginError');
const pwd=input.value.trim();
if(pwd==='admin'||pwd==='utrack'){
localStorage.setItem('dmxLoggedIn','true');
document.getElementById('loginOverlay').classList.remove('active');
document.getElementById('logoutBtn').style.display='block';
error.style.display='none';
}else{
error.style.display='block';
input.value='';
input.focus();
}
}

function logout(){
localStorage.removeItem('dmxLoggedIn');
location.reload();
}

document.getElementById('loginPasswordInput')?.addEventListener('keypress',(e)=>{
if(e.key==='Enter')checkPassword();
});

function emergencyStop(){
if(confirm('EMERGENCY STOP?\nAll fixtures will be reset to safe state!')){
fetch('/api/mode/set',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({mode:6})}).then(()=>{
alert('Emergency stop activated!');
loadStatus();
});
}
}

function switchTab(tabName){
document.querySelectorAll('.tab-content').forEach(t=>t.classList.remove('active'));
document.querySelectorAll('.tab-btn').forEach(b=>b.classList.remove('active'));
document.getElementById('tab-'+tabName).classList.add('active');
event.target.classList.add('active');
if(tabName==='stagemap')updateStageMap();
}

function setMode(mode){
fetch('/api/mode/set',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({mode})}).then(()=>loadStatus());
}

async function loadConfig(){
const r=await fetch('/api/config');
config=await r.json();
updateFixtureLists();
updateProfileList();
updateManualFixtureSelect();
document.getElementById('profileCount').textContent=config.profiles.length;
document.getElementById('activeFixtures').textContent=config.fixtures.filter(f=>f.enabled).length;
document.getElementById('fixtureCount').textContent='('+config.fixtures.length+')';
}

function updateFixtureLists(){
const dashList=document.getElementById('dashboardFixtureList');
const fixtureList=document.getElementById('fixtureList');
if(config.fixtures.length===0){
dashList.innerHTML='<div style="text-align:center;padding:40px;color:#666">No fixtures configured</div>';
fixtureList.innerHTML='<div style="text-align:center;padding:40px;color:#666">No fixtures configured. Click Add to create one.</div>';
return;
}
let dashHTML='';
let listHTML='';
config.fixtures.forEach((f,i)=>{
const p=config.profiles.find(pr=>pr.name===f.profile);
const dmxInfo=p?f.dmxAddress+' ('+p.name+')':f.dmxAddress;
dashHTML+=`<div class="fixture-item">
<div class="fixture-info">
<div class="fixture-name">${f.name}</div>
<div class="fixture-details">DMX: ${dmxInfo} | Pos: (${f.position.x.toFixed(1)}, ${f.position.y.toFixed(1)}, ${f.position.z.toFixed(1)}) | ${f.enabled?'✅ Enabled':'❌ Disabled'}</div>
</div>
</div>`;
listHTML+=`<div class="fixture-item">
<div class="fixture-info">
<div class="fixture-name">${f.name}</div>
<div class="fixture-details">Profile: ${f.profile} | DMX: ${f.dmxAddress} | Position: (${f.position.x.toFixed(1)}, ${f.position.y.toFixed(1)}, ${f.position.z.toFixed(1)})</div>
</div>
<div class="fixture-actions">
<button class="btn btn-small btn-secondary" onclick="editFixture(${i})">✏️ Edit</button>
<button class="btn btn-small fixture-copy-btn" onclick="copyFixture(${i})">📋 Copy</button>
<button class="btn btn-small btn-danger" onclick="deleteFixture(${i})">🗑️ Delete</button>
</div>
</div>`;
});
dashList.innerHTML=dashHTML;
fixtureList.innerHTML=listHTML;
}

function updateProfileList(){
const list=document.getElementById('profileList');
const select=document.getElementById('fixtureProfile');
if(config.profiles.length===0){
list.innerHTML='<div style="text-align:center;padding:40px;color:#666">No profiles configured. Click Add to create one.</div>';
select.innerHTML='<option value="">-- No profiles available --</option>';
return;
}
let listHTML='';
let selectHTML='<option value="">-- Select profile --</option>';
config.profiles.forEach((p,i)=>{
selectHTML+=`<option value="${p.name}">${p.name}</option>`;
listHTML+=`<div class="profile-card">
<div class="profile-header">
<div class="profile-name">${p.name}</div>
<div style="display:flex;gap:8px">
<button class="btn btn-small btn-danger" onclick="deleteProfile(${i})">🗑️ Delete</button>
</div>
</div>
<div class="channel-grid">
<div class="channel-item"><div class="channel-label">Pan Coarse</div><div class="channel-value">${p.panCoarse}</div></div>
<div class="channel-item"><div class="channel-label">Pan Fine</div><div class="channel-value">${p.panFine}</div></div>
<div class="channel-item"><div class="channel-label">Tilt Coarse</div><div class="channel-value">${p.tiltCoarse}</div></div>
<div class="channel-item"><div class="channel-label">Tilt Fine</div><div class="channel-value">${p.tiltFine}</div></div>
<div class="channel-item"><div class="channel-label">Dimmer</div><div class="channel-value">${p.dimmer}</div></div>
<div class="channel-item"><div class="channel-label">Shutter</div><div class="channel-value">${p.shutter}</div></div>
<div class="channel-item"><div class="channel-label">Color</div><div class="channel-value">${p.color}</div></div>
<div class="channel-item"><div class="channel-label">Gobo</div><div class="channel-value">${p.gobo}</div></div>
</div>
</div>`;
});
list.innerHTML=listHTML;
select.innerHTML=selectHTML;
}

async function loadStatus(){
const r=await fetch('/api/status');
const data=await r.json();
position=data.position;
document.getElementById('posX').textContent=position.x.toFixed(2);
document.getElementById('posY').textContent=position.y.toFixed(2);
document.getElementById('posZ').textContent=position.z.toFixed(2);
document.getElementById('posRMSE').textContent=position.rmse.toFixed(3);
document.getElementById('posValid').textContent=position.valid?'Yes':'No';
document.getElementById('uptime').textContent=Math.floor(data.uptime/1000)+'s';
const modes=['UWB-TRACKING','PAN-TEST','TILT-TEST','DIMMER-TEST','COLOR-TEST','GOBO-TEST','MANUAL','PASSTHROUGH'];
document.getElementById('currentMode').textContent=modes[data.mode]||'UNKNOWN';
document.querySelectorAll('.mode-btn').forEach((b,i)=>{
b.classList.toggle('active',i===data.mode);
});
updateStageMap();
}

function updateStageMap(){
const canvas=document.getElementById('stageCanvas');
if(!canvas)return;
const ctx=canvas.getContext('2d');
const w=parseFloat(document.getElementById('stageWidth').value);
const d=parseFloat(document.getElementById('stageDepth').value);
const cw=canvas.width;
const ch=canvas.height;
const padding=40*stageZoom;
const scale=Math.min((cw-padding*2)/w,(ch-padding*2)/d);
const offsetX=cw/2-(w*scale)/2;
const offsetY=ch/2-(d*scale)/2;
ctx.fillStyle='#0f0f0f';
ctx.fillRect(0,0,cw,ch);
ctx.strokeStyle='#444';
ctx.lineWidth=2;
ctx.strokeRect(offsetX,offsetY,w*scale,d*scale);
ctx.fillStyle='rgba(255,140,66,0.05)';
ctx.fillRect(offsetX,offsetY,w*scale,d*scale);
const gridStep=1*scale;
ctx.strokeStyle='rgba(255,140,66,0.1)';
ctx.lineWidth=1;
for(let x=0;x<=w;x++){
ctx.beginPath();
ctx.moveTo(offsetX+x*scale,offsetY);
ctx.lineTo(offsetX+x*scale,offsetY+d*scale);
ctx.stroke();
}
for(let y=0;y<=d;y++){
ctx.beginPath();
ctx.moveTo(offsetX,offsetY+y*scale);
ctx.lineTo(offsetX+w*scale,offsetY+y*scale);
ctx.stroke();
}
config.fixtures.forEach(f=>{
if(!f.enabled)return;
const fx=offsetX+f.position.x*scale;
const fy=offsetY+(d-f.position.y)*scale;
ctx.fillStyle='#66bb6a';
ctx.beginPath();
ctx.arc(fx,fy,8,0,Math.PI*2);
ctx.fill();
ctx.fillStyle='#fff';
ctx.font='10px monospace';
ctx.fillText(f.name,fx-15,fy-12);
if(position&&position.valid){
const tx=offsetX+position.x*scale;
const ty=offsetY+(d-position.y)*scale;
ctx.strokeStyle='rgba(255,140,66,0.3)';
ctx.lineWidth=2;
ctx.setLineDash([5,5]);
ctx.beginPath();
ctx.moveTo(fx,fy);
ctx.lineTo(tx,ty);
ctx.stroke();
ctx.setLineDash([]);
}
});
if(position&&position.valid){
const tx=offsetX+position.x*scale;
const ty=offsetY+(d-position.y)*scale;
ctx.fillStyle='#ff8c42';
ctx.beginPath();
ctx.arc(tx,ty,10,0,Math.PI*2);
ctx.fill();
ctx.strokeStyle='#fff';
ctx.lineWidth=2;
ctx.stroke();
}
document.getElementById('zoomLevel').textContent=(stageZoom*100).toFixed(0)+'%';
}

function zoomIn(){stageZoom*=1.2;updateStageMap()}
function zoomOut(){stageZoom*=0.8;updateStageMap()}
function zoomFit(){stageZoom=1;updateStageMap()}

function updateDMXMonitor(){
fetch('/api/dmx/status').then(r=>r.json()).then(data=>{
const monitors=['dmxMonitor','dmxMonitorManual'];
monitors.forEach(monitorId=>{
const m=document.getElementById(monitorId);
if(!m||!m.offsetParent)return;
if(m.children.length===0){
for(let i=1;i<=512;i++){
const ch=document.createElement('div');
ch.className='dmx-channel';
ch.innerHTML=`<div class="dmx-channel-num">${i}</div><div class="dmx-bar-container"><div class="dmx-bar" id="${monitorId}_bar_${i}"></div></div>`;
m.appendChild(ch);
}
}
data.channels.forEach((v,i)=>{
const bar=document.getElementById(`${monitorId}_bar_${i+1}`);
if(bar)bar.style.height=(v/255*100)+'%';
});
});
}).catch(()=>{});
}

function updateManualFixtureSelect(){
const s=document.getElementById('manualFixtureSelect');
s.innerHTML='<option value="">-- Select a fixture --</option>';
config.fixtures.forEach((f,i)=>{
s.innerHTML+=`<option value="${i}">${f.name} (DMX ${f.dmxAddress})</option>`;
});
}

function loadManualChannels(){
const showAll=document.getElementById('showAllFixtures').checked;
const panel=document.getElementById('manualChannelPanel');
const selectDiv=document.getElementById('manualFixtureSelectDiv');
if(showAll){
selectDiv.style.display='none';
let html='';
config.fixtures.forEach(f=>{
const p=config.profiles.find(pr=>pr.name===f.profile);
if(!p)return;
html+=`<div class="fixture-control-group">
<h3>${f.name} - DMX ${f.dmxAddress}</h3>
<div class="dmx-control-panel">`;
const channels=[
{name:'Pan',ch:f.dmxAddress+p.panCoarse},
{name:'Pan Fine',ch:f.dmxAddress+p.panFine},
{name:'Tilt',ch:f.dmxAddress+p.tiltCoarse},
{name:'Tilt Fine',ch:f.dmxAddress+p.tiltFine},
{name:'Dimmer',ch:f.dmxAddress+p.dimmer},
{name:'Shutter',ch:f.dmxAddress+p.shutter},
{name:'Color',ch:f.dmxAddress+p.color},
{name:'Gobo',ch:f.dmxAddress+p.gobo}
];
channels.forEach(c=>{
if(c.ch>=1&&c.ch<=512){
html+=`<div class="dmx-channel">
<div class="dmx-channel-label">${c.name}<br>CH${c.ch}</div>
<div class="dmx-channel-value" id="manual_val_${c.ch}">0</div>
<input type="range" class="dmx-slider" orient="vertical" min="0" max="255" value="0" onchange="setDMXChannel(${c.ch},this.value)">
</div>`;
}
});
html+=`</div></div>`;
});
panel.innerHTML=html||'<div style="text-align:center;padding:40px;color:#888">No fixtures with profiles configured</div>';
}else{
selectDiv.style.display='block';
const idx=document.getElementById('manualFixtureSelect').value;
if(idx===''){
panel.innerHTML='<div style="text-align:center;padding:40px;color:#888">Select a fixture to control DMX channels</div>';
return;
}
const f=config.fixtures[parseInt(idx)];
const p=config.profiles.find(pr=>pr.name===f.profile);
if(!p){
panel.innerHTML='<div style="text-align:center;padding:40px;color:#888">No profile assigned to this fixture</div>';
return;
}
let html=`<div class="dmx-control-panel">`;
const channels=[
{name:'Pan',ch:f.dmxAddress+p.panCoarse},
{name:'Pan Fine',ch:f.dmxAddress+p.panFine},
{name:'Tilt',ch:f.dmxAddress+p.tiltCoarse},
{name:'Tilt Fine',ch:f.dmxAddress+p.tiltFine},
{name:'Dimmer',ch:f.dmxAddress+p.dimmer},
{name:'Shutter',ch:f.dmxAddress+p.shutter},
{name:'Color',ch:f.dmxAddress+p.color},
{name:'Gobo',ch:f.dmxAddress+p.gobo}
];
channels.forEach(c=>{
if(c.ch>=1&&c.ch<=512){
html+=`<div class="dmx-channel">
<div class="dmx-channel-label">${c.name}<br>CH${c.ch}</div>
<div class="dmx-channel-value" id="manual_val_${c.ch}">0</div>
<input type="range" class="dmx-slider" orient="vertical" min="0" max="255" value="0" onchange="setDMXChannel(${c.ch},this.value)">
</div>`;
}
});
html+=`</div>`;
panel.innerHTML=html;
}
}

function setDMXChannel(ch,val){
fetch('/api/dmx/set',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({channel:ch,value:parseInt(val)})});
document.getElementById('manual_val_'+ch).textContent=val;
}

function openAddFixtureModal(){
document.getElementById('addFixtureModal').classList.add('active');
}

function closeAddFixtureModal(){
document.getElementById('addFixtureModal').classList.remove('active');
}

function openAddProfileModal(){
document.getElementById('addProfileModal').classList.add('active');
}

function closeAddProfileModal(){
document.getElementById('addProfileModal').classList.remove('active');
}

async function addFixture(){
const f={
name:document.getElementById('fixtureName').value,
profile:document.getElementById('fixtureProfile').value,
dmxAddress:parseInt(document.getElementById('fixtureDmxAddress').value),
enabled:document.getElementById('fixtureEnabled').checked,
position:{
x:parseFloat(document.getElementById('fixtureX').value),
y:parseFloat(document.getElementById('fixtureY').value),
z:parseFloat(document.getElementById('fixtureZ').value)
}
};
config.fixtures.push(f);
await fetch('/api/config',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify(config)});
closeAddFixtureModal();
loadConfig();
}

async function copyFixture(idx){
const orig=config.fixtures[idx];
const newF={...orig,name:orig.name+' Copy',dmxAddress:orig.dmxAddress+32};
config.fixtures.push(newF);
await fetch('/api/config',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify(config)});
loadConfig();
}

async function deleteFixture(idx){
if(confirm('Delete fixture: '+config.fixtures[idx].name+'?')){
config.fixtures.splice(idx,1);
await fetch('/api/config',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify(config)});
loadConfig();
}
}

async function addProfile(){
const p={
name:document.getElementById('profileName').value,
panCoarse:parseInt(document.getElementById('profilePanCoarse').value),
panFine:parseInt(document.getElementById('profilePanFine').value),
tiltCoarse:parseInt(document.getElementById('profileTiltCoarse').value),
tiltFine:parseInt(document.getElementById('profileTiltFine').value),
dimmer:parseInt(document.getElementById('profileDimmer').value),
shutter:parseInt(document.getElementById('profileShutter').value),
color:parseInt(document.getElementById('profileColor').value),
gobo:parseInt(document.getElementById('profileGobo').value)
};
config.profiles.push(p);
await fetch('/api/config',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify(config)});
closeAddProfileModal();
loadConfig();
}

async function deleteProfile(idx){
if(confirm('Delete profile: '+config.profiles[idx].name+'?')){
config.profiles.splice(idx,1);
await fetch('/api/config',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify(config)});
loadConfig();
}
}

async function saveWiFiConfig(){
const ssid=document.getElementById('wifiSSID').value;
const pwd=document.getElementById('wifiPassword').value;
await fetch('/api/wifi/config',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({ssid,password:pwd})});
alert('WiFi config saved. Device will restart.');
}

async function changePassword(){
const newPwd=document.getElementById('newPassword').value;
if(newPwd.length<4){
alert('Password must be at least 4 characters');
return;
}
await fetch('/api/password/set',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({password:newPwd})});
alert('Password updated successfully');
document.getElementById('newPassword').value='';
}

async function downloadConfig(){
const r=await fetch('/api/config');
const data=await r.json();
const blob=new Blob([JSON.stringify(data,null,2)],{type:'application/json'});
const url=URL.createObjectURL(blob);
const a=document.createElement('a');
a.href=url;
a.download='u-track-config.json';
a.click();
}

async function uploadConfig(e){
const file=e.target.files[0];
const text=await file.text();
const data=JSON.parse(text);
await fetch('/api/config',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify(data)});
alert('Config uploaded successfully');
loadConfig();
}

async function restartDevice(){
await fetch('/api/system/restart',{method:'POST'});
alert('Device restarting...');
setTimeout(()=>location.reload(),5000);
}

function toggleCockMode(){
const isCock=localStorage.getItem('cockMode')==='true';
if(isCock){
localStorage.removeItem('cockMode');
}else{
localStorage.setItem('cockMode','true');
}
location.reload();
}

function applyCockMode(){
if(localStorage.getItem('cockMode')==='true'||window.location.search.includes('cock')){
document.body.classList.add('cock-mode');
document.title='🍆 C.O.C.K. MODE ACTIVATED 🍆';
}
}

if(localStorage.getItem('dmxLoggedIn')==='true'){
document.getElementById('loginOverlay').classList.remove('active');
document.getElementById('logoutBtn').style.display='block';
}

applyCockMode();
loadConfig();
setInterval(loadStatus,1000);
dmxMonitorInterval=setInterval(updateDMXMonitor,100);
</script>
</body>
</html>
)===";
