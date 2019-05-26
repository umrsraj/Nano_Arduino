
#include<String.h>
#include <SoftwareSerial.h>
#define limit_sw 2
#define alcohol_sen A1
#define ldr A0

#define led A2

SoftwareSerial SIM900(12,13);

#define buzzer 8


unsigned int alc = 0;
//unsigned int ldr = 0;
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
SIM900.begin(9600);

  pinMode(buzzer, OUTPUT);
  //pinMode(light,OUTPUT);
  pinMode(led,OUTPUT);

  pinMode(alcohol_sen, INPUT);
  pinMode(limit_sw, INPUT);
  pinMode(A0,INPUT);
  //pinMode(weight, INPUT);

  pinMode(buzzer, INPUT);

//  pinMode(rf1, OUTPUT);
//  pinMode(rf2, OUTPUT);
//  pinMode(rf3, OUTPUT);

  /*digitalWrite(rf1, HIGH);
    digitalWrite(rf2, HIGH);
    digitalWrite(rf3, HIGH);
    delay(1000);
      digitalWrite(rf1, LOW);
      digitalWrite(rf2, LOW);
      digitalWrite(rf3, LOW);
      delay(1000);

    digitalWrite(rf1, HIGH);
    digitalWrite(rf2, HIGH);
    digitalWrite(rf3, HIGH);
    delay(1000);
      digitalWrite(rf1, LOW);
      digitalWrite(rf2, LOW);
      digitalWrite(rf3, LOW);
      delay(1000);

    digitalWrite(rf1, HIGH);
    digitalWrite(rf2, HIGH);
    digitalWrite(rf3, HIGH);
    delay(1000);
      digitalWrite(rf1, LOW);
      digitalWrite(rf2, LOW);
      digitalWrite(rf3, LOW);
      delay(1000);
  */

  beep ();
}

void loop()
{

int ldr_read1=analogRead(ldr);
Serial.print("LDR:");
    Serial.print("\t");
  Serial.println(ldr_read1);
  delay(10);
  
  if(ldr_read1<950){
digitalWrite(led,LOW);
    delay(100);
  }
  if(ldr_read1>950){
    
digitalWrite(led,HIGH);
    delay(100);
   
  }

  
  int alc_sen = analogRead(A1);
  Serial.print("ALCOHOL:");
  Serial.print("\t");
  Serial.println(alc_sen);
  if (alc_sen > 860)
  {
    beep ();
    Serial.println("ALERT! ALCOHOL DETECTED");
   
SIM900.print("ALCOHOL ALERT\n");
    delay(1000);
    
  }
  else if (digitalRead(limit_sw) == LOW)    // Helmet On
  {
    Serial.println(F("start switch - ON "));
//    digitalWrite(rf1, LOW);
//    digitalWrite(rf2, HIGH);
//    digitalWrite(rf3, HIGH);
     beep();
     SIM900.print("HELMET ALERT\n");
    delay(1000);
  }
  else {
    //Serial.println(F("bike start switch - OFF "));
//    digitalWrite(rf1, HIGH);
//    digitalWrite(rf2, HIGH);
//    digitalWrite(rf3, HIGH);
    //beep();
    digitalWrite(buzzer,LOW);
    delay(100);
    //SIM900.println("NORMAL\r\n");
    //delay(500);
  }

}// loop
