
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <LiquidCrystal.h>

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

volatile int buttonState;
volatile int d1 = 0;
volatile int d2 = 0;
volatile int d3 = 0;
volatile int d4 = 0;
volatile int d5 = 0;

#define relay1 2
#define relay2 3
#define relay3 4
#define relay4 5

BLYNK_WRITE(V1)
{
  int pin = param.asInt(); // assigning incoming value from pin V1 to a variable
if (pin == 1)
{
  d1 = 1;
  digitalWrite(relay1,HIGH);
}
else 
{
  d1 = 0;
  digitalWrite(relay1,LOW);
  
}
}
BLYNK_WRITE(V2)
{
  int pin = param.asInt(); // assigning incoming value from pin V1 to a variable
if (pin == 1)
{
  d2 = 1;
  digitalWrite(relay2,HIGH);
}
else 
{
  d2 = 0;
  digitalWrite(relay2,LOW);
  
}
}
BLYNK_WRITE(V3)
{
  int pin = param.asInt(); // assigning incoming value from pin V1 to a variable
if (pin == 1)
{
  d3 = 1;
  digitalWrite(relay3,HIGH);
}
else 
{
  d3 = 0;
  digitalWrite(relay3,LOW);
  
}
}
BLYNK_WRITE(V4)
{
  int pin = param.asInt(); // assigning incoming value from pin V1 to a variable
if (pin == 1)
{
  d4 = 1;
  digitalWrite(relay4,HIGH);
}
else 
{
  d4 = 0;
  digitalWrite(relay4,LOW);
  
}
}


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

//char auth[] = "822b2c465d2948ff933e7cf5f494f309";

//char auth[] = "31a4c852f9dd4245910df7173fa98d5f";

//char auth[] = "f9d4b43dbced43169cc5d9d36f65326c";
char auth[] = "fae73e20da7b45deac686fb727880a83";

LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);

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

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

#define buzzer 9





ESP8266 wifi(&EspSerial);

void beep ()
{
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(100);
}

void setup()
{
  // Debug console
  Serial.begin(9600);

   Serial.println("power up");

   pinMode(relay1,OUTPUT);
   pinMode(relay2,OUTPUT);
   pinMode(relay3,OUTPUT);
   pinMode(relay4,OUTPUT);

   lcd.begin(16,2);
   
   
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  lcd.clear ();
  lcd.setCursor(0,0);
  lcd.print("HOME AUTOAMTION      ");
  lcd.setCursor(0,1);
  lcd.print("........................");
  delay(2500);
  lcd.clear ();
  

  Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup notification button on pin 2
  pinMode(buzzer, OUTPUT);

   Blynk.notify("KIT STARTED!!!!");

}

void loop()
{
  Blynk.run();
  
  lcd.setCursor(0,0);
  lcd.print("D1: "+String(d1));
  lcd.setCursor(8,0);
  lcd.print("D2: "+String(d2));
  lcd.setCursor(0,1);
  lcd.print("D3: "+String(d3));
  //lcd.setCursor(8,1);
  //lcd.print("D2: "+String(d4));
  delay(200);
  
}
