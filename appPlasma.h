void appPlasma() {
  palettesWorker();

  // noisemap parameter declaration
  static uint32_t x,y,z;
  static uint32_t scaleX,scaleY;
  // noisemap declaration
  static uint8_t noise[width][height];

  // noisemap initialization
  uint16_t ctrlX = inoise16(11 * millis(), 0, 0);
  uint16_t ctrlY = inoise16(13 * millis(), 100000, 100000);
  x = millis() * config.speed;
  y = millis() * config.speed;
  z = millis() * config.speed;
  scaleX = ctrlX / 2;
  scaleY = ctrlY / 2;

  // build noisemap
  for (uint8_t i = 0; i < width; i++) {
    uint32_t ioffset = scaleX * (i - centreX);
    for (uint8_t j = 0; j < height; j++) {
      uint32_t joffset = scaleY * (j - centreY);
      uint16_t data = ((inoise16(x + ioffset, y + joffset, z)) + 1);
      noise[i][j] = data >> 8; } }

  // map colors from noisemap
  for (uint8_t y = 0; y < height; y++) {
    for (uint8_t x = 0; x < width; x++) {
      cubeSet(x,y,ColorFromPalette(plasmaColors,sin8(noise[x][y]))); } }

  FastLED.show();

  delay(10); }

void initPlasma() {
  strcpy(apps.name[apps.count],"Plasma");
  strcpy(apps.config[apps.count],"8,bright,speed,hueA,hueSpeedA,hueB,hueSpeedB,border,ratio");
  apps.worker[apps.count]=appPlasma;
  apps.count++; }
