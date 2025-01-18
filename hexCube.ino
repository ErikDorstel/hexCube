bool debug=true;

const char* appName="hexCube";
const char* appDesc="RGB LED Cube";

#include "Cube.h"
#include "Palettes.h"
#include "Tilt.h"
#include "Mic.h"
#include "Apps.h"
#include "WLAN.h"
#include "DNS.h"
#include "HTTPserver.h"

#include "appFire.h"
#include "appPlasma.h"
#include "appRain.h"
#include "appRects.h"
#include "appSpaghetti.h"
#include "appFills.h"
#include "appAlarm.h"
#include "appInsects.h"
#include "appGlas.h"
#include "appOscar.h"

void setup() {
  if (debug) { Serial.begin(115200); }
  initCube();
  //initTilt();
  initMic();
  initWLAN();
  initDNS();
  initHTTPServer();

  initFire();
  initPlasma();
  initRain();
  initRects();
  initSpaghetti();
  initFills();
  initAlarm();
  initInsects();
  initGlas();
  initOscar(); }

void loop() { apps.worker[apps.current](); brightWorker(); wlanWorker(); dnsWorker(); httpServerWorker(); }
