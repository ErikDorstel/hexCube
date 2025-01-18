#define lines 40

void appSpaghetti() {
  hueWorker();
  static struct { uint8_t x; uint8_t y; uint8_t c; } line[lines];
  static uint64_t apaghettiTimer;
  if (millis()>=apaghettiTimer) { apaghettiTimer=millis()+config.delay;

    for (uint8_t i=1;i<lines;i++) {
      line[i-1].x=line[i].x; line[i-1].y=line[i].y; line[i-1].c=line[i].c; }

    line[lines-1].x=random8(64); line[lines-1].y=random8(24);
    line[lines-1].c=random8(min(config.hueA,config.hueB),max(config.hueA,config.hueB));

    for (uint8_t i=1;i<lines;i++) {
      cubeLine(line[i-1].x,line[i-1].y,line[i].x,line[i].y,CHSV(line[i-1].c,255,255*(i-1)/(lines-2))); }

    cubeShow(); } }

void initSpaghetti() {
  strcpy(apps.name[apps.count],"Spaghetti");
  strcpy(apps.config[apps.count],"5,bright,delay,hueA,hueSpeedA,hueB");
  apps.worker[apps.count]=appSpaghetti;
  apps.count++; }
