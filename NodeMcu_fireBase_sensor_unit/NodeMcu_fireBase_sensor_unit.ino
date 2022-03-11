#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>                 
#include "DHT.h" 
#include <Wire.h>// Install DHT11 Library and Adafruit Unified Sensor Library
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

//for NTP time
#include <NTPClient.h>
#include <WiFiUdp.h>
//end

#include <SoftwareSerial.h>
//#include <FirebaseArduino.h>
#include <ArduinoJson.h>


#define FIREBASE_HOST "https://nodemcu-iot-a8e67.firebaseio.com/"   // the project name address from firebase id
#define FIREBASE_AUTH "qCdAFAdbQ4pK4ZJmOgW7nVy51LpQPJheX1WkMZBf"       // the secret key generated from firebase
const char* ssid = "Default_SSID";
const char* passphrase = "Default_Password";
#define DHTTYPE    DHT11

#define DHTPIN 14    // Connect Data pin of DHT to D2
int led =5;     // Connect LED to D5

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
//end

DHT dht(DHTPIN, DHTTYPE);

//Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseData firebaseDataLive;
FirebaseData motorData;
//
FirebaseJson json;

const unsigned long SECOND = 1000;
const unsigned long HOUR = 3600*SECOND;

float h;
float t;
int statusCode;
String st;
String content;
int i = 0;
int motor_value=0;
String solar_status="";
float light_presentage;
String node_id="1001";
String date_time;

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/////////////*/
// analog multiplexer 

    /* 0- General */

    #define S0 D0                             /* Assign Multiplexer pin S0 connect to pin D0 of NodeMCU */
    #define S1 D1                             /* Assign Multiplexer pin S1 connect to pin D1 of NodeMCU */
    #define S2 D2                             /* Assign Multiplexer pin S2 connect to pin D2 of NodeMCU */
    #define S3 D3                             /* Assign Multiplexer pin S3 connect to pin D3 of NodeMCU */
    #define SIG A0                            /* Assign SIG pin as Analog output for all 16 channels of Multiplexer to pin A0 of NodeMCU */

    int decimal = 2;                          // Decimal places of the sensor value outputs 
    float sensor0;                            /* Assign the name "sensor0" as analog output value from Channel C0 */
    float sensor1;                            /* Assign the name "sensor1" as analog output value from Channel C1 */
    float sensor2;                            /* Assign the name "sensor2" as analog output value from Channel C2 */
  // end analog multiplexer 
   
//battery meter
float vin = 0.0;
float vOUT = 0.0;
float R1 = 30000.0; //  
float R2 = 7500.0; //
int offset =20;
//end battery meter

float moisture_percentage;


//Function Decalration
bool testWifi(void);
void launchWeb(void);
void setupAP(void);
//Establishing Local server at port 80 whenever required
ESP8266WebServer server(80);
void setup()
{
// analog multiplex
    pinMode(S0,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin SO */        
    pinMode(S1,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S1 */  
    pinMode(S2,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S2 */ 
    pinMode(S3,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S3 */  
    pinMode(SIG, INPUT);                      /* Define analog signal pin as input or receiver from the Multiplexer pin SIG */  

//end analog multiplex

// Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
//  GMT +5.5 = 19800
  // GMT 0 = 0
  timeClient.setTimeOffset(19800);

  //Week Days
//String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//Month names
//String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
  //end

  
//dht sensor start
dht.begin();

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
   analog_signal_read();
   dht_sensor_read();
   //control_water(); 
   check_light(sensor1);
   sensorUpdate();
   date_time_update();
   keep_record_firebase();
   //fetctfirebase();
   delay(30000);

}

void dht_sensor_read(){
  
    float h = dht.readHumidity();
    float t = dht.readTemperature();         
//    Serial.print("Current humidity = ");
//    Serial.print(h);
//    Serial.print("%  ");
//    Serial.print("temperature = ");
//    Serial.print(t); 
//    Serial.println("C  ");
   // delay(1000);
  }


 void date_time_update(){
  
timeClient.update();

  unsigned long epochTime = timeClient.getEpochTime();
  Serial.print("Epoch Time: ");
  Serial.println(epochTime);

//Get a time structure
  struct tm *ptm = gmtime ((time_t *)&epochTime); 

  int monthDay = ptm->tm_mday;
  Serial.print("Month day: ");
  Serial.println(monthDay);

  int currentMonth = ptm->tm_mon+1;
  Serial.print("Month: ");
  Serial.println(currentMonth);


  int currentYear = ptm->tm_year+1900;
  Serial.print("Year: ");
  Serial.println(currentYear);

 String formattedTime = timeClient.getFormattedTime();
  Serial.print("Formatted Time: ");
  Serial.println(formattedTime);
  
      //Print complete date time:
  date_time = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay)+"_" + String(formattedTime);
  Serial.print("Current date: ");
  Serial.println(date_time);
  Serial.println("");

  }
