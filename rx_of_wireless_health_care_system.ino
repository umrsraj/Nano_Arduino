/*
 * PRIVATE AND SECURE MEDICAL DATA TRANSMISION AND ANALYSIS FOR WIRELESS SENSING HEALTHCARE SYSTEM 
 * SREYAS CLG
 * Rx kit
 */

 #include <SoftwareSerial.h>
 #include <LiquidCrystal.h>
#include <String.h>

#define buzzer 8

LiquidCrystal lcd(2,3,4,5,6,7);

String read_msg = "\0";
SoftwareSerial SIM900(9,10);

void beep()
{
   digitalWrite(buzzer, HIGH); 
   delay(1500);
    digitalWrite(buzzer, LOW); 
    delay(100);
}
//void ShowSerialData()
//{
//  while (SIM900.available() != 0)
//    Serial.write(char (SIM900.read()));
//}

void ShowSerialData()
{
  while(SIM900.available()!=0)
   read_msg = SIM900.readString();
  Serial.println("read_msg is = "); Serial.println(read_msg);
   delay(1);
  
}
void showprojectname ()
{
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("    WIRELESS    ");
    lcd.setCursor(0,1);
    lcd.print("HEALTH CARE S/M");
  delay(3000);
  
}

void setup() {
  // put your setup code here, to run once:
SIM900.begin(9600);
Serial.begin(9600);
lcd.begin(16,2);
 Serial.println("power up");
 
showprojectname ();
  
}
void loop() {
  // put your main code here, to run repeatedly:
 ShowSerialData();
 if(read_msg.indexOf("t")!=(-1))
 {
  
  Serial.println("temperature alert");
  delay(1);
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TEMPERATURE ALERT");
    lcd.setCursor(0,1);
    lcd.print("***PLZ CHECK****");
    beep ();
  delay(2000);
   read_msg = "\0";
 }
else if (read_msg.indexOf("h")!=(-1))
 {
  Serial.println("heart beat alert");
   lcd.clear();
  lcd.print("HEART BEAT ALERT");
    lcd.setCursor(0,1);
    lcd.print("***PLZ CHECK****");
beep ();
delay(2000);
 }
 else if (read_msg.indexOf("n")!=(-1))
 {
   Serial.println("system is normal");
   lcd.clear();
  lcd.print("SYSTEM IS NORMAL");
    lcd.setCursor(0,1);
    lcd.print("****************");

delay(2000);
 }
}
