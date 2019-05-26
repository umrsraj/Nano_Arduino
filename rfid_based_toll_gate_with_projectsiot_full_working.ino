/*
 WiFiEsp example: WebClient

 This sketch connects to google website using an ESP8266 module to
 perform a simple web search.

 For more details see: http://yaab-arduino.blogspot.com/p/wifiesp-example-client.html
*/
// http://projectsiot.xyz/IoTProjects/TollBooth/tollbooth.php?a=A&b=5&c=6&d=3
#include "WiFiEsp.h"
#include<String.h>
#include <LiquidCrystal.h>

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif

LiquidCrystal lcd (A5,A4,A3,A2,A1,A0);

#define m11 4
#define m12 5
#define buzzer 6
#define gled 7
#define rled 8
 
int count1 = 0;                                          // count = 0
char input[12];

 int amount = 200;
 int amount1 = 200;
void beep ()
{
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(100);
}

void forward ()
{
  digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);
  delay(50);
}
void backward ()
{
  digitalWrite(m12,HIGH);
  digitalWrite(m11,LOW);
  delay(50);
}

void stop_motor ()
{
  digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
  delay(50);
}

char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";
String A = "GET /IoTProjects/TollBooth/tollbooth.php?a=";
String B = "&b=";
String C = "&c=";
String D = "&d=";
String Z = " HTTP/1.1";
String str;

unsigned int k = 0;
unsigned int g = 0;

// Initialize the Ethernet client object
WiFiEspClient client;

void setup()
{
  // initialize serial for debugging
  Serial.begin(9600);
  lcd.begin(16,2);
lcd.clear();
lcd.setCursor(0,0);
        lcd.print("*** TOOLBOOTH ***** ");
        lcd.setCursor( 0,1);
         lcd.print("     SYSTEM     ");
         delay(1000);

         pinMode(buzzer,OUTPUT);
 pinMode(m11,OUTPUT);
 pinMode(m12,OUTPUT);
 pinMode(gled,OUTPUT);
 pinMode(rled,OUTPUT);

 digitalWrite(rled,LOW);
digitalWrite(gled,LOW);
  
  // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);

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
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  // you're connected now, so print out the data
  Serial.println("You're connected to the network");
  
  printWifiStatus();
Serial.println("sending data ---1 ");
  Serial.println();
  Serial.println("Starting connection to server...");
  // if you get a connection, report back via serial
  if (client.connect(server, 80)) {
    Serial.println("Connected to server");
    // Make a HTTP request
    client.println("GET /IoTProjects/TollBooth/tollbooth.php?a=U&b=0&c=0&d=0 HTTP/1.1");
    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
  }
}

void loop()
{

  R:
  lcd.setCursor(0,0);
    lcd.print("Please show card          ");
   lcd.setCursor(0,1);
    lcd.print("                          ");
   
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

if (input[10]=='3')
{

  lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("  CARD1 MATCHED   ");
  
  input[10]='\0';

if (amount < 5)
{
  
digitalWrite(gled,LOW);
digitalWrite(rled,HIGH);

   lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("UR BALENCE IS 0");
       lcd.setCursor(0,1);
    lcd.print(" PLZ RECHARGE  ");
    delay(2000);
    
 str = A+"A"+B+"0"+C+String(amount)+D+"N"+Z;
  sndit (); 
   
goto R;
}

else if (amount > 49)
{


digitalWrite(rled,LOW);
digitalWrite(gled,HIGH);
amount = amount - 50 ;
Serial.print("remaining bal == "); Serial.println(amount);

    if (amount < 51)
{

    lcd.setCursor(4,1);
    lcd.print("LOW BALENCE");
      
}
str = A+"A"+B+"50"+C+String(amount)+D+"Y"+Z;
  sndit ();  
delay(500);

  lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("  CARD1 MATCHED   ");  
    lcd.setCursor(0,1);
    lcd.print("RE BAL:");
       lcd.setCursor(8,1);
    lcd.print(amount);
delay(500);
forward ();
delay(2000);
stop_motor ();
delay(1000);
backward ();
delay(2000);
stop_motor();
    delay(1500);
}

} // 1st card
else if (input[10]=='4')
{
  

  lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("  CARD2 MATCHED   ");
    
  input[10]='\0';

if (amount1 < 5)
{
  
digitalWrite(gled,LOW);
digitalWrite(rled,HIGH);

   lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("UR BALENCE IS 0");
       lcd.setCursor(0,1);
    lcd.print(" PLZ RECHARGE  ");
    delay(2000);
   
str = A+"B"+B+"0"+C+String(amount1)+D+"N"+Z;
  sndit ();   
goto R;
}

else if (amount1 > 49)
{

digitalWrite(rled,LOW);
digitalWrite(gled,HIGH);

amount1 = amount1 - 50 ;
Serial.print("remaining bal == "); Serial.println(amount1);
    if (amount1 < 51)
{

    lcd.setCursor(4,1);
    lcd.print("LOW BALENCE");
      
}
str = A+"B"+B+"50"+C+String(amount1)+D+"Y"+Z;
  sndit ();   
delay(500);

  lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("  CARD-2 MATCHED   ");  
    lcd.setCursor(0,1);
    lcd.print("RE BAL:");
       lcd.setCursor(8,1);
    lcd.print(amount1);
delay(500);
forward ();
delay(2000);
stop_motor ();
delay(1000);
backward ();
delay(2000);
stop_motor();
    delay(1500);
}

} // 2nd card

else
{
digitalWrite(gled,LOW);
digitalWrite(rled,HIGH);
   lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("  INVALID CARD  ");
    delay(1600);
    lcd.setCursor(0,1);
    lcd.print("***PLZ CHECK***");
    beep  ();
    delay(1700);

str = A+"H"+B+"0"+C+"0"+D+"N"+Z;
  sndit (); 
delay(500);

}
   }

  /*
  delay(2000);
  k = k + 50;
  str = A+"A"+B+String(k)+C+String(g)+D+"Y"+Z;
  sndit ();
  delay(2000);
  k = k + 10;
  str = A+"B"+B+String(k)+C+String(g)+D+"Y"+Z;
  sndit ();
  delay(2000);
  str = A+"C"+B+String(k)+C+String(g)+D+"Y"+Z;
  sndit ();
  */
}
void sndit ()
{

Serial.print("str = "); Serial.println(str);

  // if the server's disconnected, stop the client
  if (!client.connected()) {
    Serial.println();
    Serial.println("Disconnecting from server...");
    client.stop();

    // do nothing forevermore
    //while (true);
  }
  client.flush();
   client.stop();
for(int x = 0; x<2; x++)
{
  delay(1000);
  Serial.println(x);
}
    Serial.println();
  Serial.println("Starting connection to server...");
  // if you get a connection, report back via serial
  if (client.connect(server, 80)) {
    Serial.println("Connected to server");
    // Make a HTTP request
    
    //client.println("GET /IoTProjects/TollBooth/tollbooth.php?a=A&b=5&c=6&d=3 HTTP/1.1");
   
  client.println(str);
    
    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
    
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
