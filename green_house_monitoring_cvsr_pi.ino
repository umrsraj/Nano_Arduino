/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#define TINY_GSM_MODEM_SIM900

// Default heartbeat interval for GSM is 60
// If you want override this value, uncomment and set this option:
//#define BLYNK_HEARTBEAT 30

#include <TinyGsmClient.h>
#include <BlynkSimpleSIM800.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
// char auth[] = "f9d4b43dbced43169cc5d9d36f65326c";
char auth[] = "ed9c5669b0114042855947c8d9338b75";

// Your GPRS credentials
// Leave empty, if missing user or pass
char apn[]  = "internet";
char user[] = "";
char pass[] = "";

// Hardware Serial on Mega, Leonardo, Micro
#define SerialAT Serial1

// or Software Serial on Uno, Nano
//#include <SoftwareSerial.h>
//SoftwareSerial SerialAT(12, 13); // RX, TX

TinyGsm modem(SerialAT);


#include<LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <String.h>

#define temp A0
#define hum A1
#define light A2
#define SOIL A3
#define PH A4

#define led 8
#define fan 9
#define pump1 10
#define pump2 11

#define buzzer A5

LiquidCrystal lcd (2,3,4,5,6,7);

WidgetLCD lcd1(V0);

String voltageH = "\0";
String voltageR = "\0";
String voltageL = "\0";
String voltageT = "\0";

int v1,h,l,r ,phh;
int flag = 0;
int flag1=1;

void setup() {
  // put your setup code here, to run once:
Serial.begin (9600);
SerialAT.begin(9600);
  delay(3000);
  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  Serial.println("Initializing modem...");
  modem.init() ;
  //modem.restart();

  
  
lcd.begin (16,2);
Serial.println("power up");

pinMode (temp , INPUT);
pinMode (hum , INPUT);
pinMode (light , INPUT);
pinMode (SOIL , INPUT);
pinMode (PH , INPUT);
pinMode (buzzer , INPUT);
pinMode(fan,OUTPUT);
pinMode(pump1,OUTPUT);
pinMode(pump2,OUTPUT);


if (digitalRead(buzzer)==HIGH)
{
  Blynk.begin(auth, modem, apn, user, pass);
}
lcd.clear ();
lcd.setCursor (0,0);
lcd.print ("WELCOME TO GREEN");
lcd.setCursor (0,1);
lcd.print ("HOUSE MONITORING");
//beep();
delay(100);
lcd1.clear();
lcd1.print(0,0,"WELCOME TO GREEN");
lcd1.print(0,1,"HOUSE MONITORING");
delay (2000);

lcd.clear ();
lcd.setCursor (0,0);
lcd.print ("WEATHER REPORTING");
lcd.setCursor (0,1);
lcd.print ("    WITH IoT    ");
delay(100);

lcd1.clear();
lcd1.print(0,0,"WEATHER REPORTING");
lcd1.print(0,1,"    WITH IoT    ");
 //beep();
delay(2000);

}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println("LOOP STARTED....................");

if (digitalRead(buzzer)==HIGH)
{
  Serial.println("buzzer--HIGH");
Blynk.run();
}
r=analogRead(SOIL);
delay(50);

h=analogRead(hum);
delay(50);
l=analogRead(light);
delay(50);
phh=analogRead(PH);
delay(50);

 v1=analogRead(temp);
float voltage = (v1 /1024.0)*5000;
 float cel=voltage/10;
 

  delay(10);
  cel=cel+2;
Serial.print("hum is = "); Serial.println(h);
Serial.print("light is = "); Serial.println(l);
Serial.print("SOIL is = "); Serial.println(r);
Serial.print("temp is = "); Serial.println(cel);
Serial.print("PH is = "); Serial.println(phh);

