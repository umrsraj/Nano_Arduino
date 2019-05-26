#include <SoftwareSerial.h>
#include<LiquidCrystal.h>
#include "WiFiEsp.h"
#include<String.h>
#include<stdlib.h>

#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif

int iron = 0;

int flag = 0;
int i=0,j=0,k=0,l=0;
LiquidCrystal lcd (2,3,4,5,6,7); //rs e d4 d5 d6 d7 

//SoftwareSerial SIM900(12,13);
#define led 13
/*#define p1 8
#define p2 9
#define p3 10
#define p4 11
*/
#define button1 8
#define button2 9
#define button3 10
#define button4 11
const int xpin = A6;                  // x-axis of the accelerometer
#define m1 A2
#define m2 A3
#define buzzer 5
#define vib A0

#define metal A1
char v,m;

char pass2[5] = "\0";
char pass1[5] = "1234";
char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";
char server1[] = "sms.scubedigi.com";

String A = "GET /IoTProjects/ATMSecurity/upload.php?a=";
String Z = " HTTP/1.1";
String msg = "GET /api.&to=";
// "GET /api.php?username=Mydreamacd&password=M&to=&from=MYDREM&message=WELCOME%20MESSAGE HTTP/1.1"
String iot = "\0";
String bulk = "\0";

// Initialize the Ethernet client object
WiFiEspClient client;




void beep(void)
{
  digitalWrite(buzzer, HIGH);
  delay(700);
  digitalWrite(buzzer, LOW);
  delay(100);
}

void setup() {                
           // enable debug serial
  Serial.begin(9600);
//   SIM900.begin(9600);
   Serial.println(" WELCOME ");
   Serial.println(" ....... ");
/*    pinMode(p1,INPUT);
    pinMode(p2,INPUT);
     pinMode(p3,INPUT);
      pinMode(p4,INPUT);
  */    
pinMode(button1,INPUT);
pinMode(button2,INPUT);
pinMode(button3,INPUT);
pinMode(button4,INPUT);

      pinMode(vib,INPUT);
  
      pinMode(metal,INPUT);
  pinMode(led, OUTPUT);  
  pinMode(buzzer, OUTPUT);  
    lcd.begin(16,2);
        lcd.clear();
        lcd.setCursor(4,0);
        lcd.print("WELCOME");
        lcd.setCursor(0,1);
        lcd.print("..............");
      delay(2000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("****ATM THEFT***");
        lcd.setCursor(5,1);
        lcd.print("ALERT");
        
       delay(2000);
  
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);

 

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println(F("WiFi shield not present"));
    // don't continue
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("WIFI NT DETECTED");
    lcd.setCursor(0,1);
    lcd.print("PLEASE CHECK....");
  delay(200);
    //while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print(F("Attempting to connect to WPA SSID: "));
    Serial.println(ssid);
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" CONNECTING TO  ");
    lcd.setCursor(3,1);
    lcd.print(ssid);
  delay(200);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("SERVER INIT");
    lcd.setCursor(3,1);
    lcd.print(".................");
  delay(200);
  // you're connected now, so print out the data
  Serial.println(F("You're connected to the network"));

    Serial.println(F("sending data ---1 "));
    Serial.println(F("Starting connection to server..."));
    // if you get a connection, report back via serial
    if (client.connect(server, 80)) {
      Serial.println(F("Connected to server"));
      // Make a HTTP request
      client.println("GET /IoTProjects/ATMSecurity/upload.php?a=U HTTP/1.1");
      client.println("Host: projectsiot.xyz");
      //client.println("Connection: close");
      client.println();
    }
  //  client.flush();
    // client.stop();

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("SERVER INIT");
    lcd.setCursor(3,1);
    lcd.print("done");
  delay(500);
Serial.println(F("PLEASE SHOW CARD "));

  
    lcd.clear();
    
    lcd.setCursor(0,0);
    lcd.print("ENTER PWD:        ");
    lcd.setCursor(0,1);
    lcd.print("                    ");
  i=0;
}

