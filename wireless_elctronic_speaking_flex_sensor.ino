#include "WiFiEsp.h"
#include<String.h>
#include <LiquidCrystal.h>

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif

LiquidCrystal lcd (2,3,4,5,6,7);

char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";
char server1[] = "sms.scubedigi.com";

String A = "GET /IoTProjects/ElectronicSpeaking/upload.php?a=";
String Z = " HTTP/1.1";
String msg = "GET /api.php?username=Mydreamacd&password=Mydre@m123&to=";
String bulk = "\0";
String iot = "\0";

// Initialize the Ethernet client object
WiFiEspClient client;



#define flex1 A0
#define flex2 A1
#define flex3 A2

#define v0 8
#define v1 9
#define v2 10
#define v3 11

int f1,f2,f3;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("power up");
lcd.begin(16,2);

pinMode(flex1,INPUT);
pinMode(flex2,INPUT);
pinMode(flex3,INPUT);

pinMode(v0,OUTPUT);
pinMode(v1,OUTPUT);
pinMode(v2,OUTPUT);
pinMode(v3,OUTPUT);

lcd.clear();
 lcdstring(0,0,"ELECTRONIC       ");
  lcdstring(0,1,"SPEACHING S/M    ");
  delay(2000);
  digitalWrite(v0,HIGH);
digitalWrite(v1,HIGH);
digitalWrite(v2,HIGH);
digitalWrite(v3,HIGH);
delay(1000);

   // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  while (WiFi.status() == WL_NO_SHIELD) {
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
      client.println("GET /IoTProjects/ElectronicSpeaking/upload.php?a=U HTTP/1.1");
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

digitalWrite(v0,HIGH);
digitalWrite(v1,HIGH);
digitalWrite(v2,HIGH);
digitalWrite(v3,HIGH);
delay(1000);
digitalWrite(v0,LOW);
digitalWrite(v1,HIGH);
digitalWrite(v2,HIGH);
digitalWrite(v3,HIGH);

delay(200);

digitalWrite(v0,HIGH);
digitalWrite(v1,HIGH);
digitalWrite(v2,HIGH);
digitalWrite(v3,HIGH);
delay(100);
}



void loop() {
  // put your main code here, to run repeatedly:
//analogReadResolution(8);
f1 = analogRead(flex1);
f2 = analogRead(flex2);
f3 = analogRead(flex3);
Serial.println("f1 = "+String(f1));
Serial.println("f2 = "+String(f2));
Serial.println("f3 = "+String(f3));
Serial.println("=======================================");
//delay(500);


  lcdstring(0,0,"                  ");
  lcdstring(0,1,"                 ");

  lcdstring(0,0,String(f1));
  lcdstring(0,1,String(f2));
delay(500);

if (((f1!=0)&&(f1<50))&&((f2!=0)&&(f2<50)))
{
Serial.println("i HAVE SOME EMERGENCY ");

  lcdstring(0,0,"I HV EMERGENCY     ");
  lcdstring(0,1,"PLEASE HELP ME    ");

  digitalWrite(v0,HIGH);
digitalWrite(v1,HIGH);
digitalWrite(v2,HIGH);
digitalWrite(v3,LOW);

delay(200);

digitalWrite(v0,HIGH);
digitalWrite(v1,HIGH);
digitalWrite(v2,HIGH);
digitalWrite(v3,HIGH);
delay(100);

iot = A + "C" + Z;
sndit ();
delay(200);
  
}

else if ((f1!=0)&&(f1<50))
{
  Serial.println("i need food");

  lcdstring(0,0,"I NEED MEDICINE     ");
  lcdstring(0,1,"PLEASE HELP ME    ");

  digitalWrite(v0,HIGH);
digitalWrite(v1,LOW);
digitalWrite(v2,HIGH);
digitalWrite(v3,HIGH);

delay(200);

digitalWrite(v0,HIGH);
digitalWrite(v1,HIGH);
digitalWrite(v2,HIGH);
digitalWrite(v3,HIGH);
delay(100);

iot = A + "B" + Z;
sndit ();
delay(200);
}
else if ((f2!=0)&&(f2<50))
{
  Serial.println("i need water");

  lcdstring(0,0,"HELP ME TO      ");
  lcdstring(0,1,"CROSS ROAD       ");

  digitalWrite(v0,HIGH);
digitalWrite(v1,HIGH);
digitalWrite(v2,LOW);
digitalWrite(v3,HIGH);

delay(200);

digitalWrite(v0,HIGH);
digitalWrite(v1,HIGH);
digitalWrite(v2,HIGH);
digitalWrite(v3,HIGH);
delay(100);

iot = A + "A" + Z;
sndit ();
delay(200);

  }
else
{
 //lcdstring(0,0,"ELECTRONIC       ");
  //lcdstring(0,1,"SPEACHING S/M    ");
  
    digitalWrite(v0,HIGH);
digitalWrite(v1,HIGH);
digitalWrite(v2,HIGH);
digitalWrite(v3,HIGH);

delay(200);

digitalWrite(v0,HIGH);
digitalWrite(v1,HIGH);
digitalWrite(v2,HIGH);
digitalWrite(v3,HIGH);
delay(100);
}





}//loop
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
