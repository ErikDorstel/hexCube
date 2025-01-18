WiFiUDP dnsServer;
WiFiUDP mdnsServer;
uint32_t dnsTimer; uint8_t request[200]; uint8_t reply[200]; uint8_t filter[200];

void initDNS() {
  dnsServer.begin(53);
  mdnsServer.beginMulticast(IPAddress(224,0,0,251),5353);
  dnsTimer=0; }

void replyUCAST() {
  const byte headRep[]={0x81,0x80,0,1,0,1,0,0,0,0};
  const byte footRep[]={0xC0,0x0C,0,1,0,1,0,0,0,60,0,4};
  IPAddress softAPIP=WiFi.softAPIP();
  byte hostlen=strlen(appName);
  memcpy(reply,request,2);
  memcpy(reply+2,headRep,10);
  memcpy(reply+12,request+12,hostlen+12);
  memcpy(reply+hostlen+24,footRep,12);
  memcpy(reply+hostlen+36,&softAPIP[0],4);
  dnsServer.beginPacket(dnsServer.remoteIP(),dnsServer.remotePort());
  dnsServer.write(reply,hostlen+40);
  dnsServer.endPacket(); }

void replyMCAST() {
  const byte headRep[]={0,0,0x84,0,0,0,0,1,0,0,0,0};
  const byte footRep[]={0,0,1,0x80,1,0,0,0,60,0,4};
  IPAddress localIP=WiFi.localIP();
  byte hostlen=strlen(appName);
  byte hostname[hostlen];
  memcpy(hostname,appName,hostlen);
  for (int i=0;i<hostlen;i++) { hostname[i]=tolower(hostname[i]); }
  const byte suffix[]="local";
  memcpy(reply,headRep,12);
  memset(reply+12,hostlen,1);
  memcpy(reply+13,hostname,hostlen);
  memset(reply+hostlen+13,5,1);
  memcpy(reply+hostlen+14,suffix,5);
  memcpy(reply+hostlen+19,footRep,11);
  memcpy(reply+hostlen+30,&localIP[0],4);
  mdnsServer.beginMulticastPacket();
  mdnsServer.write(reply,hostlen+34);
  mdnsServer.endPacket(); }

void dnsWorker() {
  if (dnsServer.parsePacket()) {
    if (dnsServer.available()>200) { dnsServer.flush(); } else {
      dnsServer.read(request,200);
      const byte headReq[]={1,0,0,1,0,0,0,0,0,0};
      const byte footReq[]={0,0,1,0,1};
      byte hostlen=strlen(appName);
      byte hostname[hostlen];
      memcpy(hostname,appName,hostlen);
      for (int i=0;i<hostlen;i++) { hostname[i]=tolower(hostname[i]); }
      const byte suffix[]="local";
      memcpy(filter,headReq,10);
      memset(filter+10,hostlen,1);
      memcpy(filter+11,hostname,hostlen);
      memset(filter+hostlen+11,5,1);
      memcpy(filter+hostlen+12,suffix,5);
      memcpy(filter+hostlen+17,footReq,5);
      if (memcmp(request+2,filter,hostlen+22)==0) { replyUCAST();
        if (debug) { Serial.println("Reply DNS Packet to " + dnsServer.remoteIP().toString() + "."); } } } }

  if (mdnsServer.parsePacket()) {
    if (mdnsServer.available()>200) { mdnsServer.flush(); } else {
      mdnsServer.read(request,200);
      const byte headReq[]={0,0,0,1,0,0,0,0,0,0};
      const byte footReq[]={0,0,1,0,1};
      byte hostlen=strlen(appName);
      byte hostname[hostlen];
      memcpy(hostname,appName,hostlen);
      for (int i=0;i<hostlen;i++) { hostname[i]=tolower(hostname[i]); }
      const byte suffix[]="local";
      memcpy(filter,headReq,10);
      memset(filter+10,hostlen,1);
      memcpy(filter+11,hostname,hostlen);
      memset(filter+hostlen+11,5,1);
      memcpy(filter+hostlen+12,suffix,5);
      memcpy(filter+hostlen+17,footReq,5);
      if (memcmp(request+2,filter,hostlen+22)==0) { replyMCAST();
        if (debug) { Serial.println("Reply MDNS Packet to " + mdnsServer.remoteIP().toString() + "."); } } } }

  if (millis()>=dnsTimer) { dnsTimer=millis()+30000; replyMCAST(); } }
