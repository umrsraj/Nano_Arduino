
/*
 * WIRELESS HEALTH CARE SYSTEM - 
 * 
 * http://projectsiot.xyz/IoTProjects/HealthCare/healthdisplay.php
 * 
 * http://projectsiot.xyz/IoTProjects/HealthCare/healthupload.php?a=43&b=99&c=H
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

SoftwareSerial zigbee(2, 3);

LiquidCrystal lcd (4,5,6,7,8,9);

#define buzzer 10
#define temp A0
#define heart A1
#define button A2


unsigned int flag = 0;
String hbvalue = "\0";

float temp1=0.0;
String read_msg = "\0";

String otp[11] = {"62","72","71","75","97","79","92","79","95","83","99"} ;
unsigned int no = 0;
unsigned hb = 0;
unsigned temp2 = 0;

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
    lcd.print("    WIRELESS    ");
    lcd.setCursor(0,1);
    lcd.print("HEALTH CARE S/M");
  delay(3000);

}

char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";
char server1[] = "sms.scubedigi.com";

String A = "GET //IoTProjects/HealthCare/healthupload.php?a=";
String Z = " HTTP/1.1";
String msg = "GET /api.php?username=Mydreamacd&password=Mydre@m123&to=";
// "GET /api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=WELCOME%20MESSAGE HTTP/1.1"
String iot = "\0";
String bulk = "\0";

// Initialize the Ethernet client object
WiFiEspClient client;


void setup() {
  // put your setup code here, to run once:
zigbee.begin(9600);
Serial.begin(9600);
lcd.begin(16,2);

 Serial.println("power up");
showprojectname ();

pinMode(button,INPUT);
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
      client.println("GET /IoTProjects/HealthCare/healthupload.php?a=U&b=0 HTTP/1.1");
      client.println("Host: projectsiot.xyz");
      //client.println("Connection: close");
      client.println();
    }
  //  client.flush();
    // client.stop();

Serial.println(F("PLEASE SHOW CARD "));
}

void loop() {

 hbvalue = "\0";
 no = random(11);

  
temp2 = analogRead(temp); //read data from analog pin A1. 
float V=temp2*(5/(1023.00)); //conversion of analog voltage to digital voltage. 
  temp1=V*100; //temperature in centigrade scale. 
Serial.print("temperature is = "); Serial.println(temp1);
delay(50);
Serial.print("heart = "); Serial.println(digitalRead(heart));

Serial.print("button = "); Serial.println(digitalRead(button));

if(temp1>50)
{
  zigbee.listen (); delay(1000);
zigbee.println("t"); delay(200);

flag = 1;

lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TEMPERATURE ALERT");
    lcd.setCursor(0,1);
    lcd.print("***PLZ CHECK****");
    beep ();
zigbee.println("t"); delay(200);
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
 
 delay(500);
 Serial1.listen (); delay(1000);
  
   

  if ((hb>95)||(hb<70))
  {
    zigbee.listen (); delay(1000);
    zigbee.println("h"); delay(200);
  lcd.clear();
  lcd.print("HEART BEAT ALERT");
    lcd.setCursor(0,1);
    lcd.print("HB = ");
    lcd.setCursor(6,1);
    lcd.print(hb);
beep ();
delay(100);
zigbee.println("h"); delay(200);


  }
  else
  {
  hbvalue = "\0";   
  lcd.clear();
  lcd.print("HEART BEAT NORMAL");
    lcd.setCursor(0,1);
    lcd.print("H BEAT = ");
    lcd.setCursor(10,1);
    lcd.print(hb);
  delay(2000);
  
  }
}
else
{
  zigbee.listen (); delay(1000);
zigbee.println("n"); delay(1000);
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TEMP = ");
    lcd.setCursor(8,0);
    lcd.print(temp1); 
    lcd.setCursor(0,1);
    lcd.print("HEARTBEAT NORMAL");
    zigbee.println("n"); delay(1000);
  delay(1000);
}

if (flag == 1)
{
  
flag = 0;
Serial1.listen (); delay(1000);
  
   iot = A+String(temp1)+"&b="+String(hb)+Z;

        Serial.println(iot);
       // sndit ();
 // ************************************************
  // if the server's disconnected, stop the client
  if (!client.connected()) {
    Serial.println(F("Disconnecting from server..."));
    client.stop();

    // do nothing forevermore
    //while (true);
  }
  //client.stop();
  //client.flush();

//  for (int x = 0; x < 2; x++)
//  {
//    delay(1000);
//    Serial.println(x, DEC);
//  }
  Serial.println(F("Starting connection to server..."));
  // if you get a connection, report back via serial
  if (client.connect(server, 80)) {
    Serial.println(F("Connected to server"));
    // Make a HTTP request

    //client.println("GET /IoTProjects/TollBooth/tollbooth.php?a=A&b=5&c=6&d=3 HTTP/1.1");

    client.println(A+String(temp1)+"&b="+String(hb)+Z);

    client.println("Host: projectsiot.xyz");
    //client.println("Connection: close");
    client.println();
  }
    client.stop();
  
 // ************************************************
        delay(1000);
}
} // loop



void lcdstring (unsigned int a, unsigned int b, String data)
{
  // lcd.clear();
  lcd.setCursor(a, b);
  lcd.print(data);
}
