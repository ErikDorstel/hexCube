DEFINE_GRADIENT_PALETTE( fireColorsDefine ) {
     0,     0,  0,  0,
    30,   255,  0,  0,
   150,   255,255,  0,
   255,   255,255,255 };
CRGBPalette256 fireColors=fireColorsDefine;

DEFINE_GRADIENT_PALETTE( plasmaColorsDefine ) {
     0,   0,  0,255,
   127,   0,  0,  0,
   128,   0,  0,  0,
   255, 255,  0,  0 };
CRGBPalette256 plasmaColors=plasmaColorsDefine;

void modifyPlasmaColors(int hueA,int hueB,int border,int ratio) {
  int a=127-min(127,border+ratio); int b=a+border;
  int c=b+1; int d=c+border;
  CRGB colorA; colorA.setHue(hueA);
  CRGB colorB; colorB.setHue(hueB);
  fill_gradient_RGB(plasmaColors,0,colorA,a,colorA/31);
  if (border>0) {
    fill_gradient_RGB(plasmaColors,a,colorA/31,b,CRGB(0,0,0));
    fill_gradient_RGB(plasmaColors,c,CRGB(0,0,0),d,colorB/31); }
  fill_gradient_RGB(plasmaColors,d,colorB/31,255,colorB); }
