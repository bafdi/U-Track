#pragma once

// ============================================================================
// U-TRACK DMX CONTROLLER - EMBEDDED WEB DASHBOARD v2.1 (Optimized)
// Simplified and compressed for stability
// ============================================================================

const char HTML_DASHBOARD[] PROGMEM = R"===(
<!DOCTYPE html>
<html><head><meta charset="UTF-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>U-Track DMX v2.1</title>
<style>
*{margin:0;padding:0;box-sizing:border-box}
body{font-family:Arial,sans-serif;background:#0f0f0f;color:#e8e8e8;min-height:100vh}
.container{max-width:1600px;margin:0 auto;padding:15px}
header{background:#2b2b2b;padding:15px 20px;border-radius:2px;margin-bottom:15px;border-left:3px solid #ff8c42}
h1{color:#ff8c42;font-size:1.8em;margin-bottom:5px}
.subtitle{color:#999;font-size:0.9em}
.status-badge{display:inline-block;padding:3px 10px;border-radius:2px;font-size:0.75em;background:#4caf50;color:#000;margin-left:10px}
.emergency-controls{position:fixed;top:15px;right:15px;z-index:1000}
.btn-emergency{background:#ff1744;color:#fff;border:2px solid #ff1744;padding:12px 20px;border-radius:2px;cursor:pointer;font-weight:bold}
.btn-emergency:hover{background:transparent;color:#ff1744}
.tabs{display:flex;gap:0;margin-bottom:15px;background:#1a1a1a}
.tab-btn{flex:1;padding:12px 15px;border:none;background:#1a1a1a;color:#666;cursor:pointer;font-size:12px}
.tab-btn:hover{background:#2b2b2b;color:#ff8c42}
.tab-btn.active{background:#ff8c42;color:#000}
.tab-content{display:none}
.tab-content.active{display:block}
.card{background:#2b2b2b;border-radius:2px;padding:15px;margin-bottom:12px;border-left:3px solid #ff8c42}
.card-title{font-size:1.2em;margin-bottom:12px;color:#ff8c42;font-weight:bold;border-bottom:1px solid #333;padding-bottom:6px}
.grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(280px,1fr));gap:12px}
.grid-2{display:grid;grid-template-columns:1fr 1fr;gap:12px}
.position-display{display:grid;grid-template-columns:repeat(4,1fr);gap:10px;margin-top:10px}
.position-item{background:#1a1a1a;padding:10px;border-radius:2px;text-align:center}
.position-label{font-size:0.7em;color:#666;margin-bottom:3px}
.position-value{font-size:1.6em;font-weight:bold;color:#ff8c42}
.position-unit{font-size:0.7em;color:#555}
.fixture-list{display:flex;flex-direction:column;gap:6px}
.fixture-item{background:#1a1a1a;padding:12px;border-radius:2px;display:flex;justify-content:space-between;align-items:center}
.fixture-item:hover{background:#2b2b2b}
.fixture-info{flex:1}
.fixture-name{font-size:1em;font-weight:bold;color:#fff;margin-bottom:3px}
.fixture-details{font-size:0.8em;color:#666}
.fixture-actions{display:flex;gap:6px}
.btn{padding:6px 12px;border:2px solid;border-radius:2px;cursor:pointer;font-size:11px;font-weight:bold}
.btn-primary{background:#ff8c42;color:#000;border-color:#ff8c42}
.btn-primary:hover{background:transparent;color:#ff8c42}
.btn-success{background:#4caf50;color:#000;border-color:#4caf50}
.btn-success:hover{background:transparent;color:#4caf50}
.btn-danger{background:#ff1744;color:#fff;border-color:#ff1744}
.btn-danger:hover{background:transparent;color:#ff1744}
.btn-secondary{background:transparent;color:#666;border-color:#444}
.btn-secondary:hover{border-color:#ff8c42;color:#ff8c42}
.btn-small{padding:4px 8px;font-size:10px}
.form-group{margin-bottom:12px}
.form-label{display:block;margin-bottom:5px;color:#999;font-size:0.8em;font-weight:bold}
.form-input,.form-select{width:100%;padding:8px 10px;background:#1a1a1a;border:1px solid#333;border-radius:2px;color:#fff;font-size:12px}
.form-input:focus,.form-select:focus{outline:none;border-color:#ff8c42}
.form-checkbox{margin-right:6px}
.form-row{display:grid;grid-template-columns:repeat(auto-fit,minmax(180px,1fr));gap:10px}
.modal{display:none;position:fixed;top:0;left:0;width:100%;height:100%;background:rgba(0,0,0,0.9);z-index:2000;overflow-y:auto}
.modal.active{display:flex;align-items:center;justify-content:center}
.modal-content{background:#2b2b2b;border-radius:2px;padding:20px;max-width:800px;width:90%;max-height:90vh;overflow-y:auto;border:2px solid #ff8c42}
.modal-header{display:flex;justify-content:space-between;align-items:center;margin-bottom:15px;border-bottom:1px solid #333;padding-bottom:10px}
.modal-title{font-size:1.3em;color:#ff8c42;font-weight:bold}
.modal-close{background:transparent;border:2px solid #666;color:#666;font-size:1.2em;cursor:pointer;width:30px;height:30px;border-radius:2px}
.modal-close:hover{background:#ff1744;border-color:#ff1744;color:#fff}
.mode-controls{display:grid;grid-template-columns:repeat(auto-fit,minmax(120px,1fr));gap:6px;margin-top:10px}
.mode-btn{padding:10px;background:#1a1a1a;border:2px solid #333;border-radius:2px;color:#666;cursor:pointer;font-weight:bold;text-align:center;font-size:11px}
.mode-btn:hover{border-color:#ff8c42;color:#ff8c42}
.mode-btn.active{background:#ff8c42;border-color:#ff8c42;color:#000}
.profile-list{display:grid;gap:10px;margin-top:12px}
.profile-card{background:#1a1a1a;padding:12px;border-radius:2px}
.profile-card:hover{background:#2b2b2b}
.profile-header{display:flex;justify-content:space-between;align-items:center;margin-bottom:10px}
.profile-name{font-size:1.1em;font-weight:bold;color:#fff}
.channel-grid{display:grid;grid-template-columns:repeat(auto-fill,minmax(100px,1fr));gap:6px;margin-top:10px}
.channel-item{background:#0f0f0f;padding:6px;border-radius:2px;text-align:center}
.channel-label{font-size:0.65em;color:#666;margin-bottom:2px}
.channel-value{font-size:1em;font-weight:bold;color:#ff8c42}
.stage-container{position:relative;width:100%;background:#0f0f0f;border:2px solid #333;border-radius:2px;overflow:hidden}
.stage-canvas{width:100%;display:block;cursor:crosshair}
.stage-controls{display:flex;gap:6px;margin-bottom:10px;align-items:center;flex-wrap:wrap}
.zoom-btn{padding:6px 12px;background:#1a1a1a;border:2px solid #333;border-radius:2px;color:#666;cursor:pointer;font-weight:bold;font-size:11px}
.zoom-btn:hover{border-color:#ff8c42;color:#ff8c42}
.zoom-level{color:#666;font-size:0.8em;padding:6px 10px;background:#1a1a1a;border:1px solid #333;border-radius:2px}
.stage-legend{margin-top:10px;display:flex;gap:12px;flex-wrap:wrap;justify-content:center}
.legend-item{display:flex;align-items:center;gap:5px;color:#666;font-size:0.8em}
.legend-icon{width:14px;height:14px;border-radius:2px}
.dmx-control-panel{display:grid;grid-template-columns:repeat(auto-fill,minmax(60px,1fr));gap:6px;margin-top:10px}
.dmx-channel{background:#1a1a1a;padding:6px;border-radius:2px;text-align:center}
.dmx-channel-label{font-size:0.65em;color:#666;margin-bottom:3px}
.dmx-channel-value{font-size:1em;font-weight:bold;color:#ff8c42;margin:3px 0}
.dmx-slider{width:100%;height:80px;writing-mode:bt-lr;-webkit-appearance:slider-vertical;background:#0f0f0f;outline:none}
.dmx-slider::-webkit-slider-thumb{-webkit-appearance:none;width:100%;height:10px;background:#ff8c42;cursor:pointer}
.dmx-slider::-moz-range-thumb{width:100%;height:10px;background:#ff8c42;cursor:pointer;border:none}
.manual-fixture-select{margin-bottom:10px}
.fixture-control-group{margin-bottom:15px;padding:10px;background:#1a1a1a;border-radius:2px}
.fixture-control-group h3{color:#ff8c42;margin:0 0 10px 0;font-size:0.95em}
.fixture-copy-btn{background:#4a9eff;border-color:#4a9eff;margin-left:5px}
.fixture-copy-btn:hover{background:transparent;color:#4a9eff}
.dmx-monitor{display:grid;grid-template-columns:repeat(32,1fr);gap:2px;padding:6px;background:#1a1a1a;border-radius:2px;max-height:250px;overflow-y:auto}
.dmx-channel-mon{background:#0f0f0f;padding:3px;border-radius:2px;text-align:center;min-height:60px;display:flex;flex-direction:column;justify-content:flex-end}
.dmx-channel-num{font-size:0.6em;color:#555;margin-bottom:1px}
.dmx-bar-container{flex:1;display:flex;flex-direction:column;justify-content:flex-end;background:#000;border-radius:2px;overflow:hidden}
.dmx-bar{width:100%;background:linear-gradient(to top,#4caf50 0%,#ff8c42 50%,#ff1744 100%);transition:height 0.05s;opacity:0.4}
.login-overlay{position:fixed;top:0;left:0;width:100%;height:100%;background:rgba(0,0,0,0.95);z-index:9999;display:none;align-items:center;justify-content:center}
.login-overlay.active{display:flex}
.login-box{background:#2b2b2b;border-radius:2px;padding:30px;max-width:400px;width:90%;border:3px solid #ff8c42;text-align:center}
.login-title{font-size:1.6em;color:#ff8c42;margin-bottom:8px;font-weight:bold}
.login-subtitle{color:#666;margin-bottom:20px;font-size:0.9em}
.login-input{width:100%;padding:10px 12px;background:#1a1a1a;border:2px solid #333;border-radius:2px;color:#fff;font-size:13px;margin-bottom:12px}
.login-input:focus{outline:none;border-color:#ff8c42}
.login-btn{width:100%;padding:12px;background:#ff8c42;border:2px solid #ff8c42;border-radius:2px;color:#000;font-size:14px;font-weight:bold;cursor:pointer}
.login-btn:hover{background:transparent;color:#ff8c42}
.login-error{color:#ff1744;margin-top:10px;display:none;font-weight:bold;font-size:0.8em}
@media (max-width:768px){h1{font-size:1.5em}.grid-2{grid-template-columns:1fr}.position-display{grid-template-columns:repeat(2,1fr)}.emergency-controls{position:static;margin-bottom:12px}}
</style>
</head>
<body>
<div id="loginOverlay" class="login-overlay active">
<div class="login-box">
<div class="login-title">🔒 U-Track Access</div>
<div class="login-subtitle">Enter password to access</div>
<input type="password" id="loginPasswordInput" class="login-input" placeholder="Password (admin / user)" onkeypress="if(event.key==='Enter')login()">
<button class="login-btn" onclick="login()">Login</button>
<div id="loginError" class="login-error">Incorrect password</div>
</div>
</div>
<div class="emergency-controls"><button class="btn-emergency" onclick="emergencyStop()">⚠️ EMERGENCY STOP</button></div>
<div class="container">
<header><h1>🎭 U-Track DMX Controller</h1>
<div class="subtitle">UWB Position Tracking System v2.1<span class="status-badge" id="systemStatus">Online</span></div></header>

<div class="tabs">
<button class="tab-btn active" onclick="switchTab('dashboard')">📊 Dashboard</button>
<button class="tab-btn" onclick="switchTab('stagemap')">🗺️ Stage</button>
<button class="tab-btn" onclick="switchTab('fixtures')">💡 Fixtures</button>
<button class="tab-btn" onclick="switchTab('profiles')">⚙️ Profiles</button>
<button class="tab-btn" onclick="switchTab('manual')">🎛️ Manual</button>
<button class="tab-btn" onclick="switchTab('settings')">🔧 Settings</button>
</div>

<div id="tab-dashboard" class="tab-content active">
<div class="grid-2">
<div class="card"><div class="card-title">📍 Live Position</div>
<div class="position-display">
<div class="position-item"><div class="position-label">X</div><div class="position-value" id="posX">0.00</div><div class="position-unit">m</div></div>
<div class="position-item"><div class="position-label">Y</div><div class="position-value" id="posY">0.00</div><div class="position-unit">m</div></div>
<div class="position-item"><div class="position-label">Z</div><div class="position-value" id="posZ">0.00</div><div class="position-unit">m</div></div>
<div class="position-item"><div class="position-label">RMSE</div><div class="position-value" id="posRMSE">0.000</div><div class="position-unit">accuracy</div></div>
</div></div>

<div class="card"><div class="card-title">🎮 Operating Mode</div>
<div style="margin-top:15px;text-align:center;">
<div style="font-size:1.8em;font-weight:bold;color:#ff8c42;margin-bottom:15px;" id="currentMode">UWB-TRACKING</div>
<div class="mode-controls">
<button class="mode-btn active" onclick="setMode(0)">🎯 Tracking</button>
<button class="mode-btn" onclick="setMode(1)">↔️ Pan</button>
<button class="mode-btn" onclick="setMode(2)">↕️ Tilt</button>
<button class="mode-btn" onclick="setMode(3)">💡 Dimmer</button>
<button class="mode-btn" onclick="setMode(4)">🎨 Color</button>
<button class="mode-btn" onclick="setMode(5)">🔄 Gobo</button>
<button class="mode-btn" onclick="setMode(6)">✋ Manual</button>
<button class="mode-btn" onclick="setMode(7)">🔁 Passthrough</button>
</div>
</div></div>
</div>

<div class="card"><div class="card-title">💡 Fixtures <span style="font-size:0.7em;color:#666;" id="fixtureCount">(0)</span></div>
<div class="fixture-list" id="dashboardFixtureList">
<div style="text-align:center;padding:30px;color:#555;">No fixtures configured</div>
</div></div>

<div class="card"><div class="card-title">📊 Full DMX Monitor (512 Channels)</div>
<div class="dmx-monitor" id="dmxMonitor"></div></div>

<div class="grid">
<div class="card"><div class="card-title">📈 System Info</div>
<div style="line-height:1.8;">
<div><strong>Uptime:</strong> <span id="uptime">0s</span></div>
<div><strong>Fixtures:</strong> <span id="activeFixtures">0</span></div>
<div><strong>Profiles:</strong> <span id="profileCount">0</span></div>
<div><strong>Position Valid:</strong> <span id="posValid">No</span></div>
</div></div>
</div>
</div>

<div id="tab-stagemap" class="tab-content">
<div class="card"><div class="card-title">🗺️ Stage Map</div>
<div class="stage-controls">
<button class="zoom-btn" onclick="zoomIn()">🔍+</button>
<button class="zoom-btn" onclick="zoomOut()">🔍-</button>
<button class="zoom-btn" onclick="resetZoom()">Reset</button>
<span class="zoom-level">Zoom: <span id="zoomLevel">100%</span></span>
<label style="margin-left:10px;color:#666;font-size:0.85em;">
<input type="checkbox" class="form-checkbox" id="showBeams" onchange="renderStage()">Show Beams
</label>
</div>
<div class="stage-container"><canvas id="stageCanvas" class="stage-canvas" width="800" height="600"></canvas></div>
<div class="stage-legend">
<div class="legend-item"><div class="legend-icon" style="background:#ff8c42;"></div>Moving Heads</div>
<div class="legend-item"><div class="legend-icon" style="background:#4a9eff;"></div>Target</div>
<div class="legend-item"><div class="legend-icon" style="background:#4caf50;"></div>Valid Position</div>
</div></div>
</div>

<div id="tab-fixtures" class="tab-content">
<div class="card"><div class="card-title">💡 Fixture Manager
<button class="btn btn-primary btn-small" onclick="openAddFixtureModal()" style="margin-left:auto;">➕ Add</button>
</div>
<div class="fixture-list" id="fixtureList"><div style="text-align:center;padding:20px;color:#666;">Loading...</div></div>
</div>
</div>

<div id="tab-profiles" class="tab-content">
<div class="card"><div class="card-title">⚙️ Fixture Profiles
<button class="btn btn-primary btn-small" onclick="openAddProfileModal()" style="margin-left:auto;">➕ Add</button>
</div>
<div class="profile-list" id="profileList"><div style="text-align:center;padding:20px;color:#666;">Loading...</div></div>
</div>
</div>

<div id="tab-manual" class="tab-content">
<div class="card"><div class="card-title">🎛️ Manual DMX Control</div>
<p style="color:#666;margin-bottom:12px;">Switch to MANUAL mode to use these controls.</p>

<div class="card"><div class="card-title">📊 Full DMX Monitor</div>
<div class="dmx-monitor" id="dmxMonitorManual"></div></div>

<label style="display:block;margin-bottom:10px;color:#999;">
<input type="checkbox" class="form-checkbox" id="showAllFixtures" onchange="renderManualControls()">Show all fixtures
</label>

<div class="manual-fixture-select">
<select class="form-select" id="manualFixtureSelect" onchange="renderManualControls()">
<option value="">Select a fixture...</option>
</select>
</div>

<div id="manualControlsContainer"></div>
</div>
</div>

<div id="tab-settings" class="tab-content">
<div class="card"><div class="card-title">🔧 System Settings</div>
<div class="form-group">
<label class="form-label">WiFi Configuration</label>
<div class="form-row">
<input type="text" class="form-input" id="wifiSSID" placeholder="SSID">
<input type="password" class="form-input" id="wifiPassword" placeholder="Password">
</div>
<button class="btn btn-primary" onclick="saveWiFiConfig()" style="margin-top:8px;">Save WiFi</button>
</div>
<div class="form-group">
<label class="form-label">Configuration Backup</label>
<div style="display:flex;gap:8px;">
<button class="btn btn-primary" onclick="downloadConfig()">📥 Download</button>
<button class="btn btn-success" onclick="document.getElementById('uploadInput').click()">📤 Upload</button>
<input type="file" id="uploadInput" accept=".json" style="display:none;" onchange="uploadConfig(event)">
</div>
</div>
</div>
</div>
</div>

<!-- Modals -->
<div id="addFixtureModal" class="modal">
<div class="modal-content">
<div class="modal-header">
<div class="modal-title">➕ Add New Fixture</div>
<button class="modal-close" onclick="closeAddFixtureModal()">✕</button>
</div>
<div class="form-group">
<label class="form-label">Fixture Name</label>
<input type="text" class="form-input" id="newFixtureName" placeholder="e.g. MH1 Left">
</div>
<div class="form-group">
<label class="form-label">DMX Address</label>
<input type="number" class="form-input" id="newFixtureDMX" min="1" max="512" placeholder="1-512">
</div>
<div class="form-group">
<label class="form-label">Profile</label>
<select class="form-select" id="newFixtureProfile"></select>
</div>
<div class="form-group">
<label class="form-label">Position</label>
<div class="form-row">
<input type="number" class="form-input" id="newFixtureX" placeholder="X (m)" step="0.01">
<input type="number" class="form-input" id="newFixtureY" placeholder="Y (m)" step="0.01">
<input type="number" class="form-input" id="newFixtureZ" placeholder="Z (m)" step="0.01">
</div>
</div>
<button class="btn btn-success" onclick="addFixture()">Add Fixture</button>
</div>
</div>

<div id="addProfileModal" class="modal">
<div class="modal-content">
<div class="modal-header">
<div class="modal-title">➕ Add New Profile</div>
<button class="modal-close" onclick="closeAddProfileModal()">✕</button>
</div>
<div class="form-group">
<label class="form-label">Profile Name</label>
<input type="text" class="form-input" id="newProfileName" placeholder="e.g. Robin MegaPointe">
</div>
<div class="form-row">
<div class="form-group">
<label class="form-label">Pan Coarse</label>
<input type="number" class="form-input" id="newProfilePanCoarse" min="0" max="512" value="1">
</div>
<div class="form-group">
<label class="form-label">Pan Fine</label>
<input type="number" class="form-input" id="newProfilePanFine" min="0" max="512" value="2">
</div>
<div class="form-group">
<label class="form-label">Tilt Coarse</label>
<input type="number" class="form-input" id="newProfileTiltCoarse" min="0" max="512" value="3">
</div>
<div class="form-group">
<label class="form-label">Tilt Fine</label>
<input type="number" class="form-input" id="newProfileTiltFine" min="0" max="512" value="4">
</div>
</div>
<button class="btn btn-success" onclick="addProfile()">Add Profile</button>
</div>
</div>

<script>
// Global state
let config={profiles:[],fixtures:[]};
let statusData={position:{x:0,y:0,z:0,rmse:0,valid:false},mode:0,uptime:0};
let stageZoom=1,stageOffsetX=0,stageOffsetY=0;

// Login
function login(){
const pwd=document.getElementById('loginPasswordInput').value;
if(pwd==='admin'||pwd==='user'){
document.getElementById('loginOverlay').classList.remove('active');
document.getElementById('loginError').style.display='none';
localStorage.setItem('utrack_logged_in','true');
init();
}else{
document.getElementById('loginError').style.display='block';
}}

if(localStorage.getItem('utrack_logged_in')==='true'){
document.getElementById('loginOverlay').classList.remove('active');
}

// Initialize
async function init(){
await loadConfig();
await loadStatus();
renderDashboard();
renderFixtureList();
renderProfileList();
renderManualControls();
renderStage();
setupIntervals();
}

async function loadConfig(){
try{
const res=await fetch('/api/config');
config=await res.json();
}catch(e){console.error('Config load error:',e);}}

async function loadStatus(){
try{
const res=await fetch('/api/status');
statusData=await res.json();
}catch(e){console.error('Status load error:',e);}}

function setupIntervals(){
setInterval(loadStatus,500);
setInterval(updateDashboard,500);
setInterval(updateDMXMonitor,100);
setInterval(()=>{
if(document.getElementById('tab-stagemap').classList.contains('active'))renderStage();
},200);
}

// Dashboard
function renderDashboard(){
document.getElementById('fixtureCount').textContent=`(${config.fixtures.length})`;
document.getElementById('profileCount').textContent=config.profiles.length;
document.getElementById('activeFixtures').textContent=config.fixtures.length;
const modeNames=['UWB-TRACKING','PAN-TEST','TILT-TEST','SHUTTER-DIMMER','COLOR-TEST','GOBO-TEST','MANUAL','DMX-PASSTHROUGH'];
document.getElementById('currentMode').textContent=modeNames[statusData.mode]||'UNKNOWN';
document.querySelectorAll('.mode-btn').forEach((btn,i)=>{
btn.classList.toggle('active',i===statusData.mode);
});
let html='';
config.fixtures.forEach(f=>{
html+=`<div class="fixture-item">
<div class="fixture-info">
<div class="fixture-name">${f.name}</div>
<div class="fixture-details">DMX ${f.dmxAddress} | ${f.profile.name} | Pos:(${f.position.x.toFixed(1)},${f.position.y.toFixed(1)},${f.position.z.toFixed(1)})</div>
</div></div>`;
});
if(html==='')html='<div style="text-align:center;padding:30px;color:#555;">No fixtures configured</div>';
document.getElementById('dashboardFixtureList').innerHTML=html;
}

function updateDashboard(){
document.getElementById('posX').textContent=statusData.position.x.toFixed(2);
document.getElementById('posY').textContent=statusData.position.y.toFixed(2);
document.getElementById('posZ').textContent=statusData.position.z.toFixed(2);
document.getElementById('posRMSE').textContent=statusData.position.rmse.toFixed(3);
document.getElementById('posValid').textContent=statusData.position.valid?'Yes':'No';
document.getElementById('uptime').textContent=statusData.uptime+'s';
const modeNames=['UWB-TRACKING','PAN-TEST','TILT-TEST','SHUTTER-DIMMER','COLOR-TEST','GOBO-TEST','MANUAL','DMX-PASSTHROUGH'];
document.getElementById('currentMode').textContent=modeNames[statusData.mode]||'UNKNOWN';
document.querySelectorAll('.mode-btn').forEach((btn,i)=>{
btn.classList.toggle('active',i===statusData.mode);
});
}

async function updateDMXMonitor(){
try{
const res=await fetch('/api/dmx/status');
const data=await res.json();
['dmxMonitor','dmxMonitorManual'].forEach(id=>{
const el=document.getElementById(id);
if(!el)return;
if(!el.hasChildNodes()){
for(let i=0;i<512;i++){
const ch=document.createElement('div');
ch.className='dmx-channel-mon';
ch.innerHTML=`<div class="dmx-channel-num">${i+1}</div><div class="dmx-bar-container"><div class="dmx-bar" id="${id}_bar_${i}"></div></div>`;
el.appendChild(ch);
}}
for(let i=0;i<512;i++){
const bar=document.getElementById(`${id}_bar_${i}`);
if(bar)bar.style.height=(data.channels[i]/255*100)+'%';
}});
}catch(e){console.error('DMX monitor error:',e);}}

// Fixtures
function renderFixtureList(){
let html='';
config.fixtures.forEach((f,i)=>{
html+=`<div class="fixture-item">
<div class="fixture-info">
<div class="fixture-name">${f.name}</div>
<div class="fixture-details">DMX ${f.dmxAddress} | ${f.profile.name}</div>
</div>
<div class="fixture-actions">
<button class="btn btn-secondary btn-small fixture-copy-btn" onclick="copyFixture(${i})">📋 Copy</button>
<button class="btn btn-danger btn-small" onclick="deleteFixture(${i})">🗑️</button>
</div></div>`;
});
if(html==='')html='<div style="text-align:center;padding:20px;color:#555;">No fixtures</div>';
document.getElementById('fixtureList').innerHTML=html;
}

function copyFixture(idx){
const f=config.fixtures[idx];
const newF={...f,name:f.name+' (Copy)',dmxAddress:f.dmxAddress+32};
config.fixtures.push(newF);
saveConfig();
}

function deleteFixture(idx){
if(confirm('Delete this fixture?')){
config.fixtures.splice(idx,1);
saveConfig();
}}

function openAddFixtureModal(){
document.getElementById('addFixtureModal').classList.add('active');
const sel=document.getElementById('newFixtureProfile');
sel.innerHTML='';
config.profiles.forEach(p=>{
sel.innerHTML+=`<option value="${p.name}">${p.name}</option>`;
});
}

function closeAddFixtureModal(){
document.getElementById('addFixtureModal').classList.remove('active');
}

function addFixture(){
const name=document.getElementById('newFixtureName').value;
const dmx=parseInt(document.getElementById('newFixtureDMX').value);
const profileName=document.getElementById('newFixtureProfile').value;
const x=parseFloat(document.getElementById('newFixtureX').value)||0;
const y=parseFloat(document.getElementById('newFixtureY').value)||0;
const z=parseFloat(document.getElementById('newFixtureZ').value)||0;
const profile=config.profiles.find(p=>p.name===profileName);
if(!name||!dmx||!profile){alert('Fill all fields');return;}
config.fixtures.push({name,dmxAddress:dmx,position:{x,y,z},profile});
saveConfig();
closeAddFixtureModal();
}

// Profiles
function renderProfileList(){
let html='';
config.profiles.forEach((p,i)=>{
html+=`<div class="profile-card">
<div class="profile-header">
<div class="profile-name">${p.name}</div>
<button class="btn btn-danger btn-small" onclick="deleteProfile(${i})">🗑️</button>
</div>
<div class="channel-grid">
<div class="channel-item"><div class="channel-label">Pan Coarse</div><div class="channel-value">${p.panCoarseChannel}</div></div>
<div class="channel-item"><div class="channel-label">Pan Fine</div><div class="channel-value">${p.panFineChannel}</div></div>
<div class="channel-item"><div class="channel-label">Tilt Coarse</div><div class="channel-value">${p.tiltCoarseChannel}</div></div>
<div class="channel-item"><div class="channel-label">Tilt Fine</div><div class="channel-value">${p.tiltFineChannel}</div></div>
</div></div>`;
});
if(html==='')html='<div style="text-align:center;padding:20px;color:#555;">No profiles</div>';
document.getElementById('profileList').innerHTML=html;
}

function deleteProfile(idx){
if(confirm('Delete this profile?')){
config.profiles.splice(idx,1);
saveConfig();
}}

function openAddProfileModal(){
document.getElementById('addProfileModal').classList.add('active');
}

function closeAddProfileModal(){
document.getElementById('addProfileModal').classList.remove('active');
}

function addProfile(){
const name=document.getElementById('newProfileName').value;
const panC=parseInt(document.getElementById('newProfilePanCoarse').value);
const panF=parseInt(document.getElementById('newProfilePanFine').value);
const tiltC=parseInt(document.getElementById('newProfileTiltCoarse').value);
const tiltF=parseInt(document.getElementById('newProfileTiltFine').value);
if(!name){alert('Profile name required');return;}
config.profiles.push({name,panCoarseChannel:panC,panFineChannel:panF,tiltCoarseChannel:tiltC,tiltFineChannel:tiltF,
zoomChannel:32,focusChannel:34,zoomPhysicalMinAngle:1.8,zoomPhysicalMaxAngle:42,
panMinDegrees:0,panMaxDegrees:540,tiltMinDegrees:0,tiltMaxDegrees:265,tiltHomeDegrees:41.5,
zoomCalibDist1:17,zoomCalibAngle1:25,focusDMX1:51,zoomCalibDist2:6,zoomCalibAngle2:35,focusDMX2:45,
invertTilt:false,invertPan:true,invertZoom:true,invertFocus:true,isHanging:false,panHomeOffsetDegrees:180});
saveConfig();
closeAddProfileModal();
}

// Manual DMX
function renderManualControls(){
const sel=document.getElementById('manualFixtureSelect');
const showAll=document.getElementById('showAllFixtures').checked;
let html='';
if(sel.options.length<=1){
sel.innerHTML='<option value="">Select...</option>';
config.fixtures.forEach((f,i)=>{
sel.innerHTML+=`<option value="${i}">${f.name}</option>`;
});
}
const cont=document.getElementById('manualControlsContainer');
if(showAll){
config.fixtures.forEach((f,i)=>{
html+=renderFixtureControls(f,i);
});
}else{
const idx=sel.value;
if(idx!==''){
html=renderFixtureControls(config.fixtures[idx],idx);
}}
cont.innerHTML=html||'<p style="color:#666;text-align:center;padding:20px;">Select a fixture</p>';
}

function renderFixtureControls(f,idx){
return `<div class="fixture-control-group">
<h3>${f.name} (DMX ${f.dmxAddress})</h3>
<div class="dmx-control-panel">
${[0,1,2,3,4,5,6,7,8,9,10,11].map(ch=>{
const absChannel=f.dmxAddress+ch;
return `<div class="dmx-channel">
<div class="dmx-channel-label">Ch ${ch+1}</div>
<div class="dmx-channel-value" id="dmx_${absChannel}_val">0</div>
<input type="range" class="dmx-slider" min="0" max="255" value="0" orient="vertical" 
onchange="setDMXChannel(${absChannel},this.value)" 
oninput="document.getElementById('dmx_${absChannel}_val').textContent=this.value">
</div>`;
}).join('')}
</div></div>`;
}

async function setDMXChannel(ch,val){
try{
await fetch(`/api/dmx/set?ch=${ch}&val=${val}`);
}catch(e){console.error('DMX set error:',e);}}

// Stage Map
function renderStage(){
const canvas=document.getElementById('stageCanvas');
if(!canvas)return;
const ctx=canvas.getContext('2d');
const w=canvas.width,h=canvas.height;
ctx.clearRect(0,0,w,h);
ctx.save();
ctx.translate(w/2+stageOffsetX,h/2+stageOffsetY);
ctx.scale(stageZoom,stageZoom);
ctx.fillStyle='#1a1a1a';
ctx.fillRect(-400,-300,800,600);
ctx.strokeStyle='#333';
for(let i=-20;i<=20;i++){
ctx.beginPath();
ctx.moveTo(i*20,-300);
ctx.lineTo(i*20,300);
ctx.stroke();
ctx.beginPath();
ctx.moveTo(-400,i*20);
ctx.lineTo(400,i*20);
ctx.stroke();
}
config.fixtures.forEach(f=>{
const x=f.position.x*20,y=-f.position.y*20;
ctx.fillStyle='#ff8c42';
ctx.beginPath();
ctx.arc(x,y,8,0,Math.PI*2);
ctx.fill();
ctx.fillStyle='#fff';
ctx.font='10px Arial';
ctx.fillText(f.name,x+12,y+4);
});
if(statusData.position.valid){
const tx=statusData.position.x*20,ty=-statusData.position.y*20;
ctx.fillStyle='#4a9eff';
ctx.beginPath();
ctx.arc(tx,ty,6,0,Math.PI*2);
ctx.fill();
if(document.getElementById('showBeams')&&document.getElementById('showBeams').checked){
config.fixtures.forEach(f=>{
const x=f.position.x*20,y=-f.position.y*20;
ctx.strokeStyle='rgba(255,140,66,0.3)';
ctx.lineWidth=3;
ctx.beginPath();
ctx.moveTo(x,y);
ctx.lineTo(tx,ty);
ctx.stroke();
});
}}
ctx.restore();
document.getElementById('zoomLevel').textContent=Math.round(stageZoom*100)+'%';
}

function zoomIn(){stageZoom*=1.2;renderStage();}
function zoomOut(){stageZoom/=1.2;renderStage();}
function resetZoom(){stageZoom=1;stageOffsetX=0;stageOffsetY=0;renderStage();}

// Mode control
async function setMode(mode){
try{
await fetch(`/api/mode?mode=${mode}`);
statusData.mode=mode;
updateDashboard();
}catch(e){console.error('Mode set error:',e);}}

async function emergencyStop(){
if(confirm('EMERGENCY STOP?')){
try{
await fetch('/api/emergency');
}catch(e){console.error('Emergency stop error:',e);}}}

// Config management
async function saveConfig(){
try{
await fetch('/api/config/save',{
method:'POST',
headers:{'Content-Type':'application/json'},
body:JSON.stringify(config)
});
await loadConfig();
renderDashboard();
renderFixtureList();
renderProfileList();
renderManualControls();
}catch(e){console.error('Config save error:',e);}}

function downloadConfig(){
const blob=new Blob([JSON.stringify(config,null,2)],{type:'application/json'});
const url=URL.createObjectURL(blob);
const a=document.createElement('a');
a.href=url;
a.download='utrack-config.json';
a.click();
}

function uploadConfig(e){
const file=e.target.files[0];
if(!file)return;
const reader=new FileReader();
reader.onload=async function(ev){
try{
config=JSON.parse(ev.target.result);
await saveConfig();
alert('Config uploaded successfully');
}catch(err){
alert('Invalid config file');
}};
reader.readAsText(file);
}

async function saveWiFiConfig(){
const ssid=document.getElementById('wifiSSID').value;
const password=document.getElementById('wifiPassword').value;
if(!ssid){alert('SSID required');return;}
try{
await fetch('/api/wifi/config',{
method:'POST',
headers:{'Content-Type':'application/json'},
body:JSON.stringify({ssid,password})
});
alert('WiFi config saved. Restart device to connect.');
}catch(e){alert('WiFi config error');}}

// Tab switching
function switchTab(tab){
document.querySelectorAll('.tab-content').forEach(t=>t.classList.remove('active'));
document.querySelectorAll('.tab-btn').forEach(b=>b.classList.remove('active'));
document.getElementById('tab-'+tab).classList.add('active');
event.target.classList.add('active');
if(tab==='stagemap')renderStage();
if(tab==='fixtures')renderFixtureList();
if(tab==='profiles')renderProfileList();
if(tab==='manual')renderManualControls();
}

// Stage canvas drag
let isDragging=false,lastX,lastY;
document.getElementById('stageCanvas').addEventListener('mousedown',e=>{
isDragging=true;
lastX=e.clientX;
lastY=e.clientY;
});
document.addEventListener('mousemove',e=>{
if(isDragging){
stageOffsetX+=e.clientX-lastX;
stageOffsetY+=e.clientY-lastY;
lastX=e.clientX;
lastY=e.clientY;
renderStage();
}});
document.addEventListener('mouseup',()=>{isDragging=false;});

// Auto-start if logged in
if(localStorage.getItem('utrack_logged_in')==='true'){
init();
}
</script>
</body>
</html>
)===";