// ====================================================================== loop
void loop()
{

while(i<4)
{
  if (digitalRead(button1) == HIGH)
  {
      Serial.println("BUTTON --1");
    pass2[i]='1';
    lcd.setCursor(i,1);
    lcd.print(pass2[i]);
    i++;
    delay(100);
    while(digitalRead(button1)==HIGH);
  }
  else if (digitalRead(button2) == HIGH)
  {
      Serial.println("BUTTON --2");
    pass2[i]='2';
    lcd.setCursor(i,1);
    lcd.print(pass2[i]);
    i++;
    delay(100);
    while(digitalRead(button2)==HIGH);
  }
   else if (digitalRead(button3) == HIGH)
  {
      Serial.println("BUTTON --3");
    pass2[i]='3';
    lcd.setCursor(i,1);
    lcd.print(pass2[i]);
    i++;
    delay(100);
    while(digitalRead(button3)==HIGH);
  }
  else if (digitalRead(button4) == HIGH)
  {
      Serial.println("BUTTON --4");
    pass2[i]='4';
    lcd.setCursor(i,1);
    lcd.print(pass2[i]);
    i++;
    delay(100);
    while(digitalRead(button4)==HIGH);
  } 


    pass2[4] = '\0';
  Serial.print(F("enterred password = ")); Serial.println(pass2);
 // i = 0;
}     
   if(strcmp(pass2,pass1)==0)  
  {    lcd.setCursor(0,0);
          lcd.print("ATM DOOR UNLOCK");
          
         lcd.setCursor(0,1);
          lcd.print("                 ");
       
      open_door();
         
            delay(2500);
            while(1)
            {
    check();
            }
      //    flag=1;
  }
  else
  {
       lcd.setCursor(0,0);
          lcd.print("Enter PWD:       ");
          
         lcd.setCursor(0,1);
          lcd.print("                 ");
            delay(2500);
      i=0;
  }
   

        
 delay(1000); 
}//loop

void open_door()
{
 // lcd.setCursor(11,1);
 // lcd.print("O");
  Serial.println("Door Open");
  digitalWrite(m1,LOW);
  digitalWrite(m2,HIGH);
  delay(5000);
//  Serial.println("HALT");
  digitalWrite(m1,LOW);
  digitalWrite(m2,LOW);
  delay(7000);
//  Serial.println("Gate Close");
}

void close_door()
{
    Serial.println("Door Closed");
    digitalWrite(m1,HIGH);
  digitalWrite(m2,LOW);
  delay(5000);
  //lcd.setCursor(11,1);
 // lcd.print("C");
//  Serial.println("HALT");
  digitalWrite(m1,LOW);
  digitalWrite(m2,LOW);

}

void check(void)
{
   v='N';
        m='N';
iron = analogRead(metal);
        
Serial.println("vib = " +String(vib));
Serial.println("metal = " +String(iron));


        
      if(digitalRead(vib)==LOW)
       {   Serial.println("THEFT ALERT");
        
       lcd.setCursor(0,0);
       lcd.print("ATM MOVEMENT");

       lcd.setCursor(0,1);
       lcd.print("               ");
       delay(1500);
       close_door();
       beep();
       lcd.setCursor(0,1);
       lcd.print("ATM DOOR LOCK  ");delay(1500);
       v='Y';
       }
       
       else if(iron > 300)
       {   Serial.println("bomb ALERT");
        
       lcd.setCursor(0,0);
       lcd.print("METAL DETECTED ");
       
       lcd.setCursor(0,1);
       lcd.print("               ");
       delay(1500);
       close_door();
       beep();
       lcd.setCursor(0,1);
       lcd.print("ATM DOOR LOCK  ");delay(1500);
       m='Y';
       }
       else
       {
        v='N';
        m='N';
        delay(100);
         
        }

   //iot = A+v+"&b="+m+Z;

       Serial.println(A+m+"&b="+v+Z);
       // sndit ();
 // ************************************************
  // if the server's disconnected, stop the client
  if (!client.connected()) {
    Serial.println(F("Disconnecting from server..."));
    client.stop();

    // do nothing forevermore
    //while (true);
  }
  //client.stop();
  //client.flush();

//  for (int x = 0; x < 2; x++)
//  {
//    delay(1000);
//    Serial.println(x, DEC);
//  }
  Serial.println(F("Starting connection to server..."));
  // if you get a connection, report back via serial
  if (client.connect(server, 80)) {
    Serial.println(F("Connected to server"));
    // Make a HTTP request

    //client.println("GET /IoTProjects/TollBooth/tollbooth.php?a=A&b=5&c=6&d=3 HTTP/1.1");

    client.println(A+m+"&b="+v+Z);

    client.println("Host: projectsiot.xyz");
    //client.println("Connection: close");
    client.println();
  }
    client.stop();
  
}
