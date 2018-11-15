#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

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

#define WIFI_SSID "wifiname"
#define WIFI_PASS "wifipassword"
 
#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883

#define MQTT_NAME "mqtt-username"
#define MQTT_PASS "mqtt-password"
 
//Set up MQTT and WiFi clients
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);
 
//Set up the feed you're subscribing to
//https://io.adafruit.com/diygeeks/feeds/onoff
Adafruit_MQTT_Subscribe voice = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/feeds/voice-control");
 
 
void setup()
{
  Serial.begin(9600);
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
  
  //Connect to WiFi
  
  Serial.print("\n\nConnecting Wifi... ");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
 
  Serial.println("OK!");
 
  //Subscribe to the voice feed
  mqtt.subscribe(&voice);
}
void accelerate(){
  for(int i =0; i<1024; i++){
    analogWrite(enablepin, i);
  }
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
}
void stop(){
  digitalWrite(pinfr2, LOW);
  digitalWrite(pinbr2, LOW);
  digitalWrite(pinfl2, LOW);
  digitalWrite(pinbl2, LOW);
  digitalWrite(pinfr1, LOW);
  digitalWrite(pinbr1, LOW);
  digitalWrite(pinfl1, LOW);
  digitalWrite(pinbl1, LOW);
}
void loop()
{
  MQTT_connect();
  
  //Read from our subscription queue until we run out, or
  //wait up to 5 seconds for subscription to update
  Adafruit_MQTT_Subscribe * subscription;
  while ((subscription = mqtt.readSubscription(1000)))
  {
    //If we're in here, a subscription updated...
    if (subscription == &voice)
    {
      //Print the new value to the serial monitor
      Serial.println((char*) voice.lastread);
      if (!strcmp((char*) voice.lastread, "13"))
      {
        //back
        back();
      }
      else if (!strcmp((char*) voice.lastread, "5"))
      {
        //forward
        front();
      }
      else if (!strcmp((char*) voice.lastread, "10")){
        //right
        right();
      }
      else if (!strcmp((char*) voice.lastread, "8")){
        //left
        left();
      }
      else if(!strcmp((char*) voice.lastread, "9")){
        //stop
        stop();
      }
      else{
        Serial.println("Invalid Input");
      }
    }
  }
 
  // ping the server to keep the mqtt connection alive
  if (!mqtt.ping())
  {
    mqtt.disconnect();
  }
}
 
void MQTT_connect() 
{
  int8_t ret;
 
  // Stop if already connected.
  if (mqtt.connected()) 
  {
    return;
  }
 
  Serial.print("Connecting to MQTT... ");
 
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) // connect will return 0 for connected
  { 
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) 
       {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
