#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <String.h>

#define relay 8
#define gled 11
#define rled 10
#define buzzer 9

String read_msg = "\0";

LiquidCrystal lcd (2,3,4,5,6,7);
SoftwareSerial zigbee(12,13);

void beep ()
{
  digitalWrite(buzzer,HIGH); delay(1000);
  digitalWrite(buzzer,LOW); delay(200);
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
zigbee.begin(9600);
Serial.println("power up");
lcd.begin(16,2);

pinMode(buzzer,OUTPUT);
pinMode(relay,OUTPUT);
pinMode(gled,OUTPUT);
pinMode(rled,OUTPUT);


lcd.clear();
lcdstring(0,0," ROBUST RAILWAY ");
lcdstring(0,1,"CRACK DETCTN S/M");
beep ();
delay(1500);

}

void loop() {
  // put your main code here, to run repeatedly:
while(zigbee.available() != 0)
  {
    read_msg = zigbee.readString();
    Serial.println("read_msg is = "); Serial.println(read_msg);
 }

 if (read_msg.indexOf("CRACK") != (-1))
 {
  digitalWrite(gled,LOW);
  digitalWrite(rled,HIGH);
digitalWrite(relay,LOW);
delay(100);
   lcd.clear();
  lcdstring(0,0,"  TRACK  FAULT  ");
  lcdstring(0,1,"--- DETECTED ---");
  beep ();
  delay(5000);
  while (1);
 }
 else 
 {
  
  digitalWrite(rled,LOW);
  digitalWrite(gled,HIGH);
   lcd.clear();
  lcdstring(0,0,"NO TRACK FAULT     ");
  lcdstring(0,1,"ROBOT MOVING      ");
  digitalWrite(relay,HIGH);
  delay(200);
  
 }
}// loop
void lcdstring (int a, int b, String data)
{
  lcd.setCursor(a,b);
  lcd.print(data);
}
