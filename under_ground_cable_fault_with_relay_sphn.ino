#include<stdlib.h>

/////////////////////////////
#include "WiFiEsp.h"
#include<String.h>
#ifndef HAVE_HWSERIAL1
#include <SoftwareSerial.h>
SoftwareSerial Serial1(12, 13); // RX, TX
#endif

char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";

String A = "GET /IoTProjects/Cablefault/fault.php?a=";
//http://projectsiot.xyz/
String B = "&b=";
String C = "&c=";
String D = "&d=";
String Z = " HTTP/1.1";
String iot = "\0";
WiFiEspClient client;
//////////////////////////////////////////////
*/

#include<stdlib.h>

/////////////////////////////
#include "WiFiEsp.h"
#include<String.h>
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif

char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
//char ssid[] = "AMBEST Technologies";            // your network SSID (name)
//char pass[] = "AmBeSt@@321";        // your network password


int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";

String A = "GET /IoTProjects/CableFault/fault.php?a=";
//http://projectsiot.xyz/
String B = "&b=";
String C = "&c=";
String D = "&d=";
String Z = " HTTP/1.1";
String iot = "\0";
WiFiEspClient client;
//////////////////////////////////////////////

int r=0,y=0,b=0;
#include<LiquidCrystal.h>

#define cable1 A0
#define cable2 A1
#define cable3 A2
#define buzzer 11

#define relay 10
#define gled A4
#define rled A5

LiquidCrystal lcd (2,3,4,5,6,7);

int cab1=0;
int cab2=0;
int cab3=0;

int b1;
int b2;
int b3;
int b4;
int b5;

void beep()
{
   digitalWrite(buzzer, HIGH); 
   delay(1000);
    digitalWrite(buzzer, LOW); 
    delay(100);
}
void beep2()
{
   digitalWrite(buzzer, HIGH); 
   delay(300);
    digitalWrite(buzzer, LOW); 
    delay(100);
   digitalWrite(buzzer, HIGH); 
   delay(300);
    digitalWrite(buzzer, LOW); 
    delay(100);
}

void setup() {
  // put your setup code here, to run once:
   pinMode(cable1, INPUT);
   pinMode(cable2, INPUT);
   pinMode(cable3, INPUT);

pinMode(rled,OUTPUT);
pinMode(gled,OUTPUT);

pinMode(relay,OUTPUT);
pinMode (buzzer,OUTPUT);

  lcd.begin (16,2);
  
 lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("UDERGROUND CABLE");
        lcd.setCursor(0,1);
         lcd.print(" FAULT LOCATOR ");
         delay(2000);
  digitalWrite(relay,LOW);
   
Serial.begin(9600);
  Serial.println("WELCOME");
  Serial.println(" ................ ");
Serial.println("WFI SETUP BEGINS");
    Serial.println("...............");

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
      client.println("GET /IoTProjects/CableFault/fault.php?a=U&b=0 HTTP/1.1");
      client.println("Host: projectsiot.xyz");
      client.println("Connection: close");
      client.println();
    }
    client.flush();
     client.stop();
     
delay(2000);
     
        iot = A +'U' + B+'0' +C+'0' + Z;
        sndit ();
delay(2000);
//  */
  Serial.println("IOT BASED UNDERGROUND CABLE FAULT DETECTION \n");


         beep();

 lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("UDERGROUND CABLE");
        lcd.setCursor(0,1);
         lcd.print(" FAULT LOCATOR ");
         delay(2000);
          lcd.clear();
        //  beep();
}

////////////////////////////
void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  cab1 = analogRead(cable1);
    cab2 = analogRead(cable2);
      cab3 = analogRead(cable3);
Serial.println("========================START===================================");
Serial.print("R CABLE:");Serial.print("\t");Serial.println(cab1);
Serial.print("Y CABLE:");Serial.print("\t");Serial.println(cab2);
Serial.print("B CABLE:");Serial.print("\t");Serial.println(cab3);
Serial.println("==========================END=================================");
 cab1 = map(cab1, 500, 1023, 0, 100);
 cab2 = map(cab2, 500, 1023, 0, 100);
 cab3 = map(cab3, 500, 1023, 0, 100);

Serial.println("cab1 = "+String(cab1));

if (cab1 > 5)
{
  Serial.println("cable fault at"+String(cab1));
  digitalWrite(rled,HIGH);
    digitalWrite(gled,LOW);
    digitalWrite(relay,LOW);
    delay(200);
  lcd.clear ();
   lcd.setCursor (0,0);
lcd.print ("CABLE FAULT AT   ");
lcd.setCursor (0,1);
lcd.print(cab1);
lcd.print("KM");
 
beep();
iot = A +cab1 + Z;
sndit ();

}
else
{
   lcd.clear ();
   lcd.setCursor (0,0);
lcd.print ("NO FAULT      ");
lcd.setCursor (0,1);
lcd.print ("                       ");
digitalWrite(rled,LOW);
    digitalWrite(gled,HIGH);
    digitalWrite(relay,HIGH);
    delay(200);

}

}//LOOP


///////////////////////////////////////////
void sndit ()
{

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
    
    client.println(iot);

    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
    iot = "\0";
  }

}

///////////////////////////////////////////////
