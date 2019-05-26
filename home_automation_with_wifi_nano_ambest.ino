/*
 WiFiEsp example: WebClient

 This sketch connects to google website using an ESP8266 module to
 perform a simple web search.

 For more details see: http://yaab-arduino.blogspot.com/p/wifiesp-example-client.html
*/

#include "WiFiEsp.h"
#include <LiquidCrystal.h>

#define relay1 8
#define relay2 9


// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif

char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";
String Readdata;

LiquidCrystal lcd(2,3,4,5,6,7);

// Initialize the Ethernet client object
WiFiEspClient client;

void setup()
{
  // initialize serial for debugging
  Serial.begin(9600);
  // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);
lcd.begin(16,2);

pinMode(relay1,OUTPUT);
pinMode(relay2,OUTPUT);

lcd.clear ();
lcd.setCursor (0,0);
lcd.print("   IOT  BASED   ");
lcd.setCursor (0,1);
lcd.print("HOME AUTOMATION");
delay(2000);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }


  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    
lcd.clear ();
lcd.setCursor (0,0);
lcd.print("connecting to");
lcd.setCursor (0,1);
lcd.print(ssid);
delay(20);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  // you're connected now, so print out the data
  Serial.println("You're connected to the network");
  
  printWifiStatus();

lcd.clear ();
lcd.setCursor (0,0);
lcd.print("connected to");
lcd.setCursor (0,1);
lcd.print("   network  ");
delay(200);

  Serial.println();
if (client.connect(server, 80)) {
    Serial.println("Connected to server");
    Serial.println(client.connected());
}
lcd.clear ();
lcd.setCursor (0,0);
lcd.print("LOAD 1:");
lcd.setCursor (0,1);
lcd.print("LOAD 2:");
delay(200);
}

void loop()
{
  //lcd.clear ();
 Serial.println();
 Serial.println("Starting connection to server...");
 client.println("GET /IoTProjects/HomeAutomation/updatevalues.php HTTP/1.1");
 client.println("Host: projectsiot.xyz");
 client.println();

 while (client.available())
 {
              Readdata = client.readString();
              Serial.println(Readdata);
 }
Serial.println(F("data"));
Serial.println(Readdata[Readdata.indexOf("sts0")+7]);
Serial.println(Readdata[Readdata.indexOf("sts1")+7]);
Serial.println();
Serial.println();
Serial.println(client.connected());

if (Readdata[Readdata.indexOf("sts0")+7] == '1')
{
 Serial.println(F("*** load 1 on *****"));
  digitalWrite(relay1,HIGH);
  delay(1000);
lcd.setCursor (0,0);
lcd.print("LOAD 1:");
lcd.setCursor (7,0);
lcd.print("1");
delay(200);
}

 if (Readdata[Readdata.indexOf("sts0")+7] == '0')
{
  
 Serial.println(F("*** load 1 off *****"));
  digitalWrite(relay1,LOW);
  delay(1000);
lcd.setCursor (0,0);
lcd.print("LOAD 1:");
lcd.setCursor (7,0);
lcd.print("0");
delay(2000);
}
 if (Readdata[Readdata.indexOf("sts1")+7] == '1')
{
  
 Serial.println(F("*** load 2 on *****"));
  digitalWrite(relay2,HIGH);
  delay(1000);
lcd.setCursor (0,1);
lcd.print("LOAD 2:");
lcd.setCursor (7,1);
lcd.print("1");
delay(2000);
}

 if (Readdata[Readdata.indexOf("sts1")+7] == '0')
{
  
 Serial.println(F("*** load 2 off *****"));
  digitalWrite(relay2,LOW);
  delay(1000);
lcd.setCursor (0,1);
lcd.print("LOAD 2:");
lcd.setCursor (7,1);
lcd.print("0");
delay(2000);
}


if (!client.connected()) {
if (client.connect(server, 80)) {
    Serial.println("Connected to server");
    Serial.println(client.connected());
}
  }
}


void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
