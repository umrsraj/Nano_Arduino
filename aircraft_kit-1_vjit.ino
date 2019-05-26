// http://projectsiot.xyz/IoTProjects/GreenHouse/upload.php?a=222&b=D&c=N&d=Y
// http://projectsiot.xyz/IoTProjects/GreenHouse/view.php



#include "WiFiEsp.h"
#include<String.h>
#include <LiquidCrystal.h>

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif
SoftwareSerial SIM900 (2,3);

long duration = 0;
unsigned int distance = 0;
String read_msg = "\0";
LiquidCrystal lcd (4,5,6,7,8,9);

#define buzzer A0

const int trigPin = 10;  //D6
const int echoPin = 11;  //D7



void beep ()
{
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(100);
}

char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "api.thingspeak.com";

String A = "GET /update?api_key=WXGBY1HU6V57QD3F&field1=";
String Z = " HTTP/1.1";
String iot = "\0";

int rr = 0;
int flag = 0;

// Initialize the Ethernet client object
WiFiEspClient client;

void setup()
{
  // initialize serial for debugging
  Serial.begin(9600);
SIM900.begin(9600);

  lcd.begin(16, 2);

pinMode(buzzer,OUTPUT);
pinMode(trigPin,OUTPUT);
pinMode(echoPin,INPUT);

 lcd.clear();
lcd.setCursor(0,0);
lcd.print("AIR CRAFT ANTI");
lcd.setCursor(0,1);
lcd.print("COLLISION SYSTEM");
delay(2500);

  lcd.clear();
lcd.setCursor(0,0);
lcd.print(" CONNECTING  TO ");
lcd.setCursor(0,1);
lcd.print(ssid);
delay(200);

  // initialize serial for ESP module
  Serial1.begin(9600);

  Serial1.listen ();delay(1000);
  
  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println(F("WiFi shield not present"));
    // don't continue
   // while (true);
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


Serial.println(F("PLEASE SHOW CARD "));
SIM900.listen ();delay(1000);
  
}

void loop()
{
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
Serial.print("Distance: ");
Serial.println(distance);

ShowSerialData ();
rr = 0;
if (distance < 20)
{
  rr = 100;
  flag = 0;
  Serial.println("air craft detected");
  SIM900.println("aircraft detected");
  delay(100);
   lcd.clear();
lcd.setCursor(0,0);
lcd.print("OBSTACLE/AIRCRAFT");
lcd.setCursor(0,1);
lcd.print("DETECTED       ");
beep ();
delay(1000);
iot = A + String(rr) + Z;
sndit ();

}
else if (read_msg.indexOf("aircraft")!=(-1))
{
  
  Serial.println("aircraft frm zigbee");
   lcd.clear();
lcd.setCursor(0,0);
lcd.print("OBSTACLE/AIRCRAFT");
lcd.setCursor(0,1);
lcd.print("detected           ");
beep ();
delay(2500);   
read_msg = "\0";
}
else
{
   lcd.clear();
lcd.setCursor(0,0);
lcd.print("Dist: "+String(distance));
lcd.setCursor(0,1);
lcd.print("SYSTEM IS NORMAL   ");
delay(200);
}
}// loop
  
void sndit ()
{
  Serial1.listen ();delay(500);
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
SIM900.listen ();delay(500);
}
 void lcdstring (unsigned int a, unsigned int b, String data)
 {
  lcd.setCursor(a,b);
  lcd.print(data);
 }
 void ShowSerialData()
{
  while(SIM900.available()!=0)
   read_msg = SIM900.readString();
   if (read_msg != '\0')
   {
  Serial.println("read_msg is = "); Serial.println(read_msg);
   }
   delay(1);
}
