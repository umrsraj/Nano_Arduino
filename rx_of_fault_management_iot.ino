
/*
 * FAULT MANAGEMENT SYSTEM
 * 
 * http://projectsiot.xyz/IoTProjects/CoalMines/view.php
 * 
 * http://projectsiot.xyz/IoTProjects/CoalMines/upload.php?a=52&b=Y&c=Y&d=Y
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
SoftwareSerial SIM900(2,3);

LiquidCrystal lcd (4,5,6,7,8,9);

#define buzzer 10

float temp1=0.0;
String read_msg = "\0";
int i  = 0;
String TT = "\0";

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
    lcd.print("IOT BSD FAULT     ");
    lcd.setCursor(0,1);
    lcd.print("   MANAGEMNET   ");
  delay(3000);  
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" PLATFORM WITH");
    lcd.setCursor(0,1);
    lcd.print(" PROTECTION AT  ");
  delay(3000);
   lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   COAL MINES     ");
    lcd.setCursor(0,1);
    lcd.print("..................");
  delay(3000);
}

char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";
char server1[] = "sms.scubedigi.com";

String A = "GET /IoTProjects/CoalMines/upload.php?a=";
String Z = " HTTP/1.1";
String iot = "\0";
String bulk = "\0";

String T = "N";
String H = "N";
String G = "N";
String W = "N";

// Initialize the Ethernet client object
WiFiEspClient client;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
lcd.begin(16,2);

 Serial.println("power up");
showprojectname ();
SIM900.begin(9600);
pinMode(buzzer,OUTPUT);


  // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);

 
Serial1.listen();
delay(1000);
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

lcd.clear ();
lcd.setCursor(0,0);
lcd.print("server int.........");
lcd.setCursor(0,1);
lcd.print("..........................");
delay(100);
    Serial.println(F("sending data ---1 "));
    Serial.println(F("Starting connection to server..."));
    // if you get a connection, report back via serial
    if (client.connect(server, 80)) {
      Serial.println(F("Connected to server"));
      // Make a HTTP request
      //client.println("GET /IoTProjects/HealthMonitoring/statusupload.php?a=U&b=0&c=E&d=L HTTP/1.1");
    Serial.println(A+'U'+Z);
    client.println(A+'U'+Z);
  
      client.println("Host: projectsiot.xyz");
      client.println("Connection: close");
      client.println();
    }
    client.flush();
     client.stop();

Serial.println(F("PLEASE SHOW CARD "));

lcd.clear ();
lcd.setCursor(0,0);
lcd.print("server int Done     .");
lcd.setCursor(0,1);
lcd.print("..........................");
delay(4000);
}

void loop() {


SIM900.listen();
delay(1000);

ShowSerialData ();

  if (read_msg.indexOf("TEMP")!=(-1))
 {
   read_msg = "\0";
   Serial.println("temperature alert*****");
   lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TEMPERATURE ALERT  ");
    lcd.setCursor(0,1);
    lcd.print("PLEASE CHECK.....");
    delay(100);
    SIM900.println("GAS ALERT\r\n");
   beep ();
T = "Y";   
i = read_msg.indexOf("=");
TT = read_msg.substring(i,(i+4));
Serial.println("TT =" +TT);
T=TT;
T = "Y";
sndit ();
delay(3000); 
 }
 else
 {
  T = "N";
 }
 if (read_msg.indexOf("GAS")!=(-1))
 {
   read_msg = "\0";
   Serial.println("gas alert*****");
   lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   GAS ALERT    ");
    lcd.setCursor(0,1);
    lcd.print("PLEASE CHECK.....");
    delay(100);
    SIM900.println("GAS ALERT\r\n");
   beep ();
G = "Y"; 
sndit (); 
delay(3000); 
 }
 else
 {
   G = "N";
 }
 if (read_msg.indexOf("HUM")!=(-1))
 {
   read_msg = "\0";
   Serial.println("HUMIDITY alert*****");
   lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" HUMIDITY ALERT  ");
    lcd.setCursor(0,1);
    lcd.print("PLEASE CHECK.....");
    delay(100);
   beep ();
H = "Y";  
sndit ();
delay(3000); 
 }
 else
 {
  H = "N";
 }
 if (read_msg.indexOf("WAT")!=(-1))
 {
   read_msg = "\0";
   Serial.println("Water alert*****");
   lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" WATER DETECTED ");
    lcd.setCursor(0,1);
    lcd.print("PLEASE CHECK.....");
    delay(100);
   beep ();
W = "Y"; 
sndit ();
delay(3000); 
 }
 else
 {
  W = "N";
 }
if ((W == "N")&&(G == "N")&&(H == "N"))
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("SYSTEM IS NORMAL   ");
lcd.setCursor(0,1);
lcd.print("....................");
delay(100);
}
iot = A;
 // Serial.print(F("iot = ")); Serial.println(iot);
iot += T;
  //Serial.print(F("iot = ")); Serial.println(iot);
iot += "&b=";
  //Serial.print(F("iot = ")); Serial.println(iot);
iot += H;
  //Serial.print(F("iot = ")); Serial.println(iot);
iot += "&c=";
//Serial.print(F("iot = ")); Serial.println(iot);
iot += G;
//Serial.print(F("iot = ")); Serial.println(iot);
iot += "&d=";
//Serial.print(F("iot = ")); Serial.println(iot);
iot += W;
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
Serial1.listen ();
delay(1000);
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

    client.println(A+T+"&b="+H+"&c="+G+"&d="+W+Z);

    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
    iot = "\0";
  }

}

void ShowSerialData()
{
  Serial.println("in showserial data function............");
  while(SIM900.available()!=0)
   read_msg = SIM900.readString();
   if (read_msg != "\0")
   {
  Serial.println("read_msg is = "); Serial.println(read_msg);
   delay(1);
   }
}
