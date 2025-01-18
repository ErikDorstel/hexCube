void appGlas() {
  tiltWorker();
  static uint64_t tiltTimer=millis()+1000;
  if (millis()>=tiltTimer) { tiltTimer=millis()+1000;
    Serial.println(String(tilt.x) + " " + String(tilt.y) + " " + String(tilt.z) + " " + String(tilt.d) + " " + String(tilt.xy)); }

  int y0=8-(tilt.x/16); int y1=8+(tilt.y/16); int y2=8+(tilt.x/16); int y3=8-(tilt.y/16);
  y0=abs(y0)%12; y1=abs(y1)%12; y2=abs(y2)%12; y3=abs(y3)%12;
  cubeClear();
  cubeRect(0,y0,8,12-y0,CHSV(0,255,255));
  cubeRect(8,y1,8,12-y1,CHSV(0,255,255));
  cubeRect(16,y2,8,12-y2,CHSV(0,255,255));
  cubeRect(24,y3,8,12-y3,CHSV(0,255,255));
  cubeShow(); }

void initGlas() {
  strcpy(apps.name[apps.count],"Glas");
  strcpy(apps.config[apps.count],"1,bright");
  apps.worker[apps.count]=appGlas;
  apps.count++; }
