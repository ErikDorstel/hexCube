void appFire() {

  // noisemap parameter declaration
  static uint32_t x,y,z;
  static uint32_t scaleX,scaleY;
  // noisemap declaration
  static uint8_t noise[width][height];
  // heatmap declaration
  static uint8_t heat[width][height];

  // noisemap initialization
  uint16_t ctrlX = inoise16(11 * millis(), 0, 0);
  uint16_t ctrlY = inoise16(13 * millis(), 100000, 100000);
  uint16_t ctrlZ = ((ctrlX + ctrlY) / 2);
  uint8_t speed = 10; // movement speed, standard value 27
  x = 3 * ctrlZ * speed;
  y = 15 * millis() * speed;
  z = 3 * millis() * speed;
  scaleX = ctrlX / 2;
  scaleY = ctrlY / 2;

  // build noisemap
  for (uint8_t i = 0; i < width; i++) {
    uint32_t ioffset = scaleX * (i - centreX);
    for (uint8_t j = 0; j < height; j++) {
      uint32_t joffset = scaleY * (j - centreY);
      uint16_t data = ((inoise16(x + ioffset, y + joffset, z)) + 1);
      noise[i][j] = data >> 8; } }

  // draw buttom line
  for (uint8_t x = 0; x < width; x++) {
    cubeSet(x,height-1,ColorFromPalette( fireColors, noise[x][0]) );
    heat[x][height-1] = noise[x][0]; }

  // add flares
  if (random(5)==1) {
    uint8_t xfp=random(width);
    uint8_t xfw=random(2,6);
    for (uint8_t i=0;i<xfw;i++) {
      for (uint8_t j=2;j<5;j++) {
        heat[(xfp+i)%width][height-j] = noise[(xfp+i)%width][j-1]; } } }

  // scroll up heatmap
  for (uint8_t y = 0; y < height - 1; y++) {
    for (uint8_t x = 0; x < width; x++) {
      heat[x][y] = heat[x][y + 1]; } }

  // cool the fire with noise
  for (uint8_t y = 0; y < height - 1; y++) {
    for (uint8_t x = 0; x < width; x++) {
      uint8_t dim = noise[x][y];
      dim = dim / 2.8; // cool the fire, standard value 1.4
      dim = 255 - dim;
      heat[x][y] = scale8(heat[x][y] , dim); } }

  // map colors from heatmap
  for (uint8_t y = 0; y < height - 1; y++) {
    for (uint8_t x = 0; x < width; x++) {
      cubeSet(x,y,ColorFromPalette(fireColors,heat[x][y])); } }

  FastLED.show();

  delay(10); } // synchronize speed and movement, standard value 10

void initFire() {
  strcpy(apps.name[apps.count],"Fire");
  strcpy(apps.config[apps.count],"1,bright");
  apps.worker[apps.count]=appFire;
  apps.count++; }
