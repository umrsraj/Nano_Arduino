#include <LiquidCrystal.h>
#include <stdlib.h>
#include "WiFiEsp.h"
#include<String.h>

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif

char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";

String G = "N";
String P = "N";
String M = "N";

char ss = 'N';

String A = "GET /IoTProjects/Missile/upload.php?a=";
String Z = " HTTP/1.1";
String iot = "\0";
// Initialize the Ethernet client object
WiFiEspClient client;


LiquidCrystal lcd(2,3,4,5,6,7);

#define trigPin 8
#define echoPin 9
#define gasPin A0
#define pir A1
#define m11 A4
#define m12 A5
#define lazer A2
#define buzzer A3

long duration, distance,duration1,distance1;
volatile int flag = 0;
int gas = 0;

void forward ()
{
  digitalWrite(m11,HIGH);
  digitalWrite(m12 ,LOW);
  delay(50);
}
void backward ()
{
  digitalWrite(m12,HIGH);
  digitalWrite(m11,LOW);
  delay(50);
}
void stop_motor ()
{
  digitalWrite(m12,LOW);
  digitalWrite(m11,LOW);
  delay(50);
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("power up");
lcd.begin(16,2);

pinMode(trigPin,OUTPUT);
pinMode(echoPin,INPUT);
pinMode(m11,OUTPUT);
pinMode(m12,OUTPUT);
pinMode(lazer,OUTPUT);
pinMode(buzzer,OUTPUT);
pinMode(pir,INPUT);
pinMode(gasPin,INPUT);

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
      client.println("GET /IoTProjects/Missile/upload.php?a=U&b=N&c=N HTTP/1.1");
      client.println("Host: projectsiot.xyz");
      client.println("Connection: close");
      client.println();
    }
    client.flush();
     client.stop();

  lcd.clear();
lcd.setCursor(0,0);
lcd.print("Server Init.");
lcd.setCursor(0,1);
lcd.print("Done");
  delay(5000);
Serial.println(F("PLEASE SHOW CARD "));

  
 lcd.begin(16,2);
        lcd.setCursor(0,0);
        lcd.print("MILITARY ASSISTANCE   ");
        lcd.setCursor(0,1);
         lcd.print(".................");
         delay(2000);
         beep ();
   forward ();
 

}
void loop() {
  // put your main code here, to run repeatedly:

G = "N";
P = "N";
M = "N";
Serial.println("pir= "+String(digitalRead(pir)));
gas = analogRead(gasPin);
Serial.println("gas = "+String(gas));

digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
 // distance = (duration/2) / 29.1;
distance= duration*0.034/2;
Serial.print("distance--- "); Serial.println(distance);
//distance = distance * 10;
 if(distance>220)
 {
  distance=220;
 }
 
Serial.print("distance--- "); Serial.println(distance);

 if (distance < 5)
//if (digitalRead(echoPin)==HIGH)
 {
  M = "Y";
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MISSILE DETECTED");
  lcd.setCursor(0,1);
  lcd.print("FIRING - MISSILE");
  delay(50);
  stop_motor();
  digitalWrite(lazer,HIGH);
  beep ();
  digitalWrite(lazer,LOW);

iot = A + String(M) + "&b=" + String(G) + "&c=" + String(P) + Z;
sndit ();
 forward ();
 }
 else if (gas > 900)
 {
  G = "Y";
  Serial.println("gas alert");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GAS ALERT             ");
  lcd.setCursor(0,1);
  lcd.print("               ");
  delay(2000);
iot = A + String(M) + "&b=" + String(G) + "&c=" + String(P) + Z;
sndit ();
 }
 else if (digitalRead(pir)==HIGH)
 {
  
  P = "Y";
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("INTRUDER ALERT         ");
  lcd.setCursor(0,1);
  lcd.print("               ");
iot = A + String(M) + "&b=" + String(G) + "&c=" + String(P) + Z;
sndit ();
  delay(2000);
 }
 else
 {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("NO MISSILE     ");
  lcd.setCursor(0,1);
  lcd.print("G: 0");
  lcd.setCursor(8,1);
  lcd.print("P: 0");
  delay(50);
    iot = A + String(M) + "&b=" + String(G) + "&c=" + String(P) + Z;
sndit ();
forward ();
 }
}//loop

void sndit ()
{

//  detachInterrupt(interruptPin1);
//  detachInterrupt(interruptPin2);

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
    delay(10);
    Serial.println(x, DEC);
  }
  Serial.println(F("Starting connection to server..."));
  // if you get a connection, report back via serial
  if (client.connect(server, 80)) {
    Serial.println(F("Connected to server"));
    // Make a HTTP request

    client.println( iot = A + ss + "&b=" + String(distance) + Z);

    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
    iot = "\0";
//    attachInterrupt(digitalPinToInterrupt(interruptPin1), pinisr, FALLING);
//  attachInterrupt(digitalPinToInterrupt(interruptPin2), pinisr1, FALLING);

  }

}

void beep ()
{
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(100);
  
}
/*
void pinisr ()
{
  Serial.println("in interrupt1111.....");
  Serial.println("---------moving forward ----------");
  forward();
  detachInterrupt(digitalPinToInterrupt(interruptPin1));
  //delayMicroseconds(1000000);
  //forward ();
}

void pinisr1 ()
{
  Serial.println("in interrupt2222.....");
  Serial.println("---------moving backward ----------");
  backward();
  
  detachInterrupt(digitalPinToInterrupt(interruptPin2));
//  delayMicroseconds(1000000);
}
*/
