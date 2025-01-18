#include <WiFi.h>
#include <Preferences.h>
Preferences preferences;

struct wlanConfigStruct {
  const char* ssidAP=appName;
  const char* passwordAP="";
  String ssidStation="";
  String passwordStation="";
  boolean statusStation=false;
  int reconnectCount=0; };

struct wlanConfigStruct wlanConfig;

uint32_t wlanTimer=millis()+20000;

void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info) {
  preferences.begin("wlanAuth",false); String ssidStationOld=preferences.getString("ssidStation","empty"); String passwordStationOld=preferences.getString("passwordStation","empty"); preferences.end();
  if (ssidStationOld!=wlanConfig.ssidStation || passwordStationOld!=wlanConfig.passwordStation) {
    preferences.begin("wlanAuth",false); preferences.putString("ssidStation",wlanConfig.ssidStation); preferences.putString("passwordStation",wlanConfig.passwordStation); preferences.end(); }
  wlanConfig.statusStation=true; wlanConfig.reconnectCount=0;
  if (debug) { Serial.println("WLAN Station " + wlanConfig.ssidStation + " Client with IP address " + WiFi.localIP().toString() + " connected."); } }

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info) {
  wlanConfig.statusStation=false; WiFi.disconnect(); wlanTimer=millis()+4000;
  if (debug) { Serial.println("WLAN Station disconnected."); } }

void connectWLAN() {
  WiFi.setHostname(wlanConfig.ssidAP); wlanTimer=millis()+20000;
  if (wlanConfig.ssidStation=="empty") { return; }
  if (debug) { Serial.println("WLAN Station " + wlanConfig.ssidStation + " try connect."); }
  WiFi.begin(wlanConfig.ssidStation.c_str(),wlanConfig.passwordStation.c_str()); }

void initWLAN() {
  preferences.begin("wlanAuth",false); wlanConfig.ssidStation=preferences.getString("ssidStation","empty"); wlanConfig.passwordStation=preferences.getString("passwordStation","empty"); preferences.end();
  WiFi.mode(WIFI_AP_STA);
  WiFi.onEvent(WiFiStationConnected,ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.onEvent(WiFiStationDisconnected,ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
  WiFi.softAPConfig(IPAddress(192,168,4,1),IPAddress(192,168,4,1),IPAddress(255,255,255,0)); WiFi.softAP(wlanConfig.ssidAP,wlanConfig.passwordAP);
  if (debug) { Serial.println("WLAN AP " + String(wlanConfig.ssidAP) + " with IP address " + WiFi.softAPIP().toString() + " enabled."); }
  connectWLAN(); }

void reconnectWLAN() { WiFi.disconnect(); connectWLAN(); }

void wlanWorker() {
  if (millis()>=wlanTimer) { wlanTimer=millis()+20000;
    if (!wlanConfig.statusStation) {
      if (wlanConfig.reconnectCount>5) {
        if (debug) { Serial.println("WLAN Station get stored credentials."); }
        preferences.begin("wlanAuth",false); wlanConfig.ssidStation=preferences.getString("ssidStation","empty"); wlanConfig.passwordStation=preferences.getString("passwordStation","empty"); preferences.end(); }
      if (debug) { Serial.println("WLAN Station autoreconnect."); }
      wlanConfig.reconnectCount++; reconnectWLAN(); } } }
