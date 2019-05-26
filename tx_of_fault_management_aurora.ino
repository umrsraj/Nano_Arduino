
 
#include<String.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

SoftwareSerial SIM900(12,13);
LiquidCrystal lcd (2,3,4,5,6,7);

#define temp A0
#define humPin A1
#define gasPin A2
#define wat A3
#define buzzer 8

float temp1=0.0;
String read_msg = "\0";

unsigned temp2 = 0;
int hum = 0;
int gas = 0;
String T = "N";
String H = "N";
String G = "N";
String W = "N";


void beep()
{
   digitalWrite(buzzer, HIGH); 
   delay(1000);
    digitalWrite(buzzer, LOW); 
    delay(100);
}

void showprojectname ()
{
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("IOT BSD FAULT     ");
    lcd.setCursor(0,1);
    lcd.print("   MANAGEMNET   ");
  delay(3000);  
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" PLATFORM WITH");
    lcd.setCursor(0,1);
    lcd.print(" PROTECTION AT  ");
  delay(3000);
   lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   COAL MINES     ");
    lcd.setCursor(0,1);
    lcd.print("..................");
  delay(3000);

}


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
lcd.begin(16,2);

 Serial.println("power up");
showprojectname ();


pinMode(temp,INPUT);
pinMode(humPin,INPUT);
pinMode(gasPin,INPUT);
pinMode(wat,INPUT);
pinMode(buzzer,OUTPUT);

  // initialize serial for ESP module
  SIM900.begin(9600);
  
  // check for the presence of the shield
  
Serial.println(F("PLEASE SHOW CARD "));
}

void loop() {

temp2 = analogRead(temp); //read data from analog pin A1. 
float V=temp2*(5/(1023.00)); //conversion of analog voltage to digital voltage. 
  temp1=V*100; //temperature in centigrade scale. 
temp1 = temp1-10;
Serial.print("temperature is = "); Serial.println(temp1);
delay(50);

hum = analogRead(humPin);
gas = analogRead(gasPin);
delay(50);
Serial.print(F("gas = ")); Serial.println(gas);
Serial.print(F("humidity = ")); Serial.println(hum);

 if (temp1 > 55)
{
T = "Y";
lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TEMPERATURE ALERT");
    lcd.setCursor(0,1);
    lcd.print("T: "+String(temp1));
    SIM900.println("TEMPEARUTE ALERT T="+String(temp1)+"\r\n");
    delay(1000);
    beep ();
  delay(1000);
}
else
{
T = "N";
}

if (gas > 900)
{
  G = "Y";
lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   GAS ALERT    ");
    lcd.setCursor(0,1);
    lcd.print("G:"+String(gas));
    SIM900.println("GAS ALERT\r\n");
    delay(1000);
    beep ();
  delay(1000);
}
else
{
  G = "N";
}

if (hum > 250)
{
  H = "Y";
lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" HUMIDITY ALERT  ");
    lcd.setCursor(0,1);
    lcd.print("PLEASE CHECK.....");
    SIM900.println("HUMIDITY ALERT\r\n");
    delay(1000);
    beep ();
  delay(1000);
}
else
{
  H = "N";
}

if (digitalRead(wat)== HIGH)
{
  W = "Y";
lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" WATER DETECTED ");
    lcd.setCursor(0,1);
    lcd.print("PLEASE CHECK.....");
    SIM900.println("WATER DETECTED\r\n");
    delay(1000);
    beep ();
  delay(1000);
   
}
else
{
  W = "N";
}

  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("T= "+String(temp1)+" G: "+String(gas));
//    lcd.print("T= "+String(temp1)+" G: "+G);
    lcd.setCursor(0,1);
    lcd.print("H: "+ H + "    W: " + W);
delay(300);

 
} // loop



void lcdstring (unsigned int a, unsigned int b, String data)
{
  // lcd.clear();
  lcd.setCursor(a, b);
  lcd.print(data);
}
