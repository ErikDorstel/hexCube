void appFills() {
  static uint8_t hue=0;
  static uint64_t fillsTimer;
  if (millis()>=fillsTimer) { fillsTimer=millis()+config.delay;
    cubeFill(CHSV(hue,255,255),0);
    hue+=32; if (hue>224) { hue=0; }
    cubeShow(); } }

void initFills() {
  strcpy(apps.name[apps.count],"Fills");
  strcpy(apps.config[apps.count],"2,bright,delay");
  apps.worker[apps.count]=appFills;
  apps.count++; }
