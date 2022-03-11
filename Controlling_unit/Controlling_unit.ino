#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>                 
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>


#define FIREBASE_HOST "https://nodemcu-iot-a8e67.firebaseio.com/"   // the project name address from firebase id
#define FIREBASE_AUTH "qCdAFAdbQ4pK4ZJmOgW7nVy51LpQPJheX1WkMZBf"       // the secret key generated from firebase
const char* ssid = "Default_SSID";
const char* passphrase = "Default_Password";


#define motorpin 5    // Connect D1(GPIO5)
#define motorpin2 4    // Connect D1(GPIO5)
int led =4;     // Connect LED to D5



//Define FirebaseESP8266 data object
FirebaseData motorData;
//
FirebaseJson json;

const unsigned long SECOND = 1000;
const unsigned long HOUR = 3600*SECOND;


int statusCode;
String st;
String content;
int i = 0;
String node_id="1001";
float motorvalue;
float motorvalue2;
float motordelay;
float fertilizerdelay;


//Function Decalration
bool testWifi(void);
void launchWeb(void);
void setupAP(void);
//Establishing Local server at port 80 whenever required
ESP8266WebServer server(80);
void setup()
{
//assign relay pin as output
pinMode(motorpin,OUTPUT);

 Serial.begin(115200); //Initialising if(DEBUG)Serial Monitor
  Serial.println();
  Serial.println("Disconnecting current wifi connection");
  WiFi.disconnect();
  EEPROM.begin(512); //Initialasing EEPROM
  delay(10);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println();
  Serial.println();
  Serial.println("Startup");
  //---------------------------------------- Read eeprom for ssid and pass
  Serial.println("Reading EEPROM ssid");
  String esid;
  for (int i = 0; i < 32; ++i)
  {
    esid += char(EEPROM.read(i));
  }
  Serial.println();
  Serial.print("SSID: ");
  Serial.println(esid);
  Serial.println("Reading EEPROM pass");
  String epass = "";
  for (int i = 32; i < 96; ++i)
  {
    epass += char(EEPROM.read(i));
  }
  Serial.print("PASS: ");
  Serial.println(epass);
  WiFi.begin(esid.c_str(), epass.c_str());
  // connect the firebase

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  
  if (testWifi())
  {
  Serial.println("Succesfully Connected!!!");
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
    return;
  }
  else
  {
    Serial.println("Turning the HotSpot On");
    launchWeb();
    setupAP();// Setup HotSpot
  }
  Serial.println();
  Serial.println("Waiting.");
  while ((WiFi.status() != WL_CONNECTED))
  {
    Serial.print(".");
    delay(100);
    server.handleClient();
  }

}

  void loop() {
   fetctfirebase();
   delay(30000);

}
