#define rects 20

void appRects() {
  hueWorker();
  static struct { uint8_t xa; uint8_t ya; uint8_t xb; uint8_t yb; uint8_t c; } rect[rects];
  static uint64_t rectTimer;
  if (millis()>=rectTimer) { rectTimer=millis()+config.delay;

    for (uint8_t i=1;i<rects;i++) {
      rect[i-1].xa=rect[i].xa; rect[i-1].ya=rect[i].ya; rect[i-1].c=rect[i].c;
      rect[i-1].xb=rect[i].xb; rect[i-1].yb=rect[i].yb; }

    rect[rects-1].xa=random8(64); rect[rects-1].ya=random8(24);
    rect[rects-1].xb=random8(2,8); rect[rects-1].yb=random8(2,4);
    rect[rects-1].c=random8(min(config.hueA,config.hueB),max(config.hueA,config.hueB));

    for (uint8_t i=0;i<rects;i++) {
      cubeRect(rect[i].xa,rect[i].ya,rect[i].xb,rect[i].yb,CHSV(rect[i].c,255,255*(i)/(rects-1))); }

    cubeShow(); } }

void initRects() {
  strcpy(apps.name[apps.count],"Rects");
  strcpy(apps.config[apps.count],"5,bright,delay,hueA,hueSpeedA,hueB");
  apps.worker[apps.count]=appRects;
  apps.count++; }
