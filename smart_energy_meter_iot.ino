/*
  WiFiEsp example: WebClient

  This sketch connects to google website using an ESP8266 module to
  perform a simple web search.

  For more details see: http://yaab-arduino.blogspot.com/p/wifiesp-example-client.html
*/

// http://sms.scubedigi.com/api.php?username=xxxx&password=xxxx&to=xxxxxxxxx&from=&message=xxxxxxxxxxxx
// http://projectsiot.xyz/IoTProjects/TollBooth/tollbooth.php?a=A&b=5&c=6&d=3
#include "WiFiEsp.h"
#include<String.h>
#include <LiquidCrystal.h>


// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif

LiquidCrystal lcd (2,3,4,5,6,7);

#define light1 8
#define light2 9
#define buzzer 10
#define ldrPin A0
#define ldr1Pin A1
#define ldr2Pin A2

unsigned int previous_status = 0;
unsigned int present_status = 0;
String charging_status = "\0";
char state = 'U';

int ldr = 0, ldr1 = 0, ldr2 = 0;
char light_status = '\0',light1_status = '\0',light2_status = '\0';

void beep ()
{
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(100);
}

char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";
char server1[] = "sms.scubedigi.com";

String A = "GET /IoTProjects/StreetLight/lightstore.php?a=";
String Z = " HTTP/1.1";
String msg = "GET /api.php?username=Mydreamacd&password=Mydre@m123&to=";
String bulk = "\0";
String iot = "\0";

// Initialize the Ethernet client object
WiFiEspClient client;

void setup()
{
  // initialize serial for debugging
  Serial.begin(9600);

  lcd.begin(16, 2);

pinMode(ldrPin,INPUT);
pinMode(ldr1Pin,INPUT);
pinMode(ldr2Pin,INPUT);
pinMode(buzzer,OUTPUT);
pinMode(light1,OUTPUT);
pinMode(light2,OUTPUT);

 lcd.clear();
lcd.setCursor(0,0);
lcd.print("     SMART     ");
lcd.setCursor(0,1);
lcd.print(" STREET LIGHTS ");
delay(2000);
  
   lcd.clear();
lcd.setCursor(0,0);
lcd.print("MONITORING SYSTEM");
lcd.setCursor(0,1);
lcd.print("  BASED ON IOT  ");
delay(2000);

  lcd.clear();
lcd.setCursor(0,0);
lcd.print(" CONNECTING  TO ");
lcd.setCursor(0,1);
lcd.print(ssid);
delay(200);

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

  lcd.clear();
lcd.setCursor(0,0);
lcd.print("Server Init.");
lcd.setCursor(0,1);
lcd.print("..................");
delay(100);
    Serial.println(F("sending data ---1 "));
    Serial.println(F("Starting connection to server..."));
    // if you get a connection, report back via serial
    if (client.connect(server, 80)) {
      Serial.println(F("Connected to server"));
      // Make a HTTP request
      client.println("GET /IoTProjects/StreetLight/lightstore.php?a=U&b=N&c=N HTTP/1.1");
      client.println("Host: projectsiot.xyz");
      client.println("Connection: close");
      client.println();
    }
    client.flush();
     client.stop();

    
    /*
    /////////////////////////////////////////
    ////////// initial message .......
    Serial.println(F("Starting connection to SMS server..."));
    delay(2000);

    // if you get a connection, report back via serial
    if (client.connect(server1, 80)) {
      Serial.println(F("Connected to server"));
      // Make a HTTP request
      client.println("GET /api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=KIT%20STARTED HTTP/1.1");
      client.println("Host: sms.scubedigi.com");
      client.println("Connection: close");
      client.println();
    }
    //client.flush();
    //  client.stop();

  */
  lcd.clear();
lcd.setCursor(0,0);
lcd.print("Server Init.");
lcd.setCursor(0,1);
lcd.print("Done");
  delay(5000);
Serial.println(F("PLEASE SHOW CARD "));
}

void loop()
{

ldr = analogRead(ldrPin);
delay(5);
Serial.print(F("ldr = ")); Serial.println(ldr);
if(ldr > 550)
{
light_status = 'B';
lcd.clear();
lcdstring(0,0,"   NIGHT MODE   ");
lcdstring(0,1,"   LIGHTS ON   ");
delay(2000);
digitalWrite(light1,HIGH);
delay(300);
digitalWrite(light2,HIGH);
  delay(300);
ldr1 = analogRead(ldr1Pin);
delay(50);
ldr2 = analogRead(ldr2Pin);
delay(50);
Serial.print(F("ldr1 = ")); Serial.println(ldr1);
Serial.print(F("ldr2 = ")); Serial.println(ldr2);
lcd.clear();
lcdstring(0,0,"   NIGHT MODE   ");
if(ldr1 < 300)
{
  light1_status = 'Y';
  lcdstring(0,1,"L1: ON");  
}
else
{  
  light1_status = 'N';
  lcdstring(0,1,"L1: OFF");
}
if(ldr2 < 300)
{
  light2_status = 'Y';
  lcdstring(8,1,"L2: ON");  
}
else
{  
  light2_status = 'N';
  lcdstring(8,1,"L2: OFF");
}
 iot = A + light_status + "&b=" + light1_status + "&c=" + light2_status + Z;

        Serial.println(iot);
        sndit ();
}// if night mode
else
{
light_status = 'A';
lcd.clear();
lcdstring(0,0,"    DAY MODE    ");
lcdstring(0,1,"   LIGHTS OFF   ");
delay(2000);
digitalWrite(light1,LOW);
delay(300);
digitalWrite(light2,LOW);
  delay(300);
ldr1 = analogRead(ldr1Pin);
delay(50);
ldr2 = analogRead(ldr2Pin);
delay(50);
Serial.print(F("ldr1 = ")); Serial.println(ldr1);
Serial.print(F("ldr2 = ")); Serial.println(ldr2);
lcd.clear();
lcdstring(0,0,"    DAY MODE    ");
if(ldr1 < 300)
{
  light1_status = 'Y';
  lcdstring(0,1,"L1: ON");  
}
else
{  
  light1_status = 'N';
  lcdstring(0,1,"L1: OFF");
}
if(ldr2 < 300)
{
  light2_status = 'Y';
  lcdstring(8,1,"L2: ON");  
}
else
{  
  light2_status = 'N';
  lcdstring(8,1,"L2: OFF");
}
 iot = A + light_status + "&b=" + light1_status + "&c=" + light2_status + Z;

        Serial.println(iot);
        sndit ();  
}


}// loop
  
void sndit ()
{

  Serial.print(F("IOT = ")); Serial.println(iot);

  // if the server's disconnected, stop the client
  if (!client.connected()) {
    Serial.println(F("Disconnecting from server..."));
    client.stop();

    // do nothing forevermore
    //while (true);
  }
  client.stop();
  client.flush();

  for (int x = 0; x < 1; x++)
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

}
 void lcdstring (unsigned int a, unsigned int b, String data)
 {
  lcd.setCursor(a,b);
  lcd.print(data);
 }
