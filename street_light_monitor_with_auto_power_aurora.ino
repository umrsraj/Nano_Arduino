#include "WiFiEsp.h"
#include<String.h>
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif
//char ssid[] = "AMBEST Technologies";            // your network SSID (name)
//char pass[] = "AmBeSt@@321";        // your network password

char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password

int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";
char server1[] = "sms.scubedigi.com";

String A = "GET /IoTProjects/LightPower/upload.php?a=";
String Z = " HTTP/1.1";
String msg = "GET /api.php?username=Mydreamacd&password=Mydre@m123&to=";
// "GET /api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=WELCOME%20MESSAGE HTTP/1.1"
String iot = "\0";
String bulk = "\0";
WiFiEspClient client;

#include<String.h>


#include <LiquidCrystal.h>

#define ldrPin A0
#define led1 9
#define led2 10
#define led3 11
#define buzzer 8

String light1 = "N";

String light2 = "N";
String light3 = "N";

#define ir1 A1
#define ir2 A2
#define ir3 A3

int ldr = 0;
int count1 = 0;                                          // count = 0
char input[12];
int t = 0;
float spd = 0;

void beep ()
{
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(100);
}



LiquidCrystal lcd (2,3,4,5,6,7);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("power up");
  lcd.begin(16,2);
  pinMode(buzzer,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(ldrPin,INPUT);
  pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);
  pinMode(ir3,INPUT);

beep ();

     lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("STREET LIGHT ");
     lcd.setCursor(0,1);
   lcd.print("MONITORIG SYSTEM");
   delay(2000);
     lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("WITH AUTO POWER");
     lcd.setCursor(0,1);
   lcd.print("SAVING USING LDR");
   delay(2000);


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
      client.println("GET /IoTProjects/FootStepPower/footstep.php?a=U&b=0 HTTP/1.1");
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
light1 = "L";
light2 = "L";
light3 = "L";

ldr = analogRead(ldrPin);
Serial.println("ldr ="+String(ldr));

if (ldr > 500)
{
  Serial.println("night mode");
  analogWrite(led1,45);
  delay(10);
  analogWrite(led2,45);
  delay(10);
  analogWrite(led3,45);
  delay(10);
  light1= "M";
  light2= "M";
  light3= "M";


if (digitalRead(ir1)==HIGH)
{
  Serial.println("ir-1 detected");
  digitalWrite(led1,HIGH);
  light1 = "F";
}
if (digitalRead(ir2)==HIGH)
{
  Serial.println("ir-1 detected");
  digitalWrite(led2,HIGH);
light2 = "F";
}

if (digitalRead(ir3)==HIGH)
{
  Serial.println("ir-3 detected");
  digitalWrite(led3,HIGH);
light3 = "F";
}

  
}
else
{
 Serial.println("day mode");
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  light1 = "L";
light2 = "L";
light3 = "L";
}

lcdstring(0,0,"               ");
lcdstring(0,1,"               ");
lcdstring(0,0,"L1: "+String(light1));
lcdstring(8,0,"L2: "+String(light2));
lcdstring(0,1,"L3: "+String(light3));

iot = A + light1 + "&b=" + light2 + "&c=" + light3 + Z;
sndit ();

   }//loop
void lcdstring(int a, int b, String data)
{
  lcd.setCursor(a,b);
  lcd.print(data);
}
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

 
    client.println(iot);

    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
    iot = "\0";
  }

}
