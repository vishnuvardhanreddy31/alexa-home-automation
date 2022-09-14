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
#define RelayPin1  5  //D1//cabin
#define RelayPin2 4  //D2//light3
#define RelayPin3 13 //D7//light4
#define RelayPin4 14 //D5//light5
#define RelayPin5 12 //D6//fan3

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
String Device_1_Name = "cabin";
String Device_2_Name = "light3";
String Device_3_Name = "light4";
String Device_4_Name = "light5";
String Device_5_Name = "fan3";

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
    espalexa.addDevice(Device_1_Name, cabin); //simplest definition, default state off
    espalexa.addDevice(Device_2_Name, thirdLightChanged);
    espalexa.addDevice(Device_3_Name, fourthLightChanged);
    espalexa.addDevice(Device_4_Name, fifthLightChanged);
    espalexa.addDevice(Device_5_Name, thirdFanChanged);

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
void cabin(uint8_t brightness)
{
  //Control the device
  if (brightness == 255)
    {
      digitalWrite(RelayPin1, LOW);
      digitalWrite(RelayPin2, LOW);
      digitalWrite(RelayPin3, LOW);
      digitalWrite(RelayPin4, LOW);
      digitalWrite(RelayPin5, LOW);
      Serial.println("All ON");
    }
  else
  {
    digitalWrite(RelayPin1, HIGH);
      digitalWrite(RelayPin2, HIGH);
      digitalWrite(RelayPin3, HIGH);
      digitalWrite(RelayPin4, HIGH);
      digitalWrite(RelayPin5, HIGH);
    Serial.println("All OFF");
  }
}

void thirdLightChanged(uint8_t brightness)
{
  //Control the device 
  if (brightness == 255)
    {
      digitalWrite(RelayPin2, LOW);
      Serial.println("Light3 ON");
    }
  else
  {
    digitalWrite(RelayPin2, HIGH);
    Serial.println("Light3 OFF");
  }
}

void fourthLightChanged(uint8_t brightness)
{
  //Control the device  
  if (brightness == 255)
    {
      digitalWrite(RelayPin3, LOW);
      Serial.println("Light4 ON");
    }
  else
  {
    digitalWrite(RelayPin3, HIGH);
    Serial.println("Light4 OFF");
  }
}

void fifthLightChanged(uint8_t brightness)
{
  //Control the device 
  if (brightness == 255)
    {
      digitalWrite(RelayPin4, LOW);
      Serial.println("Light5 ON");
    }
  else
  {
    digitalWrite(RelayPin4, HIGH);
    Serial.println("Light5 OFF");
  }
}

void thirdFanChanged(uint8_t brightness)
{
  //Control the device 
  if (brightness == 255)
    {
      digitalWrite(RelayPin5, LOW);
      Serial.println("Fan3 ON");
    }
  else
  {
    digitalWrite(RelayPin5, HIGH);
    Serial.println("Fan3 OFF");
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
