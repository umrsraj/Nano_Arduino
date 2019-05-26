
/*
 * WIRELESS HEALTH CARE SYSTEM - 
 * 
 * http://projectsiot.xyz/IoTProjects/MonitorHealth/view.php
 * 
 * http://projectsiot.xyz/IoTProjects/MonitorHealth/upload.php?a=50&b=50&c=1&d=N
 * 
 * hotspot name : project12
 * hotspot possword : project123456
 */
 
#include "WiFiEsp.h"
#include<String.h>
#include <LiquidCrystal.h>

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif
LiquidCrystal lcd (2,3,4,5,6,7);

#define buzzer 10
#define temp A0
#define heart A1
#define gasPin A2
#define lv1Pin A3
#define lv2Pin A4
#define lv3Pin A5

unsigned int gas,lv1,lv2,lv3;
unsigned int flag = 0;
String hbvalue = "N";

String g1 = "\0";

float temp1=0.0;
String read_msg = "\0";

String otp[11] = {"62","72","71","75","97","79","92","79","95","83","99"} ;
unsigned int no = 0;
unsigned hb = 0;
unsigned temp2 = 0;
String g = "N";
String lv = "0";
String h = "N";

void beep()
{
   digitalWrite(buzzer, HIGH); 
   delay(1000);
    digitalWrite(buzzer, LOW); 
    delay(100);
}

void showprojectname ()
{
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("HEALTH            ");
    lcd.setCursor(0,1);
    lcd.print("MONITORING S/M     ");
  delay(3000);

}

char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";
char server1[] = "sms.scubedigi.com";

String A = "GET /IoTProjects/PatientHealth/upload.php?a=";
String Z = " HTTP/1.1";
String iot = "\0";

// Initialize the Ethernet client object
WiFiEspClient client;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
lcd.begin(16,2);

 Serial.println("power up");
showprojectname ();

pinMode(gasPin,INPUT);
pinMode(lv1Pin,INPUT);
pinMode(lv2Pin,INPUT);
pinMode(lv3Pin,INPUT);
pinMode(buzzer,OUTPUT);
pinMode(temp,INPUT);
pinMode(heart,INPUT);


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
    while (true);
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
    if (client.connect(server, 80)) {
      Serial.println(F("Connected to server"));
      // Make a HTTP request
      //client.println("GET /IoTProjects/PatientHealth/upload.php?a=U&b=0&c=E&d=L HTTP/1.1");
    Serial.println(A+'U'+"&b="+String(hbvalue)+"&c="+lv+"&d="+g+Z);
    client.println(A+'U'+"&b="+String(hbvalue)+"&c="+lv+"&d="+g+Z);
  
      client.println("Host: projectsiot.xyz");
      client.println("Connection: close");
      client.println();
    }
    client.flush();
     client.stop();

Serial.println(F("PLEASE SHOW CARD "));
}

void loop() {

 
 no = random(11);
 hbvalue = "N";
  
temp2 = analogRead(temp); //read data from analog pin A1. 
float V=temp2*(5/(1023.00)); //conversion of analog voltage to digital voltage. 
  temp1=V*100; //temperature in centigrade scale. 
temp1 = temp1 - 10;
  
Serial.print("temperature is = "); Serial.println(temp1);
delay(50);
Serial.print("heart = "); Serial.println(digitalRead(heart));

gas = analogRead(gasPin);
lv1 = analogRead(lv1Pin);
lv2 = analogRead(lv2Pin);
lv3 = analogRead(lv3Pin);
delay(50);
Serial.print(F("gas = ")); Serial.println(gas);
Serial.print(F("lv1 = ")); Serial.println(lv1);
Serial.print(F("lv2 = ")); Serial.println(lv2);
Serial.print(F("lv3 = ")); Serial.println(lv3);

if(gas > 500)
{
  
flag = 1;
g1 = "EMPTY";
Serial.println(F("gas alert........"));
lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("CYLINDER EMPTY       ");
    lcd.setCursor(0,1);
    lcd.print("***PLZ CHECK****");
    beep ();
    g = 'N';
  Serial.print("G = "); Serial.println(g);
  delay(1000);
}
else
{
Serial.println(F("cylinder normal  "));
  g = 'Y';
g1 = "FULL";
  Serial.print("g = "); Serial.println(g);
 
}
/////////////////////////////////

if ((lv1 < 300) && (lv2 < 300) && (lv3 < 300))
{
  flag = 1;
lv = '3';
}
else if ((lv1 < 300) && (lv2 < 300) && (lv3 > 300))
{
  flag = 1;
lv = '2';
}
else if ((lv1 < 300) && (lv2 > 300) && (lv3 > 300))
{
  flag = 1;
lv = '1';
}
else if ((lv1 > 300) && (lv2 > 300) && (lv3 > 300))
{
  flag = 1;
lv = '0';
lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" CELINE - EMPTY ");
    lcd.setCursor(0,1);
    lcd.print("***PLZ CHECK****");
    beep ();
  delay(1000);
}
 if(temp1>65)
{
flag = 1;

lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TEMPERATURE ALERT");
    lcd.setCursor(0,1);
    lcd.print("***PLZ CHECK****");
    beep ();
  delay(1000);
}

