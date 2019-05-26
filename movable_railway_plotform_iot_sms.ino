/*
  WiFiEsp example: WebClient

  This sketch connects to google website using an ESP8266 module to
  perform a simple web search.

  For more details see: http://yaab-arduino.blogspot.com/p/wifiesp-example-client.html
*/
//http://projectsiot.xyz/IoTProjects/MovableRailway/pfupload.php?a=U
// http://projectsiot.xyz/IoTProjects/MovableRailway/pfstatus.php

#include "WiFiEsp.h"
#include<String.h>
#include <LiquidCrystal.h>


// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif

LiquidCrystal lcd (2,3,4,5,6,7);

#define ir1_sensor A0
#define ir2_sensor A1
#define m11 8 
#define m12 9
#define buzzer 10
#define rled A2
#define gled A3

unsigned int previous_status = 0;
unsigned int present_status = 0;
unsigned int ir1 = 0;
unsigned int ir2 = 0;
unsigned int flag = 0;
void forward ()
{
  digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);
  delay(50);
}
void backward ()
{
  digitalWrite(m11,LOW);
  digitalWrite(m12,HIGH);
  delay(50);
}
void stop_motor ()
{
   digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
  delay(50); 
}

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

String A = "GET /IoTProjects/MovableRailway/pfupload.php?a=";
String Z = " HTTP/1.1";
String msg = "GET /api.php?username=Mydreamacd&password=Mydre@m123&to=";
// "GET /api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=WELCOME%20MESSAGE HTTP/1.1"
String iot = "\0";
String bulk = "\0";



// 9652490222&from=MYDREM&message=person1%20detected"

// Initialize the Ethernet client object
WiFiEspClient client;

void setup()
{
  // initialize serial for debugging
  Serial.begin(9600);

  lcd.begin(16, 2);

  
lcd.clear ();
lcd.setCursor (0,0);
lcd.print ("   WELCOME TO   ");
lcd.setCursor (0,1);
lcd.print ("AUTOMATIC MOVABLE");
delay (1500);

lcd.clear ();
lcd.setCursor (0,0);
lcd.print ("RAILWAY PLATFORM");
lcd.setCursor (0,1);
lcd.print ("    WITH IoT    ");
delay(2000);

lcd.clear ();
lcd.setCursor (0,0);
lcd.print (" CONNECTING  TO ");
lcd.setCursor (0,1);
lcd.print ("    WI - FI     ");
delay(1000);

pinMode(ir1_sensor,INPUT);
pinMode(ir2_sensor,INPUT);
pinMode(buzzer,OUTPUT);
pinMode(rled,OUTPUT);
pinMode(gled,OUTPUT);
pinMode(m11,OUTPUT);
pinMode(m12,OUTPUT);

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
      client.println("GET /IoTProjects/MovableRailway/pfupload.php?a=U HTTP/1.1");
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

lcd.clear ();
lcd.setCursor (0,0);
lcd.print ("   WELCOME TO   ");
lcd.setCursor (0,1);
lcd.print ("AUTOMATIC MOVABLE");
delay (1500);

lcd.clear ();
lcd.setCursor (0,0);
lcd.print ("RAILWAY PLATFORM");
lcd.setCursor (0,1);
lcd.print ("    WITH IoT    ");
delay(200);
  
Serial.println(F("PLEASE SHOW CARD "));
}

void loop()
{
 

  ir1 = analogRead (ir1_sensor);
   ir2 = analogRead (ir2_sensor);
Serial.print(F("ir1 = ")); Serial.println(ir1);
Serial.print(F("ir2 = ")); Serial.println(ir2);   
delay(50);

if ((ir1>600)&&(flag==0))
{
flag = 1;

 lcd.clear ();
lcd.setCursor (0,0);
lcd.print ("PLATFOR  OPENING");
lcd.setCursor (0,1);
lcd.print ("*****************");
delay (500);
/*
//*************  0 - BALANCE **********************
 
  // if the server's disconnected, stop the client
  if (!client.connected()) {
    Serial.println(F("Disconnecting from server..."));
    client.stop();

    // do nothing forevermore
    //while (true);
  }
  
   client.stop();
  client.flush();
for(int x = 0; x<2; x++)
{
  delay(1000);
  Serial.println(x,DEC);
}
    Serial.println(F("Starting connection to server..."));
  // if you get a connection, report back via serial
  if (client.connect(server1, 80)) {
    Serial.println(F("Connected to server"));
    // Make a HTTP request
    
 // Serial.print(F("q == ")); Serial.println(q);
    client.println(msg+"9652490222"+"&from=MYDREM&message="+"PLATFORM%20IS%20OPEN"+Z);
    
    client.println("Host: sms.scubedigi.com");
    client.println("Connection: close");
    client.println();
    
  }
// *****************************************
        delay(2000);
*/
        // str = A+"A"+B+"0"+C+String(amount)+D+"N"+Z;
        iot = A + 'Y' + Z;

        Serial.println(iot);
        sndit ();

        delay(1000);
forward ();
delay(2000);
stop_motor ();
delay(600);

 lcd.clear ();
lcd.setCursor (0,0);
lcd.print (" PLATFOR OPENED ");
lcd.setCursor (0,1);
lcd.print ("*****************");
delay (500);
  
}
else if ((ir2>600)&&(flag==1))
{
flag = 0;

 lcd.clear ();
lcd.setCursor (0,0);
lcd.print ("PLATFOR  CLOSING ");
lcd.setCursor (0,1);
lcd.print ("*****************");
delay (500);
/*
//*************  0 - BALANCE **********************
 
  // if the server's disconnected, stop the client
  if (!client.connected()) {
    Serial.println(F("Disconnecting from server..."));
    client.stop();

    // do nothing forevermore
    //while (true);
  }
  
   client.stop();
  client.flush();
for(int x = 0; x<2; x++)
{
  delay(1000);
  Serial.println(x,DEC);
}
    Serial.println(F("Starting connection to server..."));
  // if you get a connection, report back via serial
  if (client.connect(server1, 80)) {
    Serial.println(F("Connected to server"));
    // Make a HTTP request
    
 // Serial.print(F("q == ")); Serial.println(q);
    client.println(msg+"9652490222"+"&from=MYDREM&message="+"PLATFORM%20IS%20CLOSE"+Z);
    
    client.println("Host: sms.scubedigi.com");
    client.println("Connection: close");
    client.println();
    
  }
// *****************************************
        delay(2000);
*/
        // str = A+"A"+B+"0"+C+String(amount)+D+"N"+Z;
        iot = A + 'N' + Z;

        Serial.println(iot);
        sndit ();

        delay(1000);
backward ();
delay(2000);
stop_motor ();
delay(600);

 lcd.clear ();
lcd.setCursor (0,0);
lcd.print (" PLATFOR CLOSED ");
lcd.setCursor (0,1);
lcd.print ("*****************");
delay (500);
  
}



}// loop
  
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
    // Make a HTTP request

    //client.println("GET /IoTProjects/TollBooth/tollbooth.php?a=A&b=5&c=6&d=3 HTTP/1.1");

    client.println(iot);

    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
    iot = "\0";
  }

}
