
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <LiquidCrystal.h>

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

//char auth[] = "822b2c465d2948ff933e7cf5f494f309";

//char auth[] = "31a4c852f9dd4245910df7173fa98d5f";
char auth[] = "f6d6266d70474a13afde209ff1828bdc";

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
#define relay1 2

#define relay2 3

int hum,wat,ldr;
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
//   buttonState = param.asInt();
  //Serial.print(F("buttonState = ")); Serial.println(buttonState);
}

void setup()
{
  // Debug console
  Serial.begin(9600);

   Serial.println("power up");
   lcd.begin(16,2);

   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("**  SMART  ** ");
     lcd.setCursor(0,1);
   lcd.print("IRRIGATION SYSTEM");
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
  
  //pinMode(A0, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

  //attachInterrupt(0,pinisr , FALLING);

  lcd1.clear();
lcd1.print(0,0,"**  SMART ** ");
lcd1.print(0,1,"IRRIGATION SYSTEM");
delay(1000);

   Blynk.notify("KIT STARTED!!!!");

   lcd1.clear();
   lcd.clear();

//lcd1.print(0,0,"S: ");
////lcd1.print(3,0,total_units);
//lcd1.print(8,0,"T: ");
////lcd1.print(11,0,total_cost);
//lcd1.print(0,1,"L: ");
////lcd1.print(4,1,"ON ");
//lcd1.print(8,1,"H: ");
////lcd1.print(12,1,buttonState);
//
//delay(1000);
//
//lcd.setCursor(0,0);
//lcd.print("S: ");
//lcd.setCursor(8,0);
//lcd.print("T:");
//lcd.setCursor(0,1);
//lcd.print("L: ");
//lcd.setCursor(8,1);
//lcd.print("H:");



}

int temp1,temp2;
void loop()
{
  Blynk.run();

 // Blynk.notify("PEAK TIME -- ON\n  please check....");
  
temp2 = analogRead(A0); //read data from analog pin A1. 
float V=temp2*(5/(1023.00)); //conversion of analog voltage to digital voltage. 
  temp1=V*100; //temperature in centigrade scale. 

  temp1 = temp1 - 5;
Serial.print("temperature is = "); Serial.println(temp1);
delay(50);
  
wat=analogRead(A1);
Serial.print("wat is = "); Serial.println(wat);
ldr=analogRead(A2);
Serial.print("ldr is = "); Serial.println(ldr);
hum=analogRead(A3);
Serial.print("hum is = "); Serial.println(hum);
delay(20);


lcd.setCursor(0,0);
lcd.print("T: "+String(temp1)ui);
lcd1.print(0,0,"T: "+String(temp1) );
delay(200);

/*
if(wat>500)
{
  
lcd.setCursor(2,0);
lcd.print("WET  ");
lcd1.print(2,0,"WET  " );
delay(100);
digitalWrite(relay1,LOW);
delay(200);
}
else
{
  
lcd.setCursor(2,0);
lcd.print("DRY  ");
lcd1.print(2,0,"DRY  ");
delay(100);
digitalWrite(relay1,HIGH);
delay(200);
}
*/
if(hum<700)
{
  
lcd.setCursor(8,0);
lcd.print("H: 1");
lcd1.print(8,0,"H: 1  " );
delay(100);
//digitalWrite(relay2,LOW);
}
else
{
  
lcd.setCursor(8,0);
lcd.print("H: 0");
lcd1.print(8,0,"H: 0  " );
delay(100);

}

}
