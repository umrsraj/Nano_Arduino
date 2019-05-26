#include "WiFiEsp.h"
#include<String.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd (A0,A1,A2,A3,A4,A5);
// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif

#define relay 4

volatile int units = 0;
volatile int amount = 50;
volatile int preunits = 0;
volatile int punits = 0;

String consumer = "0";
int flag = 0;
int interruptPin = 2;


char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";
String A = "GET /IoTProjects/SmartEnergyMeter/energymeter.php?a=";
String Z = " HTTP/1.1";
String iot = "\0";
String load = "Y";
WiFiEspClient client;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
lcd.begin(16,2);
Serial.println("power up");
pinMode(2,INPUT);
pinMode(relay,OUTPUT);

attachInterrupt(digitalPinToInterrupt(interruptPin),pinisr,FALLING);


lcd.clear ();

  
lcdstring(0,0,"SMART ENERGY             ");
lcdstring(0,1,"METER                   ");

  Serial1.begin(9600);

 Serial1.listen (); delay(1000);
 
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
      client.println("GET /IoTProjects/SmartEnergyMeter/energymeter.php?a=U HTTP/1.1");
      client.println("Host: projectsiot.xyz");
      client.println("Connection: close");
      client.println();
    }
    client.flush();
     client.stop();
     
delay(1000);
digitalWrite(relay,HIGH);
delay(4000);

units = 0;

load = "Y";
}

void loop() {
  // put your main code here, to run repeatedly:

  
lcdstring(0,0,"                   ");
lcdstring(0,1,"                   ");

lcd.setCursor(0,0);
lcd.print("units: "+String(units));
lcd.setCursor(0,1);
lcd.print("Rbal: "+String(amount));
 delay(100);
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

    client.println( A + String(units) + "&b=" + amount + "&c="  + load +  Z);

    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
    iot = "\0";
  }
attachInterrupt(digitalPinToInterrupt(interruptPin),pinisr,FALLING);

}//loop

void pinisr ()
{
  
  Serial.println("interrupttttttttttt");
  units++;
  punits = units;
  Serial.println("units = "+String(units));
  amount = amount - 5;
  Serial.println("amount = "+String(amount));

if (amount < 1)
{
  digitalWrite(relay,LOW);
  amount = 0;
  load = "N";
  units = 10;
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

    client.println( A + String(units) + "&b=" + amount +  Z);

    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
    iot = "\0";
  }
attachInterrupt(digitalPinToInterrupt(interruptPin),pinisr,FALLING);
}

void lcdstring(int a, int b, String data)
{
  lcd.setCursor(a,b);
  lcd.print(data);
}
