#define rains 200

void appRain() {
  hueWorker();
  static struct { uint8_t x; uint8_t y=100; uint8_t c; } rain[rains];
  static uint64_t rainTimer=millis();
  if (millis()>rainTimer) {
    rainTimer=millis()+config.delay;
    for (uint8_t i=0;i<config.count;i++) {
      if (rain[i].y>=height+config.length-2) {
        if (random8(3)==0) {
          rain[i].x=random8(width);
          rain[i].y=0;
          rain[i].c=random8(min(config.hueA,config.hueB),max(config.hueA,config.hueB));
          cubeSet(rain[i].x,rain[i].y,CHSV(rain[i].c,255,255));
        }
      } else {
        rain[i].y++;
        for (int j=0;j<config.length;j++) {
          if (rain[i].y-j<height && rain[i].y>=j) {
            cubeSet(rain[i].x,rain[i].y-j,CHSV(rain[i].c,255,255*(config.length-1-j)/(config.length-1)));
          }  
        }
      }
    }
    FastLED.show();
  }
}

void initRain() {
  strcpy(apps.name[apps.count],"Rain");
  strcpy(apps.config[apps.count],"7,bright,delay,hueA,hueSpeedA,hueB,count,length");
  apps.worker[apps.count]=appRain;
  apps.count++; }
