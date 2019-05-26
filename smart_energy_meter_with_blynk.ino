
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <LiquidCrystal.h>

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

//char auth[] = "822b2c465d2948ff933e7cf5f494f309";

char auth[] = "f2c313e969c842b19348182eadd4ccff";
//char auth[] = "e6e70d14882a458593f892a38c332f61";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "project12";
char pass[] = "project123456";

unsigned int flag= 0;

// Hardware Serial on Mega, Leonardo, Micro...
//#define EspSerial Serial1

// or Software Serial on Uno, Nano...
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(12, 13); // RX, TX
LiquidCrystal lcd(4,5,6,7,8,9); 

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

#define buzzer 10


volatile int buttonState;
 int units = 0;
int units1 = 0;
int cost = 0;
int cost1 = 0;
int total_cost = 0;
int total_units = 0;


ESP8266 wifi(&EspSerial);

void beep ()
{
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(100);
}
WidgetLCD lcd1(V0);
BLYNK_WRITE(V1)
{
   buttonState = param.asInt();
  Serial.print(F("buttonState = ")); Serial.println(buttonState);
}

void setup()
{
  // Debug console
  Serial.begin(9600);

   Serial.println("power up");
   lcd.begin(16,2);

   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("  SMART ENERGY  ");
     lcd.setCursor(0,1);
   lcd.print("MONITORING SYSTEM");
   delay(2000);

   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print(" connecting  to ");
     lcd.setCursor(0,1);
   lcd.print("****network****");
   delay(200);
   
   
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup notification button on pin 2
  pinMode(A0, INPUT);
  pinMode(buzzer, OUTPUT);

  attachInterrupt(0,pinisr , FALLING);

  lcd1.clear();
lcd1.print(0,0,"  SMART ENERGY  ");
lcd1.print(0,1,"MONITORING SYSTEM");
delay(1000);

   Blynk.notify("KIT STARTED!!!!");

   lcd1.clear();
   lcd.clear();
}

void loop()
{
  Blynk.run();

if (buttonState == 1)
{
  Blynk.notify("PEAK TIME -- ON\n  please check....");
 
}
  
Serial.println(analogRead(A0));
if (analogRead(A0) > 150)
{
 if (flag < 3)
 {
  Blynk.notify("Heavy Load -- ON\n  please check....");
  delay(100);
  flag ++;
  Serial.print(F("flag = ")); Serial.println(flag);
 }
lcd1.print(0,0,"U: ");
lcd1.print(3,0,total_units);
lcd1.print(8,0,"C: ");
lcd1.print(11,0,total_cost);
lcd1.print(0,1,"HL: ");
lcd1.print(4,1,"ON ");
lcd1.print(8,1,"PT: ");
lcd1.print(12,1,buttonState);

delay(1000);

lcd.setCursor(0,0);
lcd.print("U: ");
lcd.setCursor(3,0);
lcd.print(total_units);
lcd.setCursor(8,0);
lcd.print("C: ");
lcd.setCursor(12,0);
lcd.print(total_cost);


lcd.setCursor(0,1);
lcd.print("HL: ");
lcd.setCursor(4,1);
lcd.print("ON ");
lcd.setCursor(8,1);
lcd.print("PT: ");
lcd.setCursor(12,1);
lcd.print(buttonState);
delay(1000);
}

else if (analogRead(A0) < 150)
{
lcd1.print(0,0,"U: ");
lcd1.print(3,0,total_units);
lcd1.print(8,0,"C: ");
lcd1.print(11,0,total_cost);
lcd1.print(0,1,"HL: ");
lcd1.print(4,1,"OFF");
lcd1.print(8,1,"PT: ");
lcd1.print(12,1,buttonState);

lcd.setCursor(0,0);
lcd.print("U: ");
lcd.setCursor(3,0);
lcd.print(total_units);
lcd.setCursor(8,0);
lcd.print("C: ");
lcd.setCursor(12,0);
lcd.print(total_cost);

delay(1000);

lcd.setCursor(0,1);
lcd.print("HL: ");
lcd.setCursor(4,1);
lcd.print("OFF");
lcd.setCursor(8,1);
lcd.print("PT: ");
lcd.setCursor(12,1);
lcd.print(buttonState);
delay(1000);
}


}

void pinisr ()
{
  Serial.println("interrup occured");

  Serial.print("buttonState = ");Serial.println(buttonState);

if(buttonState == 0)
{
   units++;
  
  Serial.print(F("units = ")); Serial.println(units);
  cost = units * 5;
}
else if(buttonState == 1)
{
   units1++;
  
  Serial.print(F("units1 = ")); Serial.println(units1);
  cost1 = units1 * 10;
}
total_cost = cost + cost1;
Serial.print(F("total_cost = ")); Serial.println(total_cost);
total_units = units + units1;
Serial.print(F("total_units = ")); Serial.println(total_units);
delay(1000);
}
