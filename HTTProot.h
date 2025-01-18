String httpget(String request) {
  String response="";

  // webUI specific pages

  if (request.indexOf("/getApps")>=0) {
    response+=String(apps.count) + ",";
    for (int i=0;i<apps.count;i++) { response+=String(apps.name[i]); response+=","; }
    response+=String(config.bright) + ",";
    response+=String(config.delay) + ",";
    response+=String(config.speed) + ",";
    response+=String(config.hueA) + ",";
    response+=String(config.hueSpeedA) + ",";
    response+=String(config.hueB) + ",";
    response+=String(config.hueSpeedB) + ",";
    response+=String(config.border) + ",";
    response+=String(config.ratio) + ",";
    response+=String(config.count) + ",";
    response+=String(config.length) + ","; }

  else if (request.indexOf("/setApp")>=0) {
    int a=request.indexOf(",")+1;
    cubeClear(); apps.current=request.substring(a).toInt();
    response+=String(apps.current) + ",";
    response+=String(apps.config[apps.current]) + ","; }

  else if (request.indexOf("/getApp")>=0) {
    response+=String(apps.current) + ",";
    response+=String(apps.config[apps.current]) + ","; }

  else if (request.indexOf("/setBright")>=0) {
    int a=request.indexOf(",")+1;
    config.bright=request.substring(a).toInt();
    response+=String(config.bright) + ","; }

  else if (request.indexOf("/setDelay")>=0) {
    int a=request.indexOf(",")+1;
    config.delay=request.substring(a).toInt();
    response+=String(config.delay) + ","; }

  else if (request.indexOf("/setSpeed")>=0) {
    int a=request.indexOf(",")+1;
    config.speed=request.substring(a).toInt();
    response+=String(config.speed) + ","; }

  else if (request.indexOf("/setHueA")>=0) {
    int a=request.indexOf(",")+1;
    config.hueA=request.substring(a).toInt();
    modifyPlasmaColors(config.hueA,config.hueB,config.border,config.ratio);
    response+=String(config.hueA) + ","; }

  else if (request.indexOf("/setHueSpeedA")>=0) {
    int a=request.indexOf(",")+1;
    config.hueSpeedA=request.substring(a).toInt();
    response+=String(config.hueSpeedA) + ","; }

  else if (request.indexOf("/setHueB")>=0) {
    int a=request.indexOf(",")+1;
    config.hueB=request.substring(a).toInt();
    modifyPlasmaColors(config.hueA,config.hueB,config.border,config.ratio);
    response+=String(config.hueB) + ","; }

  else if (request.indexOf("/setHueSpeedB")>=0) {
    int a=request.indexOf(",")+1;
    config.hueSpeedB=request.substring(a).toInt();
    response+=String(config.hueSpeedB) + ","; }

  else if (request.indexOf("/setBorder")>=0) {
    int a=request.indexOf(",")+1;
    config.border=request.substring(a).toInt();
    modifyPlasmaColors(config.hueA,config.hueB,config.border,config.ratio);
    response+=String(config.border) + ","; }

  else if (request.indexOf("/setRatio")>=0) {
    int a=request.indexOf(",")+1;
    config.ratio=request.substring(a).toInt();
    modifyPlasmaColors(config.hueA,config.hueB,config.border,config.ratio);
    response+=String(config.ratio) + ","; }

  else if (request.indexOf("/setCount")>=0) {
    int a=request.indexOf(",")+1;
    config.count=request.substring(a).toInt();
    response+=String(config.count) + ","; }

  else if (request.indexOf("/setLength")>=0) {
    int a=request.indexOf(",")+1;
    config.length=request.substring(a).toInt();
    response+=String(config.length) + ","; }

  // WLAN Choose specific pages

  else if (request.indexOf("/appName")>=0) {
    response+=String(appName) + ",";
    response+=String(appDesc) + ","; }

  else if (request.indexOf("/chooseAP")>=0) { response=choose_html; }

  else if (request.indexOf("/statusAP")>=0) { if (wlanConfig.statusStation) { response="<div class=\"x1\">WLAN AP " + wlanConfig.ssidStation + " connected.</div>";
    response+="<div class=\"x1\">IP Address " + WiFi.localIP().toString() + "</div>"; } else { response="<div class=\"x1\">No WLAN AP connected.</div>"; } }

  else if (request.indexOf("/configAP")>=0) {
    if (WiFi.softAPgetStationNum()==0) { response=a2h(wlanConfig.ssidStation) + "," + a2h(wlanConfig.passwordStation) + ","; }
    else { response=a2h(wlanConfig.ssidStation) + ",,"; } }

  else if (request.indexOf("/scanAP")>=0) {
    wlanTimer=millis()+20000; int indexes=WiFi.scanNetworks(); response+="<div class=\"x1\"><table>"; for (int index=0;index<indexes;++index) { if (WiFi.SSID(index)!="") {
      response+="<tr><td onclick=\"setAP(\'" + WiFi.SSID(index) + "\');\">" + WiFi.RSSI(index) + "&nbsp;dB&nbsp;&nbsp;&nbsp;&nbsp;" + WiFi.SSID(index) + "</td></tr>"; } } response+="</table></div>"; }

  else if (request.indexOf("/connectAP")>=0) {
    int a=request.indexOf(",")+1; int b=request.indexOf(",",a)+1;
    if (!wlanConfig.statusStation || WiFi.softAPgetStationNum()==0) {
      wlanConfig.ssidStation=h2a(request.substring(a,b-1)); wlanConfig.passwordStation=h2a(request.substring(b)); wlanConfig.reconnectCount=0; reconnectWLAN(); }
    else { if (debug) { Serial.println("WLAN Station reconnect prevented."); } } }

  // Default page

  else if (request.indexOf("/favicon.ico")>=0) { }

  else { response=index_html; }

  return response; }
