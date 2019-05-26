/*
  WiFiEsp example: WebClient

  This sketch connects to google website using an ESP8266 module to
  perform a simple web search.

  For more details see: http://yaab-arduino.blogspot.com/p/wifiesp-example-client.html
*/

// http://sms.scubedigi.com/api.php?username=xxxx&password=xxxx&to=xxxxxxxxx&from=&message=xxxxxxxxxxxx
// http://projectsiot.xyz/IoTProjects/TollBooth/tollbooth.php?a=A&b=5&c=6&d=3
#include "WiFiEsp.h"
#include<String.h>
#include <LiquidCrystal.h>


// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif

LiquidCrystal lcd (2,3,4,5,6,7);

#define button 8
#define buzzer 9

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

String A = "GET /IoTProjects/SuperMarket/upload.php?a=";
String Z = " HTTP/1.1";
String msg = "GET /api.php?username=Mydreamacd&password=Mydre@m123&to=";
String bulk = "\0";
String iot = "\0";


String items = "\0";

int count1 = 0; 
// count = 0
char input[12];

int  q = 0;

const int meat = 500;
const int oil = 100;
const int pen = 20;
const int soap = 50;
const int toy = 250;

int no = 0;
int no1 = 0;

int s = 0;
int m = 0;
int p = 0;
int t = 0;
int o = 0;

int amount = 1000;
int cost = 0;


// Initialize the Ethernet client object
WiFiEspClient client;

