#include "WiFiEsp.h"
#include<String.h>
#include <LiquidCrystal.h>

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif

LiquidCrystal lcd (A0,A1,A2,A3,A4,A5);

#define en 2
#define sw 3
#define m11 5 // MOTORS INTERFACING
#define m12 4
#define m21 6
#define m22 7
#define buzzer 8
#define ir 9

void beep1(void)
{
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(50);
}
void beep(void)
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

String zone = "Y";
String obs = "Y";

String A = "GET /IoTProjects/RspeedZone/speed.php?a=";
String Z = " HTTP/1.1";
String iot = "\0";

// Initialize the Ethernet client object
WiFiEspClient client;

void setup()
{
  // initialize serial for debugging
  Serial.begin(9600);

  lcd.begin(16, 2);
  
  pinMode(en, INPUT); 
  pinMode(sw, INPUT);  
  
   pinMode(m11, OUTPUT);
    pinMode(m12, OUTPUT);
     pinMode(m21, OUTPUT);
      pinMode(m22, OUTPUT);
  pinMode(buzzer, OUTPUT);
pinMode (ir,INPUT);


 lcd.clear();
lcd.setCursor(0,0);
lcd.print("SMART ZONE VEHICLE");
lcd.setCursor(0,1);
lcd.print("SPEED CONTROL     ");
delay(3000);

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
      client.println("GET //RspeedZone/speed.php?a=U&b=N HTTP/1.1");
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

     digitalWrite(m11,HIGH);
     digitalWrite(m12,LOW);
     digitalWrite(m21,HIGH);
     digitalWrite(m22,LOW); 
     delay(200);
     
}

void loop()
{
zone = "N";
obs = "N";
if (digitalRead(ir)==HIGH)
{
      Serial.println("*****obstacle detected******");
    lcd.setCursor(0,0);
lcd.print("OBSTACLE DETECTED    ");
lcd.setCursor(0,1);
lcd.print("VEHICLE - STOP    ");
delay(30);
    obs = "Y";
digitalWrite(m11,LOW);
     digitalWrite(m12,LOW);
     digitalWrite(m21,LOW);
     digitalWrite(m22,LOW); 
     delay(200);
beep ();
delay(1000);
}


else if (digitalRead(en)==HIGH)
{
    Serial.println("*****school zone detected******");
  lcd.clear();
    lcd.setCursor(0,0);
lcd.print("ZONE DETECTED    ");
lcd.setCursor(0,1);
lcd.print("VEHICLE - SLOW    ");
delay(30);
    zone = "Y";
analogWrite(m11,120);
     digitalWrite(m12,LOW);
     analogWrite(m21,120);
     digitalWrite(m22,LOW); 
     delay(200);
beep1 ();
delay(100);
}
else
{
  lcd.clear();
    lcd.setCursor(0,0);
lcd.print("SYSTEM IS NORMAL");
lcd.setCursor(0,1);
lcd.print("VEHICLE - MOVING    ");
delay(30);
 
  digitalWrite(m11,HIGH);
     digitalWrite(m12,LOW);
    digitalWrite(m21,HIGH);
     digitalWrite(m22,LOW); 
}
 iot = A + obs + "&b=" + zone + Z;

        Serial.println(iot);
        sndit ();  



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
    delay(10);
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
