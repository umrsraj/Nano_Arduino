
#include "WiFiEsp.h"
#include<String.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd (A0,A1,A2,A3,A4,A5);

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif


#define ct1Pin A0
#define ct2Pin A1
#define ct3Pin A2
#define ct4Pin A3
#define relay 11
#define buzzer 9
#define theft 10
#define magnet 8

int ct1 = 0, ct2 = 0;
float ct3 = 0, ct4 = 0;
int difference = 0;
volatile int units = 0;
volatile int cost = 0;
volatile int preunits = 0;
volatile int punits = 0;
volatile int pulses = 0;
volatile int bal = 50;

String consumer = "0";
int flag = 0;
String tamper = "N";
String mag = "N";
String bypass = "N";
int interruptPin = 2;

int lightflag = 1;

void beep ()
{
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(100);
}
void beep1 ()
{
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(100);
}
char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";
String A = "GET /IoTProjects/Meter/upload.php?a=";
String Z = " HTTP/1.1";
String iot = "\0";
WiFiEspClient client;



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

Serial.println("power up");
pinMode(ct1Pin,INPUT);
pinMode(ct2Pin,INPUT);
pinMode(ct3Pin,INPUT);
pinMode(ct4Pin,INPUT);
pinMode(2,INPUT);
pinMode(theft,INPUT);
pinMode(magnet,INPUT);
pinMode(buzzer,OUTPUT);
pinMode(relay,OUTPUT);



lcd.begin(16,2);

lcd.clear ();
lcd.setCursor(0,0);
lcd.print("     SMART      ");
lcd.setCursor(0,1);
lcd.print("  ENERGY METER  ");
delay(3000);

attachInterrupt(digitalPinToInterrupt(interruptPin),pinisr,FALLING);

  Serial1.begin(9600);

 Serial1.listen (); delay(1000);
 
   // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println(F("WiFi shield not present"));
    // don't continue
    //while (true);
  }
lcd.clear ();
lcd.setCursor(0,0);
lcd.print("CONNECTION TO");
lcd.setCursor(0,1);
lcd.print(ssid);
delay(300);
  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print(F("Attempting to connect to WPA SSID: "));
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }
lcd.clear ();
lcd.setCursor(0,0);
lcd.print("CONNECTED TO");
lcd.setCursor(0,1);
lcd.print("WI - FI ");
delay(2000);
  // you're connected now, so print out the data
  Serial.println(F("You're connected to the network"));

lcd.clear ();
lcd.setCursor(0,0);
lcd.print("server init.   ");
lcd.setCursor(0,1);
lcd.print("please wait    ");
delay(2000);
  
    Serial.println(F("sending data ---1 "));
    Serial.println(F("Starting connection to server..."));
    // if you get a connection, report back via serial
    if (client.connect(server, 80)) {
      Serial.println(F("Connected to server"));
      // Make a HTTP request
      client.println("GET /IoTProjects/Meter/upload.php?a=U HTTP/1.1");
      client.println("Host: projectsiot.xyz");
      client.println("Connection: close");
      client.println();
    }
    client.flush();
     client.stop();
delay(2000);
digitalWrite(relay,HIGH);
beep ();
delay(4000);

lcd.clear ();
lcd.setCursor(0,0);
lcd.print("server init.   ");
lcd.setCursor(0,1);
lcd.print("done             ");
delay(4000);


 Serial1.listen (); delay(1000);

units = 0;
cost = 0;

bal = 50;
}

void loop() {
  // put your main code here, to run repeatedly:

  tamper = "N";

if (digitalRead(theft)==HIGH)
{
  Serial.println("tampering alert....");
  flag =0;
  tamper = "Y";
  digitalWrite(relay,LOW);
  delay(200);
  beep ();
  lcd.clear ();
lcd.setCursor(0,0);
lcd.print("TAMPERING ALERT   ");
lcd.setCursor(0,1);
lcd.print("PLEASE CHECK      ");

 Serial.println("updating to iot");
   iot = A + String(units) + "&b=" + String(bal) + "&c=" + tamper + Z;

        Serial.println(iot);
        sndit ();

delay(4000);
lcd.clear();
 
}
else
{
  if(bal>1)
  {
    digitalWrite(relay,HIGH);
  }
  else if (units > 9)
  {
        digitalWrite(relay,LOW);
    Serial.println("load off");
    
units = 10;
cost = 50;

bal = 0;
   Serial.println("updating to iot");
   iot = A + String(units) + "&b=" + String(bal) + "&c=" + tamper + Z;

        Serial.println(iot);
        sndit ();
  }
}
if (!(punits == preunits))
{
  
  tamper = "N";
  preunits = punits;
  flag = 0;
   Serial.println("updating to iot");
   iot = A + String(units) + "&b=" + String(bal) + "&c=" + tamper + Z;

        Serial.println(iot);
        sndit ();
}

lcd.setCursor(0,0);
lcd.print("                      ");
lcd.setCursor(0,1);
lcd.print("                       ");

lcd.setCursor(0,0);
lcd.print("Units:"+String(units));
lcd.setCursor(9,0);
lcd.print("Cost:"+String(cost));
lcd.setCursor(0,1);
lcd.print("Rbal:"+String(bal));
lcd.setCursor(9,1);
lcd.print("Tamp:"+String(tamper));
delay(200);

}//loop

void pinisr ()
{
  
  Serial.println("interrupttttttttttt");
  units++;
  punits = units; 
  cost = units*5;
  bal = bal - 5 ;
 // units = int(pulses/20);
  Serial.println("units = "+String(units));
 Serial.println("cost ="+String(cost));
  Serial.println("bal = "+String(bal));

  if (units > 9)
  {
    digitalWrite(relay,LOW);
    Serial.println("load off");
    
units = 10;
cost = 50;

bal = 0;

  }
 }

void sndit ()
{
detachInterrupt(digitalPinToInterrupt(interruptPin));

//Serial1.listen(); delay(1000);

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

    client.println(A + String(units) + "&b=" + String(bal) + "&c=" + tamper + Z);

    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
    iot = "\0";
  }
attachInterrupt(digitalPinToInterrupt(interruptPin),pinisr,FALLING);
}

