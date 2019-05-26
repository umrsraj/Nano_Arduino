
#include<String.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

LiquidCrystal lcd (2,3,4,5,6,7);
SoftwareSerial SIM900(12,13);

#define sped A1
#define ldrPin A0
#define memsPin A2


#define en 8
#define relay 11

unsigned int alc = 0;
unsigned int ldr = 0;
unsigned int mems = 0;


void setup()
{
  // initialize serial for debugging
  Serial.begin(9600);
Serial.println(F("bike section of *** SMART HELMET ***"));

pinMode(en,INPUT);
pinMode(obs,INPUT);
pinMode(memsPin,INPUT);
pinMode(ldrPin,INPUT);
pinMode(sped,INPUT);

pinMode(light,OUTPUT);
pinMode(relay,OUTPUT);
pinMode(d2,OUTPUT);
pinMode(d3,OUTPUT);

pinMode(buzzer,OUTPUT);
pinMode(alcohol_sen,INPUT);
pinMode(limit,INPUT);

}

void loop()
{

 alc = analogRead(alcohol_sen);
 delay(50);

 Serial.print(F("alcohol = "));Serial.println(alc);

delay(200);

if ((digitalRead(limit)==HIGH)||(alc>600))
{
  Serial.println(F("bike start switch - ON "));
  if(alc > 600)
  {
  Serial.println(F("ALCOHOL ALERT"));
     beep ();    
  }
  digitalWrite(en, LOW);
    digitalWrite(d1, LOW);
    digitalWrite(d2, HIGH);
    digitalWrite(d3, HIGH);
    digitalWrite(d4, HIGH);
    delay(2000);  
}
 else
 {
   Serial.println(F("switch close"));
  digitalWrite(en, HIGH);
  delay(100);
 }
 
}// loop
  
