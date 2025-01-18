void appAlarm() {
  static uint8_t hue=config.hueA,x=0;
  static int direction=1;
  static uint64_t alarmTimer;
  if (millis()>=alarmTimer) { alarmTimer=millis()+config.delay;
    cubeClear();
    cubeRect(x,0,16,24,CHSV(hue,255,255));
    hue+=direction;
    if (hue<=min(config.hueA,config.hueB)) { direction=1; }
    if (hue>=max(config.hueA,config.hueB)) { direction=-1; }
    x++; x%=64;
    cubeShow(); } }

void initAlarm() {
  strcpy(apps.name[apps.count],"Alarm");
  strcpy(apps.config[apps.count],"4,bright,delay,hueA,hueB");
  apps.worker[apps.count]=appAlarm;
  apps.count++; }
