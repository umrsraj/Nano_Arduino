
#include "WiFiEsp.h"
#include<String.h>
#include <LiquidCrystal.h>


// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif

SoftwareSerial SIM900 (4,5);

#define ct1Pin A0
#define ct2Pin A1
#define ct3Pin A2
#define ct4Pin A3
#define relay 11
#define buzzer 10
#define theft 9
#define magnet 8

int ct1 = 0, ct2 = 0;
float ct3 = 0, ct4 = 0;
int difference = 0;
volatile int units = 0;
volatile int cost = 0;
volatile int preunits = 0;
volatile int punits = 0;

String consumer = "0";
int flag = 0;
String tamper = "N";
String mag = "N";
String bypass = "N";
int interruptPin = 2;

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
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(100);
}
char ssid[] = "project13";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";
String A = "GET /IoTProjects/EnergyMeter/upload.php?a=";
String Z = " HTTP/1.1";
String iot = "\0";
WiFiEspClient client;



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("power up");
pinMode(ct1Pin,INPUT);
pinMode(ct2Pin,INPUT);
pinMode(ct3Pin,INPUT);
pinMode(ct4Pin,INPUT);
pinMode(2,INPUT);
pinMode(theft,INPUT);
pinMode(magnet,INPUT);
pinMode(buzzer,OUTPUT);
pinMode(relay,OUTPUT);



attachInterrupt(digitalPinToInterrupt(interruptPin),pinisr,FALLING);

  Serial1.begin(9600);
 SIM900.begin(9600);

 Serial1.listen (); delay(1000);
 
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
      client.println("GET /IoTProjects/EnergyMeter/upload.php?a=U HTTP/1.1");
      client.println("Host: projectsiot.xyz");
      client.println("Connection: close");
      client.println();
    }
    client.flush();
     client.stop();


delay(4000);
beep ();
units = 0;

 Serial1.listen (); delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
ct1 = analogRead(ct1Pin);
ct2 = analogRead(ct2Pin);
ct3 = analogRead(ct3Pin);
ct4 = analogRead(ct4Pin);

delay(50);
Serial.println("ct1 = "+String(ct1));
Serial.println("ct2 = "+String(ct2));
Serial.println("ct3 = "+String(ct3));
Serial.println("ct4 = "+String(ct4));
//Serial.println("difference..... = " +String(ct1-ct2));
//Serial.println("difference%%%%%% = " +String(-(ct2-ct1)));
Serial.println("=========================");
delay(500);

ct3 = (ct3/2)/100;
ct4 = (ct4/2)/100;

difference = ct1 - ct2;
Serial.println("difference = "+String(difference));

Serial.println("load-1 current= " +String(ct3));
Serial.println("load-2 current= " +String(ct4));
Serial.println();
Serial.println("*****************************************************");

if ((difference > 30) || (difference < -30))
{
  Serial.println("THEFT OCCURED......");
  flag =0;
  bypass = "Y";
  beep ();
 // digitalWrite(relay,LOW);
 digitalWrite(relay,LOW);
 delay(1000);
 
  sendsms("09676454550","BYPASS ALERT\n PLEASE CHECK");
}
else if (digitalRead(theft)==HIGH)
{
  Serial.println("tampering alert....");
  flag =0;
  tamper = "Y";
  beep ();
  digitalWrite(relay,LOW);
 delay(1000);
 
  sendsms("09676454550","TAMPERING ALERT\n PLEASE CHECK");
}
else if (digitalRead(magnet)==LOW)
{
  Serial.println("magnet alert....");
  flag =0;
  mag = "Y";
  digitalWrite(relay,LOW);
 delay(1000);
 beep ();
  
  sendsms("09676454550","MAGNETIC ALERT\n PLEASE CHECK");
}
else if(units == 25)
{
  Serial.println("50% consumed");
  flag =0;
  consumer = "A";
  delay(200);
  
  sendsms("08501889023","YOU HAVE CONSUMED 50%\n");
  
}

else if(units == 40)
{
  Serial.println("90% consumed");
  flag =0;
  consumer = "B";
  delay(200);
  sendsms("08501889023","YOU HAVE CONSUMED 90%\n");
}

else if(units == 50)
{
  Serial.println("50% consumed");
  flag =0;
  consumer = "C";
  delay(100);
  digitalWrite(relay,LOW);
  delay(1000);
  sendsms("08501889023","YOU HAVE CONSUMED 100%\nLOAD -- OFF");
}
else if (!(punits == preunits))
{
  preunits = punits;
  flag = 0;
}
else
{
  flag ++;
  digitalWrite(relay,HIGH);
  delay(300);
  Serial.println("falg = "+String(flag));
  consumer = "0";
  tamper = "N";
  mag = "N";
  bypass = "N";
}
if (flag < 2)
{
  Serial.println("updating to iot");
   iot = A + String(units) + "&b=" + consumer +"&c=" + tamper + "&d=" + mag + "&e=" + bypass + "&f=" + String(ct3) + "&g=" + String(ct4) + "&h=0" +  Z;

        Serial.println(iot);
        sndit ();
}
}//loop

void pinisr ()
{
  
  Serial.println("interrupttttttttttt");
  units++;
  punits = units;
  Serial.println("units = "+String(units));
 }

void sndit ()
{
detachInterrupt(digitalPinToInterrupt(interruptPin));

//Serial1.listen(); delay(1000);

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

    client.println( A + String(units) + "&b=" + consumer +"&c=" + tamper + "&d=" + mag + "&e=" + bypass + "&f=" + String(ct3) + "&g=" + String(ct4) + "&h=0" +  Z);

    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
    iot = "\0";
  }
attachInterrupt(digitalPinToInterrupt(interruptPin),pinisr,FALLING);
}
void sendsms (String bb , String qq)
  {
    Serial.println("sending sms : "+qq);
    SIM900.listen();
    delay(1000);
   
     SIM900.print("AT\r\n");
        SIM900.print('\n');
        ShowSerialData();
        delay(1000);
        SIM900.print("ATE1\r\n");
        ShowSerialData();
        delay(1000);
       SIM900.print("AT&W\r\n");
        SIM900.print('\n');
        ShowSerialData();
        delay(1000);
        SIM900.print("AT+CMGF=1\r\n");
        ShowSerialData();
        delay(1000);
        SIM900.print("AT+CNMI=2,2,0,0,0\r\n");
        ShowSerialData();
        delay(2000);
       // Serial.print("AT+CSMP=17,167,0,0\n");
       // delay(2000); 
        SIM900.print("AT+CMGS=\""+bb+"\"\r");
        ShowSerialData();
       // Serial.print('"');
      //Serial.print("9014449822");
      //Serial.print('"');
      //Serial.print('\r');
        SIM900.print('\n');
        delay(1000);
        SIM900.print(qq);
     SIM900.print('\r');
      SIM900.print('\n');
      
     delay(1000);
       SIM900.print((char)26);
       ShowSerialData();
        delay(2000);
        ShowSerialData();
        delay(500);
        beep1 ();
        Serial1.listen();
    delay(1000);
   }
void ShowSerialData()
{
  while(SIM900.available()!=0)
    Serial.write(char (SIM900.read()));
}

