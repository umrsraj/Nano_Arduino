/*
  WiFiEsp example: WebClient

  This sketch connects to google website using an ESP8266 module to
  perform a simple web search.

  For more details see: http://yaab-arduino.blogspot.com/p/wifiesp-example-client.html
*/

#include "WiFiEsp.h"
#include<String.h>
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif
char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password

//char ssid[] = "project12";            // your network SSID (name)
//char pass[] = "project123456";        // your network password

int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";
char server1[] = "sms.scubedigi.com";

String A = "GET /IoTProjects/AirPollution/upload.php?a=";
String Z = " HTTP/1.1";
String msg = "GET /api.php?username=Mydreamacd&password=Mydream123&to=";
String iot = "\0";
String bulk = "\0";

// Initialize the Ethernet client object
WiFiEspClient client;

#include<String.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd (2,3,4,5,6,7);

#define voltage_sensor A0
#define alc_sensor A1
#define relay 8
#define buzzer 9
#define rled 10
#define gled 11

unsigned int previous_status = 0;
unsigned int present_status = 0;
unsigned int vol = 0;
float voltage = 0.0;
String charging_status = "\0";
char state = 'U';
int alc =0;

char sound = 'N';
char gas = 'N';
void sndit (void);
void beep ()
{
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(100);
}
void lcdstring (unsigned int a, unsigned int b, String data)
{
  // lcd.clear();
  lcd.setCursor(a, b);
  lcd.print(data);
}

void setup()
{
  // initialize serial for debugging
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.clear();
  lcdstring(0,0," AIR POLLUTION   ");
  lcdstring(0,1,"   SYSTEM        ");
  delay(2000);
/*
  lcd.clear();
  lcdstring(0,0,"GENERATION  WITH");
  lcdstring(0,1,"MOBILE  CHARGING");
  delay(1500);
*/
pinMode(relay,OUTPUT);

pinMode(buzzer,OUTPUT);
pinMode(gled,OUTPUT);
pinMode(rled,OUTPUT);
pinMode(voltage_sensor,INPUT);
pinMode(alc_sensor,INPUT);


  digitalWrite(rled, LOW);
  digitalWrite(gled, LOW);

  // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println(F("WiFi shield not present"));
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print(F("Attempting to connect to WPA SSID: "));
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  // you're connected now, so print out the data
  Serial.println(F("You're connected to the network"));

  
    Serial.println(F("sending data ---1 "));
    Serial.println(F("Starting connection to server..."));
    // if you get a connection, report back via serial
    if (client.connect(server, 80)) {
      Serial.println(F("Connected to server"));
      // Make a HTTP request
      client.println("GET /IoTProjects/AirPollution/upload.php?a=U&b=0 HTTP/1.1");
      client.println("Host: projectsiot.xyz");
      client.println("Connection: close");
      client.println();
    }
    client.flush();
     client.stop();
    
    /////////////////////////////////////////
 
Serial.println(F("PLEASE SHOW CARD "));
}

void loop()
{
 vol = analogRead(voltage_sensor);
delay(50);
Serial.print("sensor value = "); Serial.println(vol);
//alc = analogRead(alc_sensor);
//delay(50);
//Serial.print("alc value = "); Serial.println(alc);

//voltage = vol * (5.00/1023.00)*5;

//Serial.print("voltage = "); Serial.println(voltage);

if(vol >750)
{
  digitalWrite(gled,LOW);
  digitalWrite(rled,HIGH);
  
  present_status = 100;
  digitalWrite(relay,LOW);
  lcd.clear ();
  lcdstring(0,0,"  AIR :POLLUTED");
 // lcdstring(0,1," CHARGING -- OFF");
charging_status = "OFF";
 sound = 'Y';
  beep (); 
  iot = A + sound  + Z;

        Serial.println(iot);
        sndit ();

        delay(3000);
 
}
else
{
  digitalWrite(gled,HIGH);
  digitalWrite(rled,LOW);
  
  present_status = 10;
    digitalWrite(relay,HIGH);
 sound = 'N';
  lcd.clear ();
  lcdstring(0,0,"  AIR :NORMAL");
 /* lcd.setCursor(0,10);
  lcd.print(voltage);
  lcdstring(0,1," CHARGING -- ON ");
  charging_status = "ON";
*/
  iot = A + sound  + Z;

        Serial.println(iot);
        sndit ();

        delay(30);

}
/*
if(alc >900)
{
  digitalWrite(gled,LOW);
  digitalWrite(rled,HIGH);
  
  present_status = 100;
  digitalWrite(relay,LOW);
 // lcd.clear ();
 //lcdstring(0,0,"gas="+String(alc));
  lcdstring(0,1,"GAS  ALERT");
charging_status = "OFF";
gas = 'Y';
  beep ();
  delay(1000);  
}
else
{
  digitalWrite(gled,HIGH);
  digitalWrite(rled,LOW);
  
  present_status = 10;
    digitalWrite(relay,HIGH);
 gas = 'N';
 // lcd.clear ();
  //lcdstring(0,0,"SOUND :NORMAL");
   lcdstring(0,1,"GAS :NORMAL");
 /* lcd.setCursor(0,10);
  lcd.print(voltage);
  lcdstring(0,1," CHARGING -- ON ");
  charging_status = "ON";
*/
//}


     
  
}// loop
  
void sndit ()
{

Serial.println();
Serial.println();
Serial.println();
  Serial.print(F("A = ")); Serial.println(iot);

  // if the server's disconnected, stop the client
  if (!client.connected()) {
    Serial.println(F("Disconnecting from server..."));
    client.stop();

    // do nothing forevermore
    //while (true);
  }
  client.stop();
  client.flush();

  for (int x = 0; x < 2; x++)
  {
    delay(1000);
    Serial.println(x, DEC);
  }
  Serial.println(F("Starting connection to server..."));
  // if you get a connection, report back via serial
  if (client.connect(server, 80)) {
    Serial.println(F("Connected to server"));
    // Make a HTTP request

    //client.println("GET /IoTProjects/TollBooth/tollbooth.php?a=A&b=5&c=6&d=3 HTTP/1.1");

    client.println(iot);

    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
    iot = "\0";
  }
Serial.println();
Serial.println();
Serial.println();
}//sndit