Serial.println("//////////////////////");
/*
if (phh < 355)
{
Serial.println ("PH SENSOR  alert");
lcd.clear ();
lcd.setCursor (0,0);
lcd.print ("PH SENSOR ALERT    ");
lcd.setCursor (0,1);
lcd.print ("PLEASE CHECK............");
Blynk.notify("PH SENSOR ALERT\nPLEASE CHECK...."); delay(600);
//beep();

lcd1.clear();
lcd1.print(0,0,"PH SENSOR ALERT    ");
lcd1.print(0,1,"***PLZ CHECK***");
delay(100);
voltageH = "100";
delay (2000);
digitalWrite(pump2,HIGH);
delay(300);
//sms ("09177581517","PH SENSOR ALERT\nPLEASE CHECK......");
}
else 
{
  Serial.println ("PH normal\r\n");
  voltageH = "0";
digitalWrite(pump2,LOW);
delay(30);
}
*/
if (h<700)
{
Serial.println ("humidity alert");
lcd.clear ();
lcd.setCursor (0,0);
lcd.print (" HUMIDITY ALERT");
lcd.setCursor (0,1);
lcd.print ("H: "+String(h));
Blynk.notify("HUMIDITY ALERT\nPLEASE CHECK...."); delay(600);
//beep();

lcd1.clear();
lcd1.print(0,0," HUMIDITY ALERT");
lcd1.print(0,1,"***PLZ CHECK***");
delay(100);
voltageH = "100";
delay (2000);
//digitalWrite(pump2,HIGH);
digitalWrite(fan,HIGH);
delay(300);
sms ("09177581517","HUMIDITY ALERT\nPLEASE CHECK......");
}
else 
{
  Serial.println ("humidity normal\r\n");
  voltageH = "0";
//digitalWrite(pump2,LOW);
digitalWrite(fan,LOW);
delay(300);
}

if (l<100)
{
Serial.println ("NIGHT mode");
lcd.clear ();
lcd.setCursor (0,0);
lcd.print ("   NIGHT MODE   ");
lcd.setCursor (0,1);
lcd.print ("L: "+String(l));
//beep();
lcd1.clear();
lcd1.print(0,0,"   NIGHT MODE   ");
lcd1.print(0,1,"***PLZ CHECK***");
delay(100);
Blynk.notify("NIGHT MODE ");delay(500);
voltageL = "0";

digitalWrite(led,HIGH);
delay(300);
delay (2000);
}
else 
{
 Serial.println ("day mode detected\r\n");
  voltageL = "0";
digitalWrite(led,LOW);
delay(300); 
}
if (r<600)
{
Serial.println ("rain detected");
lcd.clear ();
lcd.setCursor (0,0);
lcd.print (" SOIL DETECTED ");
lcd.setCursor (0,1);
lcd.print ("S: "+String(r));
//beep();

lcd1.clear();
lcd1.print(0,0," SOIL DETECTED ");
lcd1.print(0,1,"***PLZ CHECK***");
delay(100);
voltageR = "100";
digitalWrite(pump1,HIGH);
delay(300);
delay (2000);

sms ("09177581517","SOIL DRY DETECTED\nMOTOR ON");
}
else
{
  delay(100);
digitalWrite(pump1,LOW);
delay(300);
}

if (cel>40)
{
Serial.println ("temperature increased");
lcd.clear ();
lcd.setCursor (0,0);
lcd.print ("TEMPERATURE ALERT");
lcd.setCursor (0,1);
lcd.print ("T: "+String(cel));
//beep();
lcd1.clear();
lcd1.print(0,0,"TEMPERATURE ALERT");
lcd1.print(0,1,"***PLZ CHECK***");
delay(100);
Blynk.notify("temperature alert\nplease check");delay(100);
voltageT = cel;
digitalWrite(fan,HIGH);
delay(300);
delay (2000);
sms ("09177581517","TEMPERATURE ALERT\nT: "+String(cel)+"\nPLEASE CHECK......");
}
else 
{
 Serial.println ("Temperature is normal \r\n");
  voltageT = cel ;
digitalWrite(fan,LOW);
delay(300); 
}
lcd.clear();
lcd.setCursor(0,0);
lcd.print("T:"+String(cel));
lcd.setCursor(8,0);
lcd.print("H:0");
lcd.setCursor(0,1);
lcd.print("L:"+String(voltageL));
lcd.setCursor(5,1);
lcd.print("R:0");
lcd.setCursor(10,1);
lcd.print("PH:0");
delay(50);

lcd1.clear();
lcd1.print(0,0,"T:"+String(cel));
lcd1.print(8,0,"H:0");
lcd1.print(0,1,"L:"+String(voltageL));
lcd1.print(5,1,"R:0");
lcd1.print(10,1,"PH:0");
delay(100);

}//loop
////////////////////////////////////
void sms (String yy, String xx)
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
  Serial1.print("AT+CMGS=\""+yy+"\"\r");
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
