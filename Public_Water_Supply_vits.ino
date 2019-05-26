#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
char auth[] = "e94e67e532e04e7191c4c1abcd0d0cca";
//char auth[] = "d65b617278f44e3da3b6cb1886d028b5"; //LYNK AUTHENTICATION----------
char ssid[] = "AMBEST Technologies";
char pass[] = "AmBeSt@@321";
#define ESP8266_BAUD 9600
ESP8266 wifi(&Serial);

//////////////////////////////////////////////////
#include<LiquidCrystal.h>
LiquidCrystal lcd (A0,A1,A2,A3,A4,A5);
#define soil_sen1 10
#define soil_sen2 11
#define soil_sen3 12

#define led_red 6
#define led_grn 7
#define relay1 4
#define bz 5
///////////////////////////////////////////////////
void buz()
{
  digitalWrite(bz,1);
  delay(1500);
  digitalWrite(bz,0);
}

void led_red_on()
{
  digitalWrite(led_red,1);
  digitalWrite(led_grn,0);
}

void led_grn_on()
{
  digitalWrite(led_red,0);
  digitalWrite(led_grn,1);
}

///////////////////
WidgetLCD lcd1(V1);  //VIRTUAL LCD..
///////////////////

void setup()
{  
   pinMode(soil_sen1,INPUT);
   pinMode(soil_sen2,INPUT);
   pinMode(soil_sen3,INPUT);
   pinMode(relay1,OUTPUT);
   pinMode(bz,OUTPUT);
   lcd.begin(16,2);
   lcd.setCursor(4,0); 
   lcd.print("WELCOME");
   lcd.setCursor(0,1); 
   lcd.print(" ................ ");
//digitalWrite(bz,1);
   
   Serial.begin(9600);
   Serial.println("WELCOME");
   Serial.begin(ESP8266_BAUD);
   delay(10);

    Blynk.begin(auth, wifi, ssid, pass);
buz();
   lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("PUBLIC WATER");
        lcd.setCursor(0,1);
         lcd.print("SUPPLY GRID MONT.");
         delay(2000);

   
     lcd1.clear();
  lcd1.print(0, 0, "PUBLIC WATER");
  lcd1.print(0, 1, "SUPPLY GRID MONT.");
  digitalWrite(relay1,LOW);
   
   Serial.println("PUBLIC WATER SUPPLY GRID MONITORING");
   delay(500);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("PL1:");
   lcd.setCursor(8,0);
   lcd.print("PL2:");
   lcd.setCursor(0,1);
   lcd.print("PL3:");
buz();buz();  
  lcd1.clear();
  lcd1.print(0, 0, "PL1:");
  lcd1.print(8, 0, "PL2:");
  lcd1.print(0, 1, "PL3:");

}

void loop() 
{  
  Blynk.run();
  soil_sensor1();
  soil_sensor2();
  soil_sensor3();
  delay(2000);
}

void soil_sensor1()
{
    if(digitalRead(soil_sen1)==1)
    {
     lcd.setCursor(4,0);
     lcd.print("WL ");
     lcd1.print(4, 0, "WL ");
     Serial.println("PL1 LEAKAGE ALERT!"); 
    
    led_red_on();
    buz();
    }
    else{
      lcd.setCursor(4,0);
     lcd.print("NWL");
     lcd1.print(4, 0, "NWL");
      Serial.println("PL1 NO LEAKGAE:)"); 
      
    led_grn_on();
    
    }
}

void soil_sensor2()
{
    if(digitalRead(soil_sen2)==1)
    {
     lcd.setCursor(12,0);
     lcd.print("WL ");
     lcd1.print(12, 0, "WL ");
     Serial.println("PL2 LEAKAGE ALERT!!"); 
   
    led_red_on();
    buz();
    
    }
    else{
      
     lcd.setCursor(12,0);
     lcd.print("NWL");
     lcd1.print(12, 0, "NWL");
      Serial.println("PL2 NO LEAKGAE:)"); 
      
    led_grn_on();
    
    }
}

void soil_sensor3()
{
    if(digitalRead(soil_sen3)==1)
    {
     lcd.setCursor(4,1);
     lcd.print("WL ");
     lcd1.print(4, 1, "WL ");
     Serial.println("PL3 LEAKAGE ALERT!!"); 
     
    led_red_on();
    buz();
    
    }
    else{
      
     lcd.setCursor(4,1);
     lcd.print("NWL");
     lcd1.print(4, 1, "NWL");
      Serial.println("PL3 NO LEAKAGE:)"); 
      
    led_grn_on();
    
    }
}
