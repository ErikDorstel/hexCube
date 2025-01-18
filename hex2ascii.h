// Hex to ASCII Library
// 2021 Erik Dorstel
// call ascii=h2a(hex);
// call hex=a2h(ascii);

String h2a(String hValue) {
  String aValue=""; for (int index=0;index<hValue.length();index+=2) {
    int h1=hValue.charAt(index); if (h1>96) { h1-=87; } else if (h1>64) { h1-=55; } else { h1-=48; }
    int h2=hValue.charAt(index+1); if (h2>96) { h2-=87; } else if (h2>64) { h2-=55; } else { h2-=48; }
    char h=h1*16+h2; aValue+=h; } return aValue; }

String a2h(String aValue) {
  String hValue=""; for (int index=0;index<aValue.length();index+=1) {
    hValue+=String(aValue.charAt(index),HEX); } return hValue; }
