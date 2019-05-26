#include "WiFiEsp.h"
#include<String.h>
#include <LiquidCrystal.h>
#include <Time.h> 
#include <Wire.h> 
#include <DS1307RTC.h>


// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif

LiquidCrystal lcd (6,7,8,9,10,11);

#define swI 2
#define swD 3
#define swH 4
#define swM 5
#define m11 A0
#define m12 A1
#define buzzer A2

int i=0,j=0,k=0;
int count=0;

int flag = 0;

int count1 = 0;                                          // count = 0
char input[12];

void beep ()
{
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(100);
}

void beep1 ()
{
  digitalWrite(buzzer, HIGH);
  delay(300);
  digitalWrite(buzzer, LOW);
  delay(10);
}

char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";
char server1[] = "sms.scubedigi.com";

String A = "GET /IoTProjects/StreetLight/lightstore.php?a=";
String Z = " HTTP/1.1";
String msg = "GET /api.php?username=Mydreamacd&password=Mydre@m123&to=";
String bulk = "\0";
String iot = "\0";

// Initialize the Ethernet client object
WiFiEspClient client;

void setup()
{
  // initialize serial for debugging
  Serial.begin(9600);

  lcd.begin(16, 2);
pinMode(buzzer,OUTPUT);

  pinMode(swI,INPUT);
  pinMode(swD,INPUT);
  pinMode(swH,INPUT);
  pinMode(swM,INPUT);
  
 pinMode(m11,OUTPUT);
 pinMode(m12,OUTPUT);

 lcd.clear();
lcd.setCursor(0,0);
lcd.print("EXAM LEAKAGE S/M     ");
lcd.setCursor(0,1);
lcd.print(".....................");
delay(2000);

  
   alarmSet();

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
      client.println("GET /IoTProjects/StreetLight/lightstore.php?a=U&b=N&c=N HTTP/1.1");
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
}

void loop()
{
lcd.setCursor(0,0);
    lcd.print("Alarm:"+String(j)+":"+String(k));
   lcd.setCursor(0,1);
    lcd.print("Time:"+String(hour())+":"+String(minute()));
delay(30);

 if( (hour() ==j)&&(minute() ==k)&&(flag==0))
   {
   beep1 ();
   }

   
  if(Serial.available())
   {
      count1 = 0;
      while(Serial.available() && count1 < 12)          // Read 12 characters and store them in input array
      {
         input[count1] = Serial.read();
         count1++;
         delay(5);
      }//WHILE
//

 Serial.println(input);                           // Print RFID tag number 
   Serial.print("input[10] is "); Serial.println(input[10]);

if (input[10]== '2')
{
  Serial.println("card matched");

lcdstring(0,0,"CARD1 MATCHED    ");

 if( (hour() ==j)&&(minute() ==k))
   {
    
lcdstring(0,1,"DOOR OPENING      ");
flag = 1;
Serial.println("time matched ");
digitalWrite(m11,HIGH);
digitalWrite(m12,LOW);
delay(2000);

 iot = A + 'Y' + Z;

        Serial.println(iot);
        sndit ();
        
digitalWrite(m11,LOW);
digitalWrite(m12,LOW);
delay(10000);

lcdstring(0,1,"DOOR CLOSING       ");
digitalWrite(m11,LOW);
digitalWrite(m12,LOW);
delay(2000);
   }  
   else
   {
    
lcdstring(0,1,"TIME NOT MATCHED     ");
     iot = A + 'N' + Z;

        Serial.println(iot);
        sndit ();
    Serial.println("time not matched please check ");
   }
}
else
{
  
lcdstring(0,0,"INVALID CARD       ");
lcdstring(0,1,"PLEASE CHECK        ");
  Serial.println("invalid card ");
  beep ();
  delay(1000);
}
   }//serial available


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
 //set time ----------------------------------------------------

void alarmSet()
{
  lcd.clear(); //Use it to clear the LCD Widget
    lcd.setCursor(0,0);
        lcd.print("Pls SET TIME FOR");
        lcd.setCursor( 0,1);
         lcd.print("STREET LIGHTS ON");
        delay(2000);

while(count<2)   //********************
{  
  //++ INCREMENT
if(digitalRead(swI)==0)
{
i++;
         lcd.clear(); //Use it to clear the LCD Widget
         lcd.setCursor(4,0);
        lcd.print("TIME++");
        lcd.setCursor(4, 1);                                           // Set LCD cursor position (column,row) 
         lcd.print(i);
        delay(200);
 }

  //-- DECREMENT
if(digitalRead(swD)==0)
{
i--;
         lcd.clear(); //Use it to clear the LCD Widget
         lcd.setCursor(4,0);
        lcd.print("TIME--");
        lcd.setCursor(4, 1);                                           // Set LCD cursor position (column,row) 
            lcd.print(i);
        delay(200);
 }

  //SET H
if(digitalRead(swH)==0)
{
j=i;
count++;
         lcd.clear(); //Use it to clear the LCD Widget
         lcd.setCursor(4,0);
        lcd.print("SET HOURS :");
        lcd.setCursor(4, 1);                                           // Set LCD cursor position (column,row) 
           lcd.print(j);
        delay(200);
 } 

    //SET M
if(digitalRead(swM)==0)
{
k=i;
 count++;
         lcd.clear(); //Use it to clear the LCD Widget
         lcd.setCursor(4,0);
        lcd.print("SET MINITS :");
        lcd.setCursor(4, 1);                                           // Set LCD cursor position (column,row) 
          lcd.print(k);
        delay(200);
 } 
}//while closed
Serial.print("hours --"); Serial.println(j);
Serial.print("minutes --"); Serial.println(k);
delay(2000);
    lcd.clear(); //Use it to clear the LCD Widget
    lcd.setCursor(0,0);
        lcd.print("ALARM SET AT");
        lcd.setCursor( 1,1);
         lcd.print(" H:");
           lcd.print(j);
          lcd.setCursor( 6,1);
         lcd.print(" M:");
           lcd.print(k);
        delay(2000); lcd.clear(); //Use it to clear the LCD Widget

}
//-----------------------------------------------------------------
