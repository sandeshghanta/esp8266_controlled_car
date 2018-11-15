#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#define enablepin D0

//Right part
//motor A
#define pinfr1 D1
#define pinfr2 D2
// motor B
#define pinbr1 D3
#define pinbr2 D4
//Left part
// motor C
#define pinfl1 D5
#define pinfl2 D6
// motor D
#define pinbl1 D7
#define pinbl2 D8

// wifi
#define WIFI_SSID //your wifi name
#define WIFI_PASS //your wifi password

void setup() {
  Serial.begin(9600);
  Serial.println( "\r\n\r\n--------------------------------------" );
  Serial.println( "START setup" );
  delay(500);

  pinMode(enablepin, OUTPUT);
  pinMode(pinfr1, OUTPUT);
  pinMode(pinfr2, OUTPUT);
  pinMode(pinbr1, OUTPUT);
  pinMode(pinbr2, OUTPUT);
  pinMode(pinfl1, OUTPUT);
  pinMode(pinfl2, OUTPUT);
  pinMode(pinbl1, OUTPUT);
  pinMode(pinbl2, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  //WiFi.hostname( GetNameDev() );

  Serial.print("Connecting to WIFI");

  // Wait for connection
  while( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println( WIFI_SSID );
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  UDPSetup();
  Serial.println( "END setup" );
}
void back(){
  digitalWrite(pinfr2, HIGH);
  digitalWrite(pinbr2, HIGH);
  digitalWrite(pinfl1, HIGH);
  digitalWrite(pinbl1, HIGH);
  digitalWrite(pinfr1, LOW);
  digitalWrite(pinbr1, LOW);
  digitalWrite(pinfl2, LOW);
  digitalWrite(pinbl2, LOW);
  accelerate();
  delay(30);
  reset_all();
}
void left(){
  digitalWrite(pinfr1, HIGH);
  digitalWrite(pinbr1, HIGH);
  digitalWrite(pinfl1, HIGH);
  digitalWrite(pinbl1, HIGH);
  digitalWrite(pinfr2, LOW);
  digitalWrite(pinbr2, LOW);
  digitalWrite(pinfl2, LOW);
  digitalWrite(pinbl2, LOW);
  accelerate();
  delay(30);
  reset_all();
}
void right(){
  digitalWrite(pinfr2, HIGH);
  digitalWrite(pinbr2, HIGH);
  digitalWrite(pinfl2, HIGH);
  digitalWrite(pinbl2, HIGH);
  digitalWrite(pinfr1, LOW);
  digitalWrite(pinbr1, LOW);
  digitalWrite(pinfl1, LOW);
  digitalWrite(pinbl1, LOW);
  accelerate();
  delay(30);
  reset_all();
}
void front(){
  Serial.println("forward");
  digitalWrite(pinfr1, HIGH);
  digitalWrite(pinbr1, HIGH);
  digitalWrite(pinfl2, HIGH);
  digitalWrite(pinbl2, HIGH);
  digitalWrite(pinfr2, LOW);
  digitalWrite(pinbr2, LOW);
  digitalWrite(pinfl1, LOW);
  digitalWrite(pinbl1, LOW);
  accelerate();
  delay(30);
  reset_all();
}
void reset_all(){
  digitalWrite(pinfr1, LOW);
  digitalWrite(pinbr1, LOW);
  digitalWrite(pinfl2, LOW);
  digitalWrite(pinbl2, LOW);
  digitalWrite(pinfr2, LOW);
  digitalWrite(pinbr2, LOW);
  digitalWrite(pinfl1, LOW);
  digitalWrite(pinbl1, LOW);
}
void accelerate(){
  for(int i =0; i<1024; i++){
    analogWrite(enablepin, i);
  }
}
void loop() {
 UDPLoop();
}
