 
#include "WiFiEsp.h"
#include<String.h>
#include <LiquidCrystal.h>

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif

LiquidCrystal lcd (2,3,4,5,6,7);

#define wind A0
#define solar A1

int r, i, flag;


#define ldr_1 A2
#define ldr_2 A3
#define ldr_3 A4
#define ldr_4 A5

#define m11 8
#define m12 9
#define m21 10
#define m22 11

unsigned int ldr1 = 0;
unsigned int ldr2 = 0;
unsigned int ldr3 = 0;
unsigned int ldr4 = 0;

unsigned int t = 0;

float w = 0;
float s = 0;
float sol  = 0.0;
float win  = 0.0;

void lcdstring (int a, int b, String w);

char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";
String A = "GET /IoTProjects/Hybrid/upload.php?a=";
String Z = " HTTP/1.1";
String iot = "\0";
// Initialize the Ethernet client object
WiFiEspClient client;


String voltageS = "\0";
String voltageW = "\0";

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("power up");

 lcd.begin(16,2);

Serial.println("power up");


lcd.clear ();
lcd.setCursor (0,0);
lcd.print ("WELCOME TO HYBRID");
lcd.setCursor (0,1);
lcd.print ("POWER GENERATION");

delay (13000);



lcd.clear ();
lcd.setCursor (0,0);
lcd.print ("     SYSTEM");
lcd.setCursor (0,1);
lcd.print ("    WITH IoT    ");
delay(2000);


pinMode(ldr_1,INPUT);
pinMode(ldr_2,INPUT);
pinMode(ldr_3,INPUT);
pinMode(ldr_4,INPUT);

pinMode(wind,INPUT);
pinMode(solar,INPUT);

pinMode(m11,OUTPUT);
pinMode(m12,OUTPUT);
pinMode(m21,OUTPUT);
pinMode(m22,OUTPUT);

  // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println(F("WiFi shield not present"));
    // don't continue
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("WIFI NT DETECTED");
    lcd.setCursor(0,1);
    lcd.print("PLEASE CHECK....");
  delay(200);
    //while (true);
  }
  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print(F("Attempting to connect to WPA SSID: "));
    Serial.println(ssid);
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" CONNECTING TO  ");
    lcd.setCursor(3,1);
    lcd.print(ssid);
  delay(200);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  // you're connected now, so print out the data
  Serial.println(F("You're connected to the network"));

    Serial.println(F("sending data ---1 "));
    Serial.println(F("Starting connection to server..."));
    // if you get a connection, report back via serial
    if (client.connect(server, 300)) {
      Serial.println(F("Connected to server"));
      // Make a HTTP request
      //client.println("GET /IoTProjects/PatientHealth/upload.php?a=U&b=0&c=E&d=L HTTP/1.1");
    Serial.println(A+'U'+"&b="+String(win)+Z);
    client.println(A+'U'+"&b="+String(win)+Z);
  
      client.println("Host: projectsiot.xyz");
      client.println("Connection: close");
      client.println();
    }
    client.flush();
     client.stop();

Serial.println(F("PLEASE SHOW CARD "));



}

void loop() {
  // put your main code here, to run repeatedly:

w = analogRead (wind);
s = analogRead (solar);

ldr1 = analogRead(ldr_1);
ldr2 = analogRead(ldr_2);
ldr3 = analogRead(ldr_3);
ldr4 = analogRead(ldr_4);
delay (20);

Serial.print("wind value = "); Serial.println(w);
Serial.print("solar value = "); Serial.println (s);
Serial.println("");
Serial.print("ldr1 = "); Serial.println(ldr1);
Serial.print("ldr2 = "); Serial.println(ldr2);
Serial.print("ldr3 = "); Serial.println(ldr3);
Serial.print("ldr4 = "); Serial.println(ldr4);
Serial.println("");
Serial.println("");
//s = s*125/1023;
//w = w*125/1023;

//s = (s/2) - 2;
//w = (w/2) - 2;

 sol= s * (5.00/1023.00)*5;
win= w * (5.00/1023.00)*5;

Serial.print("WIND VOLTAGE = "); Serial.println (sol);
Serial.print("SOLAR VOLTAGE = "); Serial.println (win);

voltageS = sol;
voltageW = win;

lcd.clear ();
lcd.setCursor (0,0);
lcd.print ("S:"+String(sol));
lcd.setCursor (0,1);
lcd.print ("W:"+String(win));

if((ldr1>300)&&(ldr2<300))
{
  t++;
  Serial.print("t = "); Serial.println(t);
  Serial.println("moving down");
  digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);
  delay(400);
   digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
  digitalWrite(m21,LOW);
  digitalWrite(m22,LOW);
  
}
else if((ldr1<300)&&(ldr2>300))
{
  t++;
  Serial.print("t = "); Serial.println(t);
  Serial.println("moving up");
  digitalWrite(m11,LOW);
  digitalWrite(m12,HIGH);
  delay(400);
   digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
  digitalWrite(m21,LOW);
  digitalWrite(m22,LOW);
  //thingspeak ();
}
else if((ldr3>300)&&(ldr4<300))
{
  t++;
  Serial.print("t = "); Serial.println(t);
  Serial.println("moving left**");
  digitalWrite(m21,HIGH);
  digitalWrite(m22,LOW);
  delay(400);
   digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
  digitalWrite(m21,LOW);
  digitalWrite(m22,LOW);
 // thingspeak ();
}
else if((ldr3<300)&&(ldr4>300))
{
  t++;
  Serial.print("t = "); Serial.println(t);
  Serial.println("moving right**");
  digitalWrite(m21,LOW);
  digitalWrite(m22,HIGH);
  delay(400);
   digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
  digitalWrite(m21,LOW);
  digitalWrite(m22,LOW);
  //thingspeak ();
}
else
{
  Serial.println("STOP");
    digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
  digitalWrite(m21,LOW);
  digitalWrite(m22,LOW);
 // thingspeak ();
}
  iot  = A  + String(sol) + "&b=" + String(win) + Z ;
      Serial.println(iot);
       sndit ();

}//loop
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
    delay(10);
    Serial.println(x, DEC);
  }
  Serial.println(F("Starting connection to server..."));
  // if you get a connection, report back via serial
  if (client.connect(server, 80)) {
    Serial.println(F("Connected to server"));
    // Make a HTTP request

    //client.println("GET /IoTProjects/TollBooth/tollbooth.php?a=A&b=5&c=6&d=3 HTTP/1.1");

    client.println(A+String(sol)+"&b="+String(win)+Z);

    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
    iot = "\0";
  }

}
void lcdstring (int a, int b, String w)
{
  lcd.setCursor(a,b);
  lcd.print(w);
}
