/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  Attention! Please check out TinyGSM guide:
    http://tiny.cc/tiny-gsm-readme

  WARNING: GSM modem support is for BETA testing.

  This sketch shows how to write values to Virtual Pins

  NOTE:
  BlynkTimer provides SimpleTimer functionality:
    http://playground.arduino.cc/Code/SimpleTimer

  App project setup:
    Value Display widget attached to Virtual Pin V5
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#define TINY_GSM_MODEM_SIM900

// Default heartbeat interval for GSM is 60
// If you want override this value, uncomment and set this option:
//#define BLYNK_HEARTBEAT 30

#include <TinyGsmClient.h>
#include <BlynkSimpleSIM800.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd (A13,A12,A11,A10,A9,A8);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
//char auth[] = "f9d4b43dbced43169cc5d9d36f65326c";
char auth[] = "270c5156139b44888d783ad27b42433a";

// Your GPRS credentials
// Leave empty, if missing user or pass
char apn[]  = "airtelgprs.com";
char user[] = "";
char pass[] = "";
unsigned int a = 0;

// Hardware Serial on Mega, Leonardo, Micro
#define SerialAT Serial1


#define temp A0
#define ir A1
#define rf A2
#define ldrPin A6
#define weightPin A7
#define fan 8
#define pi 9
#define gled 10
#define rled 11

float temp1 = 0.0;
unsigned temp2 = 0;
int ldr = 0;
int weight = 0;

void lcdstring(int a, int b, String data)
{
  lcd.setCursor(a, b);
  lcd.print(data);
}


// or Software Serial on Uno, Nano
//#include <SoftwareSerial.h>
//SoftwareSerial SerialAT(13, 12); // RX, TX

TinyGsm modem(SerialAT);
WidgetLCD lcd1(V0);

void setup()
{
  // Debug console
  Serial.begin(9600);
lcd.begin(16,2);
  delay(10);


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("EFFICIENT HEALTH");
  lcd.setCursor(0, 1);
  lcd.print(" MONITORING OF  ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  PATIENT AND   ");
  lcd.setCursor(0, 1);
  lcd.print("  SURROUNDINGS  ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   USING IOT    ");
  lcd.setCursor(0, 1);
  lcd.print("   TECHNOLOGY   ");
  delay(20);


  // Set GSM module baud rate
  SerialAT.begin(9600);
  delay(3000);

  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  Serial.println("Initializing modem...");
  //modem.restart();
   modem.init();

  // Unlock your SIM card with a PIN
  //modem.simUnlock("1234");

  Blynk.begin(auth, modem, apn, user, pass);

  // Setup a function to be called every second
  //timer.setInterval(1000L, myTimerEvent);

pinMode(ir, INPUT);
  pinMode(temp, INPUT);
  pinMode(rf, INPUT);

pinMode(weightPin, INPUT);
pinMode(ldrPin, INPUT);
  
  pinMode(fan, OUTPUT);
  pinMode(pi, OUTPUT);
  pinMode(gled,OUTPUT);
  pinMode(rled,OUTPUT);
  
Serial.println("kit started");
  Blynk.notify("KIT STARTED!!!!"); delay(1000);
  sms ("KIT STARTED");
  lcd1.clear();
  lcd.clear();
}

