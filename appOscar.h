void appOscar() {
  micWorker();
  static int x=0;
  cubeLine(x,0,x,24,CHSV(160,255,255));
  cubeLine(x,23,x,23-((abs(mic.max)>>4)%24),CHSV(0,255,255));
  x++; x%=64;
  cubeShow(); }

void initOscar() {
  strcpy(apps.name[apps.count],"Oscar");
  strcpy(apps.config[apps.count],"1,bright");
  apps.worker[apps.count]=appOscar;
  apps.count++; }
