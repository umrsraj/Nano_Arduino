
// Code to use SoftwareSerial
#include "WiFiEsp.h"
#include<String.h>
#include <LiquidCrystal.h>
#include<stdlib.h>

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif

LiquidCrystal lcd (2, 3, 4, 5, 6, 7);


#define LEV1 A0
#define LEV2 A1
#define LEV3 A2

#define MTP 8
#define MTN 9
#define buzzer 10

unsigned int  lev1, lev2, lev3;
String lev,gate;
int flag = 0;

void beep()
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
char server1[] = "sms.scubedigi.com";

String A = "GET /IoTProjects/DamGate/damupload.php?a=";
String Z = " HTTP/1.1";
String msg = "GET /api.php?username=Mydreamacd&password=Mydre@m123&to=";
// "GET /api.php?username=Mydreamacd&password=M&to=&from=MYDREM&message=WELCOME%20MESSAGE HTTP/1.1"
String iot = "\0";
String bulk = "\0";

// Initialize the Ethernet client object
WiFiEspClient client;



//================================================================================ setup
void setup() {
  Serial.begin(9600);
lcd.begin(16, 2);
  
  pinMode(buzzer, OUTPUT);
  pinMode(MTP, OUTPUT);
  pinMode(MTN, OUTPUT);
  pinMode(LEV1, INPUT);
  pinMode(LEV2, INPUT);
  pinMode(LEV3, INPUT);
  

  Serial.println("IOT BASED DAM GATE CONTROL SYSTEM \n");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("IOT BSD DAM-GATE");
  lcd.setCursor(0, 1);
  lcd.print(" CONTROL SYSTEM ");
  delay(2000);



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
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("SERVER INIT");
    lcd.setCursor(3,1);
    lcd.print(".................");
  delay(200);
  // you're connected now, so print out the data
  Serial.println(F("You're connected to the network"));

    Serial.println(F("sending data ---1 "));
    Serial.println(F("Starting connection to server..."));
    // if you get a connection, report back via serial
    if (client.connect(server, 80)) {
      Serial.println(F("Connected to server"));
      // Make a HTTP request
      client.println("GET /IoTProjects/DamGate/damupload.php?a=U&b=0 HTTP/1.1");
      client.println("Host: projectsiot.xyz");
      //client.println("Connection: close");
      client.println();
    }
  //  client.flush();
    // client.stop();

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("SERVER INIT");
    lcd.setCursor(3,1);
    lcd.print("done");
  delay(500);
Serial.println(F("PLEASE SHOW CARD "));


  //parking slots details
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("L1= ");
  lcd.setCursor(5, 0);
  lcd.print("0");
  lcd.setCursor(9, 0);
  lcd.print("L2= ");
  lcd.setCursor(13, 0);
  lcd.print("0");

  lcd.setCursor(0, 1);
  lcd.print("L3= ");
  lcd.setCursor(5, 1);
  lcd.print("0");
  lcd.setCursor(9, 1);
  lcd.print("GA= ");
  lcd.setCursor(13, 1);
  lcd.print("0");
  delay(200);

}


// ====================================================================== loop
void loop() {


  lev1 = analogRead(LEV1);
  Serial.println(lev1);

  lev2 = analogRead(LEV2);
  Serial.println(lev2);

  lev3 = analogRead(LEV3);
  Serial.println(lev3);



  //IF ALL LEVEL FULL--------DAM FULL-----
  if ((lev1 > 500) && (lev2 > 500) && (lev3 > 500))
  { 
   
    lev = '3';
    gate = 'O';

    lcd.setCursor(5, 0);
    lcd.print("1");
    lcd.setCursor(13, 0);
    lcd.print("1");
    lcd.setCursor(5, 1);
    lcd.print("1");

    beep();
    
    if (flag == 1)
    {
      //lcd.setCursor(13, 1);
     // lcd.print("1");
      flag = 0;
      digitalWrite(MTP, HIGH);
      digitalWrite(MTN, LOW);
      delay(4000);
      digitalWrite(MTP, LOW);
      digitalWrite(MTN, LOW);
      delay(100);
      lcd.setCursor(13, 1);
      lcd.print("O");
    }

  }  //DAM GATE FULL


  //if DAM GATE IS EMPTY
  if ((lev1 < 500) && (lev2 < 500) && (lev3 < 500))
  { 
    lev = '0';
    gate = 'C';
    lcd.setCursor(5, 0);
    lcd.print("0");
    lcd.setCursor(13, 0);
    lcd.print("0");
    lcd.setCursor(5, 1);
    lcd.print("0");

   
    if (flag == 0)
    {
      beep();
   //   lcd.setCursor(13, 1);
     // lcd.print("1");
      flag = 1;
      digitalWrite(MTP, LOW);
      digitalWrite(MTN, HIGH);
      delay(4000);
      digitalWrite(MTP, LOW);
      digitalWrite(MTN, LOW);
      delay(100);
      lcd.setCursor(13, 1);
      lcd.print("C");
    }


  }  //DAM GATE EMPTY



  //1ST LEVEL DETECT
  if ((lev1 > 500) && (lev2 < 500) && (lev3 < 500))
  {
    lev = '1';
    gate = 'C';
    lcd.setCursor(5, 0);
    lcd.print("1");
    lcd.setCursor(13, 0);
    lcd.print("0");
    lcd.setCursor(5, 1);
    lcd.print("0");
    lcd.setCursor(13, 1);
    lcd.print("0");
    if (flag == 0)
    {
      beep();
   //   lcd.setCursor(13, 1);
     // lcd.print("1");
      flag = 1;
      digitalWrite(MTP, LOW);
      digitalWrite(MTN, HIGH);
      delay(4000);
      digitalWrite(MTP, LOW);
      digitalWrite(MTN, LOW);
      delay(100);
      lcd.setCursor(13, 1);
      lcd.print("C");
    }


  }  //DAM GATE AT LEVEL-1


  //2ND LEVEL DETECT
  if ((lev1 > 500) && (lev2 > 500) && (lev3 < 500))
  {
    lev = '2';
    gate = 'C';
    lcd.setCursor(5, 0);
    lcd.print("1");
    lcd.setCursor(13, 0);
    lcd.print("1");
    lcd.setCursor(5, 1);
    lcd.print("0");
    lcd.setCursor(13, 1);
    lcd.print("0");
    if (flag == 0)
    {
      beep();
   //   lcd.setCursor(13, 1);
     // lcd.print("1");
      flag = 1;
      digitalWrite(MTP, LOW);
      digitalWrite(MTN, HIGH);
      delay(4000);
      digitalWrite(MTP, LOW);
      digitalWrite(MTN, LOW);
      delay(100);
      lcd.setCursor(13, 1);
      lcd.print("C");
    }


  }  //DAM GATE AT LEVEL-1

   iot = A+lev+"&b="+String(gate)+Z;

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

    client.println(A+String(lev)+"&b="+String(gate)+Z);

    client.println("Host: projectsiot.xyz");
    //client.println("Connection: close");
    client.println();
  }
    client.stop();
  
 // ************************************************
        delay(1000);
}//loop
