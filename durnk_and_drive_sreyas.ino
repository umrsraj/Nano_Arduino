
#include "WiFiEsp.h"
#include <LiquidCrystal.h>
#include <String.h>
#include <stdio.h>
#include <stdlib.h>

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif

char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";

String A = "GET /IoTProjects/DrunkDrive1/upload.php?a=";
String Z = " HTTP/1.1";
String msg = "GET /api.php?username=Mydreamacd&password=Mydrm123&to=";
String bulk = "\0";
String iot = "\0";

// Initialize the Ethernet client object
WiFiEspClient client;



LiquidCrystal lcd (2, 3, 4, 5, 6, 7);

unsigned int gas, lv1, lv2, lv3;

String veh = "A";
String lv = "0";
int alc = 0;
int i = 0;
String ALC = "N";

#define lv1Pin A0
#define lv2Pin A1
#define lv3Pin A2
#define alcPin A3
#define parking A4
#define relay A5
#define buzzer 8

void beep ()
{
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(100);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);

  Serial.println("power up");

  pinMode(lv1Pin, INPUT);
  pinMode(lv2Pin, INPUT);
  pinMode(lv3Pin, INPUT);

  pinMode(alcPin, INPUT);
  pinMode(parking, INPUT);

  pinMode(relay, OUTPUT);

  lcd.clear ();
  lcdstring(0, 0, " IOT BSD DRUNK   ");
  lcdstring(0, 1, "AND DRIVE DETECTION");
  delay(3000);

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



}

void loop() {
  // put your main code here, to run repeatedly:

  while (digitalRead(parking) == LOW)
  {
    veh = "A";
    lv = "R";
    digitalWrite(relay,HIGH);
    delay(200);
    Serial.println("no parknig");
    alc = analogRead(alcPin);
    Serial.println("alc = " + String(alc));
    lcd.clear ();
    lcdstring(0, 0, "VEHICLE MOVING      ");

    if (alc > 900)
    {
      Serial.println("alcohol alert");
      digitalWrite(relay, LOW);
      delay(100);
      ALC = "Y";
      lcdstring(0, 1, "ALC:" + ALC);
      beep ();
      iot =  A + veh + "&b=" + ALC + "&c=" + lv + Z;
      sndit ();
      delay(2500);
    }
    else
    {
      ALC = "N";
       iot =  A + veh + "&b=" + ALC + "&c=" + lv + Z;
      sndit ();
    }
  }//no parking

  while (digitalRead(parking) == HIGH)
  {
digitalWrite(relay,LOW);
delay(100);
veh = "B";
ALC = "R";
    Serial.println("PARKING   .......");
    lv1 = analogRead(lv1Pin);
    lv2 = analogRead(lv2Pin);
    lv3 = analogRead(lv3Pin);
    delay(50);
    Serial.print(F("lv1 = ")); Serial.println(lv1);
    Serial.print(F("lv2 = ")); Serial.println(lv2);
    Serial.print(F("lv3 = ")); Serial.println(lv3);


    lcdstring(0, 0, "                    ");
    lcdstring(0, 1, "                    ");
    lcdstring (0, 0, "VEHICLE PARKED    ");

    if ((lv1 < 300) && (lv2 < 300) && (lv3 < 300))
    {
      // flag = 1;
      lv = '3';
    }
    else if ((lv1 < 300) && (lv2 < 300) && (lv3 > 300))
    {
      // flag = 1;
      lv = '2';
    }
    else if ((lv1 < 300) && (lv2 > 300) && (lv3 > 300))
    {
      // flag = 1;
      lv = '1';
    }
    else if ((lv1 > 300) && (lv2 > 300) && (lv3 > 300))
    {
      lv = '0';
      lcdstring (0, 0, "FUEL THEFT ALERT");
      lcdstring (0, 1, "PLEASE CHECK           ");
      beep ();
   iot =  A + veh + "&b=" + ALC + "&c=" + lv + Z;
      sndit ();
      delay(2500);
    }
    if (lv != '0')
    {
      lcdstring(0, 0, "                    ");
      lcdstring(0, 1, "                    ");
      lcdstring (0, 0, "VEHICLE PARKED    ");
      lcdstring (0, 1, "FL: " + String(lv));
      
       iot =  A + veh + "&b=" + ALC + "&c=" + lv + Z;
      sndit ();
      delay(200);
    }
  }//while parking

}//loop


void lcdstring(int a, int b, String data)
{
  lcd.setCursor(a, b);
  lcd.print(data);
}
void sndit ()
{
   iot =  A + veh + "&b=" + ALC + "&c=" + lv + Z;

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

    client.println( A + veh + "&b=" + ALC + "&c=" + lv + Z);

    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
    iot = "\0"; 

} 
}
