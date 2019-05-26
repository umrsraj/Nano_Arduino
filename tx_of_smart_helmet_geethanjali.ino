#include<String.h>
#include <SoftwareSerial.h>
#define limit A1
#define alcPin A0
#define ldrPin A0
#define buzzer 10
#define light 11

unsigned int alc = 0;
unsigned int ldr = 0;
unsigned int sw = 0;


void beep ()
{
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(100);
}

void setup()
{
  // initialize serial for debugging
  Serial.begin(9600);
Serial.println(F("HELMET SECTION OF *** SMART HELMET ***"));


pinMode(buzzer,OUTPUT);
pinMode(light,OUTPUT);

pinMode(alcPin,INPUT);
pinMode(limit,INPUT);
pinMode(memsPin,INPUT);
pinMode(ldrPin,INPUT);

beep ();

}

void loop()
{

 alc = analogRead(alcohol_sen);
 delay(50);

 Serial.print(F("alcohol = "));Serial.println(alc);

delay(200);

if (digitalRead(limit)==HIGH)
{
  Serial.println(F("bike start switch - OFF "));
 
  if(alc > 600)
  {
  Serial.println(F("ALCOHOL ALERT"));
     beep ();   
      digitalWrite(en, LOW);
    digitalWrite(d1, LOW);
    digitalWrite(d2, HIGH);
    digitalWrite(d3, HIGH);
    digitalWrite(d4, HIGH);
    delay(2000);  
  }
  else 
  {
    Serial.println(F("no helmet......"));
     //beep ();   
      digitalWrite(en, LOW);
    digitalWrite(d1, LOW);
    digitalWrite(d2, LOW);
    digitalWrite(d3, HIGH);
    digitalWrite(d4, HIGH);
    delay(2000);  
  }
  
}
 else
 {
   Serial.println(F("switch close"));
  digitalWrite(en, HIGH);
  delay(100);
 }
 
}// loop
  
