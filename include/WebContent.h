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
*{margin:0;padding:0;box-sizing:border-box}
body{font-family:-apple-system,BlinkMacSystemFont,'Segoe UI',Roboto,sans-serif;background:linear-gradient(135deg,#1a1a1a 0%,#2d2d2d 50%,#0a0a0a 100%);color:#e8e8e8;min-height:100vh}
.container{max-width:1600px;margin:0 auto;padding:20px}
header{background:#2d2d2d;padding:25px;border-radius:15px;margin-bottom:25px;box-shadow:0 8px 32px rgba(0,0,0,0.5);border:1px solid #444}
h1{color:#ff8c42;font-size:2.8em;text-shadow:0 0 20px rgba(255,140,66,0.4);margin-bottom:10px}
.subtitle{color:#b0b0b0;font-size:1.1em;display:flex;align-items:center;gap:10px}
.status-badge{display:inline-block;padding:5px 15px;border-radius:20px;font-size:0.85em;font-weight:600;background:rgba(255,140,66,0.2);color:#ff8c42;border:1px solid #ff8c42}
.emergency-controls{position:fixed;top:20px;right:20px;z-index:1000}
.btn-emergency{background:linear-gradient(135deg,#ff4444 0%,#cc0000 100%);color:white;border:none;padding:18px 35px;border-radius:50px;font-size:16px;font-weight:bold;cursor:pointer;box-shadow:0 6px 25px rgba(255,68,68,0.4);transition:all 0.3s;text-transform:uppercase}
.btn-emergency:hover{transform:translateY(-2px);box-shadow:0 8px 30px rgba(255,68,68,0.6)}
.tabs{display:flex;gap:10px;margin-bottom:25px;background:#1a1a1a;padding:10px;border-radius:12px}
.tab-btn{flex:1;padding:15px 25px;border:none;background:#2d2d2d;color:#b0b0b0;border-radius:8px;cursor:pointer;transition:all 0.3s;font-size:15px;font-weight:600}
.tab-btn:hover{background:#3d3d3d;color:#fff}
.tab-btn.active{background:linear-gradient(135deg,#ff8c42 0%,#ff6b1a 100%);color:white;box-shadow:0 4px 15px rgba(255,140,66,0.4)}
.tab-content{display:none;animation:fadeIn 0.3s}
.tab-content.active{display:block}
@keyframes fadeIn{from{opacity:0;transform:translateY(10px)}to{opacity:1;transform:translateY(0)}}
.card{background:#2d2d2d;border-radius:12px;padding:25px;margin-bottom:20px;box-shadow:0 4px 20px rgba(0,0,0,0.5);border:1px solid #444}
.card-title{font-size:1.5em;margin-bottom:20px;color:#ff8c42;display:flex;align-items:center;gap:10px}
.grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(300px,1fr));gap:20px}
.grid-2{display:grid;grid-template-columns:1fr 1fr;gap:20px}
.position-display{display:grid;grid-template-columns:repeat(4,1fr);gap:15px;margin-top:15px}
.position-item{background:#1a1a1a;padding:15px;border-radius:8px;text-align:center;border:1px solid #ff8c42}
.position-label{font-size:0.85em;color:#b0b0b0;margin-bottom:5px}
.position-value{font-size:1.8em;font-weight:bold;color:#ff8c42}
.position-unit{font-size:0.8em;color:#888}
.fixture-list{display:flex;flex-direction:column;gap:10px}
.fixture-item{background:#3d3d3d;padding:20px;border-radius:10px;display:flex;justify-content:space-between;align-items:center;transition:all 0.3s;border:1px solid #555}
.fixture-item:hover{background:#4d4d4d;border-color:#ff8c42}
.fixture-info{flex:1}
.fixture-name{font-size:1.2em;font-weight:600;color:#fff;margin-bottom:5px}
.fixture-details{font-size:0.9em;color:#b0b0b0}
.fixture-actions{display:flex;gap:10px}
.btn{padding:10px 20px;border:none;border-radius:6px;cursor:pointer;font-size:14px;font-weight:600;transition:all 0.3s}
.btn-primary{background:linear-gradient(135deg,#ff8c42 0%,#ff6b1a 100%);color:white;box-shadow:0 4px 15px rgba(255,140,66,0.3)}
.btn-primary:hover{transform:translateY(-2px)}
.btn-success{background:linear-gradient(135deg,#66bb6a 0%,#43a047 100%);color:white}
.btn-danger{background:linear-gradient(135deg,#ef5350 0%,#e53935 100%);color:white}
.btn-secondary{background:#555;color:#fff}
.btn-small{padding:8px 15px;font-size:12px}
.form-group{margin-bottom:20px}
.form-label{display:block;margin-bottom:8px;color:#b0b0b0;font-size:0.95em;font-weight:600}
.form-input,.form-select{width:100%;padding:12px 15px;background:#1a1a1a;border:1px solid #555;border-radius:6px;color:#fff;font-size:14px}
.form-input:focus,.form-select:focus{outline:none;border-color:#ff8c42;background:#2d2d2d}
.form-checkbox{margin-right:8px}
.form-row{display:grid;grid-template-columns:repeat(auto-fit,minmax(200px,1fr));gap:15px}
.modal{display:none;position:fixed;top:0;left:0;width:100%;height:100%;background:rgba(0,0,0,0.85);z-index:2000;overflow-y:auto}
.modal.active{display:flex;align-items:center;justify-content:center}
.modal-content{background:#2d2d2d;border-radius:15px;padding:30px;max-width:800px;width:90%;max-height:90vh;overflow-y:auto;box-shadow:0 20px 60px rgba(0,0,0,0.7);border:1px solid #555}
.modal-header{display:flex;justify-content:space-between;align-items:center;margin-bottom:25px}
.modal-title{font-size:1.8em;color:#ff8c42}
.modal-close{background:none;border:none;color:#fff;font-size:2em;cursor:pointer;width:40px;height:40px;border-radius:50%}
.modal-close:hover{background:#3d3d3d}
.mode-controls{display:grid;grid-template-columns:repeat(auto-fit,minmax(150px,1fr));gap:10px;margin-top:15px}
.mode-btn{padding:15px;background:#3d3d3d;border:2px solid #555;border-radius:8px;color:#fff;cursor:pointer;font-weight:600;text-align:center}
.mode-btn:hover{background:#4d4d4d;border-color:#ff8c42}
.mode-btn.active{background:rgba(255,140,66,0.2);border-color:#ff8c42;color:#ff8c42}
.profile-list{display:grid;gap:15px;margin-top:20px}
.profile-card{background:#3d3d3d;padding:20px;border-radius:10px;border:1px solid #555}
.profile-card:hover{border-color:#ff8c42;background:#4d4d4d}
.profile-header{display:flex;justify-content:space-between;align-items:center;margin-bottom:15px}
.profile-name{font-size:1.3em;font-weight:600;color:#fff}
.channel-grid{display:grid;grid-template-columns:repeat(auto-fill,minmax(120px,1fr));gap:10px;margin-top:15px}
.channel-item{background:#1a1a1a;padding:10px;border-radius:6px;text-align:center}
.channel-label{font-size:0.75em;color:#b0b0b0;margin-bottom:5px}
.channel-value{font-size:1.2em;font-weight:bold;color:#ff8c42}
.stage-container{position:relative;width:100%;background:#1a1a1a;border:2px solid #555;border-radius:8px;overflow:hidden}
.stage-canvas{width:100%;display:block;cursor:crosshair}
.stage-controls{display:flex;gap:10px;margin-bottom:15px;align-items:center}
.zoom-btn{padding:8px 16px;background:#3d3d3d;border:1px solid #555;border-radius:6px;color:#fff;cursor:pointer;font-weight:600}
.zoom-btn:hover{background:#4d4d4d;border-color:#ff8c42}
.zoom-level{color:#b0b0b0;font-size:0.9em;margin:0 10px}
.stage-legend{margin-top:15px;display:flex;gap:20px;flex-wrap:wrap;justify-content:center}
.legend-item{display:flex;align-items:center;gap:8px;color:#b0b0b0;font-size:0.9em}
.legend-icon{width:20px;height:20px;border-radius:3px}
.dmx-control-panel{display:grid;grid-template-columns:repeat(auto-fill,minmax(80px,1fr));gap:10px;margin-top:15px}
.dmx-channel{background:#1a1a1a;padding:10px;border-radius:6px;text-align:center;border:1px solid #555}
.dmx-channel-label{font-size:0.75em;color:#b0b0b0;margin-bottom:5px}
.dmx-channel-value{font-size:1em;font-weight:bold;color:#ff8c42;margin:5px 0}
.dmx-slider{width:100%;height:100px;writing-mode:bt-lr;-webkit-appearance:slider-vertical;background:#3d3d3d;outline:none}
.dmx-slider::-webkit-slider-thumb{-webkit-appearance:none;width:20px;height:10px;background:#ff8c42;cursor:pointer}
.manual-fixture-select{margin-bottom:15px}
@media (max-width:768px){h1{font-size:2em}.grid-2{grid-template-columns:1fr}.position-display{grid-template-columns:repeat(2,1fr)}.emergency-controls{position:static;margin-bottom:20px}}
</style>
</head>
<body>
<div class="emergency-controls"><button class="btn-emergency" onclick="emergencyStop()">⚠️ EMERGENCY STOP</button></div>
<div class="container">
<header><h1>🎭 U-Track DMX Controller</h1>
<div class="subtitle">Advanced UWB Position Tracking System v2.0<span class="status-badge" id="systemStatus">Online</span></div></header>

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
<div class="card"><div class="card-title">🎛️ Manual DMX Control</div>
<div class="manual-fixture-select">
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

document.addEventListener('DOMContentLoaded',()=>{
loadConfig();loadStatus();setInterval(loadStatus,1000);
const w=localStorage.getItem('stageWidth');
const d=localStorage.getItem('stageDepth');
const z=localStorage.getItem('stageZoom');
if(w){stageWidth=parseFloat(w);document.getElementById('stageWidth').value=stageWidth}
if(d){stageDepth=parseFloat(d);document.getElementById('stageDepth').value=stageDepth}
if(z){stageZoom=parseFloat(z)}
updateStageMap();
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
</script>
</body>
</html>
)===";
