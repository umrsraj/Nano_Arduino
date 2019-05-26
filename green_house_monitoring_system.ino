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
#define soilPin A2
#define humPin A1
#define ldrPin A3
#define buzzer 8
#define relay1 9
#define relay2 10

float temp1=0.0;
unsigned temp2 = 0;
int soil  = 0;
int hum = 0;
int ldr = 0;
String L = " ";
String S = " ";
String H = " ";

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

char server[] = "projectsiot.xyz";
char server1[] = "sms.scubedigi.com";

String A = "GET /IoTProjects/GreenHouse/upload.php?a=";
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
pinMode(soilPin,INPUT);
pinMode(humPin,INPUT);
pinMode(ldrPin,INPUT);
pinMode(buzzer,OUTPUT);
pinMode(relay1,OUTPUT);
pinMode(relay2,OUTPUT);


 lcd.clear();
lcd.setCursor(0,0);
lcd.print("GREEN HOUSE      ");
lcd.setCursor(0,1);
lcd.print("MONITORING SYSTEM");
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
      client.println("GET /IoTProjects/GreenHouse/upload.php?a=U&b=N&c=N HTTP/1.1");
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

temp2 = analogRead(temp); //read data from analog pin A1. 
float V=temp2*(5/(1023.00)); //conversion of analog voltage to digital voltage. 
  temp1=V*100; //temperature in centigrade scale. 

Serial.print("temperature is = "); Serial.println(temp1);
delay(50);

ldr = analogRead(ldrPin);
delay(50);
soil = analogRead(soilPin);
delay(50);
hum = analogRead(humPin);
delay(50);

Serial.println("soil = "+String(soil));
Serial.println("ldr = "+String(ldr));
Serial.println("hum = "+String(hum));


if (temp1 > 55)
{
   lcdstring(0,0,"T: "+String(temp1));
  lcdstring(9,0,"H: "+ String(H));
  lcdstring(0,1,"S: "+ String(S));
  lcdstring(9,1,"L: "+ String(L));
  delay(20);
//msg = p + "HIGH%20TEMPERATURE%20ALERT%0AT:"+String(temp1);
//sendmsg();
  
  digitalWrite(relay1,HIGH);
  delay(2000);
}
else
{
  delay(100);
  digitalWrite(relay1,LOW);
  delay(200);
}
 if (soil < 500)
{
  S = "Y";
   lcdstring(0,0,"T: "+String(temp1));
  lcdstring(9,0,"H: "+ String(H));
  lcdstring(0,1,"S: "+ String(S));
  lcdstring(9,1,"L: "+ String(L));
  delay(20);
//msg = p + "SOIOL%20WET%0AMOTOR%20OFF";
//sendmsg();
  digitalWrite(relay2,LOW);
  delay(2000);
}

else
{
  S = "N";
  delay(100);
  digitalWrite(relay2,HIGH);
  delay(300);
}
 if (hum < 700)
{
  H = "Y";
   lcdstring(0,0,"T: "+String(temp1));
  lcdstring(9,0,"H: "+ String(H));
  lcdstring(0,1,"S: "+ String(S));
  lcdstring(9,1,"L: "+ String(L));
  delay(20);
  delay(2000);
}
else
{
  H = "N";
}
if (ldr < 1000)
{
  Serial.println("DAY TIME DETECTED");
  L = "D";
}
else
{
  Serial.println("NIGHT TIME DETECTED");
  L = "N";  
}

if ((temp1 < 55)&&(H == "N")&&(S == "N"))
{
  Serial.println("system is normal");
  
  lcd.clear();
  lcdstring(0,0,"T: "+String(temp1));
  lcdstring(9,0,"H: "+ String(H));
  lcdstring(0,1,"S: "+ String(S));
  lcdstring(9,1,"L: "+ String(L));
  delay(100);
  iot  = A + String(temp1) + "&b=" + L +"&c=" + H + "&d=" + S + Z;
  sndit();
}
else
{
  
  iot  = A + String(temp1) + "&b=" + L +"&c=" + H + "&d=" + S + Z;
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
