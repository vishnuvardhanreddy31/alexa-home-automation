#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLFRIVnj-0"
#define BLYNK_DEVICE_NAME "Automation of IoT Lab"
#define BLYNK_AUTH_TOKEN "7d72et463nCM1WqR2r5BJvYL1mdBVqMX"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp8266.h>





char auth[] = "7d72et463nCM1WqR2r5BJvYL1mdBVqMX";//Paste auth token you copied


char ssid[] = "IOTlab";///Enter your wifi name
char pass[] = "iotlab@p202";// Enter wifi password

BlynkTimer timer;

BLYNK_WRITE(V0)
{
  int relay1 = param.asInt();
  digitalWrite(5,relay1);
  }
  BLYNK_WRITE(V1)
{
  int realy2 = param.asInt();
  digitalWrite(4,realy2);
  }
   BLYNK_WRITE(V2)
{
  int realy3 = param.asInt();
  digitalWrite(12,realy3);
  }
   BLYNK_WRITE(V3)
{
  int realy4 = param.asInt();
  digitalWrite(13,realy4);
  }
  BLYNK_WRITE(V4)
{
  int realy5 = param.asInt();
  digitalWrite(14,realy5);
  }

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(14,OUTPUT);
delay(1000);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  // Setup a function to be called every second
  //timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
} 