void setup()
{
  // initialize serial for debugging
  Serial.begin(9600);

  lcd.begin(16, 2);

pinMode(button,INPUT);
pinMode(buzzer,OUTPUT);

 
lcd.clear();
lcdstring(0,0,"SMART TROLLY FOR");
lcdstring(0,1,"   MEGA MALLS   ");
delay(2000);

  

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
      client.println("GET /IoTProjects/SuperMarket/upload.php?a=U&b=&c=0&d=0 HTTP/1.1");
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

lcd.setCursor(0, 0);
  lcd.print("Please show card          ");
  lcd.setCursor(0, 1);
  lcd.print("                          ");

if (digitalRead(button) == LOW)
{

Serial.println("BUTTON -- PRESSED ");

lcd.setCursor(0, 0);
  lcd.print("Please show card          ");
  lcd.setCursor(0, 1);
  lcd.print("                          ");

 if (Serial.available())
  {
    count1 = 0;
    while (Serial.available() && count1 < 12)         // Read 12 characters and store them in input array
    {
      input[count1] = Serial.read();
      count1++;
      delay(5);
    }//WHILE
    //

    Serial.println(input);                           // Print RFID tag number
    Serial.print(F("input[10] is ")); Serial.println(input[10]);

 if (input[10]=='C')
    {

    if(m > 0)
    {
      m--;
      
    
    Serial.print("meat = "); Serial.println(m);
      cost = cost - meat;
   Serial.println(F("you REMOVED -- MEAT = 500 "));
   Serial.print(F("total bill = ")); Serial.println(cost);  
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   MEAT : 500   "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}
    }
else if (input[10]=='F')
    {
    
    if(o > 0)
    {
      o--;
      
    
    Serial.print("oil = "); Serial.println(o);

    cost = cost - oil;
    
   Serial.println(F("you REMOVED -- OIL = 100 "));
   Serial.print(F("total bill = ")); Serial.println(cost);  
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   OIL : 100    "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}
    }
else if (input[10]=='2')
    {

    if(p > 0)
    {
      p--;
      
    
    Serial.print("pen = "); Serial.println(p);
      
    cost = cost - pen;
    
   Serial.println(F("you REMOVED --  PEN = 20 "));
   Serial.print(F("total bill = ")); Serial.println(cost);  
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   PEN : 20    "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}
    }
else if (input[10]=='A')
    {

        if(t > 0)
    {
      t--;
      
    
    Serial.print("toy = "); Serial.println(t);
  
    cost = cost - toy;
    
   Serial.println(F("you REMOVED --  TOY = 250 "));
   Serial.print(F("total bill = ")); Serial.println(cost);  
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   TOY : 250    "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}
    }
else if (input[10]=='E')
    {

     if(s > 0)
    {
      s--;
      
    
    Serial.print("soap = "); Serial.println(s);
     
    cost = cost - soap;
    
   Serial.println(F("you REMOVED --  SOAP = 50 "));
   Serial.print(F("total bill = ")); Serial.println(cost);  
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   SOAP : 50    "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}
    }

  
}// serial available for button

}//if button
    
else if (Serial.available())
  {
    count1 = 0;
    while (Serial.available() && count1 < 12)         // Read 12 characters and store them in input array
    {
      input[count1] = Serial.read();
      count1++;
      delay(5);
    }//WHILE
    //

    Serial.println(input);                           // Print RFID tag number
    Serial.print(F("input[10] is ")); Serial.println(input[10]);

 if (input[10]=='C')
    {
      m++;
      Serial.print("meats = "); Serial.println(m);
      //items += "meat%2C";
      //Serial.print(F("items = ")); Serial.println(items);
      cost = cost + meat;
   Serial.println(F("you enterred -- MEAT = 500 "));
   Serial.print(F("total bill = ")); Serial.println(cost);  

   
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   MEAT : 500   "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}
else if (input[10]=='F')
    {
      
      o++;
      Serial.print("oil = "); Serial.println(o);
    //items += "oil%2C";
      //Serial.print(F("items = ")); Serial.println(items);
    cost = cost + oil;
    
   Serial.println(F("you enterred -- OIL = 100 "));
   Serial.print(F("total bill = ")); Serial.println(cost);  
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   OIL : 100    "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}
else if (input[10]=='2')
    {
      
    //   items += "pen%2C";
     // Serial.print(F("items = ")); Serial.println(items);
     
      p++;
      Serial.print("pens = "); Serial.println(p); 
    cost = cost + pen;
    
   Serial.println(F("you enterred --  PEN = 20 "));
   Serial.print(F("total bill = ")); Serial.println(cost);  
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   PEN : 20    "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}
else if (input[10]=='A')
    {
      
 //   items += "toy%2C";
 //     Serial.print(F("items = ")); Serial.println(items);
   
      t++;
      Serial.print("toys = "); Serial.println(t);   
    cost = cost + toy;
    
   Serial.println(F("you enterred --  TOY = 250 "));
   Serial.print(F("total bill = ")); Serial.println(cost);  
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   TOY : 250    "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}

else if (input[10]=='E')
    {
      
    //items += "soap%2C";
     Serial.print(F("items = ")); Serial.println(items);
      
      s++;
      Serial.print("soap = "); Serial.println(s);
    cost = cost + soap;
    
   Serial.println(F("you enterred --  SOAP = 50 "));
   Serial.print(F("total bill = ")); Serial.println(cost);  
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   SOAP : 50    "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}

else if (input[10]=='5')
{

lcd.clear();
lcdstring(0,0,"CARD  AUTHERIZED");
lcdstring(0,1,"****************");
delay(2000);

lcd.clear();
lcdstring(0,0,"FINAL BILL: ");
lcdstring(12,0,String(cost));
delay(2000);


 if ((amount < cost)|| (amount <= 0))
{
  lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("insufficient bal");
       lcd.setCursor(0,1);
    lcd.print(" PLZ RECHARGE  ");
    delay(1000);
    beep ();
}
else if (amount >= cost)
{

lcd.clear();

if (amount <101)
{
    lcd.setCursor(0,1);
    lcd.print("    LOW BALENCE  ");      
}  
  Serial.print(F("amount = ")); Serial.println(amount);
  amount = amount - cost;
  Serial.print(F("cost = ")); Serial.println(cost);
  Serial.print(F("amount****** = ")); Serial.println(amount);

lcdstring(0,0,"RE CARD BAL=");
lcdstring(12,0,String(amount));
delay(1000);
beep ();



}
if(m>0)
{
  items += "Meat-";
  items += String(m);
  items += "%2C";
}
if(s>0)
{
  items += "Soap-";
  items += String(s);
  items += "%2C";
}
if(p>0)
{
  items += "Pen-";
  items += String(p);
  items += "%2C";
}
if(o>0)
{
  items += "Oil-";
  items += String(o);
  items += "%2C";
}
if(t>0)
{
  items += "toy-";
  items += String(t);
  items += "%2C";
}
Serial.print("items = "); Serial.println(items);
iot = A +'A' + "&b=" + items + "&c=" + String(cost) + "&d=" + String (amount)+Z;
Serial.println(iot);
        sndit ();
}

else
{

  lcd.clear ();
  lcd.setCursor (0,0);
  lcd.print("INVALID CARD");
  lcd.setCursor (0,1); 
    lcd.print("PLEASE CHECK......");
    delay(200);
    beep ();
    delay(1000);
  
}
  } // Serial.available ()


 
} // loop
  
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

    client.println(A +'A' + "&b=" + items + "&c=" + String(cost) + "&d=" + String (amount)+Z);

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
