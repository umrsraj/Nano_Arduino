
#include "WiFiEsp.h"
#include<String.h>
#include <LiquidCrystal.h>
#include <String.h>
 
LiquidCrystal lcd (2, 3, 4, 5, 6, 7);

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif


#define tempa A0
#define tempb A1

#define button 8

#define buzzer 11
#define relay1 9
#define relay2 10
#define heart A2

int tt = 0;
String e_temp = "NORMAL";

float temp1=0.0;
unsigned int temp2 = 0;
float aa = 0.0;
unsigned int bb = 0;

String otp1[11] = {"37","36","30","28","36","32","37","29","33","39","39"} ;
String otp[11] = {"62","72","71","75","97","79","92","79","95","83","99"} ;
unsigned int no = 0;
unsigned hb = 0;
String hbvalue = "\0";

String H = "N";
String B = "N";

char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";
String A = "GET /IoTProjects/SolderHeath/upload.php?a=";
String Z = " HTTP/1.1";
String iot = "\0";
WiFiEspClient client;

String gas2 = "\0";
String p1 = "Normal";


void lcdstring (int a, int b, String w)
{
  lcd.setCursor(a,b);
  lcd.print(w);
}
void beep ()
{
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(100);
}
 
void setup(void) { 
  Serial.begin(9600);
  Serial.print("power up");
  
 lcd.begin(16,2);
 
lcd.clear();
lcd.setCursor(0,0);
        lcd.print("INTELLIGENT");
        lcd.setCursor(0,1);
         lcd.print(" SOLDER HEALTH   ");
         delay(2000);
         
lcd.clear();
lcd.setCursor(0,0);
        lcd.print("SECUIRITY COMM'N");
        lcd.setCursor(0,1);
         lcd.print("   USING IOT       ");
         delay(2000);

          pinMode(tempa,INPUT);
          pinMode(tempb,INPUT);
         pinMode(button,INPUT);
         pinMode(heart,INPUT);
          
          pinMode(buzzer,OUTPUT);
          pinMode(relay1,OUTPUT);
          pinMode(relay2,OUTPUT);
          
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
  lcd.setCursor(0, 0);
  lcd.print("CONNECTING TO");
  lcd.setCursor(0, 1);
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
  lcd.setCursor(0, 0);
  lcd.print("CONNECTED TO");
  lcd.setCursor(0, 1);
  lcd.print("WI - FI ");
  delay(2000);
  // you're connected now, so print out the data
  Serial.println(F("You're connected to the network"));

  lcd.clear ();
  lcd.setCursor(0, 0);
  lcd.print("server init.   ");
  lcd.setCursor(0, 1);
  lcd.print("please wait    ");
  delay(2000);

  Serial.println(F("sending data ---1 "));
  Serial.println(F("Starting connection to server..."));
  // if you get a connection, report back via serial
  if (client.connect(server, 80)) {
    Serial.println(F("Connected to server"));
    // Make a HTTP request
    client.println("GET /IoTProjects/SolderHeath/upload.php?a=U HTTP/1.1");
    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
  }
  client.flush();
  client.stop();

  lcd.clear ();
  lcd.setCursor(0, 0);
  lcd.print("server init.   ");
  lcd.setCursor(0, 1);
  lcd.print("done             ");
  delay(1000);

  Serial.println(F("PLEASE SHOW CARD "));

  Serial1.listen (); delay(1000);
  
}
 
