///*

#include "WiFiEsp.h"
#include <String.h>
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif

char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password

int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";
char server1[] = "sms.scubedigi.com";

String A = "GET /IoTProjects/BlindStick/upload.php?a=";
String Z = " HTTP/1.1";
String msg = "GET /api.php?username=Mydreamacd&password=Mydre@m123&to=";
String iot = "\0";
String bulk = "\0";
WiFiEspClient client;
//*/
char U = 'N';
char F = 'N';
char M = 'N';
char W = 'N';


#include <LiquidCrystal.h>

LiquidCrystal lcd (2,3,4,5,6,7);

#define trigPin A0
#define echoPin A1
#define mirPin A2
#define watPin A3
#define memsPin A4
#define buzzer A5


#define v0 8
#define v1 9
#define v2 10
#define v3 11

int mir = 0;
int mems = 0;
int wat = 0;

long duration, distance,duration1,distance1;




void lcdstring(int a, int b, String data)
{
  lcd.setCursor(a,b);
  lcd.print(data);
}

void beep ()
{
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(100);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
Serial.println("power up");
lcd.begin(16,2);

pinMode(trigPin,OUTPUT);
pinMode(echoPin,INPUT);
pinMode(mirPin,INPUT);
pinMode(memsPin,INPUT);
pinMode(watPin,INPUT);
pinMode(buzzer,OUTPUT);

pinMode(v0,OUTPUT);
pinMode(v1,OUTPUT);
pinMode(v3,OUTPUT);
pinMode(v2,OUTPUT);
  
digitalWrite(v0,HIGH);
digitalWrite(v1,HIGH);
digitalWrite(v2,HIGH);
digitalWrite(v3,HIGH);

lcd.clear ();
lcdstring(0,0,"BLIND STICK         ");
lcdstring(0,1,"USING IOT                   ");
delay(3000);


///*
  // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println(F("WiFi shield not present"));
    // don't continue
   // while (true);
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
      client.println("GET /IoTProjects/BlindStick/upload.php?a=U&b=0 HTTP/1.1");
      client.println("Host: projectsiot.xyz");
      client.println("Connection: close");
      client.println();
    }
    client.flush();
     client.stop();
 //*/   
Serial.println(F("PLEASE SHOW CARD "));


}

void loop()
{

lcdstring(0,0,"                       ");
lcdstring(0,1,"                       ");

U = 'N';
F = 'N';
M = 'N';
W = 'N';

  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

Serial.print("distance--- "); Serial.println(distance);

mir = digitalRead(mirPin);
Serial.println("mir="+String(mir));
mems = analogRead(memsPin);
Serial.println("mems="+String(mems));
wat = analogRead(watPin);
Serial.println("wat="+String(wat));

//lcd.clear ();
//lcdstring(0,0,"MEMS ");
//lcd.print(mems);
//delay(1000);




 if(distance>220)
 {
  distance=220;
 }
 
if (distance < 5)
{
  Serial.println("obstacle alert");
  lcdstring(0,0,"OBSTACLE ALERT      ");
  lcdstring(0,1,"PLEASE CHECK        ");
 beep ();
 U = 'Y';
  digitalWrite(v0,LOW);
delay(200);
digitalWrite(v0,HIGH);
delay(200);
 delay(2000);
}
else if (mir == 0)
{
  Serial.println("steps detected");
    lcdstring(0,0,"STEPS DETECTED      ");
  lcdstring(0,1,"PLEASE CHECK        ");
beep ();
 M = 'Y';
  digitalWrite(v1,LOW);
delay(200);
digitalWrite(v1,HIGH);
delay(200);
  delay(2000);
}

else if (wat < 800)
{
  Serial.println("WATER DETECTED");
    lcdstring(0,0,"WATER DETECTED      ");
  lcdstring(0,1,"PLEASE CHECK        ");
beep ();
 W = 'Y';

digitalWrite(v2,LOW);
delay(200);
digitalWrite(v2,HIGH);
delay(200);
  delay(2000);
}

else if ((mems < 350)|| (mems > 500))
{
  Serial.println("FALLING ALERT");
    lcdstring(0,0,"FALLING ALERT      ");
  lcdstring(0,1,"PLEASE CHECK        ");
beep ();
 F = 'Y';

  digitalWrite(v3,LOW);
delay(200);
digitalWrite(v3,HIGH);
delay(200);
  delay(2000);
}
else
{  
  lcdstring(0,1,"                      ");
  lcdstring(0,0,"SYSTEM IS NORMAL");
  delay(200);
}
 iot = A + U + "&b=" + W + "&c=" + M + "&d=" + F + Z;
 sndit ();
 
}//loop
//
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
    delay(1);
    Serial.println(x, DEC);
  }
  Serial.println(F("Starting connection to server..."));
  // if you get a connection, report back via serial
  if (client.connect(server, 80)) {
    Serial.println(F("Connected to server"));
    // Make a HTTP request

 
    client.println(A + U + "&b=" + W + "&c=" + M + "&d=" + F + Z);

    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
    iot = "\0";
  }

}

//*/
