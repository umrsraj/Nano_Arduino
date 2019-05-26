
#include "WiFiEsp.h"
#include<String.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd (2,3,4,5,6,7);

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif


#define button 8
#define buzzer 9
#define irsensor 10



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
char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";
String A = "GET /IoTProjects/SuperMarket/upload.php?a=";
String Z = " HTTP/1.1";
String iot = "\0";
WiFiEspClient client;

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


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

Serial.println("power up");
pinMode(buzzer,OUTPUT);
pinMode(irsensor,INPUT);
pinMode(button,INPUT);




lcd.begin(16,2);
lcd.clear();
lcdstring(0,0,"SMART TROLLY FOR");
lcdstring(0,1,"   MEGA MALLS   ");
delay(3000);


  Serial1.begin(9600);

 Serial1.listen (); delay(1000);
 
   // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println(F("WiFi shield not present"));
    // don't continue
    //while (true);
  }
lcd.clear ();
lcd.setCursor(0,0);
lcd.print("CONNECTING TO");
lcd.setCursor(0,1);
lcd.print(ssid);
delay(300);
  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print(F("Attempting to connect to WPA SSID: "));
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }
lcd.clear ();
lcd.setCursor(0,0);
lcd.print("CONNECTED TO");
lcd.setCursor(0,1);
lcd.print("WI - FI ");
delay(2000);
  // you're connected now, so print out the data
  Serial.println(F("You're connected to the network"));

lcd.clear ();
lcd.setCursor(0,0);
lcd.print("server init.   ");
lcd.setCursor(0,1);
lcd.print("please wait    ");
delay(2000);
  
    Serial.println(F("sending data ---1 "));
    Serial.println(F("Starting connection to server..."));
    // if you get a connection, report back via serial
    if (client.connect(server, 80)) {
      Serial.println(F("Connected to server"));
      // Make a HTTP request
      client.println("GET /IoTProjects/SuperMarket/upload.php?a=U HTTP/1.1");
      client.println("Host: projectsiot.xyz");
      client.println("Connection: close");
      client.println();
    }
    client.flush();
     client.stop();
     
lcd.clear ();
lcd.setCursor(0,0);
lcd.print("server init.   ");
lcd.setCursor(0,1);
lcd.print("done             ");
delay(4000);

Serial.println(F("PLEASE SHOW CARD "));

 Serial1.listen (); delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
lcd.setCursor(0, 0);
  lcd.print("Please show card          ");
  lcd.setCursor(0, 1);
  lcd.print("                          ");

  //Serial.println("ir sensor = " + String(digitalRead(irsensor)));
/*
if(digitalRead(irsensor) == HIGH)
{
  beep ();
}
*/
if (digitalRead(button) == HIGH)
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
else if (input[10]=='A')
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
else if (input[10]=='8')
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
else if (input[10]=='1')
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
else if (input[10]=='7')
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
/*
for (q = 0; q <60; q++)
{
 if( items[no] == '$')
 {
  Serial.println("$ found-removing null");
  items.remove(no, 1);
 }
}//for loop
*/

  
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
else if (input[10]=='A')
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
else if (input[10]=='8')
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
else if (input[10]=='1')
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

else if (input[10]=='7')
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

else if (input[10]=='B')
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
    beep ();
    delay(1000);
}
else if (amount >= cost)
{

lcd.clear();
 Serial.print(F("amount = ")); Serial.println(amount);
  amount = amount - cost;
  Serial.print(F("cost = ")); Serial.println(cost);
  Serial.print(F("amount****** = ")); Serial.println(amount);
  
if (amount <101)
{
    lcd.setCursor(0,1);
    lcd.print("    LOW BALENCE  ");      
}  
 

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
iot = A +'A' + "&b=" + items + "&c=" + String(cost) + "&d=" + String (amount) + Z;
Serial.println(iot);
        sndit ();
items = "%20";
  cost = 0;
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



}//loop

void sndit ()
{

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

    client.println(A +'A' + "&b=" + items + "&c=" + String(cost) + "&d=" + String (amount) + Z);

    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
    iot = "\0";
  }
}
void lcdstring(int a, int b, String data)
{
  lcd.setCursor(a,b);
  lcd.print(data);
}

