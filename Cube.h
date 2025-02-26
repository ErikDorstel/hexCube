#include <FastLED.h>

#define width   64
#define height  24
#define centreX 31
#define centreY 11

CRGB cube[5][256];

const uint16_t transform[64][8]=
{ { 256,256,256,256,256,256,256,  0 },{ 256,256,256,256,256,256, 30,  1 },{ 256,256,256,256,256, 34, 29,  2 },{ 256,256,256,256, 60, 35, 28,  3 },{ 256,256,256, 68, 59, 36, 27,  4 },{ 256,256, 90, 69, 58, 37, 26,  5 },{ 256,102, 89, 70, 57, 38, 25,  6 },{ 120,103, 88, 71,56, 39, 24,  7 },
  { 256,104, 87, 72, 55, 40, 23,  8 },{ 256,256, 86, 73, 54, 41, 22,  9 },{ 256,256,256, 74, 53, 42, 21, 10 },{ 256,256,256,256, 52, 43, 20, 11 },{ 256,256,256,256,256, 44, 19, 12 },{ 256,256,256,256,256,256, 18, 13 },{ 256,256,256,256,256,256,256, 14 },{ 256,256,256,256,256,256,256,256 },
  { 256,256,256,256,256,256,256, 15 },{ 256,256,256,256,256,256, 17, 16 },{ 256,256,256,256,256, 45, 46, 47 },{ 256,256,256,256, 51, 50, 49, 48 },{ 256,256,256, 75, 76, 77, 78, 79 },{ 256,256, 85, 84, 83, 82, 81, 80 },{ 256,105,106,107,108,109,110,111 },{ 119,118,117,116,115,114,113,112 },
  { 256,137,138,139,140,141,142,143 },{ 256,256,149,148,147,146,145,144 },{ 256,256,256,171,172,173,174,175 },{ 256,256,256,256,179,178,177,176 },{ 256,256,256,256,256,205,206,207 },{ 256,256,256,256,256,256,209,208 },{ 256,256,256,256,256,256,256,239 },{ 256,256,256,256,256,256,256,256 },
  { 256,256,256,256,256,256,256,240 },{ 256,256,256,256,256,256,238,241 },{ 256,256,256,256,256,210,237,242 },{ 256,256,256,256,204,211,236,243 },{ 256,256,256,180,203,212,235,244 },{ 256,256,170,181,202,213,234,245 },{ 256,150,169,182,201,214,233,246 },{ 136,151,168,183,200,215,232,247 },
  { 256,152,167,184,199,216,231,248 },{ 256,256,166,185,198,217,230,249 },{ 256,256,256,186,197,218,229,250 },{ 256,256,256,256,196,219,228,251 },{ 256,256,256,256,256,220,227,252 },{ 256,256,256,256,256,256,226,253 },{ 256,256,256,256,256,256,256,254 },{ 256,256,256,256,256,256,256,256 },
  { 256,256,256,256,256,256,256,255 },{ 256,256,256,256,256,256,225,224 },{ 256,256,256,256,256,221,222,223 },{ 256,256,256,256,195,194,193,192 },{ 256,256,256,187,188,189,190,191 },{ 256,256,165,164,163,162,161,160 },{ 256,153,154,155,156,157,158,159 },{ 135,134,133,132,131,130,129,128 },
  { 256,121,122,123,124,125,126,127 },{ 256,256,101,100, 99, 98, 97, 96 },{ 256,256,256, 91, 92, 93, 94, 95 },{ 256,256,256,256, 67, 66, 65, 64 },{ 256,256,256,256,256, 61, 62, 63 },{ 256,256,256,256,256,256, 33, 32 },{ 256,256,256,256,256,256,256, 31 },{ 256,256,256,256,256,256,256,256 } };

void cubeBright(uint8_t bright) { FastLED.setBrightness(bright); }
void cubeClear() { FastLED.clear(); }
void cubeShow() { FastLED.show(); }

void cubeSet(uint8_t x, uint8_t y, CRGB c) {
  x=x%64; y=y%24;
  if (y<8) { uint16_t idx=transform[x][y]; if (idx<256) { cube[4][idx]=c; } }
  else { if(y%2) { cube[x>>4][((y-8)<<4)+(x%16)]=c; } else { cube[x>>4][((y-8)<<4)+15-(x%16)]=c; } } }

void cubeSet(uint8_t x, uint8_t y, CHSV c) {
  x=x%64; y=y%24;
  if (y<8) { uint16_t idx=transform[x][y]; if (idx<256) { cube[4][idx]=c; } }
  else { if(y%2) { cube[x>>4][((y-8)<<4)+(x%16)]=c; } else { cube[x>>4][((y-8)<<4)+15-(x%16)]=c; } } }

void cubeFill(CHSV c, bool now) {
  for (uint8_t y=0;y<24;y++) { for (uint8_t x=0;x<64;x++) {
    cubeSet(x,y,c); if (now) { cubeShow(); } } } }

void cubeRect(uint8_t xa, uint8_t ya, uint8_t xb, uint8_t yb, CHSV c) {
  for (uint8_t y=ya;y<ya+yb;y++) {
    for (uint8_t x=xa;x<xa+xb;x++) {
      cubeSet(x,y,c); } } }

void cubeLine(uint8_t xa, uint8_t ya, uint8_t xb, uint8_t yb, CHSV c) {
  int dx=abs(xb-xa),sx=xa<xb?1:-1,dy=-abs(yb-ya),sy=ya<yb?1:-1,err1=dx+dy,err2;
  while (1) { cubeSet(xa,ya,c); if (xa==xb && ya==yb) break; err2=2*err1;
    if (err2>dy) { err1+=dy; xa+=sx; } if (err2<dx) { err1+=dx;ya+=sy; } } }

void initCube() {
  FastLED.addLeds<NEOPIXEL,25>(cube[0],256);
  FastLED.addLeds<NEOPIXEL,26>(cube[1],256);
  FastLED.addLeds<NEOPIXEL,27>(cube[2],256);
  FastLED.addLeds<NEOPIXEL,32>(cube[3],256);
  FastLED.addLeds<NEOPIXEL,33>(cube[4],256);
  cubeBright(0); cubeClear(); cubeShow(); }
