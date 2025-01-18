#define pixels 20

void appInsects() {
  hueWorker();
  static struct { float x; float y; uint8_t c; float xDiff; float yDiff; uint8_t xOld; uint8_t yOld; } pixel[pixels];
  static uint64_t insectsTimer;
  if (millis()>=insectsTimer) { insectsTimer=millis()+config.delay;
    for (int i=0;i<20;i++) {

      if ((pixel[i].xDiff==0 && pixel[i].yDiff==0) || random8(100)==0) {
        pixel[i].xDiff=random8(60,100)/100.0; pixel[i].yDiff=random8(20,100)/100.0;
        pixel[i].c=random8(min(config.hueA,config.hueB),max(config.hueA,config.hueB)); }

      pixel[i].x+=pixel[i].xDiff; pixel[i].y+=pixel[i].yDiff;
      if (pixel[i].x<0) { pixel[i].x=63; }
      if (pixel[i].x>=64) { pixel[i].x=0; }
      if (pixel[i].y<0) { pixel[i].yDiff*=-1; pixel[i].y=0; }
      if (pixel[i].y>=24) { pixel[i].yDiff*=-1; pixel[i].y=23; }

      if ((uint8_t)pixel[i].y<8) { while (transform[(uint8_t)pixel[i].x][(uint8_t)pixel[i].y]==256) {
        pixel[i].x+=pixel[i].xDiff; pixel[i].y+=pixel[i].yDiff;
        if (pixel[i].x<0) { pixel[i].x=63; }
        if (pixel[i].x>=64) { pixel[i].x=0; }
        if (pixel[i].y<0) { pixel[i].yDiff*=-1; pixel[i].y=0; }
        if (pixel[i].y>=24) { pixel[i].yDiff*=-1; pixel[i].y=23; } } }

      cubeSet(pixel[i].xOld,pixel[i].yOld,CHSV(0,0,0));
      cubeSet(pixel[i].x,pixel[i].y,CHSV(pixel[i].c,255,255));
      pixel[i].xOld=pixel[i].x; pixel[i].yOld=pixel[i].y; }
    cubeShow(); } }

void initInsects() {
  strcpy(apps.name[apps.count],"Insects");
  strcpy(apps.config[apps.count],"5,bright,delay,hueA,hueSpeedA,hueB");
  apps.worker[apps.count]=appInsects;
  apps.count++; }
