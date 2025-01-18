WiFiServer tcpServer(80);
#define requestTimeout 1000

#include "index_html.h"
#include "choose_html.h"
#include "hex2ascii.h"
#include "HTTProot.h"

void initHTTPServer() { tcpServer.begin(); }

void httpServerWorker() {
  WiFiClient httpServerClient=tcpServer.available(); String header="";
  if (httpServerClient) { String currentLine=""; uint64_t requestTimer=millis()+requestTimeout;
    while (httpServerClient.connected()) {
      if (millis()>=requestTimer) { httpServerClient.println("Request timeout"); break; }
      if (httpServerClient.available()) { char c=httpServerClient.read(); header+=c;
        if (c=='\n') {
          if (currentLine.length()==0) {
            httpServerClient.println("HTTP/1.1 200 OK");
            httpServerClient.println("Content-Type: text/html; charset=utf-8");
            httpServerClient.println("Connection: keep-alive");
            httpServerClient.println("Keep-Alive: timeout=5, max=1000");
            httpServerClient.println("Server: ESP32 wlanSkeleton Erik Dorstel");
            httpServerClient.println();
            int a=header.indexOf("GET "); int b=header.indexOf(" ",a+4);
            if (a>=0) { httpServerClient.println(httpget(header.substring(a+4,b)));
              if (debug) { Serial.println("HTTP Request " + header.substring(a+4,b) + " from " + httpServerClient.remoteIP().toString() + " received."); } }
            break; }
          else { currentLine=""; } }
        else if (c!='\r') { currentLine+=c; } } }
    header = ""; httpServerClient.stop(); } }
