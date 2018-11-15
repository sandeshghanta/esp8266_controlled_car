#include "ArduinoJson.h"
WiFiUDP Udp;
unsigned int localUdpPort = 4320;  // local port to listen on
byte incomingPacket[255];  // buffer for incoming packets
long time_udp_call;
bool udp_call;
char line[5];

void UDPSetup(){
  strcpy(line,"true");
  Udp.begin(localUdpPort);
  udp_call = false;
}

void UDPLoop(){
  StaticJsonBuffer<200> js;
  int packetSize = Udp.parsePacket();
    int len = Udp.read(incomingPacket, 255);
    JsonObject& root = js.parseObject(incomingPacket);
    if(!root.success()){
      return;
    }
    else{
      Serial.println("Parsing Done!");
      char temp[5];
      strcpy(temp,root["btn_l"]);
      if (strcmp(temp,line) == 0){
        left();
      }
      strcpy(temp,root["btn_r"]);
      if (strcmp(temp,line) == 0){
        right();
      }
      strcpy(temp,root["btn_f"]);
      if (strcmp(temp,line) == 0){
        front();
      }
      else{
        for (int i=0;i<5;i++){
          Serial.print(temp[i]);
        }
        Serial.println();
      }
      strcpy(temp,root["btn_b"]);
      if (strcmp(temp,line) == 0){
        back();
      }
    }
}
