#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <TinyGPS++.h>
#include <String.h>
#include <stdio.h>

LiquidCrystal lcd (2,3,4,5,6,7);
SoftwareSerial SIM900 (12,13);

String read_msg = "\0";

// The TinyGPS++ object
TinyGPSPlus gps;

#define buzzer 9
#define sw 8

#define ss Serial

void beep ()
{
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(100);
}
void beep1 ()
{
  digitalWrite(buzzer,HIGH);
  delay(200);
  digitalWrite(buzzer,LOW);
  delay(100);
  digitalWrite(buzzer,HIGH);
  delay(200);
  digitalWrite(buzzer,LOW);
  delay(100);
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
SIM900.begin(9600);
lcd.begin(16,2);

Serial.println("power up"); 


pinMode(buzzer,OUTPUT);
pinMode(sw,INPUT);

lcd.clear ();
lcdstring(0,0,"BUS TRACKING S/M");
lcdstring(0,1,".................");
delay(2000);
sendbal ("08897275887","KIT STARTED");

}

void loop() {
  // put your main code here, to run repeatedly:
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();
   if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
   // while(true);
   lcd.clear();
   lcdstring(0,0,"NO GPS DETECTED");
   lcdstring(0,1,"  CHECK WIRING  ");
   delay(1500);
  }

/*
  if (digitalRead(sw)==HIGH)
  {
    Serial.println("button pressed***********");
   lcdstring(0,0,"WOMEN IN DANGER   ");
   lcdstring(0,1,"       AT          ");
   beep ();
   delay(1500);
   lcdstring(0,0,"LAT:"+String(gps.location.lat(),6));
   lcdstring(0,1,"LNG:"+String(gps.location.lng(),6));
   delay(2500);  
   sendbal ("09652202270","WOMEN IN DANGER\nAT\nLAT:"+String(gps.location.lat(),6)+"\nLNG:"+String(gps.location.lng(),6));
beep1 ();
   sendbal ("08885694832","WOMEN IN DANGER\nAT\nLAT:"+String(gps.location.lat(),6)+"\nLNG:"+String(gps.location.lng(),6));
beep1 ();
 }
 else
 {
 
  else
  {
   lcdstring(0,0,"LAT:"+String(gps.location.lat(),6));
   lcdstring(0,1,"LNG:"+String(gps.location.lng(),6));
   delay(100);
 }
 }
 */
  
ShowSerialData();
if ((read_msg.indexOf("TRACK")!=(-1))||(read_msg.indexOf("track")!=(-1)))
{
  lcd.clear ();
  lcdstring(0,0,"SENDING VEHICLE");
  lcdstring(0,1,"   LOCATION    ");
  delay(2000);

  lcd.clear ();
  lcdstring(0,0,"SENDING VEHICLE");
  lcdstring(0,1,"LOCATION TO -- 1");
  delay(200);
  
sendbal ("08897275887","YOUR VEHICLE IS AT \nLAT:"+String(gps.location.lat(),6)+"\nLNG:"+String(gps.location.lng(),6));
  lcd.clear ();
  lcdstring(0,0,"SENDING VEHICLE");
  lcdstring(0,1,"LOCATION TO -- 2");
  delay(200);
  
sendbal ("08885694832","YOUR VEHICLE IS AT \nLAT:"+String(gps.location.lat(),6)+"\nLNG:"+String(gps.location.lng(),6));
  lcd.clear ();
  lcdstring(0,0,"SENDING VEHICLE");
  lcdstring(0,1,"LOCATION TO -- 3");
  delay(200);
  /*
sendbal ("09824798951","YOUR VEHICLE IS AT \nLAT:"+String(gps.location.lat(),6)+"\nLNG:"+String(gps.location.lng(),6));

    lcd.clear ();
  lcdstring(0,0,"SENDING VEHICLE");
  lcdstring(0,1,"LOCATION TO -- 4");
  delay(200);
  
sendbal ("09502174055","YOUR VEHICLE IS AT \nLAT:"+String(gps.location.lat(),6)+"\nLNG:"+String(gps.location.lng(),6));

  lcd.clear ();
  lcdstring(0,0,"SENDING VEHICLE");
  lcdstring(0,1,"LOCATION TO -- 5");
  delay(200);
  
sendbal ("09000605634","YOUR VEHICLE IS AT \nLAT:"+String(gps.location.lat(),6)+"\nLNG:"+String(gps.location.lng(),6));
    lcd.clear ();
  lcdstring(0,0,"SENDING VEHICLE");
  lcdstring(0,1,"LOCATION TO -- 1");
  delay(200);
  
sendbal ("09848829577","YOUR VEHICLE IS AT \nLAT:"+String(gps.location.lat(),6)+"\nLNG:"+String(gps.location.lng(),6));
*/

  delay(100);
  lcd.clear ();
  lcdstring(0,0,"VEHICLE LOCATION");
  lcdstring(0,1,"      SENT      ");
  delay(2000);
}

}//loop
void sendbal (String UU,String x)
{
  SIM900.print("AT\r\n");
        SIM900.print('\n');
        ShowSerialData();
        delay(3000);
        SIM900.print("ATE1\r\n");
        ShowSerialData();
        delay(3000);
       SIM900.print("AT&W\r\n");
        SIM900.print('\n');
        ShowSerialData();
        delay(3000);
        SIM900.print("AT+CMGF=1\r\n");
        ShowSerialData();
        delay(3000);
        SIM900.print("AT+CNMI=2,2,0,0,0\r\n");
        ShowSerialData();
        delay(2000);
       // Serial.print("AT+CSMP=17,167,0,0\n");
        delay(2000); 
        SIM900.print("AT+CMGS=\""+UU+"\"\r");
        ShowSerialData();
       // Serial.print('"');
      //Serial.print("9014449822");
      //Serial.print('"');
      //Serial.print('\r');
        SIM900.print('\n');
       delay(1000);
       SIM900.println(x);
     
       SIM900.println();
      
     SIM900.print('\r');
      SIM900.print('\n');
      
     delay(3000);
       SIM900.print((char)26);
       ShowSerialData();
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
void lcdstring(int a, int b, String data)
{
  lcd.setCursor(a,b);
  lcd.print(data);
}
void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    lcd.clear();
    lcdstring(0,0,"LAT:"+String(gps.location.lat(), 6));
    lcdstring(0,1,"LNG:"+String(gps.location.lng(), 6));
    delay(700);
  }
  else
  {
    Serial.print(F("INVALID"));
    lcd.clear();
    lcdstring(0,0,"INVALID LOCATION");
    lcdstring(0,1,"PLEASE CHECK");
    delay(2000);
  }

  Serial.println();
}
