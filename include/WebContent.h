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
body{font-family:-apple-system,BlinkMacSystemFont,'Segoe UI',Roboto,sans-serif;background:linear-gradient(135deg,#0f0c29 0%,#302b63 50%,#24243e 100%);color:#e0e0e0;min-height:100vh}
.container{max-width:1600px;margin:0 auto;padding:20px}
header{background:rgba(0,0,0,0.4);padding:25px;border-radius:15px;margin-bottom:25px;box-shadow:0 8px 32px rgba(0,0,0,0.4);backdrop-filter:blur(10px);border:1px solid rgba(255,255,255,0.1)}
h1{color:#00d4ff;font-size:2.8em;text-shadow:0 0 20px rgba(0,212,255,0.6);margin-bottom:10px}
.subtitle{color:#888;font-size:1.1em;display:flex;align-items:center;gap:10px}
.status-badge{display:inline-block;padding:5px 15px;border-radius:20px;font-size:0.85em;font-weight:600;background:rgba(76,175,80,0.2);color:#4caf50;border:1px solid #4caf50}
.emergency-controls{position:fixed;top:20px;right:20px;z-index:1000}
.btn-emergency{background:linear-gradient(135deg,#ff1744 0%,#c62828 100%);color:white;border:none;padding:18px 35px;border-radius:50px;font-size:16px;font-weight:bold;cursor:pointer;box-shadow:0 6px 25px rgba(255,23,68,0.4);transition:all 0.3s;text-transform:uppercase}
.btn-emergency:hover{transform:translateY(-2px);box-shadow:0 8px 30px rgba(255,23,68,0.6)}
.tabs{display:flex;gap:10px;margin-bottom:25px;background:rgba(0,0,0,0.3);padding:10px;border-radius:12px}
.tab-btn{flex:1;padding:15px 25px;border:none;background:rgba(255,255,255,0.05);color:#aaa;border-radius:8px;cursor:pointer;transition:all 0.3s;font-size:15px;font-weight:600}
.tab-btn:hover{background:rgba(255,255,255,0.1);color:#fff}
.tab-btn.active{background:linear-gradient(135deg,#00d4ff 0%,#0091ea 100%);color:white;box-shadow:0 4px 15px rgba(0,212,255,0.3)}
.tab-content{display:none;animation:fadeIn 0.3s}
.tab-content.active{display:block}
@keyframes fadeIn{from{opacity:0;transform:translateY(10px)}to{opacity:1;transform:translateY(0)}}
.card{background:rgba(0,0,0,0.3);border-radius:12px;padding:25px;margin-bottom:20px;box-shadow:0 4px 20px rgba(0,0,0,0.3);border:1px solid rgba(255,255,255,0.05)}
.card-title{font-size:1.5em;margin-bottom:20px;color:#00d4ff;display:flex;align-items:center;gap:10px}
.grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(300px,1fr));gap:20px}
.grid-2{display:grid;grid-template-columns:1fr 1fr;gap:20px}
.position-display{display:grid;grid-template-columns:repeat(4,1fr);gap:15px;margin-top:15px}
.position-item{background:rgba(0,212,255,0.1);padding:15px;border-radius:8px;text-align:center;border:1px solid rgba(0,212,255,0.3)}
.position-label{font-size:0.85em;color:#888;margin-bottom:5px}
.position-value{font-size:1.8em;font-weight:bold;color:#00d4ff}
.position-unit{font-size:0.8em;color:#aaa}
.fixture-list{display:flex;flex-direction:column;gap:10px}
.fixture-item{background:rgba(255,255,255,0.05);padding:20px;border-radius:10px;display:flex;justify-content:space-between;align-items:center;transition:all 0.3s;border:1px solid rgba(255,255,255,0.05)}
.fixture-item:hover{background:rgba(255,255,255,0.08);border-color:rgba(0,212,255,0.3)}
.fixture-info{flex:1}
.fixture-name{font-size:1.2em;font-weight:600;color:#fff;margin-bottom:5px}
.fixture-details{font-size:0.9em;color:#888}
.fixture-actions{display:flex;gap:10px}
.btn{padding:10px 20px;border:none;border-radius:6px;cursor:pointer;font-size:14px;font-weight:600;transition:all 0.3s}
.btn-primary{background:linear-gradient(135deg,#00d4ff 0%,#0091ea 100%);color:white;box-shadow:0 4px 15px rgba(0,212,255,0.3)}
.btn-primary:hover{transform:translateY(-2px)}
.btn-success{background:linear-gradient(135deg,#4caf50 0%,#388e3c 100%);color:white}
.btn-danger{background:linear-gradient(135deg,#f44336 0%,#d32f2f 100%);color:white}
.btn-secondary{background:rgba(255,255,255,0.1);color:#fff}
.btn-small{padding:8px 15px;font-size:12px}
.form-group{margin-bottom:20px}
.form-label{display:block;margin-bottom:8px;color:#aaa;font-size:0.95em;font-weight:600}
.form-input,.form-select{width:100%;padding:12px 15px;background:rgba(255,255,255,0.05);border:1px solid rgba(255,255,255,0.1);border-radius:6px;color:#fff;font-size:14px}
.form-input:focus,.form-select:focus{outline:none;border-color:#00d4ff;background:rgba(255,255,255,0.08)}
.form-checkbox{margin-right:8px}
.form-row{display:grid;grid-template-columns:repeat(auto-fit,minmax(200px,1fr));gap:15px}
.modal{display:none;position:fixed;top:0;left:0;width:100%;height:100%;background:rgba(0,0,0,0.8);z-index:2000;overflow-y:auto}
.modal.active{display:flex;align-items:center;justify-content:center}
.modal-content{background:linear-gradient(135deg,#1e1e2e 0%,#2a2a3e 100%);border-radius:15px;padding:30px;max-width:800px;width:90%;max-height:90vh;overflow-y:auto;box-shadow:0 20px 60px rgba(0,0,0,0.5)}
.modal-header{display:flex;justify-content:space-between;align-items:center;margin-bottom:25px}
.modal-title{font-size:1.8em;color:#00d4ff}
.modal-close{background:none;border:none;color:#fff;font-size:2em;cursor:pointer;width:40px;height:40px;border-radius:50%}
.modal-close:hover{background:rgba(255,255,255,0.1)}
.mode-controls{display:grid;grid-template-columns:repeat(auto-fit,minmax(150px,1fr));gap:10px;margin-top:15px}
.mode-btn{padding:15px;background:rgba(255,255,255,0.05);border:2px solid rgba(255,255,255,0.1);border-radius:8px;color:#fff;cursor:pointer;font-weight:600;text-align:center}
.mode-btn:hover{background:rgba(255,255,255,0.1);border-color:rgba(0,212,255,0.5)}
.mode-btn.active{background:rgba(0,212,255,0.2);border-color:#00d4ff;color:#00d4ff}
.profile-list{display:grid;gap:15px;margin-top:20px}
.profile-card{background:rgba(255,255,255,0.05);padding:20px;border-radius:10px;border:1px solid rgba(255,255,255,0.1)}
.profile-card:hover{border-color:rgba(0,212,255,0.3);background:rgba(255,255,255,0.08)}
.profile-header{display:flex;justify-content:space-between;align-items:center;margin-bottom:15px}
.profile-name{font-size:1.3em;font-weight:600;color:#fff}
.channel-grid{display:grid;grid-template-columns:repeat(auto-fill,minmax(120px,1fr));gap:10px;margin-top:15px}
.channel-item{background:rgba(0,0,0,0.3);padding:10px;border-radius:6px;text-align:center}
.channel-label{font-size:0.75em;color:#888;margin-bottom:5px}
.channel-value{font-size:1.2em;font-weight:bold;color:#00d4ff}
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
<button class="tab-btn" onclick="switchTab('fixtures')">💡 Fixtures</button>
<button class="tab-btn" onclick="switchTab('profiles')">⚙️ Profiles</button>
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

<div id="tab-settings" class="tab-content">
<div class="card"><div class="card-title">🔧 System Settings</div>
<div class="form-group"><label class="form-label">WiFi SSID</label>
<input type="text" class="form-input" value="U-Track-DMX" disabled></div>
<div class="form-group"><label class="form-label">Configuration</label>
<div style="display:flex;gap:10px">
<button class="btn btn-primary" onclick="downloadConfig()">📥 Download</button>
<button class="btn btn-success" onclick="document.getElementById('uploadInput').click()">📤 Upload</button>
<input type="file" id="uploadInput" accept=".json" style="display:none" onchange="uploadConfig(event)">
</div></div></div>
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

document.addEventListener('DOMContentLoaded',()=>{
loadConfig();loadStatus();setInterval(loadStatus,1000);
});

function switchTab(n){
document.querySelectorAll('.tab-btn').forEach(b=>b.classList.remove('active'));
document.querySelectorAll('.tab-content').forEach(c=>c.classList.remove('active'));
event.target.classList.add('active');
document.getElementById('tab-'+n).classList.add('active');
currentTab=n;
if(n==='fixtures')loadFixtures();
if(n==='profiles')loadProfiles();
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
function closeModal(id){document.getElementById(id).classList.remove('active')}

function openAddFixtureModal(){
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
config.fixtures.push(f);
await saveConfig();
closeModal('addFixtureModal');
loadFixtures();updateUI();
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
