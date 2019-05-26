/*
 WiFiEsp example: WebClient

 This sketch connects to google website using an ESP8266 module to
 perform a simple web search.

 For more details see: http://yaab-arduino.blogspot.com/p/wifiesp-example-client.html
*/
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

#define slot1Pin A0
#define slot2Pin A1
#define slot3Pin A2
#define slot4Pin A3


#define m11 8
#define m12 9
#define buzzer 10
#define gled A4
#define rled A5
 String S1 = "N";
String S2 = "N";
String S3 = "N";
String S4 = "N";

void lcdstring (int a, int b, String w);
int s1 = 0;
int s2 = 0;
int s3 = 0;
int s4 = 0;

unsigned int P1 = 0;
unsigned int P2 = 0;
unsigned int P3 = 0;
unsigned int P4 = 0;

String slot1 = "0";
String slot2 = "0";
String slot3 = "0";
String slot4 = "0";

int count1 = 0;                                          // count = 0
char input[12];

void beep ()
{
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(100);
}

void forward () 
{
  digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);
}
void backward () 
{
  digitalWrite(m12,HIGH);
  digitalWrite(m11,LOW);
}
void stopp () 
{
  digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
}
char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";
String A = "GET /IoTProjects/CarParking/upload.php?a=";
String Z = " HTTP/1.1";
String str;

// Initialize the Ethernet client object
WiFiEspClient client;

void setup()
{
  // initialize serial for debugging
  Serial.begin(9600);
  lcd.begin(16,2);
lcd.clear();  
   lcd.setCursor(0,0);
    lcd.print(" RFID BASED CAR ");
     
  lcd.setCursor(0,1);
    lcd.print(" PARKING SLOTS  ");
    delay(2000);

         pinMode(buzzer,OUTPUT);
 pinMode(m11,OUTPUT);
 pinMode(m12,OUTPUT);
 pinMode(gled,OUTPUT);
 pinMode(rled,OUTPUT);
 pinMode(slot1Pin,INPUT);
 pinMode(slot2Pin,INPUT);
 pinMode(slot3Pin,INPUT);
 pinMode(slot4Pin,INPUT);

 digitalWrite(rled,LOW);
digitalWrite(gled,LOW);
  
  // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  // you're connected now, so print out the data
  Serial.println("You're connected to the network");
  
Serial.println("sending data ---1 ");
  Serial.println();
  Serial.println("Starting connection to server...");
  // if you get a connection, report back via serial
  if (client.connect(server, 80)) {
    Serial.println("Connected to server");
    // Make a HTTP request
    client.println("GET /IoTProjects/CarParking/upload.php?a=U&b=0&c=0&d=0 HTTP/1.1");
    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
  }
}

void loop()
{

s1 = analogRead(slot1Pin);
s2 = analogRead(slot2Pin);
s3 = analogRead(slot3Pin);
s4 = analogRead(slot4Pin);

Serial.print("ldr1 = "); Serial.println(s1);
Serial.print("ldr2 = "); Serial.println(s2);
Serial.print("ldr3 = "); Serial.println(s3);
Serial.print("ldr4 = "); Serial.println(s4);

lcd.setCursor(0,1);
    lcd.print("                     ");

if (s1>970)
{
  P1 = 1;
  S1 = "Y";
}
else 
{
  P1 = 0;
  S1 = "N";
}
if (s2>970)
{
  P2 = 1;
  S2 = "Y";
}
else 
{
  P2 = 0;
  S2 = "N";
}
if (s3>970)
{
  P3 = 1;
  S3 = "Y";
}
else 
{
  P3 = 0;
  S3 = "N";
}
if (s4>900)
{
  P4 = 1;
  S4 = "Y";
}
else 
{
  P4 = 0;
  S4 = "N";
}

lcd.setCursor(0,0);
    lcd.print("plz show card         ");
lcdstring(0,1,"S1:"+String(P1)+"S2:"+String(P2)+"S3:"+String(P3)+"S4:"+String(P4));
if(Serial.available())
   {
      count1 = 0;
      while(Serial.available() && count1 < 12)          // Read 12 characters and store them in input array
      {
         input[count1] = Serial.read();
         count1++;
         delay(5);
      }//WHILE
//

 Serial.println(input);                           // Print RFID tag number 
   Serial.print("input[10] is "); Serial.println(input[10]);

if (input[10]=='1')
{
Serial.println("1st vehicle detected");
  if((P1==0)||(P2==0)||(P3==0)||(P4==0))
  {
    Serial.println("gate opening...........");
    
    lcdstring(0,0,"GATE OPENING............");
    forward ();
    delay(2000);
    lcdstring(0,0,"GATE - OPEN           ");
    stopp ();
    delay(5000);
     lcdstring(0,0,"GATE CLOSING............");
    backward ();
    delay(2000);
    stopp ();
    lcdstring(0,0,"GATE - CLOSE           ");
    delay(300);
  }
  else
  {
    
    lcdstring(0,0,"ALL SLOTS FULL       ");
  }
}
else if (input[10]=='9')
{
Serial.println("2nd vehicle detected");
  if((P1==0)||(P2==0)||(P3==0)||(P4==0))
  {
    Serial.println("gate opening...........");
    
    lcdstring(0,0,"GATE OPENING............");
    forward ();
    delay(2000);
    lcdstring(0,0,"GATE - OPEN           ");
    stopp ();
    delay(5000);
     lcdstring(0,0,"GATE CLOSING............");
    backward ();
    delay(2000);
    stopp ();
    lcdstring(0,0,"GATE - CLOSE           ");
    delay(300);
    
  }
  else
  {
    
    lcdstring(0,0,"ALL SLOTS FULL       ");
    delay(2000);
    lcdstring(0,0,"                       ");
  }
}
else
{
 
    lcdstring(0,0,"INVALID CARD...............      ");
    beep ();     
    delay(2000);
    lcdstring(0,0,"                       ");
}
  

}
  str  = A  +S1 + "&b=" + S2 +"&c=" + S3 + "&d=" + S4 + Z;
  sndit ();
}
void sndit ()
{

Serial.print("str = "); Serial.println(A +S1 + "&b=" + S2 +"&c=" + S3 + "&d=" + S4 + Z);
Serial.println();
  // if the server's disconnected, stop the client
  if (!client.connected()) {
    Serial.println();
    Serial.println("Disconnecting from server...");
    client.stop();

    // do nothing forevermore
    //while (true);
  }
  client.flush();
   client.stop();
for(int x = 0; x<2; x++)
{
  delay(1000);
  Serial.println(x);
}
    Serial.println();
  Serial.println("Starting connection to server...");
  // if you get a connection, report back via serial
  if (client.connect(server, 80)) {
    Serial.println("Connected to server");
    // Make a HTTP request
    
    //client.println("GET /IoTProjects/TollBooth/tollbooth.php?a=A&b=5&c=6&d=3 HTTP/1.1");
   
  client.println(A + S1 + "&b=" + S2 +"&c=" + S3 + "&d=" + S4 + Z);
    
    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
    
}
  
}

void lcdstring (int a, int b, String w)
{
  lcd.setCursor(a,b);
  lcd.print(w);
}
