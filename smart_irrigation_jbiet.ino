#include "WiFiEsp.h"

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif

char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "api.thingspeak.com";

// Initialize the Ethernet client object
WiFiEspClient client;


#include <LiquidCrystal.h>
#include <String.h>

LiquidCrystal lcd (2,3,4,5,6,7);
String A = "GET /update?api_key=494L6MKERWKK7H1W&field1=";
String Z = " HTTP/1.1";
String iot = "\0";;
#define temp A0
#define humPin A1
#define soilPin A2
#define ldr_sen A3
#define relay 8
#define buzzer 9


float temp1=0.0;
unsigned temp2 = 0;
int hum = 0;
int flag = 0;

String H = "\0";
String S = "\0";
String M = "\0";

void lcdstring(int a, int b, int data)
{
  lcd.setCursor(a,b);
  lcd.print(data);
}

void beep ()
{
  digitalWrite(buzzer,HIGH); delay(1000);
  digitalWrite(buzzer,LOW); delay(100);
}
void beep1 ()
{
  digitalWrite(buzzer,HIGH); delay(400);
  digitalWrite(buzzer,LOW); delay(200);
  digitalWrite(buzzer,HIGH); delay(400);
  digitalWrite(buzzer,LOW); delay(200);
  digitalWrite(buzzer,HIGH); delay(400);
  digitalWrite(buzzer,LOW); delay(100);
}
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
lcd.begin(16,2);

Serial.println("power up");
Serial1.begin(9600);

pinMode(temp,INPUT);
pinMode(humPin,INPUT);
pinMode(soilPin,INPUT);
pinMode(buzzer,OUTPUT);
pinMode(relay,OUTPUT);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("SMART IRRIGATION");
lcd.setCursor(0,1);
lcd.print(".................");
delay(2000);


  WiFi.init(&Serial1);
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    
lcd.clear();
lcd.setCursor(0,0);
lcd.print("WI-FI NOT CONNECTED");
lcd.setCursor(0,1);
lcd.print("PLEASE RESTART KIT");
delay(10);
    while (true);
  }

lcd.clear();
lcd.setCursor(0,0);
lcd.print("CONNECTING TO");
lcd.setCursor(0,1);
lcd.print(ssid);
delay(10);
  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }
lcd.clear();
lcd.setCursor(0,0);
lcd.print("CONNECTED TO");
lcd.setCursor(0,1);
lcd.print(ssid);
delay(10);
  // you're connected now, so print out the data
  Serial.println("You're connected to the network");

}

void loop() {
  // put your main code here, to run repeatedly:

H = "\0";
S = "\0";

temp2 = analogRead(temp);
float V=temp2*(5/(1023.00)); //conversion of analog voltage to digital voltage. 
  temp1=V*100; //temperature in centigrade scale. 

  temp1 = temp1 - 5;
Serial.print("temperature is = "); Serial.println(temp1);
delay(50);
hum = analogRead(humPin);
Serial.println("hum = "+String(hum));

int ldr=analogRead(ldr_sen);
Serial.print("LDR:");
Serial.println(ldr);

if(ldr>900){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("NIGHT MODE");
  delay(2000);
}
else{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("DAY MODE");
  delay(2000);
}
if (temp1 > 65)
{
  M = "0";
  flag = 0;
Serial.println("temperature alert");
  lcd.clear ();
 lcd.setCursor(0,0);
 lcd.print("TEPERATURE ALERT ");
 lcd.setCursor(0,1);
 lcd.print("T: "+String(temp1));
 digitalWrite(relay,LOW);
 delay(2000);
 beep ();
}
else if (hum < 600)
{
  H = "100";
  M = "0";
  flag = 0;
  Serial.println("humidity alert");
  lcd.clear ();
 lcd.setCursor(0,0);
 lcd.print("HUMIDITY ALERT ");
 lcd.setCursor(0,1);
 lcd.print("MOTOR OFF");
 digitalWrite(relay,LOW);
 delay(2000);
 beep ();
}//*/
else if (digitalRead(soilPin)==LOW)
{
  S = "100";
  M = "0";
  flag = 0;
  Serial.println("SOIL WET DETECTED");
  lcd.clear ();
 lcd.setCursor(0,0);
 lcd.print("SOIL WET      ");
 lcd.setCursor(0,1);
 lcd.print("MOTOR OFF");
 digitalWrite(relay,LOW);
 delay(2000);
 beep ();
}
else
{
  M = "100";
  lcd.clear ();
lcd.setCursor (0,0);
lcd.print ("T: "+String(temp1));
lcd.setCursor (0,1);
lcd.print ("H: L");
lcd.setCursor (8,1);
lcd.print ("S: L");
lcd.setCursor (0,1);
digitalWrite(relay,HIGH);
delay(100);
}
//flag = 3;
if (flag < 2)
{
  flag ++;
  iot =A+ String(temp1)+"field2="+H+"field3="+S+"field4="+M ;
  Serial.println("sending data to server");
  Serial.println("iot = "+ A+ String(temp1)+"&field2="+H+"&field3="+S+"&field4="+M);
  
lcd.clear();
lcd.setCursor(0,0);
lcd.print("sending data   ");
lcd.setCursor(0,1);
lcd.print("   to server   ");
  delay(6000);
  
  Serial.println("Starting connection to server...");
  // if you get a connection, report back via serial
  if (client.connect(server, 80)) {
    Serial.println("Connected to server");
    // Make a HTTP request
    client.println(A+ String(temp1)+"&field2="+H+"&field3="+S+"&field4="+M);
    client.println("Host: api.thingspeak.com");
    client.println("Connection: close");
    client.println();
  }

  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }
   if (!client.connected()) {
    Serial.println();
    Serial.println("Disconnecting from server...");
    client.stop();

  Serial.println("sending data to server");
lcd.clear();
lcd.setCursor(0,0);
lcd.print("  data  sent   ");
lcd.setCursor(0,1);
lcd.print("   to server   ");
  delay(10000);
  beep1 ();
}
}
}//loop
void sendserver (String rr)
{
  Serial.println("sending data to server");
  Serial.println("iot = "+String(iot));
  
lcd.clear();
lcd.setCursor(0,0);
lcd.print("sending data   ");
lcd.setCursor(0,1);
lcd.print("   to server   ");
  delay(6000);
  
  Serial.println("Starting connection to server...");
  // if you get a connection, report back via serial
  if (client.connect(server, 80)) {
    Serial.println("Connected to server");
    // Make a HTTP request
    client.println(rr);
    client.println("Host: api.thingspeak.com");
    client.println("Connection: close");
    client.println();
  }

  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }
   if (!client.connected()) {
    Serial.println();
    Serial.println("Disconnecting from server...");
    client.stop();

  Serial.println("sending data to server");
lcd.clear();
lcd.setCursor(0,0);
lcd.print("  data  sent   ");
lcd.setCursor(0,1);
lcd.print("   to server   ");
  delay(10000);
  beep1 ();
}
}
