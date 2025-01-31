const char *index_html=R"(

<!DOCTYPE html>
<html lang="en"><head>
<title>hexCube</title>
<meta name="author" content="Erik Dorstel">
<meta name="generator" content="vi">
<meta name="repository" content="https://github.com/ErikDorstel/hexCube">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta charset="utf-8">
<style>
html   { font-family:Arial; }
div    { background-color:#e0e0e0; color:#000000; border:0px; padding:0px; margin:0px; text-align:center; width:100%; user-select:none; display:inline-block; }
select { background-color:#f0f0f0; color:#000000; font-size:1.0em; border:0px; padding:0px; margin:0px; }
table  { margin-left:auto; margin-right:auto; }
td     { text-align:right; }
.x0a   { background-color:#c2d5ed; padding:0.2em 0em 0.1em; width:100%; font-size:1.5em; }
.x0b   { background-color:#c2d5ed; padding:0.1em 0em 0.2em; width:100%; font-size:1.2em; }
.x0    { background-color:#c2d5ed; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x1a   { background-color:#f0f0f0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x1b   { background-color:#e0e0e0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x2    { background-color:#e0e0e0; padding:0.3em 0em; width:48%; font-size:1.4em; }
.x3    { background-color:#e0e0e0; padding:0.3em 0em; width:32%; font-size:1.4em; }
.x4    { background-color:#e0e0e0; padding:0.3em 0em; width:24%; font-size:1.4em; }
.x5    { background-color:#e0e0e0; padding:0.3em 0em; width:19%; font-size:1.4em; }
.but   { background-color:#f0f0f0; padding:0.1em 0.4em; }
.left  { text-align:left; padding:0.2em 0em; }
.list  { background-color:#e0e0e0; padding:0.3em 1em; width:auto; margin-right:0.5em; margin-bottom:0.4em; border-radius:0.5em; }
</style>
<script>

function webUIinit() {
  brightValues=[-1,0,1,2,3,5,7,10,15,22,31,44,63,90,127,180,255,-1];
  delayValues=[-1,0,1,2,3,5,7,10,15,22,31,44,63,90,127,180,255,361,511,723,1023,-1];
  speedValues=[-1,0,1,2,3,5,7,10,15,22,31,44,63,90,127,180,255,361,511,723,1023,-1];
  hueValues=[-1,0,16,32,48,64,80,96,112,128,144,160,176,192,208,224,240,255,-1];
  hueSpeedValues=[-1,0,1,2,3,4,5,6,7,8,9,10,12,14,16,18,20,-1];
  borderValues=[-1,0,16,32,48,64,80,96,112,-1];
  ratioValues=[-1,0,16,32,48,64,80,96,112,-1];
  countValues=[-1,5,10,20,40,60,80,120,160,200,-1];
  lengthValues=[-1,2,3,4,5,6,7,8,9,10,11,12,-1];
  appList=[]; appConfig=[]; bright=0; delay=0; speed=0; hueA=0; hueSpeedA=0; hueB=0; hueSpeedB=0; border=0; ratio=0; count=0; length=0;
  red="#E09090"; green="#90E090"; yellow="#FFE460"; gray="#e0e0e0"; darkgray="#d0d0d0"; blue="#c2d5ed";
  appName="&nbsp;"; appDesc="&nbsp;"; ajaxObj=[]; requestAJAX('appName'); requestAJAX('getApps'); requestAJAX('getApp'); }

function doDisplayApps() {
  id("apps").innerHTML="";
  listCount=appList[0]*1;
  for (i=0;i<listCount;i++) { id("apps").innerHTML+="<div class=\"list\" id=\"app" + i + "\" onclick=\"setApp(" + i + ");\">" + appList[i+1] + "</div>"; }
  bright=appList[listCount+1]*1; id("brightValue").innerHTML=bright;
  delay=appList[listCount+2]*1; id("delayValue").innerHTML=delay;
  speed=appList[listCount+3]*1; id("speedValue").innerHTML=speed;
  hueA=appList[listCount+4]*1; id("hueAValue").innerHTML=hueA;
  hueSpeedA=appList[listCount+5]*1; id("hueSpeedAValue").innerHTML=hueSpeedA;
  hueB=appList[listCount+6]*1; id("hueBValue").innerHTML=hueB;
  hueSpeedB=appList[listCount+7]*1; id("hueSpeedBValue").innerHTML=hueSpeedB;
  border=appList[listCount+8]*1; id("borderValue").innerHTML=border;
  ratio=appList[listCount+9]*1; id("ratioValue").innerHTML=ratio;
  count=appList[listCount+10]*1; id("countValue").innerHTML=count;
  length=appList[listCount+11]*1; id("lengthValue").innerHTML=length; }

function doMarkApps() {
  listCount=appList[0]*1;
  for (i=0;i<listCount;i++) { id("app"+i).style.backgroundColor=gray; }
  id("app"+appConfig[0]).style.backgroundColor=blue;
  id("bright").style.display="none";
  id("delay").style.display="none";
  id("speed").style.display="none";
  id("hueA").style.display="none";
  id("hueSpeedA").style.display="none";
  id("hueB").style.display="none";
  id("hueSpeedB").style.display="none";
  id("border").style.display="none";
  id("ratio").style.display="none";
  id("count").style.display="none";
  id("length").style.display="none";
  configCount=appConfig[1]*1;
  for (i=0;i<configCount;i++) { id(appConfig[i+2]).style.display="block"; } }

function setApp(value) { requestAJAX('setApp,' + value); }

function setBright(value) {
  for (i=0;i<brightValues.length;i++) { if (bright==brightValues[i]) { break; } }
  if (value==0 && brightValues[i-1]>-1) { bright=brightValues[i-1]; }
  if (value==1 && brightValues[i+1]>-1) { bright=brightValues[i+1]; }
  if (value==2) { if (bright==0) { bright=22; } else { bright=0; } }
  requestAJAX('setBright,' + bright);
  id("brightValue").innerHTML="&nbsp;"; }

function setDelay(value) {
  for (i=0;i<delayValues.length;i++) { if (delay==delayValues[i]) { break; } }
  if (value==0 && delayValues[i-1]>-1) { delay=delayValues[i-1]; }
  if (value==1 && delayValues[i+1]>-1) { delay=delayValues[i+1]; }
  if (value==2) { delay=63; }
  requestAJAX('setDelay,' + delay);
  id("delayValue").innerHTML="&nbsp;"; }

function setSpeed(value) {
  for (i=0;i<speedValues.length;i++) { if (speed==speedValues[i]) { break; } }
  if (value==0 && speedValues[i-1]>-1) { speed=speedValues[i-1]; }
  if (value==1 && speedValues[i+1]>-1) { speed=speedValues[i+1]; }
  if (value==2) { speed=22; }
  requestAJAX('setSpeed,' + speed);
  id("speedValue").innerHTML="&nbsp;"; }

function setHueA(value) {
  for (i=0;i<hueValues.length;i++) { if (hueA==hueValues[i]) { break; } }
  if (value==0 && hueValues[i-1]>-1) { hueA=hueValues[i-1]; }
  if (value==1 && hueValues[i+1]>-1) { hueA=hueValues[i+1]; }
  if (value==2) { hueA=160; }
  requestAJAX('setHueA,' + hueA);
  id("hueAValue").innerHTML="&nbsp;"; }

function setHueSpeedA(value) {
  for (i=0;i<hueSpeedValues.length;i++) { if (hueSpeedA==hueSpeedValues[i]) { break; } }
  if (value==0 && hueSpeedValues[i-1]>-1) { hueSpeedA=hueSpeedValues[i-1]; }
  if (value==1 && hueSpeedValues[i+1]>-1) { hueSpeedA=hueSpeedValues[i+1]; }
  if (value==2) { hueSpeedA=0; }
  requestAJAX('setHueSpeedA,' + hueSpeedA);
  id("hueSpeedAValue").innerHTML="&nbsp;"; }

function setHueB(value) {
  for (i=0;i<hueValues.length;i++) { if (hueB==hueValues[i]) { break; } }
  if (value==0 && hueValues[i-1]>-1) { hueB=hueValues[i-1]; }
  if (value==1 && hueValues[i+1]>-1) { hueB=hueValues[i+1]; }
  if (value==2) { hueB=255; }
  requestAJAX('setHueB,' + hueB);
  id("hueBValue").innerHTML="&nbsp;"; }

function setHueSpeedB(value) {
  for (i=0;i<hueSpeedValues.length;i++) { if (hueSpeedB==hueSpeedValues[i]) { break; } }
  if (value==0 && hueSpeedValues[i-1]>-1) { hueSpeedB=hueSpeedValues[i-1]; }
  if (value==1 && hueSpeedValues[i+1]>-1) { hueSpeedB=hueSpeedValues[i+1]; }
  if (value==2) { hueSpeedB=0; }
  requestAJAX('setHueSpeedB,' + hueSpeedB);
  id("hueSpeedBValue").innerHTML="&nbsp;"; }

function setBorder(value) {
  for (i=0;i<borderValues.length;i++) { if (border==borderValues[i]) { break; } }
  if (value==0 && borderValues[i-1]>-1) { border=borderValues[i-1]; }
  if (value==1 && borderValues[i+1]>-1) { border=borderValues[i+1]; }
  if (value==2) { border=0; }
  requestAJAX('setBorder,' + border);
  id("borderValue").innerHTML="&nbsp;"; }

function setRatio(value) {
  for (i=0;i<ratioValues.length;i++) { if (ratio==ratioValues[i]) { break; } }
  if (value==0 && ratioValues[i-1]>-1) { ratio=ratioValues[i-1]; }
  if (value==1 && ratioValues[i+1]>-1) { ratio=ratioValues[i+1]; }
  if (value==2) { ratio=0; }
  requestAJAX('setRatio,' + ratio);
  id("ratioValue").innerHTML="&nbsp;"; }

function setCount(value) {
  for (i=0;i<countValues.length;i++) { if (count==countValues[i]) { break; } }
  if (value==0 && countValues[i-1]>-1) { count=countValues[i-1]; }
  if (value==1 && countValues[i+1]>-1) { count=countValues[i+1]; }
  if (value==2) { count=20; }
  requestAJAX('setCount,' + count);
  id("countValue").innerHTML="&nbsp;"; }

function setLength(value) {
  for (i=0;i<lengthValues.length;i++) { if (length==lengthValues[i]) { break; } }
  if (value==0 && lengthValues[i-1]>-1) { length=lengthValues[i-1]; }
  if (value==1 && lengthValues[i+1]>-1) { length=lengthValues[i+1]; }
  if (value==2) { length=5; }
  requestAJAX('setLength,' + length);
  id("lengthValue").innerHTML="&nbsp;"; }

function requestAJAX(value) {
  ajaxObj[value]=new XMLHttpRequest; ajaxObj[value].url=value; ajaxObj[value].open("GET",value,true);
  ajaxObj[value].setRequestHeader("Content-Type","application/x-www-form-urlencoded");
  ajaxObj[value].addEventListener('load',replyAJAX); ajaxObj[value].send(); }

function replyAJAX(event) {
  if (event.target.status==200) {
    if (event.target.url=="appName") {
      id("appName").innerHTML=event.target.responseText.split(",")[0];
      id("appDesc").innerHTML=event.target.responseText.split(",")[1]; }
    else if (event.target.url=="getApps") { appList=event.target.responseText.split(","); doDisplayApps(); }
    else if (event.target.url.startsWith("setBright")) { id("brightValue").innerHTML=event.target.responseText.split(",")[0]; }
    else if (event.target.url.startsWith("setDelay")) { id("delayValue").innerHTML=event.target.responseText.split(",")[0]; }
    else if (event.target.url.startsWith("setSpeed")) { id("speedValue").innerHTML=event.target.responseText.split(",")[0]; }
    else if (event.target.url.startsWith("setHueA")) { id("hueAValue").innerHTML=event.target.responseText.split(",")[0]; }
    else if (event.target.url.startsWith("setHueSpeedA")) { id("hueSpeedAValue").innerHTML=event.target.responseText.split(",")[0]; }
    else if (event.target.url.startsWith("setHueB")) { id("hueBValue").innerHTML=event.target.responseText.split(",")[0]; }
    else if (event.target.url.startsWith("setHueSpeedB")) { id("hueSpeedBValue").innerHTML=event.target.responseText.split(",")[0]; }
    else if (event.target.url.startsWith("setBorder")) { id("borderValue").innerHTML=event.target.responseText.split(",")[0]; }
    else if (event.target.url.startsWith("setRatio")) { id("ratioValue").innerHTML=event.target.responseText.split(",")[0]; }
    else if (event.target.url.startsWith("setCount")) { id("countValue").innerHTML=event.target.responseText.split(",")[0]; }
    else if (event.target.url.startsWith("setLength")) { id("lengthValue").innerHTML=event.target.responseText.split(",")[0]; }
    else if (event.target.url.startsWith("getApp")) { appConfig=event.target.responseText.split(","); doMarkApps(); }
    else if (event.target.url.startsWith("setApp")) { appConfig=event.target.responseText.split(","); doMarkApps(); } } }

function mapValue(value,inMin,inMax,outMin,outMax) { return (value-inMin)*(outMax-outMin)/(inMax-inMin)+outMin; }
function id(id) { return document.getElementById(id); }

</script></head><body onload="webUIinit();">

<div><div class="x0a" id="appName">&nbsp;</div></div>
<div><div class="x0b" id="appDesc">&nbsp;</div></div>

<div><div class="x1b" onclick="location.replace('/chooseAP');">Choose WLAN AP</div></div>

<div>
<div class="x1a" id="apps">&nbsp;</div>
<div style="display:none" id="bright">
     <div class="x2" onclick="setBright(2);">Brightness</div>
     <div class="x2" style="text-align:left">
          <span class="but" onclick="setBright(0);">&minus;</span>
          <div style="width:3em" id="brightValue">&nbsp;</div>
          <span class="but" onclick="setBright(1);">&plus;</span></div></div>
<div style="display:none" id="delay">
     <div class="x2" onclick="setDelay(2);">Delay</div>
     <div class="x2" style="text-align:left">
          <span class="but" onclick="setDelay(0);">&minus;</span>
          <div style="width:3em" id="delayValue">&nbsp;</div>
          <span class="but" onclick="setDelay(1);">&plus;</span></div></div>
<div style="display:none" id="speed">
     <div class="x2" onclick="setSpeed(2);">Speed</div>
     <div class="x2" style="text-align:left">
          <span class="but" onclick="setSpeed(0);">&minus;</span>
          <div style="width:3em" id="speedValue">&nbsp;</div>
          <span class="but" onclick="setSpeed(1);">&plus;</span></div></div>
<div style="display:none" id="hueA">
     <div class="x2" onclick="setHueA(2);">Color A</div>
     <div class="x2" style="text-align:left">
          <span class="but" onclick="setHueA(0);">&minus;</span>
          <div style="width:3em" id="hueAValue">&nbsp;</div>
          <span class="but" onclick="setHueA(1);">&plus;</span></div></div>
<div style="display:none" id="hueSpeedA">
     <div class="x2" onclick="setHueSpeedA(2);">Speed A</div>
     <div class="x2" style="text-align:left">
          <span class="but" onclick="setHueSpeedA(0);">&minus;</span>
          <div style="width:3em" id="hueSpeedAValue">&nbsp;</div>
          <span class="but" onclick="setHueSpeedA(1);">&plus;</span></div></div>
<div style="display:none" id="hueB">
     <div class="x2" onclick="setHueB(2);">Color B</div>
     <div class="x2" style="text-align:left">
          <span class="but" onclick="setHueB(0);">&minus;</span>
          <div style="width:3em" id="hueBValue">&nbsp;</div>
          <span class="but" onclick="setHueB(1);">&plus;</span></div></div>
<div style="display:none" id="hueSpeedB">
     <div class="x2" onclick="setHueSpeedB(2);">Speed B</div>
     <div class="x2" style="text-align:left">
          <span class="but" onclick="setHueSpeedB(0);">&minus;</span>
          <div style="width:3em" id="hueSpeedBValue">&nbsp;</div>
          <span class="but" onclick="setHueSpeedB(1);">&plus;</span></div></div>
<div style="display:none" id="border">
     <div class="x2" onclick="setBorder(2);">Border</div>
     <div class="x2" style="text-align:left">
          <span class="but" onclick="setBorder(0);">&minus;</span>
          <div style="width:3em" id="borderValue">&nbsp;</div>
          <span class="but" onclick="setBorder(1);">&plus;</span></div></div>
<div style="display:none" id="ratio">
     <div class="x2" onclick="setRatio(2);">Ratio</div>
     <div class="x2" style="text-align:left">
          <span class="but" onclick="setRatio(0);">&minus;</span>
          <div style="width:3em" id="ratioValue">&nbsp;</div>
          <span class="but" onclick="setRatio(1);">&plus;</span></div></div>
<div style="display:none" id="count">
     <div class="x2" onclick="setCount(2);">Count</div>
     <div class="x2" style="text-align:left">
          <span class="but" onclick="setCount(0);">&minus;</span>
          <div style="width:3em" id="countValue">&nbsp;</div>
          <span class="but" onclick="setCount(1);">&plus;</span></div></div>
<div style="display:none" id="length">
     <div class="x2" onclick="setLength(2);">Length</div>
     <div class="x2" style="text-align:left">
          <span class="but" onclick="setLength(0);">&minus;</span>
          <div style="width:3em" id="lengthValue">&nbsp;</div>
          <span class="but" onclick="setLength(1);">&plus;</span></div></div>
</div>

</body></html>

)";
