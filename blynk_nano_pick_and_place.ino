
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <LiquidCrystal.h>

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

#define m1a 2
#define m1b 3
#define m2a 4
#define m2b 5

#define m11 6
#define m12 7
#define m21 8
#define m22 9


void up(void)
{
  Serial.println("......moving up ....");
  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
   delay(1000);
    digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  delay(10);
 
}
void down(void)
{
  Serial.println("......moving down ....");
 
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
   delay(1000);
    digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  delay(10);
}
void openn(void)
{
  Serial.println("......moving Opening ....");
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
   delay(1500);
    digitalWrite(m21, LOW);
  digitalWrite(m22, LOW);
  delay(10);
}
void closee(void)
{
  Serial.println("......moving closing ....");
  digitalWrite(m21, LOW);
  digitalWrite(m22, HIGH);
   delay(1500);
    digitalWrite(m21, LOW);
  digitalWrite(m22, LOW);
  delay(10);
}
void forward(void)
{
  Serial.println("moving forward ....");
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);
   delay(100);
}

void backward(void)
{
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);
   delay(100);
}

void left(void)
{
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);
  delay(100);
}

void right(void)
{
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);
  delay(100);
}

void stop_motor(void)
{
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, LOW);
  delay(100);
}


BLYNK_WRITE(V1)
{
  int pin = param.asInt(); // assigning incoming value from pin V1 to a variable
if (pin == 1)
{
forward ();
}
}
BLYNK_WRITE(V2)
{
  int pin = param.asInt(); // assigning incoming value from pin V1 to a variable
if (pin == 1)
{
backward ();
}
}
BLYNK_WRITE(V3)
{
  int pin = param.asInt(); // assigning incoming value from pin V1 to a variable
if (pin == 1)
{
left ();
}
}
BLYNK_WRITE(V4)
{
  int pin = param.asInt(); // assigning incoming value from pin V1 to a variable
if (pin == 1)
{
right ();
}
}
BLYNK_WRITE(V5)
{
  int pin = param.asInt(); // assigning incoming value from pin V1 to a variable
if (pin == 1)
{
stop_motor();
}
}
BLYNK_WRITE(V6)
{
  int pin = param.asInt(); // assigning incoming value from pin V1 to a variable
if (pin == 1)
{
up ();
}
}
BLYNK_WRITE(V7)
{
  int pin = param.asInt(); // assigning incoming value from pin V1 to a variable
if (pin == 1)
{
down ();
}
}
BLYNK_WRITE(V8)
{
  int pin = param.asInt(); // assigning incoming value from pin V1 to a variable
if (pin == 1)
{
openn ();
}
}
BLYNK_WRITE(V9)
{
  int pin = param.asInt(); // assigning incoming value from pin V1 to a variable
if (pin == 1)
{
closee ();
}
}
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

//char auth[] = "822b2c465d2948ff933e7cf5f494f309";

//char auth[] = "31a4c852f9dd4245910df7173fa98d5f";

//char auth[] = "f9d4b43dbced43169cc5d9d36f65326c";
char auth[] = "d700e85161024a4abe532d08037c03d6";

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

ESP8266 wifi(&EspSerial);

void setup()
{
  // Debug console
  Serial.begin(9600);

   Serial.println("power up");

   lcd.begin(16,2);
   
   
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

 

  Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup notification button on pin 2
 
   Blynk.notify("KIT STARTED!!!!");

}

void loop()
{
  Blynk.run();

  
}
