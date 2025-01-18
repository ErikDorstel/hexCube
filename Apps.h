struct configStruct {
  int bright=22;
  int delay=63;
  int speed=22;
  int hueA=160;
  int hueSpeedA=0;
  int hueB=255;
  int hueSpeedB=0;
  int border=0;
  int ratio=0;
  int count=20;
  int length=5; } config;

struct appsStruct {
  int count=0;
  int current=0;
  char name[20][20]={""};
  char config[20][100]={""};
  void (*worker[20])()={nullptr}; } apps;

void brightWorker() {
  static int currentBright=0;
  static uint64_t brightTimer;
  if (millis()>=brightTimer) { brightTimer=millis()+100;
    int deltaBright=config.bright-currentBright;
      if (deltaBright!=0) {
           if (deltaBright>100) { currentBright+=10; }
      else if (deltaBright<-100) { currentBright-=10; }
      else if (deltaBright>30) { currentBright+=5; }
      else if (deltaBright<-30) { currentBright-=5; }
      else if (deltaBright>0) { currentBright+=1; }
      else if (deltaBright<0) { currentBright-=1; }
      cubeBright(currentBright); } } }

void hueWorker() {
  static uint64_t hueSpeedTimer;
  if (millis()>=hueSpeedTimer) { hueSpeedTimer=millis()+400;
    if (config.hueSpeedA>0) {
      config.hueA+=config.hueSpeedA; config.hueA%=256;
      config.hueB=config.hueA+32; if (config.hueB>255) { config.hueB=255; } } } }

void palettesWorker() {
  static uint64_t hueSpeedTimer;
  if (millis()>=hueSpeedTimer) { hueSpeedTimer=millis()+400;
    if (config.hueSpeedA>0 || config.hueSpeedB>0) {
      config.hueA+=config.hueSpeedA; config.hueA%=256;
      config.hueB+=config.hueSpeedB; config.hueB%=256;
      modifyPlasmaColors(config.hueA,config.hueB,config.border,config.ratio); } } }