void loop()
{
  Serial.println("loop started");
  Blynk.run();

  temp2 = analogRead(temp); //read data from analog pin A1.
  float V = temp2 * (5 / (1023.00)); //conversion of analog voltage to digital voltage.
  temp1 = V * 100; //temperature in centigrade scale.
  Serial.print(F("temperature is = ")); Serial.println(temp1);
  delay(50);
weight = analogRead(weightPin);
ldr = analogRead(ldrPin);
Serial.println("weight= "+String(weight));
Serial.println("ldr= "+String(ldr));

  if (temp1 > 65)
  {
    digitalWrite(gled,LOW);
    digitalWrite(rled,HIGH);
    digitalWrite(pi, LOW);
    Serial.println(F("temperature alert*********"));
    lcd.clear();
    lcdstring(0, 0, "TEMPERATURE ALERT");
    lcdstring(0, 1, "please check......");
    delay(200);
    digitalWrite(fan, HIGH);
    // beep ();
    Blynk.notify("Temperature alert \nPresent Temp:" + String(temp1)); delay(200);
    lcd1.clear();
    lcd1.print(0, 0, "TEMPERATURE ALERT");
    lcd1.print(0, 1, "please check......");
    delay(2000);
    sms ("Temperature alert \nPresent Temp:" + String(temp1));
  }
  else
  {
    digitalWrite(fan,LOW);
  }
 if (digitalRead(rf) == HIGH)
  {
    digitalWrite(gled,LOW);
    digitalWrite(rled,HIGH);
    digitalWrite(pi, HIGH);
    Serial.println(F("rf alert*********"));
    lcd.clear();
    lcdstring(0, 0, "PATIENT FALL ALERT");
    lcdstring(0, 1, "please check......");
    delay(200);
    //digitalWrite(fan, LOW);
    // beep ();
    Blynk.notify("Patient Fall alert "); delay(200);
    lcd1.clear();
    lcd1.print(0, 0, "PATIENT FALL ALERT");
    lcd1.print(0, 1, "please check......");

    delay(2000);
    sms ("Patient Fall alert");
  }

else  if (weight > 600)
  {
    digitalWrite(gled,LOW);
    digitalWrite(rled,HIGH);
    digitalWrite(pi,LOW);
    Serial.println(F("OXIGEN CYLINDER IS EMPTY"));
    lcd.clear();
    lcdstring(0, 0, "CYLINDER IS EMPTY");
    lcdstring(0, 1, "please check......");
    delay(200);
    //digitalWrite(fan, LOW);
    // beep ();
    Blynk.notify("OXYGEN CYLINDER EMPTY\nPLEASE CHECK..."); delay(200);
    lcd1.clear();
    lcd1.print(0, 0, "CYLINDER  EMPTY    ");
    lcd1.print(0, 1, "please check......");

    delay(2000);
    sms ("OXYGEN CYLINDER EMPTY\nPLEASE CHECK...");
  }
else  if ((ldr > 95)&&(ldr<200))
  {
    digitalWrite(gled,LOW);
    digitalWrite(rled,HIGH);
    digitalWrite(pi,LOW);
    Serial.println(F("LEVEL IS LOW"));
    lcd.clear();
    lcdstring(0, 0, "LEVEL -- LOW");
    lcdstring(0, 1, "please check......");
    delay(200);
    //digitalWrite(fan, LOW);
    // beep ();
    Blynk.notify("LEVEL IS LOW\nPLEASE CHECK..."); delay(200);
    lcd1.clear();
    lcd1.print(0, 0, "LEVEL -- LOW");
    lcd1.print(0, 1, "please check......");

    delay(2000);
   sms ("LEVEL IS LOW\nPLEASE CHECK...");
  }
    /*
 else  if (digitalRead(ir) == LOW)
  {
       digitalWrite(gled,LOW);
    digitalWrite(rled,HIGH);
 digitalWrite(pi, HIGH);
    Serial.println(F("celine level alert*********"));
    lcd.clear();
    lcdstring(0, 0, "CELINE IS EMPTY     ");
    lcdstring(0, 1, "please check......");
    delay(200);
    //digitalWrite(fan, LOW);
    // beep ();
    Blynk.notify("Celine Empty alert "); delay(200);
    lcd1.clear();
    lcd1.print(0, 0, "CELINE IS EMPTY     ");
    lcd1.print(0, 1, "please check......");

    delay(2000);

    sms ("CELINE EMPTY ALERT");
  }
  */
else
  {
    digitalWrite(rled,LOW);
    digitalWrite(gled,HIGH);
    lcd.clear();
    lcdstring(0, 0, "Temp:" + String(temp1));
    lcdstring(0, 1, "C:F");
    lcdstring(8, 1, "BL:F");
    delay(300);
     lcd1.clear();
    lcd1.print(0, 0, "Temp:" + String(temp1));
    lcd1.print(0, 1, "C:F");
    lcd1.print(8, 1, "BL:F");
    delay(300);
  }


}
void sms (String xx)
{
  lcd1.clear();
  lcd1.print(0,0,"sending sms ");
  lcd1.print(0,1,".............");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("sending sms.......... ");
  Serial1.print("AT\r\n");
  Serial1.print('\n');
  ShowSerialData();
  delay(3000);
  Serial1.print("ATE1\r\n");
  ShowSerialData();
  delay(3000);
  Serial1.print("AT&W\r\n");
  Serial1.print('\n');
  ShowSerialData();
  delay(3000);
  Serial1.print("AT+CMGF=1\r\n");
  ShowSerialData();
  delay(3000);
  Serial1.print("AT+CNMI=2,2,0,0,0\r\n");
  ShowSerialData();
  delay(2000);
  // Serial.print("AT+CSMP=17,167,0,0\n");
  delay(2000);
  Serial1.print("AT+CMGS=\"09573809538\"\r");
  ShowSerialData();
  // Serial.print('"');
  //Serial.print("9014449822");
  //Serial.print('"');
  //Serial.print('\r');
  Serial1.print('\n');
  delay(1000);
  Serial1.print(xx);
  // Serial1.print("EMPTY \n");
  Serial1.print('\r');
  Serial1.print('\n');

  delay(3000);
  Serial1.print((char)26);
  ShowSerialData();
  lcd.setCursor(0, 0);
  lcd.print("****sms sent****");
  delay(5000);

}
void ShowSerialData()
{
  while (Serial1.available() != 0)
    Serial.write(char (Serial1.read()));
}
