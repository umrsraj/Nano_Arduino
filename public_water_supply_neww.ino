
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <LiquidCrystal.h>

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).


//char auth[] = "f9d4b43dbced43169cc5d9d36f65326c";
char auth[] = "f9431a507b674ba4ba7ec0d601c96dd1";

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
LiquidCrystal lcd(2,3,4,5,6,7); 

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

#define soil1Pin A0
#define soil2Pin A1
#define soil3Pin A2

#define relay 8
#define buzzer 9
#define gled 10
#define rled 11


int s1 = 0;
int s2 = 0;
int s3 = 0;

volatile int buttonState;

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

  pinMode(soil1Pin, INPUT);
  pinMode(soil2Pin, INPUT);
  pinMode(soil3Pin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(gled, OUTPUT);
  pinMode(rled, OUTPUT);


   lcd.clear();
   lcdstring(0,0,"PUBLIC WATER SUPPLY");
   lcdstring(0,1,"GRID MONITORING     ");
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


   lcd1.clear();
   lcd1.print(0,0,"PUBLIC WATER SUPPLY");
   lcd1.print(0,1,"GRID MONITORING     ");
   delay(2000);

   Blynk.notify("KIT STARTED!!!!");

   lcd1.clear();
   lcd.clear();
}

void loop()
{
  Blynk.run();

if (buttonState == 0)
{
  
     lcd.clear();
   lcdstring(0,0,"PLEASE SWITCH ON  ");
   lcdstring(0,1,"WATER SUPPLY        ");
   delay(200);
   digitalWrite(relay,LOW);
  delay(200);
      lcd1.clear();
   lcd1.print(0,0,"PLEASE SWITCH ON  ");
   lcd1.print(0,1,"WATER SUPPLY        ");
   delay(2000);
 
}
else if (buttonState == 1)
  {
    digitalWrite(relay,HIGH);
    delay(300);
    s1 = digitalRead(soil1Pin);
    s2 = digitalRead(soil2Pin);
    s3 = digitalRead(soil3Pin);
    Serial.println("soil1 = "+String(s1));
    Serial.println("soil2 = "+String(s2));
    Serial.println("soil3 = "+String(s3));

    if ((buttonState == 1)&&((s1==1)||(s2==1)||(s3==1)))
  {
  Blynk.notify("WATER LEAKING\nPLEASE CHECK");
    delay(200);
    beep ();
  }


     lcd.clear();
   lcdstring(0,0,"WATER SUPPLY ON    ");
   lcdstring(0,1,"L1:"+String(s1));
   lcdstring(5,1,"L2:"+String(s2));
   lcdstring(10,1,"L3:"+String(s3));
   delay(200);
      lcd1.clear();
   lcd1.print(0,0,"WATER SUPPLY ON    ");
   lcd1.print(0,1,"L1:"+String(s1));
   lcd1.print(5,1,"L2:"+String(s2));
   lcd1.print(10,1,"L3:"+String(s3));
   delay(2000);

    
    
  }
  

}//loop

void lcdstring (int a, int b, String dAta)
{
  lcd.setCursor(a,b);
  lcd.print(dAta);
}
