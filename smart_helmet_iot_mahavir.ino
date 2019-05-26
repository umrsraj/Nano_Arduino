
#include "WiFiEsp.h"
#include<String.h>

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
//SoftwareSerial SIM900(2, 3); // RX, TX
#endif

char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";
char server1[] = "sms.scubedigi.com";


String read_msg = "\0";


String ALC = "N";
String HEL = "N";
String OBS = "N";
String ACCI = "N";
String LOC = "%20";

String A = "GET /IoTProjects/SmartHelmet1/upload.php?a=";
String Z = " HTTP/1.1";
String msg = "GET /api.php?username=Mydreamacd&password=Mydrm123&to=";
String bulk = "\0";
String iot = "\0";

// Initialize the Ethernet client object
WiFiEspClient client;

#include <LiquidCrystal.h>
LiquidCrystal lcd (2,3,4,5,6,7);

#define buzzer 11
#define relay 10
#define ldr A1
#define memsPin A4
#define ir A2
#define led A3
#define limit A0
#define pin 8

int mems = 0;
void beep ()
{
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(100);
}

 void lcdstring (unsigned int a, unsigned int b, String data)
 {
  lcd.setCursor(a,b);
  lcd.print(data);
 }

void setup()
{
  // initialize serial for debugging
  Serial.begin(9600);
Serial.println(F("BYKE SECTION OF *** SMART HELMET ***"));
//SIM900.begin(9600);


lcd.begin(16,2);

  lcd.setCursor(4,0); 
   lcd.print("WELCOME");
   lcd.setCursor(0,1); 
   lcd.print(" ................ ");

   lcd.clear();
        lcd.setCursor(2,0);
        lcd.print("SMART HELMET ");
        lcd.setCursor(0,1);
         lcd.print("................. ");
         delay(2000);
        //  lcd.clear();
pinMode(buzzer,OUTPUT);
pinMode(relay,OUTPUT);
pinMode(led,OUTPUT);
pinMode(ldr,INPUT);
pinMode(memsPin,INPUT);
pinMode(ir,INPUT);
pinMode(limit,INPUT);
pinMode(pin,OUTPUT);
digitalWrite(pin,HIGH);
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

void loop()
{
mems = analogRead(memsPin);
Serial.println("mems = "+String(mems));

//lcd.setCursor(0,1);
//lcd.print("mems="+String(mems));
//delay(1000);
  
int ldr_read1=analogRead(ldr);
Serial.print("LDR:");
    Serial.print("\t");
  Serial.println(ldr_read1);
  delay(10);
  
  if(ldr_read1<400){
digitalWrite(led,LOW);
    delay(100);
  }
  if(ldr_read1>400){
    
digitalWrite(led,HIGH);
    delay(100);
   
  }

 

 if (mems < 400)
{
  ACCI = "Y";
LOC = "%20";
digitalWrite(pin,LOW);
  Serial.println("accident occured......");
  digitalWrite(relay,0);
  digitalWrite(relay,0);
    delay(100);
    lcd.setCursor(0,0);
    lcd.print("ACCIDENT ALERT  ");
    lcd.setCursor(0,1);
    lcd.print("PLEASE CHECK     ");
    beep();
    delay(1000);
    
digitalWrite(pin,HIGH);
}
else
{
 
  ACCI = "N";
  LOC = "%20";
}
if (digitalRead(limit)==HIGH)
{
 OBS = "Y";
LOC ="%20";
  Serial.println("NO HELMET    ");
  digitalWrite(relay,0);
  digitalWrite(relay,0);
    delay(100);
    lcd.setCursor(0,0);
    lcd.print("NO HELMET      ");
    lcd.setCursor(0,1);
    lcd.print("PLEASE CHECK   ");
    beep();
    delay(1000);

}
if (digitalRead(ir)==HIGH)
{
 OBS = "Y";
LOC ="%20";
  Serial.println("OBSTACLE occured......");
  digitalWrite(relay,0);
  digitalWrite(relay,0);
    delay(100);
    lcd.setCursor(0,0);
    lcd.print("OBSTACLE ALERT  ");
    lcd.setCursor(0,1);
    lcd.print("PLEASE CHECK   ");
    beep();
    delay(1000);

}
  
else
{
  
 OBS = "N";
 LOC = "%20";
}
if ((digitalRead(ir)==LOW)&&(mems > 400)&&(digitalRead(limit)==LOW))
{
  Serial.println("system is normal");
  lcdstring(0,0,"SYSTEM IS NORMAL   ");
  lcdstring(0,1,"VEHICLE MOVING      ");
  
  digitalWrite(relay,1);
  delay(100);
  
 read_msg = "\0";
}


 iot = A +ALC + "&b=" + OBS + "&c=" + ACCI + "&d=" + HEL + Z;

Serial1.listen (); delay(500);

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

    //client.println("GET /IoTProjects/TollBooth/tollbooth.php?a=A&b=5&c=6&d=3 HTTP/1.1");

    client.println( A +ALC + "&b=" + OBS + "&c=" + ACCI + "&d=" + HEL + Z);

    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
    iot = "\0"; 


  }  

   
}// loop
/*
void ShowSerialData()
{
  SIM900.listen();
  delay(200);
  while(SIM900.available()!=0)
   read_msg = SIM900.readString();
 
  Serial.println("read_msg is = "); Serial.println(read_msg);

   delay(1);
}
*/
