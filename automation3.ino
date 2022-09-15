/**********************************************************************************
 *  TITLE: Alexa control 5 channel Relay Module using NodeMCU or ESP32
 **********************************************************************************/

#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>
// define the GPIO connected with Relays
#define RelayPin1  5  //D1//line one
#define RelayPin2 4  //D2//light6
#define RelayPin3 13 //D7//light7
#define RelayPin4 14 //D5//light8
#define RelayPin5 12 //D6//fan4

// prototypes
boolean connectWifi();

//callback functions
void firstLightChanged(uint8_t brightness);
/**void secondLightChanged(uint8_t brightness);
void thirdLightChanged(uint8_t brightness);
void fourthLightChanged(uint8_t brightness);
void fifthLightChanged(uint8_t brightness);**/

// WiFi Credentials
const char* ssid = "IOTlab";
const char* password = "iotlab@p202";

// device names
String Device_1_Name = "channel1";
String Device_2_Name = "light6";
String Device_3_Name = "light7";
String Device_4_Name = "light8";
String Device_5_Name = "fan4";

boolean wifiConnected = false;

Espalexa espalexa;

void setup()
{
  Serial.begin(115200);

  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);
  pinMode(RelayPin5, OUTPUT);

  // Initialise wifi connection
  wifiConnected = connectWifi();

  if (wifiConnected)
  {
    // Define your devices here.
    espalexa.addDevice(Device_1_Name, channel1); //simplest definition, default state off
    espalexa.addDevice(Device_2_Name, sixthLightChanged);
    espalexa.addDevice(Device_3_Name, seventhLightChanged);
    espalexa.addDevice(Device_4_Name, eightLightChanged);
    espalexa.addDevice(Device_5_Name, fourthFanChanged);

    espalexa.begin();
  }
  else
  {
    while (1)
    {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}

void loop()
{
  espalexa.loop();
  delay(1);
}

//our callback functions
void channel1(uint8_t brightness)
{
  //Control the device
  if (brightness == 255)
    {
      digitalWrite(RelayPin1, LOW);
      digitalWrite(RelayPin2, LOW);
      digitalWrite(RelayPin3, LOW);
      digitalWrite(RelayPin4, LOW);
      //digitalWrite(RelayPin5, LOW);
      Serial.println("channel1 ON");
    }
  else
  {
    digitalWrite(RelayPin1, HIGH);
      digitalWrite(RelayPin2, HIGH);
      digitalWrite(RelayPin3, HIGH);
      digitalWrite(RelayPin4, HIGH);
      //digitalWrite(RelayPin5, HIGH);
    Serial.println("channel1 OFF");
  }
}

void sixthLightChanged(uint8_t brightness)
{
  //Control the device 
  if (brightness == 255)
    {
      digitalWrite(RelayPin2, LOW);
      Serial.println("Light6 ON");
    }
  else
  {
    digitalWrite(RelayPin2, HIGH);
    Serial.println("Light6 OFF");
  }
}

void seventhLightChanged(uint8_t brightness)
{
  //Control the device  
  if (brightness == 255)
    {
      digitalWrite(RelayPin3, LOW);
      Serial.println("Light7 ON");
    }
  else
  {
    digitalWrite(RelayPin3, HIGH);
    Serial.println("Light7 OFF");
  }
}

void eightLightChanged(uint8_t brightness)
{
  //Control the device 
  if (brightness == 255)
    {
      digitalWrite(RelayPin4, LOW);
      Serial.println("Light8 ON");
    }
  else
  {
    digitalWrite(RelayPin4, HIGH);
    Serial.println("Light8 OFF");
  }
}

void fourthFanChanged(uint8_t brightness)
{
  //Control the device 
  if (brightness == 255)
    {
      digitalWrite(RelayPin5, LOW);
      Serial.println("Fan4 ON");
    }
  else
  {
    digitalWrite(RelayPin5, HIGH);
    Serial.println("Fan4 OFF");
  }
}

// connect to wifi – returns true if successful or false if not
boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