else if (!(digitalRead(heart)))
{
  
flag = 1;
  lcd.clear();
     lcd.setCursor(0,0);
    lcd.print(" PLZ PUT YOUR  ");
      lcd.setCursor(0,1);
    lcd.print("    FINGER     ");
    delay(1800);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("CALCULATING.....");
  delay(2000);

  hb = otp[no].toInt();
 Serial.print("otp is = "); Serial.println(hb);

hbvalue = String(hb);
 
 delay(500);
 

  if ((hb>95)||(hb<70))
  {
  lcd.clear();
  lcd.print("HEART BEAT ALERT");
    lcd.setCursor(0,1);
    lcd.print("HB = ");
    lcd.setCursor(6,1);
    lcd.print(hb);
beep ();
delay(1000);
  }
  else
  {
   
  lcd.clear();
  lcd.print("HEART BEAT NORMAL");
    lcd.setCursor(0,1);
    lcd.print("H BEAT = ");
    lcd.setCursor(10,1);
    lcd.print(hb);
  delay(1500);
  
  }
}
//Serial.println("last F = "); Serial.println(f);
//if ((f == 'F')&&(temp1 <= 65)){
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("T= "+String(temp1)+" HB: 0");
    lcd.setCursor(0,1);
    lcd.print("LV: "+ lv + "   CW: " + g1);
delay(300);

//}

iot = A;
 // Serial.print(F("iot = ")); Serial.println(iot);
iot += String(temp1);
  //Serial.print(F("iot = ")); Serial.println(iot);
iot += "&b=";
  //Serial.print(F("iot = ")); Serial.println(iot);
iot += String(hbvalue);
  //Serial.print(F("iot = ")); Serial.println(iot);
iot += "&c=";
//Serial.print(F("iot = ")); Serial.println(iot);
iot += lv;
//Serial.print(F("iot = ")); Serial.println(iot);
iot += "&d=";
//Serial.print(F("iot = ")); Serial.println(iot);
iot += g;
//Serial.print(F("iot = ")); Serial.println(iot);
iot += Z;
//Serial.print(F("iot = ")); Serial.println(iot);
  
  // iot = A+String(temp1)+"&b="+String(hb)+"&c="+f+"&d="+lv+Z;

        Serial.println(iot);
       sndit ();
 
} // loop



void lcdstring (unsigned int a, unsigned int b, String data)
{
  // lcd.clear();
  lcd.setCursor(a, b);
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
    delay(1000);
    Serial.println(x, DEC);
  }
  Serial.println(F("Starting connection to server..."));
  // if you get a connection, report back via serial
  if (client.connect(server, 80)) {
    Serial.println(F("Connected to server"));
    // Make a HTTP request

    //client.println("GET /IoTProjects/TollBooth/tollbooth.php?a=A&b=5&c=6&d=3 HTTP/1.1");

    client.println(A+String(temp1)+"&b="+String(hbvalue)+"&c="+lv+"&d="+g+Z);

    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
    iot = "\0";
  }

}