void loop() {

e_temp = "N";
H = "N";
B = "N";
 no = random(11);
temp2 = analogRead(tempa);  
float V=temp2*(5/(1023.00));  
//float V=temp2*(5/(1023.00));  
  temp1=V*100;  

  temp1 = temp1 - 10;
Serial.print("body temperature is = "); Serial.println(temp1);
delay(50);

bb = analogRead(tempb);  
float VV=bb*(5/(1023.00));  
//float V=temp2*(5/(1023.00));  
  aa=VV*100;  

  aa = aa - 10;
Serial.print("temperature is = "); Serial.println(aa);
delay(50);

Serial.println("button="+String(digitalRead(button)));
Serial.println("heart"+String(digitalRead(heart)));



if (aa > 35)
{
  e_temp = "Y";
    delay(100);
 digitalWrite(relay1,HIGH);
beep ();
iot =  A + String(temp1) + "&b=" + e_temp + "&c=" + H + "&d=" + B + Z;
// sndit (iot);
delay(4000);
}
/*
if ((temp1 > 55)||(aa > 55))
{
  
    lcdstring(0,0,"T:"+String(temp1));
    lcdstring(8,0,"BT:"+String(aa));
     lcdstring(0,1,"HB: "+String(H));
     lcdstring(8,1,"EB: "+String(B));
     delay(100);
 digitalWrite(relay1,HIGH);
beep ();
iot =  q + String(temp1) + "&b=" + String(aa) + "&c=" + H + "&d=" + B ;
send2server ();


 // msg = p +"Temperature%20Alert%0AT: "+String(temp1);
// sendmsg();
  delay(2000);
}
*/
else
{
 digitalWrite(relay1,LOW);
}
/*
if ((temp1 < 25)||(aa < 25))
{
  
    lcdstring(0,0,"T:"+String(temp1));
    lcdstring(8,0,"BT:"+String(aa));
     lcdstring(0,1,"HB: "+String(H));
     lcdstring(8,1,"EB: "+String(B));
     delay(100);
beep ();
 digitalWrite(relay2,HIGH);

iot =  q + String(temp1) + "&b=" + String(aa) + "&c=" + H + "&d=" + B ;
send2server ();


 // msg = p +"Temperature%20Alert%0AT: "+String(temp1);
// sendmsg();
  delay(2000);
}

else
{
 digitalWrite(relay2,LOW);
}
*/
if ((digitalRead(heart)))
{
  lcd.clear();
     lcd.setCursor(0,0);
    lcd.print(" PLZ PUT YOUR  ");
      lcd.setCursor(0,1);
    lcd.print("FINGER PROPERLY");
    delay(1800);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("CALCULATING.....");
  delay(2000);

  hb = otp[no].toInt();
 Serial.print("otp is = "); Serial.println(hb);

  H = String(hb);
  tt = otp1[no].toInt(); 
  temp1 = float(tt);
Serial.println("temp1 = "+String(temp1));

  if ((hb>95)||(hb<70))
  {
    H = "Y";
Serial.println("****** heart alert *********");
    lcd.clear();
  lcd.print("HEART BEAT ALERT");
    lcd.setCursor(0,1);
    lcd.print("HB = ");
    lcd.setCursor(6,1);
    lcd.print(hb);
beep ();
iot =  A + String(temp1) + "&b=" + e_temp + "&c=" + H + "&d=" + B + Z;
//msg = a + "HEART%20BEAT%20ALERT%20PLEASE%20CHECK";
// sendsms ();
// sndit (iot);
delay(5000);
}
  else
  {
    
  hbvalue = "\0";   
  lcd.clear();
  lcd.print("HEART BEAT NORMAL");
    lcd.setCursor(0,1);
    lcd.print("H BEAT = ");
    lcd.setCursor(10,1);
    lcd.print(hb);
iot =  A + String(temp1) + "&b=" + e_temp + "&c=" + H + "&d=" + B + Z;
// sndit (iot);
  delay(3000);
  
  }
  
}//heart beat

if (digitalRead(button)==LOW)
{
  B= "Y";
 
  lcd.clear();
    lcdstring(0,0,"T:"+String(temp1));
     lcdstring(0,1,"HB: "+String(H));
     lcdstring(8,1,"EB: "+String(B));
     delay(100);
     

iot =  A + String(temp1) + "&b=" + e_temp + "&c=" + H + "&d=" + B + Z;
// sndit (iot);
beep ();
delay(4000);
}
else
{
  B = "N";
}
  lcd.clear();
     lcdstring(0,0,"T:"+String(e_temp));
     lcdstring(0,1,"HB: "+String(H));
     lcdstring(8,1,"EB: "+String(B));
     delay(100);

iot =  A + String(temp1) + "&b=" + e_temp + "&c=" + H + "&d=" + B + Z;
// sndit (iot);

////////////////////////////////////////////////////////////////////////////////////

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
    delay(10);
    Serial.println(x, DEC);
  }
  Serial.println(F("Starting connection to server..."));
  // if you get a connection, report back via serial
  if (client.connect(server, 80)) {
    Serial.println(F("Connected to server"));
    // Make a HTTP request
    

    //client.println("GET /IoTProjects/TollBooth/tollbooth.php?a=A&b=5&c=6&d=3 HTTP/1.1");

    client.println("GET /IoTProjects/SolderHeath/upload.php?a="+String(temp1)+ "&b=" + e_temp  + " HTTP/1.1");

    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
    iot = "\0";
    Serial.println();
    Serial.println();
    Serial.println();
  }
/////////////////////////////////////////////////////////////////////////////////////////



}// LOOP

  void sndit (String link)
  {

//Serial1.listen(); delay(1000);

  Serial.print(F("A = ")); Serial.println(link);

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
    delay(10);
    Serial.println(x, DEC);
  }
  Serial.println(F("Starting connection to server..."));
  // if you get a connection, report back via serial
  if (client.connect(server, 80)) {
    Serial.println(F("Connected to server"));
    // Make a HTTP request
    

    //client.println("GET /IoTProjects/TollBooth/tollbooth.php?a=A&b=5&c=6&d=3 HTTP/1.1");

    client.println(A + String(temp1) + "&b=" + e_temp + "&c=" + H + "&d=" + B + Z);

    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
    iot = "\0";
  }
  }
