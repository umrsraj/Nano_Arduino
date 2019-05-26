
#include "WiFiEsp.h"
#include<String.h>

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
SoftwareSerial SIM900(2, 3); // RX, TX
#endif



char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";
String read_msg = "\0";

int t = 0;

String crack = "N";


String A = "GET /IoTProjects/RailwayCrack/upload.php?a=";
String Z = " HTTP/1.1";
String msg = "GET /api.php?username=Mydreamacd&password=Mydrm123&to=";
String bulk = "\0";
String iot = "\0";

// Initialize the Ethernet client object
WiFiEspClient client;

#include <LiquidCrystal.h>
LiquidCrystal lcd (4,5,6,7,8,9);

#define ir1 10
#define ir2 11
#define m11 A0
#define m12 A1
#define m21 A2
#define m22 A3
#define buzzer A4

int mems = 0;
void forward ()
{
  digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);
  digitalWrite(m21,HIGH);
  digitalWrite(m22,LOW);
  delay(50);
}

void backward ()
{
  digitalWrite(m11,LOW);
  digitalWrite(m12,HIGH);
  digitalWrite(m21,LOW);
  digitalWrite(m22,HIGH);
  delay(50);
}

void left ()
{
  digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);
 digitalWrite(m21,LOW);
  digitalWrite(m22,HIGH);
  delay(50);
}
void right ()
{
   digitalWrite(m11,LOW);
  digitalWrite(m12,HIGH);
  digitalWrite(m21,HIGH);
  digitalWrite(m22,LOW);
  delay(50);
}
void stop_motor ()
{
   digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
  digitalWrite(m21,LOW);
  digitalWrite(m22,LOW);
  delay(50);
}
void beep ()
{
  digitalWrite(buzzer,HIGH); delay(1000);
  digitalWrite(buzzer,LOW); delay(100);
}

 void lcdstring (unsigned int a, unsigned int b, String data)
 {
  lcd.setCursor(a,b);
  lcd.print(data);
 }

void setup()
{
Serial.begin(9600);
Serial.println(F("POWERE UP"));
SIM900.begin(9600);

lcd.begin(16,2);

lcd.clear();
lcdstring(0,0," ROBUST RAILWAY ");
lcdstring(0,1,"CRACK DETCTN S/M");
 delay(2000);
        //  lcd.clear();

pinMode(buzzer,OUTPUT);
pinMode(ir1,INPUT);
pinMode(ir2,INPUT);
pinMode(m11,OUTPUT);
pinMode(m12,OUTPUT);
pinMode(m21,OUTPUT);
pinMode(m22,OUTPUT);

beep ();

  // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);

Serial1.listen (); delay(1000);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println(F("WiFi shield not present"));
    // don't continue
//    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print(F("Attempting to connect to WPA SSID: "));
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }
   lcd.clear();
        lcd.setCursor(2,0);
        lcd.print("SERVER INT      ");
        lcd.setCursor(0,1);
         lcd.print("PLEASE WAIT      ");
         delay(200);
iot = A + "U" + Z;
sndit ();
   lcd.clear();
        lcd.setCursor(2,0);
        lcd.print("SERVER INIT DONE   ");
        lcd.setCursor(0,1);
         lcd.print("                  ");
         delay(2000);
iot = A + "N" + Z;
sndit ();

delay(3000);
forward ();

}

void loop()
{

if ((digitalRead(ir1)==LOW)||(digitalRead(ir2)==LOW))
{
  Serial.println("crack fault detected please check");
stop_motor ();
SIM900.listen();
SIM900.print("CRACK DETECTED "); delay(100);
beep ();
SIM900.print("CRACK DETECTED "); delay(100);
delay(2000);

iot = A + "Y" + Z;
sndit ();
delay(2000);
for(int k = 0; k<10;k++)
{
SIM900.print("CRACK DETECTED "); delay(100);
  iot = A + "Y" + Z;
sndit ();
  }
  while (1);
}
   
}// loop

void ShowSerialData()
{
  SIM900.listen();
  delay(200);
  while(SIM900.available()!=0)
   read_msg = SIM900.readString();
 
  Serial.println("read_msg is = "); Serial.println(read_msg);

   delay(1);
}
void sndit ()
{
Serial1.listen();
delay(1000);
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

    client.println(iot);

    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
    iot = "\0";
  }

}
