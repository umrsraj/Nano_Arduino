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

LiquidCrystal lcd (2,3,4,5,6,7);

#define temp A0
#define smokePin A2
#define vibPin A1
#define memsPin A3
#define trigPin 8
#define echoPin 9


long duration, distance,duration1,distance1;

float temp1=0.0;
unsigned temp2 = 0;
int smoke  = 0;
int mems = 0;
int vib = 0;

String S = "N";
String V = "N";
String M = "N";
String O = "N";


char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";

String A = "GET /IoTProjects/BlockBox/upload.php?a=";
String Z = " HTTP/1.1";
String iot = "\0";

// Initialize the Ethernet client object
WiFiEspClient client;

void setup()
{
  // initialize serial for debugging
  Serial.begin(9600);

  lcd.begin(16, 2);

pinMode(temp,INPUT);
pinMode(smokePin,INPUT);
pinMode(vibPin,INPUT);
pinMode(memsPin,INPUT);
pinMode(trigPin,OUTPUT);
pinMode(echoPin,INPUT);

 lcd.clear();
lcd.setCursor(0,0);
lcd.print("IOT BSD LOW END     ");
lcd.setCursor(0,1);
lcd.print("AUTOMOTIVE DRIVE");
delay(2500);

 lcd.clear();
lcd.setCursor(0,0);
lcd.print("RECORDER AS       ");
lcd.setCursor(0,1);
lcd.print("BLOCK BOX         ");
delay(2500);

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
      client.println("GET /IoTProjects/BlockBox/upload.php?a=U&b=N&c=N HTTP/1.1");
      client.println("Host: projectsiot.xyz");
      client.println("Connection: close");
      client.println();
    }
    client.flush();
     client.stop();

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
S="N";
V="N";
M="N";
O="N";
digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
delay(50);
            
 if(distance>220)
 {
  distance=220;
 }       
Serial.println("distance = "+String(distance));

 
temp2 = analogRead(temp); //read data from analog pin A1. 
float VV=temp2*(5/(1023.00)); //conversion of analog voltage to digital voltage. 
  temp1=VV*100; //temperature in centigrade scale. 

Serial.print("temperature is = "); Serial.println(temp1);
delay(50);

smoke = analogRead(smokePin);
delay(50);
vib = analogRead(vibPin);
delay(50);
mems = analogRead(memsPin);
delay(50);

Serial.println("smoke = "+String(smoke));
Serial.println("vib = "+String(vib));
Serial.println("mems = "+String(mems));


if (temp1 > 55)
{
Serial.println("temperature alert");
lcdstring(0,0,"                        ");
lcdstring(0,1,"                        ");

lcdstring(0,0,"TEMPERATURE ALERT     ");
lcdstring(0,1,"T: "+String(temp1));

delay(500);
} 
if (distance < 10)
{
  O = "Y";
 Serial.println("OBSTACLE alert");
 lcdstring(0,0,"                        ");
lcdstring(0,1,"                        ");

lcdstring(0,0,"OBSTACLE ALERT     ");
lcdstring(0,1,"PLEASE CHECK     ");
  iot  = A + String(temp1) + "&b=" + S +"&c=" + V + "&d=" + M + "&e=" + O + Z;
  sndit();
delay(5000);
}
else
{
  O = "N";
}
 if (smoke > 300)
{
  S = "Y";
 Serial.println("smoke alert");
 lcdstring(0,0,"                        ");
lcdstring(0,1,"                        ");

lcdstring(0,0,"SMOKE ALERT     ");
lcdstring(0,1,"PLEASE CHECK     ");
  iot  = A + String(temp1) + "&b=" + S +"&c=" + V + "&d=" + M + "&e=" + O + Z;
  sndit();
delay(5000);
}

else
{
  S = "N";
}
 if (vib < 700)
{
  V = "Y";
  Serial.println("vibration alert");
lcdstring(0,0,"                        ");
lcdstring(0,1,"                        ");

lcdstring(0,0,"VIBRATION ALERT     ");
lcdstring(0,1,"PLEASE CHECK       ");

  iot  = A + String(temp1) + "&b=" + S +"&c=" + V + "&d=" + M + "&e=" + O + Z;
  sndit();
delay(5000);
}
else
{
  V = "N";
}
if (mems < 400)
{
  Serial.println("crash detected");
  M= "Y";
  lcdstring(0,0,"                        ");
lcdstring(0,1,"                        ");

lcdstring(0,0,"CRASH ALERT     ");
lcdstring(0,1,"PLEASE CHECK       ");

  iot  = A + String(temp1) + "&b=" + S +"&c=" + V + "&d=" + M + "&e=" + O + Z;
  sndit();
delay(5000);
}
else
{
  M = "N";  
}

if ((temp1 < 55)&&(V == "N")&&(M == "N")&&(distance > 10))
{
  Serial.println("system is normal");
  
  lcd.clear();
  lcdstring(0,0,"T: "+String(temp1));
  lcdstring(9,0,"S: "+ String(S));
  lcdstring(0,1,"D: "+ String(distance));
  lcdstring(9,1,"C: "+ String(mems));
  delay(100);
  iot  = A + String(temp1) + "&b=" + S +"&c=" + V + "&d=" + M + "&e=" + O + Z;
  sndit();
}
else
{
  

  iot  = A + String(temp1) + "&b=" + S +"&c=" + V + "&d=" + M + "&e=" + O + Z;
  sndit();
}
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

}
 void lcdstring (unsigned int a, unsigned int b, String data)
 {
  lcd.setCursor(a,b);
  lcd.print(data);
 }
