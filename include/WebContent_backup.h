#pragma once

// ============================================================================
// U-TRACK DMX CONTROLLER - EMBEDDED WEB DASHBOARD v2.0
// Complete Single-Page Application - Minified for PROGMEM
// ============================================================================

const char HTML_DASHBOARD[] PROGMEM = R"===(
<!DOCTYPE html>
<html><head><meta charset="UTF-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>U-Track DMX v2.0</title>
<style>
@import url('https://fonts.googleapis.com/css2?family=Inter:wght@400;500;600;700&family=Roboto+Mono:wght@400;500;700&display=swap');
*{margin:0;padding:0;box-sizing:border-box}
body{font-family:'Inter',sans-serif;background:#0f0f0f;color:#e8e8e8;min-height:100vh;background-image:repeating-linear-gradient(0deg,transparent,transparent 1px,rgba(255,170,0,0.03) 1px,rgba(255,170,0,0.03) 2px),repeating-linear-gradient(90deg,transparent,transparent 1px,rgba(255,170,0,0.03) 1px,rgba(255,170,0,0.03) 2px);background-size:50px 50px}
.container{max-width:1800px;margin:0 auto;padding:20px}
header{background:rgba(43,43,43,0.95);padding:20px 30px;border-radius:2px;margin-bottom:20px;border-left:4px solid #ffaa00;box-shadow:0 2px 10px rgba(0,0,0,0.8)}
h1{color:#ffaa00;font-size:2.2em;font-weight:700;letter-spacing:-0.5px;margin-bottom:8px;text-transform:uppercase;font-family:'Roboto Mono',monospace}
.subtitle{color:#b0b0b0;font-size:0.95em;display:flex;align-items:center;gap:10px;font-weight:500}
.status-badge{display:inline-block;padding:4px 12px;border-radius:2px;font-size:0.8em;font-weight:700;background:#4caf50;color:#0f0f0f;letter-spacing:0.5px;text-transform:uppercase;font-family:'Roboto Mono',monospace}
.status-badge{display:inline-block;padding:4px 12px;border-radius:2px;font-size:0.8em;font-weight:700;background:#4caf50;color:#0f0f0f;letter-spacing:0.5px;text-transform:uppercase;font-family:'Roboto Mono',monospace}
.emergency-controls{position:fixed;top:20px;right:20px;z-index:1000}
.btn-emergency{background:#ff1744;color:white;border:2px solid #ff1744;padding:14px 28px;border-radius:2px;font-size:15px;font-weight:700;cursor:pointer;transition:all 0.2s;text-transform:uppercase;letter-spacing:1px;font-family:'Roboto Mono',monospace}
.btn-emergency:hover{background:transparent;color:#ff1744}
.tabs{display:flex;gap:0;margin-bottom:20px;background:#1a1a1a;border:1px solid #333}
.tab-btn{flex:1;padding:14px 20px;border:none;background:#1a1a1a;color:#808080;border-right:1px solid #333;cursor:pointer;transition:all 0.2s;font-size:13px;font-weight:600;text-transform:uppercase;letter-spacing:0.5px}
.tab-btn:hover{background:#2b2b2b;color:#ffaa00}
.tab-btn.active{background:#ffaa00;color:#0f0f0f;font-weight:700}
.tab-content{display:none;animation:fadeIn 0.2s}
.tab-content.active{display:block}
@keyframes fadeIn{from{opacity:0}to{opacity:1}}
.card{background:rgba(43,43,43,0.95);border-radius:2px;padding:20px;margin-bottom:15px;border-left:3px solid #ffaa00;box-shadow:0 2px 8px rgba(0,0,0,0.6)}
.card-title{font-size:1.3em;margin-bottom:15px;color:#ffaa00;font-weight:700;text-transform:uppercase;letter-spacing:0.5px;border-bottom:1px solid #333;padding-bottom:8px;display:flex;align-items:center;gap:10px}
.grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(300px,1fr));gap:15px}
.grid-2{display:grid;grid-template-columns:1fr 1fr;gap:15px}
.position-display{display:grid;grid-template-columns:repeat(4,1fr);gap:12px;margin-top:12px}
.position-item{background:#1a1a1a;padding:12px;border-radius:2px;text-align:center;border:1px solid #333;transition:border-color 0.2s}
.position-item:hover{border-color:#ffaa00}
.position-label{font-size:0.75em;color:#808080;margin-bottom:4px;text-transform:uppercase;letter-spacing:0.5px;font-weight:600}
.position-value{font-size:2em;font-weight:700;color:#ffaa00;font-family:'Roboto Mono',monospace}
.position-unit{font-size:0.75em;color:#666;text-transform:uppercase}
.fixture-list{display:flex;flex-direction:column;gap:8px}
.fixture-item{background:#1a1a1a;padding:15px;border-radius:2px;display:flex;justify-content:space-between;align-items:center;transition:all 0.2s;border:1px solid #333}
.fixture-item:hover{border-color:#ffaa00;background:#2b2b2b}
.fixture-info{flex:1}
.fixture-name{font-size:1.1em;font-weight:700;color:#fff;margin-bottom:4px;text-transform:uppercase;letter-spacing:0.5px}
.fixture-details{font-size:0.85em;color:#808080;font-family:'Roboto Mono',monospace}
.fixture-actions{display:flex;gap:8px}
.btn{padding:8px 16px;border:2px solid;border-radius:2px;cursor:pointer;font-size:13px;font-weight:700;transition:all 0.2s;text-transform:uppercase;letter-spacing:0.5px}
.btn-primary{background:#ffaa00;color:#0f0f0f;border-color:#ffaa00}
.btn-primary:hover{background:transparent;color:#ffaa00}
.btn-success{background:#4caf50;color:#0f0f0f;border-color:#4caf50}
.btn-success:hover{background:transparent;color:#4caf50}
.btn-danger{background:#ff1744;color:#fff;border-color:#ff1744}
.btn-danger:hover{background:transparent;color:#ff1744}
.btn-secondary{background:transparent;color:#808080;border-color:#555}
.btn-secondary:hover{border-color:#ffaa00;color:#ffaa00}
.btn-small{padding:6px 12px;font-size:11px}
.btn-small{padding:6px 12px;font-size:11px}
.form-group{margin-bottom:15px}
.form-label{display:block;margin-bottom:6px;color:#b0b0b0;font-size:0.85em;font-weight:600;text-transform:uppercase;letter-spacing:0.5px}
.form-input,.form-select{width:100%;padding:10px 12px;background:#1a1a1a;border:1px solid #333;border-radius:2px;color:#fff;font-size:13px;font-family:'Roboto Mono',monospace;transition:border-color 0.2s}
.form-input:focus,.form-select:focus{outline:none;border-color:#ffaa00}
.form-checkbox{margin-right:8px;accent-color:#ffaa00}
.form-row{display:grid;grid-template-columns:repeat(auto-fit,minmax(200px,1fr));gap:12px}
.modal{display:none;position:fixed;top:0;left:0;width:100%;height:100%;background:rgba(0,0,0,0.9);z-index:2000;overflow-y:auto}
.modal.active{display:flex;align-items:center;justify-content:center}
.modal-content{background:#2b2b2b;border-radius:2px;padding:25px;max-width:900px;width:90%;max-height:90vh;overflow-y:auto;box-shadow:0 10px 50px rgba(0,0,0,0.9);border:2px solid #ffaa00}
.modal-header{display:flex;justify-content:space-between;align-items:center;margin-bottom:20px;border-bottom:1px solid #333;padding-bottom:12px}
.modal-title{font-size:1.5em;color:#ffaa00;font-weight:700;text-transform:uppercase;letter-spacing:0.5px}
.modal-close{background:transparent;border:2px solid #808080;color:#808080;font-size:1.5em;cursor:pointer;width:35px;height:35px;border-radius:2px;transition:all 0.2s}
.modal-close:hover{background:#ff1744;border-color:#ff1744;color:#fff}
.mode-controls{display:grid;grid-template-columns:repeat(auto-fit,minmax(140px,1fr));gap:8px;margin-top:12px}
.mode-btn{padding:12px;background:#1a1a1a;border:2px solid #333;border-radius:2px;color:#808080;cursor:pointer;font-weight:700;text-align:center;text-transform:uppercase;letter-spacing:0.5px;font-size:12px;transition:all 0.2s}
.mode-btn:hover{border-color:#ffaa00;color:#ffaa00}
.mode-btn.active{background:#ffaa00;border-color:#ffaa00;color:#0f0f0f}
.profile-list{display:grid;gap:12px;margin-top:15px}
.profile-card{background:#1a1a1a;padding:15px;border-radius:2px;border:1px solid #333;transition:border-color 0.2s}
.profile-card:hover{border-color:#ffaa00}
.profile-header{display:flex;justify-content:space-between;align-items:center;margin-bottom:12px}
.profile-name{font-size:1.2em;font-weight:700;color:#fff;text-transform:uppercase;letter-spacing:0.5px}
.channel-grid{display:grid;grid-template-columns:repeat(auto-fill,minmax(110px,1fr));gap:8px;margin-top:12px}
.channel-item{background:#0f0f0f;padding:8px;border-radius:2px;text-align:center;border:1px solid #333}
.channel-label{font-size:0.7em;color:#808080;margin-bottom:3px;text-transform:uppercase;letter-spacing:0.5px}
.channel-value{font-size:1.1em;font-weight:700;color:#ffaa00;font-family:'Roboto Mono',monospace}
.stage-container{position:relative;width:100%;background:#0f0f0f;border:2px solid #333;border-radius:2px;overflow:hidden}
.stage-canvas{width:100%;display:block;cursor:crosshair}
.stage-controls{display:flex;gap:8px;margin-bottom:12px;align-items:center;flex-wrap:wrap}
.zoom-btn{padding:8px 14px;background:#1a1a1a;border:2px solid #333;border-radius:2px;color:#808080;cursor:pointer;font-weight:700;font-size:12px;text-transform:uppercase;letter-spacing:0.5px;transition:all 0.2s}
.zoom-btn:hover{border-color:#ffaa00;color:#ffaa00}
.zoom-level{color:#808080;font-size:0.85em;font-family:'Roboto Mono',monospace;font-weight:700;padding:8px 12px;background:#1a1a1a;border:1px solid #333;border-radius:2px}
.stage-legend{margin-top:12px;display:flex;gap:15px;flex-wrap:wrap;justify-content:center}
.legend-item{display:flex;align-items:center;gap:6px;color:#808080;font-size:0.85em;font-weight:600;text-transform:uppercase;letter-spacing:0.5px}
.legend-icon{width:16px;height:16px;border-radius:2px;border:1px solid #333}
.legend-icon{width:16px;height:16px;border-radius:2px;border:1px solid #333}
.dmx-control-panel{display:grid;grid-template-columns:repeat(auto-fill,minmax(70px,1fr));gap:8px;margin-top:12px}
.dmx-channel{background:#1a1a1a;padding:8px;border-radius:2px;text-align:center;border:1px solid #333}
.dmx-channel-label{font-size:0.7em;color:#808080;margin-bottom:4px;text-transform:uppercase;letter-spacing:0.3px;font-weight:600}
.dmx-channel-value{font-size:1.1em;font-weight:700;color:#ffaa00;margin:4px 0;font-family:'Roboto Mono',monospace}
.dmx-slider{width:100%;height:90px;writing-mode:bt-lr;-webkit-appearance:slider-vertical;background:#0f0f0f;outline:none;border:1px solid #333;border-radius:2px}
.dmx-slider::-webkit-slider-thumb{-webkit-appearance:none;width:100%;height:12px;background:#ffaa00;cursor:pointer;border-radius:2px}
.dmx-slider::-moz-range-thumb{width:100%;height:12px;background:#ffaa00;cursor:pointer;border-radius:2px;border:none}
.manual-fixture-select{margin-bottom:12px}
.fixture-control-group{margin-bottom:20px;padding:12px;background:#1a1a1a;border-radius:2px;border:1px solid #333}
.fixture-control-group h3{color:#ffaa00;margin:0 0 12px 0;font-size:1em;text-transform:uppercase;letter-spacing:0.5px;font-weight:700}
.beam-overlay{position:absolute;top:0;left:0;pointer-events:none;z-index:10}
.beam{opacity:0.4;stroke-width:40;stroke-linecap:round;filter:blur(8px)}
.fixture-copy-btn{background:#4a9eff;border-color:#4a9eff;margin-left:5px}
.fixture-copy-btn:hover{background:transparent;color:#4a9eff}
.dmx-monitor{display:grid;grid-template-columns:repeat(32,1fr);gap:2px;padding:8px;background:#1a1a1a;border-radius:2px;max-height:280px;overflow-y:auto;border:1px solid #333}
.dmx-channel{background:#0f0f0f;padding:4px;border-radius:2px;text-align:center;border:1px solid #333;min-height:70px;display:flex;flex-direction:column;justify-content:flex-end}
.dmx-channel-num{font-size:0.65em;color:#666;margin-bottom:2px;font-family:'Roboto Mono',monospace;font-weight:700}
.dmx-bar-container{flex:1;display:flex;flex-direction:column;justify-content:flex-end;background:#000;border-radius:2px;overflow:hidden;border:1px solid #222}
.dmx-bar{width:100%;background:linear-gradient(to top,#4caf50 0%,#ffaa00 50%,#ff1744 100%);transition:height 0.05s;opacity:0.3}
.password-section{background:#1a1a1a;padding:12px;border-radius:2px;margin-top:12px;border:1px solid #333}
.password-section{background:#1a1a1a;padding:12px;border-radius:2px;margin-top:12px;border:1px solid #333}
.cock-mode .container{background:linear-gradient(135deg,#ff69b4,#ff1493,#c71585)}
.cock-mode h1,.cock-mode h2{color:#fff;text-shadow:2px 2px 4px rgba(0,0,0,0.8)}
.cock-mode .card{background:rgba(255,255,255,0.95);border:2px solid #ff69b4}
.cock-mode .btn{background:#ff1493;border:2px solid #fff}
.cock-mode .btn:hover{background:#ff69b4;transform:scale(1.1) rotate(5deg)}
.cock-mode *{cursor:url('data:image/svg+xml;utf8,<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24"><text y="20" font-size="20">🍆</text></svg>'),auto!important}
.cock-easter-egg{position:fixed;bottom:10px;right:10px;font-size:10px;color:#555;cursor:pointer;opacity:0.3;transition:opacity 0.3s}
.cock-easter-egg:hover{opacity:1}
.login-overlay{position:fixed;top:0;left:0;width:100%;height:100%;background:rgba(0,0,0,0.95);z-index:9999;display:none;align-items:center;justify-content:center}
.login-overlay.active{display:flex}
.login-box{background:#2b2b2b;border-radius:2px;padding:40px;max-width:480px;width:90%;box-shadow:0 20px 60px rgba(0,0,0,0.95);border:3px solid #ffaa00;text-align:center}
.login-title{font-size:2em;color:#ffaa00;margin-bottom:10px;font-weight:700;text-transform:uppercase;letter-spacing:1px;font-family:'Roboto Mono',monospace}
.login-subtitle{color:#808080;margin-bottom:25px;font-size:0.95em;font-weight:600;text-transform:uppercase;letter-spacing:0.5px}
.login-modes{display:grid;grid-template-columns:1fr 1fr;gap:15px;margin-bottom:25px}
.mode-card{background:#1a1a1a;padding:25px 15px;border-radius:2px;border:2px solid #333;cursor:pointer;transition:all 0.2s}
.mode-card:hover{border-color:#ffaa00;background:#2b2b2b}
.mode-card.selected{border-color:#ffaa00;background:rgba(255,170,0,0.1)}
.mode-icon{font-size:2.5em;margin-bottom:8px}
.mode-name{font-size:1.1em;font-weight:700;color:#fff;margin-bottom:6px;text-transform:uppercase;letter-spacing:0.5px}
.mode-desc{font-size:0.8em;color:#808080;text-transform:uppercase;letter-spacing:0.3px}
.login-input{width:100%;padding:12px 15px;background:#1a1a1a;border:2px solid #333;border-radius:2px;color:#fff;font-size:14px;margin-bottom:15px;font-family:'Roboto Mono',monospace;transition:border-color 0.2s}
.login-input:focus{outline:none;border-color:#ffaa00}
.login-btn{width:100%;padding:14px;background:#ffaa00;border:2px solid #ffaa00;border-radius:2px;color:#0f0f0f;font-size:15px;font-weight:700;cursor:pointer;transition:all 0.2s;text-transform:uppercase;letter-spacing:1px}
.login-btn:hover{background:transparent;color:#ffaa00}
.login-error{color:#ff1744;margin-top:12px;display:none;font-weight:700;text-transform:uppercase;letter-spacing:0.5px;font-size:0.85em}
.logout-btn{position:fixed;top:20px;left:20px;padding:10px 18px;background:#1a1a1a;border:2px solid #333;border-radius:2px;color:#808080;cursor:pointer;z-index:1000;font-weight:700;text-transform:uppercase;letter-spacing:0.5px;font-size:12px;transition:all 0.2s}
.logout-btn:hover{background:#ffaa00;border-color:#ffaa00;color:#0f0f0f}
.viewer-mode .tab-btn:not([data-viewer-allowed]){display:none!important}
.viewer-mode .emergency-controls{display:none!important}
.viewer-mode .fixture-actions{display:none!important}
.viewer-mode .btn:not(.logout-btn){pointer-events:none;opacity:0.5}
@media (max-width:768px){h1{font-size:1.8em}.grid-2{grid-template-columns:1fr}.position-display{grid-template-columns:repeat(2,1fr)}.emergency-controls{position:static;margin-bottom:15px}.login-modes{grid-template-columns:1fr}}
</style>
</head>
<body>
<div id="loginOverlay" class="login-overlay active">
<div class="login-box">
<div class="login-title">🎭 U-Track Access</div>
<div class="login-subtitle">Choose your access level</div>
<div class="login-modes">
<div class="mode-card" onclick="selectMode('viewer')">
<div class="mode-icon">👁️</div>
<div class="mode-name">Viewer</div>
<div class="mode-desc">Monitor only<br>No control</div>
</div>
<div class="mode-card" onclick="selectMode('user')">
<div class="mode-icon">🔧</div>
<div class="mode-name">User</div>
<div class="mode-desc">Full control<br>Password required</div>
</div>
</div>
<div id="passwordSection" style="display:none">
<input type="password" id="loginPasswordInput" class="login-input" placeholder="Enter Password">
<button class="login-btn" onclick="checkPassword()">Login</button>
</div>
<div id="loginError" class="login-error">Incorrect password</div>
</div>
</div>
<button id="logoutBtn" class="logout-btn" style="display:none" onclick="logout()">🚪 Logout</button>
<div class="emergency-controls"><button class="btn-emergency" onclick="emergencyStop()">⚠️ EMERGENCY STOP</button></div>
<div class="container">
<header><h1>🎭 U-Track DMX Controller</h1>
<div class="subtitle">Advanced UWB Position Tracking System v2.0<span class="status-badge" id="systemStatus">Online</span></div></header>

<div class="tabs">
<button class="tab-btn active" onclick="switchTab('dashboard')" data-viewer-allowed>📊 Dashboard</button>
<button class="tab-btn" onclick="switchTab('stagemap')" data-viewer-allowed>🗺️ Stage Map</button>
<button class="tab-btn" onclick="switchTab('fixtures')" data-viewer-allowed>💡 Fixtures</button>
<button class="tab-btn" onclick="switchTab('profiles')">⚙️ Profiles</button>
<button class="tab-btn" onclick="switchTab('manual')" data-viewer-allowed>🎛️ Manual DMX</button>
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

<div class="card"><div class="card-title">� DMX Monitor <span style="font-size:0.7em;color:#888">(512 channels)</span></div>
<div class="dmx-monitor" id="dmxMonitor"></div></div>

<div class="card"><div class="card-title">�💡 Active Fixtures <span style="font-size:0.7em;color:#888" id="fixtureCount">(0)</span></div>
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
<button class="zoom-btn" onclick="toggleBeams()" id="beamToggle">💡 Show Beams</button>
<span class="zoom-level" id="zoomLevel">100%</span>
</div>
<div class="stage-container">
<canvas id="stageCanvas" class="stage-canvas" width="1600" height="1200"></canvas>
<svg id="beamOverlay" class="beam-overlay" width="1600" height="1200" style="display:none"></svg>
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
<button class="btn btn-primary" onclick="saveWiFiConfig()">💾 Save WiFi Settings</button>
<div style="margin-top:10px;padding:10px;background:#3d3d3d;border-radius:6px;font-size:0.9em">
<strong>Note:</strong> Device will connect to external WiFi as client while maintaining its own Access Point. 
You can access the dashboard from both networks.
</div>

<h3 style="color:#ff8c42;margin:30px 0 15px">Configuration Backup</h3>
<div class="form-group"><label class="form-label">Configuration Management</label>
<div style="display:flex;gap:10px">
<button class="btn btn-primary" onclick="downloadConfig()">📥 Download</button>
<button class="btn btn-success" onclick="document.getElementById('uploadInput').click()">📤 Upload</button>
<input type="file" id="uploadInput" accept=".json" style="display:none" onchange="uploadConfig(event)">
</div></div>

<h3 style="color:#ff8c42;margin:30px 0 15px">Password Protection</h3>
<div class="password-section">
<div class="form-group"><label class="form-label">Enable Password Protection</label>
<label><input type="checkbox" id="enablePassword" class="form-checkbox" onchange="togglePasswordFields()"> Require password to access dashboard</label>
</div>
<div id="passwordFields" style="display:none">
<div class="form-group"><label class="form-label">Password</label>
<input type="password" id="adminPassword" class="form-input" placeholder="Enter password"></div>
<div class="form-group"><label class="form-label">Confirm Password</label>
<input type="password" id="confirmPassword" class="form-input" placeholder="Confirm password"></div>
<button class="btn btn-primary" onclick="savePassword()">💾 Save Password</button>
</div>
</div>

<h3 style="color:#ff8c42;margin:30px 0 15px">DMX Mode Control</h3>
<div class="form-group"><label class="form-label">DMX Channel for Mode Switching</label>
<input type="number" id="dmxModeChannel" class="form-input" min="1" max="512" value="511" placeholder="Enter DMX channel (1-512)">
<div style="margin-top:10px;padding:10px;background:#3d3d3d;border-radius:6px;font-size:0.9em">
<strong>Mode Values:</strong> 0-50: Tracking Mode | 51-100: Manual Mode | 101-150: Emergency Stop | 151-255: Resume
</div>
<button class="btn btn-primary" onclick="saveDMXModeChannel()">💾 Save Mode Channel</button>
</div>

<h3 style="color:#ff8c42;margin:30px 0 15px">Full DMX Monitor</h3>
<div style="background:#1a1a1a;padding:15px;border-radius:8px;border:1px solid #555">
<label><input type="checkbox" id="enableDMXMonitor" class="form-checkbox" onchange="toggleDMXMonitor()"> Show all 512 DMX channels</label>
<div id="dmxMonitorPanel" style="display:none;margin-top:15px">
<div class="dmx-monitor-grid" id="dmxMonitorGrid"></div>
</div>
</div>
</div>
</div>

</div>

<div id="addFixtureModal" class="modal">
<div class="modal-content">
<div class="modal-header"><div class="modal-title">➕ Add Fixture</div>
<button class="modal-close" onclick="closeModal('addFixtureModal')">&times;</button></div>
<div class="form-group"><label class="form-label">Fixture Name</label>
<input type="text" id="fixtureName" class="form-input" placeholder="e.g., Front Spot 1"></div>
<div class="form-row">
<div class="form-group"><label class="form-label">DMX Address</label>
<input type="number" id="fixtureDMX" class="form-input" min="1" max="512" value="1"></div>
<div class="form-group"><label class="form-label">Profile</label>
<select id="fixtureProfile" class="form-select"><option>Loading...</option></select></div>
</div>
<div class="form-group"><label class="form-label">Position (meters)</label></div>
<div class="form-row">
<div class="form-group"><label class="form-label">X</label>
<input type="number" id="fixtureX" class="form-input" step="0.01" value="0"></div>
<div class="form-group"><label class="form-label">Y</label>
<input type="number" id="fixtureY" class="form-input" step="0.01" value="0"></div>
<div class="form-group"><label class="form-label">Z</label>
<input type="number" id="fixtureZ" class="form-input" step="0.01" value="2.5"></div>
</div>
<div style="display:flex;gap:10px;margin-top:20px">
<button class="btn btn-success" onclick="addFixture()">✓ Add</button>
<button class="btn btn-secondary" onclick="closeModal('addFixtureModal')">Cancel</button>
</div></div>
</div>

<div id="addProfileModal" class="modal">
<div class="modal-content">
<div class="modal-header"><div class="modal-title">➕ Add Profile</div>
<button class="modal-close" onclick="closeModal('addProfileModal')">&times;</button></div>
<div class="form-group"><label class="form-label">Profile Name</label>
<input type="text" id="profileName" class="form-input" placeholder="e.g., MAC 250"></div>
<h3 style="color:#00d4ff;margin:20px 0 15px">DMX Channels</h3>
<div class="form-row">
<div class="form-group"><label class="form-label">Pan Coarse</label>
<input type="number" id="profilePanCoarse" class="form-input" value="1"></div>
<div class="form-group"><label class="form-label">Pan Fine</label>
<input type="number" id="profilePanFine" class="form-input" value="2"></div>
<div class="form-group"><label class="form-label">Tilt Coarse</label>
<input type="number" id="profileTiltCoarse" class="form-input" value="3"></div>
<div class="form-group"><label class="form-label">Tilt Fine</label>
<input type="number" id="profileTiltFine" class="form-input" value="4"></div>
</div>
<div class="form-row">
<div class="form-group"><label class="form-label">Zoom</label>
<input type="number" id="profileZoom" class="form-input" value="0"></div>
<div class="form-group"><label class="form-label">Focus</label>
<input type="number" id="profileFocus" class="form-input" value="0"></div>
</div>
<h3 style="color:#00d4ff;margin:20px 0 15px">Physical Limits</h3>
<div class="form-row">
<div class="form-group"><label class="form-label">Pan Range (°)</label>
<input type="number" id="profilePanMax" class="form-input" value="540"></div>
<div class="form-group"><label class="form-label">Tilt Range (°)</label>
<input type="number" id="profileTiltMax" class="form-input" value="270"></div>
<div class="form-group"><label class="form-label">Tilt Home (°)</label>
<input type="number" id="profileTiltHome" class="form-input" value="135"></div>
</div>
<h3 style="color:#00d4ff;margin:20px 0 15px">Options</h3>
<div class="form-row">
<div class="form-group"><label><input type="checkbox" id="profileInvertPan" class="form-checkbox"> Invert Pan</label></div>
<div class="form-group"><label><input type="checkbox" id="profileInvertTilt" class="form-checkbox"> Invert Tilt</label></div>
<div class="form-group"><label><input type="checkbox" id="profileIsHanging" class="form-checkbox" checked> Is Hanging</label></div>
</div>
<div style="display:flex;gap:10px;margin-top:25px">
<button class="btn btn-success" onclick="addProfile()">✓ Add</button>
<button class="btn btn-secondary" onclick="closeModal('addProfileModal')">Cancel</button>
</div></div>
</div>

<script>
let config={profiles:[],fixtures:[]};
let currentTab='dashboard';
let stageWidth=30;
let stageDepth=25;
let stageZoom=1.0;
let editingFixtureIndex=-1;
let showBeams=false;
let cockMode=false;
let dmxMonitorData=new Array(513).fill(0);
let userMode='viewer';
let selectedLoginMode='';

document.addEventListener('DOMContentLoaded',()=>{
const savedMode=localStorage.getItem('userMode');
const loggedIn=localStorage.getItem('dmxLoggedIn')==='true';
if(savedMode&&loggedIn){
applyUserMode(savedMode);
document.getElementById('loginOverlay').classList.remove('active');
document.getElementById('logoutBtn').style.display='block';
}
loadConfig();loadStatus();
setInterval(loadStatus,1000);
setInterval(updateDMXMonitor,100);
const w=localStorage.getItem('stageWidth');
const d=localStorage.getItem('stageDepth');
const z=localStorage.getItem('stageZoom');
if(w){stageWidth=parseFloat(w);document.getElementById('stageWidth').value=stageWidth}
if(d){stageDepth=parseFloat(d);document.getElementById('stageDepth').value=stageDepth}
if(z){stageZoom=parseFloat(z)}
updateStageMap();
applyCockMode();
});

function switchTab(n){
document.querySelectorAll('.tab-btn').forEach(b=>b.classList.remove('active'));
document.querySelectorAll('.tab-content').forEach(c=>c.classList.remove('active'));
event.target.classList.add('active');
document.getElementById('tab-'+n).classList.add('active');
currentTab=n;
if(n==='fixtures')loadFixtures();
if(n==='profiles')loadProfiles();
if(n==='stagemap')updateStageMap();
if(n==='manual')loadManualFixtureList();
}

async function loadConfig(){
try{
const r=await fetch('/api/config');
config=await r.json();
updateUI();
}catch(e){console.error('Load config error:',e)}}

async function loadStatus(){
try{
const r=await fetch('/api/status');
const s=await r.json();
document.getElementById('posX').textContent=s.position.x.toFixed(2);
document.getElementById('posY').textContent=s.position.y.toFixed(2);
document.getElementById('posZ').textContent=s.position.z.toFixed(2);
document.getElementById('posRMSE').textContent=s.position.rmse.toFixed(3);
document.getElementById('posValid').textContent=s.position.valid?'Yes':'No';
document.getElementById('currentMode').textContent=s.mode;
updateModeButtons(s.mode);
document.getElementById('uptime').textContent=formatUptime(s.uptime);
document.getElementById('activeFixtures').textContent=s.fixtureCount;
document.getElementById('fixtureCount').textContent='('+s.fixtureCount+')';
if(currentTab==='stagemap')updateStageMap(s.position);
}catch(e){console.error('Status error:',e)}}

function updateModeButtons(m){
const map={'UWB-TRACKING':0,'PAN-TEST':1,'TILT-TEST':2,'SHUTTER-DIMMER':3,'COLOR-TEST':4,'GOBO-TEST':5,'MANUAL':6,'DMX-PASSTHROUGH':7};
const idx=map[m]||0;
document.querySelectorAll('.mode-btn').forEach((b,i)=>b.classList.toggle('active',i===idx));
}

function updateUI(){
document.getElementById('profileCount').textContent=config.profiles.length;
updateDashboardFixtures();
}

function updateDashboardFixtures(){
const l=document.getElementById('dashboardFixtureList');
if(config.fixtures.length===0){
l.innerHTML='<div style="text-align:center;padding:40px;color:#666">No fixtures</div>';
return;
}
l.innerHTML=config.fixtures.map((f,i)=>`
<div class="fixture-item">
<div class="fixture-info">
<div class="fixture-name">${f.name}</div>
<div class="fixture-details">
${f.profileName} | DMX:${f.dmxAddress} | Pos:(${f.position.x.toFixed(2)},${f.position.y.toFixed(2)},${f.position.z.toFixed(2)})
</div></div></div>
`).join('');
}

function loadFixtures(){
const l=document.getElementById('fixtureList');
if(config.fixtures.length===0){
l.innerHTML='<div style="text-align:center;padding:40px;color:#666">No fixtures</div>';
return;
}
l.innerHTML=config.fixtures.map((f,i)=>`
<div class="fixture-item">
<div class="fixture-info">
<div class="fixture-name">${f.name}</div>
<div class="fixture-details">${f.profileName} | DMX:${f.dmxAddress} | X=${f.position.x}m Y=${f.position.y}m Z=${f.position.z}m</div>
</div>
<div class="fixture-actions">
<button class="btn btn-primary btn-small" onclick="editFixture(${i})">✏️ Edit</button>
<button class="fixture-copy-btn btn btn-small" onclick="copyFixture(${i})">📋 Copy</button>
<button class="btn btn-danger btn-small" onclick="deleteFixture(${i})">🗑️</button>
</div></div>
`).join('');
}

function loadProfiles(){
const l=document.getElementById('profileList');
if(config.profiles.length===0){
l.innerHTML='<div style="text-align:center;padding:40px;color:#666">No profiles</div>';
return;
}
l.innerHTML=config.profiles.map((p,i)=>`
<div class="profile-card">
<div class="profile-header">
<div class="profile-name">${p.name}</div>
<button class="btn btn-danger btn-small" onclick="deleteProfile(${i})">🗑️</button>
</div>
<div class="channel-grid">
<div class="channel-item"><div class="channel-label">Pan</div><div class="channel-value">${p.panCoarse}/${p.panFine}</div></div>
<div class="channel-item"><div class="channel-label">Tilt</div><div class="channel-value">${p.tiltCoarse}/${p.tiltFine}</div></div>
<div class="channel-item"><div class="channel-label">Pan Range</div><div class="channel-value">${p.panMax}°</div></div>
<div class="channel-item"><div class="channel-label">Tilt Range</div><div class="channel-value">${p.tiltMax}°</div></div>
</div></div>
`).join('');
}

function openModal(id){document.getElementById(id).classList.add('active')}
function closeModal(id){
document.getElementById(id).classList.remove('active');
if(id==='addFixtureModal'){
editingFixtureIndex=-1;
document.querySelector('#addFixtureModal .modal-title').textContent='➕ Add Fixture';
}
}

function openAddFixtureModal(){
editingFixtureIndex=-1;
document.getElementById('fixtureName').value='';
document.getElementById('fixtureDMX').value=1;
document.getElementById('fixtureX').value=0;
document.getElementById('fixtureY').value=0;
document.getElementById('fixtureZ').value=2.5;
document.querySelector('#addFixtureModal .modal-title').textContent='➕ Add Fixture';
const s=document.getElementById('fixtureProfile');
s.innerHTML=config.profiles.map(p=>`<option value="${p.name}">${p.name}</option>`).join('');
openModal('addFixtureModal');
}

function openAddProfileModal(){openModal('addProfileModal')}

async function addFixture(){
const f={
name:document.getElementById('fixtureName').value,
dmxAddress:parseInt(document.getElementById('fixtureDMX').value),
profileName:document.getElementById('fixtureProfile').value,
position:{
x:parseFloat(document.getElementById('fixtureX').value)||0,
y:parseFloat(document.getElementById('fixtureY').value)||0,
z:parseFloat(document.getElementById('fixtureZ').value)||0
}};
if(!f.name||!f.profileName){alert('Fill all fields');return}
if(editingFixtureIndex>=0){
config.fixtures[editingFixtureIndex]=f;
editingFixtureIndex=-1;
}else{
config.fixtures.push(f);
}
await saveConfig();
closeModal('addFixtureModal');
loadFixtures();updateUI();
}

function editFixture(i){
const f=config.fixtures[i];
editingFixtureIndex=i;
document.getElementById('fixtureName').value=f.name;
document.getElementById('fixtureDMX').value=f.dmxAddress;
document.getElementById('fixtureX').value=f.position.x;
document.getElementById('fixtureY').value=f.position.y;
document.getElementById('fixtureZ').value=f.position.z;
const s=document.getElementById('fixtureProfile');
s.innerHTML=config.profiles.map(p=>`<option value="${p.name}" ${p.name===f.profileName?'selected':''}>${p.name}</option>`).join('');
document.querySelector('#addFixtureModal .modal-title').textContent='✏️ Edit Fixture';
openModal('addFixtureModal');
}

async function deleteFixture(i){
if(!confirm('Delete fixture?'))return;
config.fixtures.splice(i,1);
await saveConfig();
loadFixtures();updateUI();
}

function copyFixture(i){
const f=config.fixtures[i];
const copy={
name:`${f.name} (Copy)`,
profileName:f.profileName,
dmxAddress:f.dmxAddress+32,
position:{x:f.position.x+1,y:f.position.y,z:f.position.z}
};
if(copy.dmxAddress>512)copy.dmxAddress=1;
config.fixtures.push(copy);
saveConfig().then(()=>{loadFixtures();updateUI();});
}

let beamsVisible=false;
function toggleBeams(){
beamsVisible=!beamsVisible;
const overlay=document.getElementById('beamOverlay');
const btn=document.getElementById('beamToggle');
overlay.style.display=beamsVisible?'block':'none';
btn.textContent=beamsVisible?'💡 Hide Beams':'💡 Show Beams';
if(beamsVisible)drawBeams();
}

function drawBeams(){
const svg=document.getElementById('beamOverlay');
const canvas=document.getElementById('stageCanvas');
const w=parseFloat(document.getElementById('stageWidth').value);
const d=parseFloat(document.getElementById('stageDepth').value);
const cw=canvas.width;
const ch=canvas.height;
const padding=40*stageZoom;
const scale=Math.min((cw-padding*2)/w,(ch-padding*2)/d);
const offsetX=cw/2-(w*scale)/2;
const offsetY=ch/2-(d*scale)/2;
let beams='';
config.fixtures.forEach(f=>{
const fx=offsetX+f.position.x*scale;
const fy=offsetY+(d-f.position.y)*scale;
if(position&&position.valid){
const tx=offsetX+position.x*scale;
const ty=offsetY+(d-position.y)*scale;
beams+=`<line x1="${fx}" y1="${fy}" x2="${tx}" y2="${ty}" stroke="rgba(255,140,66,0.4)" stroke-width="30" opacity="0.6"/>`;
beams+=`<circle cx="${fx}" cy="${fy}" r="8" fill="#ff8c42" opacity="0.8"/>`;
}
});
svg.innerHTML=beams;
}

let dmxMonitorInterval=null;
function updateDMXMonitor(){
fetch('/api/dmx/status').then(r=>r.json()).then(data=>{
const monitors=['dmxMonitor','dmxMonitorManual'];
monitors.forEach(monitorId=>{
const m=document.getElementById(monitorId);
if(!m)return;
if(!m.children.length){
let html='';
for(let i=1;i<=512;i++){
html+=`<div class="dmx-channel"><div class="dmx-channel-num">${i}</div><div class="dmx-bar-container"><div class="dmx-bar" id="${monitorId}_dmx${i}" style="height:0%"></div></div></div>`;
}
m.innerHTML=html;
}
});
data.channels.forEach((v,i)=>{
monitors.forEach(monitorId=>{
const bar=document.getElementById(`${monitorId}_dmx${i+1}`);
if(bar){
const pct=(v/255*100).toFixed(1);
bar.style.height=pct+'%';
bar.style.opacity=(v>0)?1:0.3;
}
});
});
}).catch(()=>{});
}

function selectMode(mode){
selectedLoginMode=mode;
document.querySelectorAll('.mode-card').forEach(c=>c.classList.remove('selected'));
event.target.closest('.mode-card').classList.add('selected');
if(mode==='viewer'){
applyUserMode('viewer');
localStorage.setItem('userMode','viewer');
localStorage.setItem('dmxLoggedIn','true');
document.getElementById('loginOverlay').classList.remove('active');
document.getElementById('logoutBtn').style.display='block';
}else{
document.getElementById('passwordSection').style.display='block';
document.getElementById('loginPasswordInput').focus();
}
}

function checkPassword(){
const input=document.getElementById('loginPasswordInput');
const error=document.getElementById('loginError');
const pwd=input.value.trim();
if(pwd==='admin'||pwd==='user'){
applyUserMode('user');
localStorage.setItem('userMode','user');
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

function applyUserMode(mode){
userMode=mode;
if(mode==='viewer'){
document.body.classList.add('viewer-mode');
}else{
document.body.classList.remove('viewer-mode');
}
}

function logout(){
localStorage.removeItem('dmxLoggedIn');
localStorage.removeItem('userMode');
location.reload();
}

document.getElementById('loginPasswordInput')?.addEventListener('keypress',(e)=>{
if(e.key==='Enter')checkPassword();
});

async function addProfile(){
const p={
name:document.getElementById('profileName').value,
panCoarse:parseInt(document.getElementById('profilePanCoarse').value),
panFine:parseInt(document.getElementById('profilePanFine').value),
tiltCoarse:parseInt(document.getElementById('profileTiltCoarse').value),
tiltFine:parseInt(document.getElementById('profileTiltFine').value),
zoom:parseInt(document.getElementById('profileZoom').value),
focus:parseInt(document.getElementById('profileFocus').value),
panMin:0,
panMax:parseFloat(document.getElementById('profilePanMax').value),
tiltMin:0,
tiltMax:parseFloat(document.getElementById('profileTiltMax').value),
tiltHome:parseFloat(document.getElementById('profileTiltHome').value),
panHomeOffset:0,
invertPan:document.getElementById('profileInvertPan').checked,
invertTilt:document.getElementById('profileInvertTilt').checked,
invertZoom:false,
isHanging:document.getElementById('profileIsHanging').checked,
dimmer:0,shutter:0,colorWheel:0,goboWheel:0,goboRotation:0,control:0,
zoomMinAngle:5,zoomMaxAngle:50,zoomCalibDist1:5,zoomCalibAngle1:25,
focusDMX1:127,zoomCalibDist2:20,zoomCalibAngle2:5,focusDMX2:10,
invertFocus:false,panDeadZone:2,tiltDeadZone:2
};
if(!p.name){alert('Enter profile name');return}
config.profiles.push(p);
await saveConfig();
closeModal('addProfileModal');
loadProfiles();updateUI();
}

async function deleteProfile(i){
if(!confirm('Delete profile?'))return;
config.profiles.splice(i,1);
await saveConfig();
loadProfiles();updateUI();
}

async function saveConfig(){
try{
const r=await fetch('/api/config/save',{
method:'POST',
headers:{'Content-Type':'application/json'},
body:JSON.stringify(config)
});
if(!r.ok)alert('Save failed');
}catch(e){console.error('Save error:',e);alert('Save failed')}}

async function setMode(m){
try{await fetch('/api/mode?mode='+m);loadStatus()}
catch(e){console.error('Mode error:',e)}}

async function emergencyStop(){
if(!confirm('EMERGENCY STOP?'))return;
try{await fetch('/api/emergency');alert('Emergency stop activated')}
catch(e){console.error('Emergency error:',e)}}

function downloadConfig(){
const dataStr=JSON.stringify(config,null,2);
const dataUri='data:application/json;charset=utf-8,'+encodeURIComponent(dataStr);
const link=document.createElement('a');
link.setAttribute('href',dataUri);
link.setAttribute('download','utrack-config.json');
link.click();
}

async function uploadConfig(event){
const file=event.target.files[0];
if(!file)return;
const reader=new FileReader();
reader.onload=async(e)=>{
try{
config=JSON.parse(e.target.result);
await saveConfig();
alert('Config uploaded');
loadConfig();
}catch(error){alert('Invalid config')}};
reader.readAsText(file);
}

function zoomIn(){
stageZoom=Math.min(stageZoom*1.2,5.0);
localStorage.setItem('stageZoom',stageZoom);
updateStageMap();
document.getElementById('zoomLevel').textContent=Math.round(stageZoom*100)+'%';
}

function zoomOut(){
stageZoom=Math.max(stageZoom/1.2,0.3);
localStorage.setItem('stageZoom',stageZoom);
updateStageMap();
document.getElementById('zoomLevel').textContent=Math.round(stageZoom*100)+'%';
}

function zoomFit(){
stageZoom=1.0;
localStorage.setItem('stageZoom',stageZoom);
updateStageMap();
document.getElementById('zoomLevel').textContent='100%';
}

function loadManualFixtureList(){
const sel=document.getElementById('manualFixtureSelect');
sel.innerHTML='<option value="">-- Select a fixture --</option>'+
config.fixtures.map((f,i)=>`<option value="${i}">${f.name} (DMX ${f.dmxAddress})</option>`).join('');
}

function loadManualChannels(){
const showAll=document.getElementById('showAllFixtures')?.checked;
if(showAll){
if(config.fixtures.length===0){
document.getElementById('manualChannelPanel').innerHTML='<div style="text-align:center;padding:40px;color:#888">No fixtures configured</div>';
return;
}
let html='';
config.fixtures.forEach((f,fidx)=>{
const profile=config.profiles.find(p=>p.name===f.profileName);
if(!profile)return;
const channels=[
{name:'Pan',ch:profile.panCoarse,id:`f${fidx}_panCoarse`},
{name:'PanFine',ch:profile.panFine,id:`f${fidx}_panFine`},
{name:'Tilt',ch:profile.tiltCoarse,id:`f${fidx}_tiltCoarse`},
{name:'TiltFine',ch:profile.tiltFine,id:`f${fidx}_tiltFine`},
{name:'Zoom',ch:profile.zoom,id:`f${fidx}_zoom`},
{name:'Focus',ch:profile.focus,id:`f${fidx}_focus`},
{name:'Dimmer',ch:profile.dimmer||0,id:`f${fidx}_dimmer`},
{name:'Shutter',ch:profile.shutter||0,id:`f${fidx}_shutter`}
].filter(c=>c.ch>0);
html+=`<div class="fixture-control-group"><h3>${f.name} (DMX ${f.dmxAddress})</h3><div class="dmx-control-panel">`;
html+=channels.map(c=>`
<div class="dmx-channel">
<div class="dmx-channel-label">${c.name}<br>CH ${f.dmxAddress+c.ch-1}</div>
<input type="range" class="dmx-slider" orient="vertical" min="0" max="255" value="0" 
oninput="setDMXChannel(${f.dmxAddress+c.ch-1},this.value,'${c.id}Value')">
<div class="dmx-channel-value" id="${c.id}Value">0</div>
</div>
`).join('');
html+=`</div></div>`;
});
document.getElementById('manualChannelPanel').innerHTML=html;
document.getElementById('manualFixtureSelectDiv').style.display='none';
return;
}
document.getElementById('manualFixtureSelectDiv').style.display='block';
const sel=document.getElementById('manualFixtureSelect');
const idx=parseInt(sel.value);
if(isNaN(idx)||idx<0){
document.getElementById('manualChannelPanel').innerHTML='<div style="text-align:center;padding:40px;color:#888">Select a fixture to control DMX channels</div>';
return;
}
const f=config.fixtures[idx];
const profile=config.profiles.find(p=>p.name===f.profileName);
if(!profile){
document.getElementById('manualChannelPanel').innerHTML='<div style="text-align:center;padding:40px;color:#888">Profile not found</div>';
return;
}
const channels=[
{name:'Pan',ch:profile.panCoarse,id:'panCoarse'},
{name:'Pan Fine',ch:profile.panFine,id:'panFine'},
{name:'Tilt',ch:profile.tiltCoarse,id:'tiltCoarse'},
{name:'Tilt Fine',ch:profile.tiltFine,id:'tiltFine'},
{name:'Zoom',ch:profile.zoom,id:'zoom'},
{name:'Focus',ch:profile.focus,id:'focus'},
{name:'Dimmer',ch:profile.dimmer||0,id:'dimmer'},
{name:'Shutter',ch:profile.shutter||0,id:'shutter'}
].filter(c=>c.ch>0);
document.getElementById('manualChannelPanel').innerHTML='<div class="dmx-control-panel">'+
channels.map(c=>`
<div class="dmx-channel">
<div class="dmx-channel-label">${c.name}<br>CH ${f.dmxAddress+c.ch-1}</div>
<input type="range" class="dmx-slider" orient="vertical" min="0" max="255" value="0" 
oninput="setDMXChannel(${f.dmxAddress+c.ch-1},this.value,'${c.id}Value')">
<div class="dmx-channel-value" id="${c.id}Value">0</div>
</div>
`).join('')+'</div>';
}

async function setDMXChannel(ch,val,elemId){
document.getElementById(elemId).textContent=val;
try{
await fetch('/api/dmx/set?ch='+ch+'&val='+val);
}catch(e){console.error('DMX set error:',e)}
}

async function saveWiFiConfig(){
const ssid=document.getElementById('wifiSSID').value;
const pass=document.getElementById('wifiPassword').value;
if(!ssid){alert('Enter WiFi SSID');return}
try{
const r=await fetch('/api/wifi/config',{
method:'POST',
headers:{'Content-Type':'application/json'},
body:JSON.stringify({ssid:ssid,password:pass})
});
if(r.ok){
alert('WiFi settings saved! Device will connect to network on next restart.');
}else{
alert('Failed to save WiFi settings');
}
}catch(e){
console.error('WiFi config error:',e);
alert('Error saving WiFi settings');
}
}

function updateStageMap(position){
const w=parseFloat(document.getElementById('stageWidth').value)||30;
const d=parseFloat(document.getElementById('stageDepth').value)||25;
stageWidth=w;stageDepth=d;
localStorage.setItem('stageWidth',w);
localStorage.setItem('stageDepth',d);
const canvas=document.getElementById('stageCanvas');
if(!canvas)return;
const ctx=canvas.getContext('2d');
const cw=canvas.width;
const ch=canvas.height;
const padding=80;
const drawW=cw-2*padding;
const drawH=ch-2*padding;
const baseScale=Math.min(drawW/w,drawH/d);
const scale=baseScale*stageZoom;
const offsetX=padding+(drawW-w*scale)/2;
const offsetY=padding+(drawH-d*scale)/2;
ctx.clearRect(0,0,cw,ch);
ctx.fillStyle='#1a1a1a';
ctx.fillRect(0,0,cw,ch);
ctx.save();
ctx.strokeStyle='#555';
ctx.lineWidth=3;
ctx.strokeRect(offsetX,offsetY,w*scale,d*scale);
ctx.fillStyle='#2d2d2d';
ctx.fillRect(offsetX,offsetY,w*scale,d*scale);
ctx.strokeStyle='#444';
ctx.lineWidth=1;
const gridStep=stageZoom<0.5?10:5;
for(let i=0;i<=w;i+=gridStep){
const x=offsetX+i*scale;
ctx.beginPath();
ctx.moveTo(x,offsetY);
ctx.lineTo(x,offsetY+d*scale);
ctx.stroke();
ctx.fillStyle='#888';
ctx.font='12px monospace';
ctx.fillText(i+'m',x-12,offsetY+d*scale+25);
}
for(let i=0;i<=d;i+=gridStep){
const y=offsetY+d*scale-i*scale;
ctx.beginPath();
ctx.moveTo(offsetX,y);
ctx.lineTo(offsetX+w*scale,y);
ctx.stroke();
ctx.fillStyle='#888';
ctx.font='12px monospace';
ctx.fillText(i+'m',offsetX-35,y+5);
}
const iconSize=Math.max(8,12*stageZoom);
const fontSize=Math.max(11,14*stageZoom);
config.fixtures.forEach(f=>{
const fx=offsetX+f.position.x*scale;
const fy=offsetY+(d-f.position.y)*scale;
ctx.fillStyle='#66bb6a';
ctx.beginPath();
ctx.arc(fx,fy,iconSize,0,Math.PI*2);
ctx.fill();
ctx.strokeStyle='#4caf50';
ctx.lineWidth=2*stageZoom;
ctx.stroke();
ctx.fillStyle='#fff';
ctx.font=`bold ${Math.round(16*stageZoom)}px sans-serif`;
ctx.fillText('💡',fx-iconSize,fy+iconSize/2);
if(stageZoom>=0.8){
ctx.fillStyle='#fff';
ctx.font=`${fontSize}px sans-serif`;
ctx.fillText(f.name,fx+iconSize+4,fy+5);
}
});
if(position&&position.valid){
const tx=offsetX+position.x*scale;
const ty=offsetY+(d-position.y)*scale;
const targetSize=Math.max(10,15*stageZoom);
ctx.fillStyle='rgba(255,140,66,0.3)';
ctx.beginPath();
ctx.arc(tx,ty,targetSize*2,0,Math.PI*2);
ctx.fill();
ctx.fillStyle='#ff8c42';
ctx.beginPath();
ctx.arc(tx,ty,targetSize,0,Math.PI*2);
ctx.fill();
ctx.strokeStyle='#ff6b1a';
ctx.lineWidth=3*stageZoom;
ctx.stroke();
ctx.fillStyle='#fff';
ctx.font=`bold ${Math.round(18*stageZoom)}px sans-serif`;
ctx.fillText('🎯',tx-targetSize,ty+targetSize/2);
if(stageZoom>=0.7){
ctx.fillStyle='#ff8c42';
ctx.font=`bold ${Math.round(14*stageZoom)}px sans-serif`;
ctx.fillText(`(${position.x.toFixed(1)},${position.y.toFixed(1)})`,tx+targetSize+5,ty-targetSize);
}
}
ctx.restore();
}

function formatUptime(s){
const d=Math.floor(s/86400);
const h=Math.floor((s%86400)/3600);
const m=Math.floor((s%3600)/60);
const sec=s%60;
if(d>0)return`${d}d ${h}h ${m}m`;
if(h>0)return`${h}h ${m}m ${sec}s`;
if(m>0)return`${m}m ${sec}s`;
return`${sec}s`;
}

function applyCockMode(){
const urlParams=new URLSearchParams(window.location.search);
const isCock=urlParams.get('mode')==='cock'||localStorage.getItem('cockMode')==='true';
if(isCock){
document.body.classList.add('cock-mode');
const headerTitle=document.querySelector('h1');
if(headerTitle)headerTitle.innerHTML='🐔 C.O.C.K. Control Panel 🍆';
document.querySelectorAll('.card-title').forEach(el=>{
if(el.textContent.includes('Fixture'))el.textContent='🐔 '+el.textContent.replace('💡','🐔');
});
localStorage.setItem('cockMode','true');
}else{
document.body.classList.remove('cock-mode');
localStorage.removeItem('cockMode');
}
}

function toggleCockMode(){
const isCockActive=localStorage.getItem('cockMode')==='true';
if(isCockActive){
localStorage.removeItem('cockMode');
window.location.search='';
}else{
localStorage.setItem('cockMode','true');
window.location.search='?mode=cock';
}
}

</script>
<div class="cock-easter-egg" onclick="toggleCockMode()" title="Toggle C.O.C.K. Mode">🐔</div>
</body>
</html>
)===";

