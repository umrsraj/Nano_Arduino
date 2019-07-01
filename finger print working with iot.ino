#include <Adafruit_Fingerprint.h>
#include<LiquidCrystal.h>
#include <stdlib.h>
#include <String.h>
#define mySerial Serial2
LiquidCrystal lcd (A0,A1,A2,A3,A4,A5);

///////////////////// finger print //////////////////////

#define ps_bt 3
#define en_sw  4
#define ver_sw 5
#define bz     A7

#define button1 10
#define button2 11
#define button3 12
#define button4 13

#define p1 6
#define p2 7
#define p3 8
#define p4 9

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

char passs[5] = "\0";
char pass1[5] = "1234";
char pass2[5] = "1111";
char pass3[5] = "2222";
char pass4[5] = "3333";
char pass5[5] = "4444";

uint8_t id=0;
int i=0;
int rr = 0;
int flagg = 1;

 int a=0,b=0,c=0,d=0;
int u1=0,u2=0,u3=0,u4=0,u5=0,u6=0,u7=0;
int getFingerprintIDez();

////////////////////////////////////////////////////////
//http://projectsiot.xyz/IoTProjects/ForthGeneration/display.php
#include "WiFiEsp.h"
#include<String.h>
// Emulate Serial1 on pins 7/6 if not present

char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password

//char ssid[] = "AMBEST Technologies";            // your network SSID (name)
//char pass[] = "AmBeSt@@321";        // your network password

int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";
//http://projectsiot.xyz/IoTProjects/ForthGeneration/fp.php?a=0&b=0&c=0&d=0
String A = "GET /IoTProjects/ForthGeneration/fp.php?a=";
String B = "&b=";
String C = "&c=";
String D = "&d=";
//String E = "&e=";
String Z = " HTTP/1.1";
String iot = "\0";
  
WiFiEspClient client;
void setup()  
{
  Serial.begin(9600);
  Serial1.begin(9600);
  //finger.begin(9600);
  pinMode(en_sw,INPUT_PULLUP);
  pinMode(ver_sw,INPUT_PULLUP);

pinMode(button1,INPUT);
pinMode(button2,INPUT);
pinMode(button3,INPUT);
pinMode(button4,INPUT);

pinMode(ps_bt,INPUT);
   
   pinMode(p1,INPUT_PULLUP);
    pinMode(p2,INPUT_PULLUP);
     pinMode(p3,INPUT_PULLUP);
      pinMode(p4,INPUT_PULLUP);
  pinMode(bz,OUTPUT);
 lcd.begin(16,2);
 lcd.setCursor(4,0);
 lcd.print("WELCOME");
 lcd.setCursor(0,1);
 lcd.print(" .............. ");

 Serial.println(F("WELCOME"));
// Serial1.println("WELCOME");
//////////////////////init finger print /////////////////////////

 while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println(F("\n\nAdafruit Fingerprint sensor enrollment & Verify"));
  finger.begin(9600);
  
  if (finger.verifyPassword()) {
    Serial.println(F("Found fingerprint sensor!"));
  } else {
    Serial.println(F("Did not find fingerprint sensor :("));
    while (1) { delay(1); }
  }

///////////////////////////////////////////////////////////////
  
  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println(F("WiFi shield not present"));
    // don't continue
    //while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print(F("Attempting to connect to WPA SSID: "));
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  // you're connected now, so print out the data
  Serial.println(F("You're connected to the network"));

  
    Serial.println(F("sending data ---1 "));
    Serial.println(F("Starting connection to server..."));
  ///printWifiStatus();

  if (client.connect(server, 80)) {
  Serial.println(F("Connected to server"));
     client.println("GET /IoTProjects/ForthGeneration/fp.php?a=U&b=0&c=0&d=0 HTTP/1.1");
      client.println("Host: projectsiot.xyz");
      client.println("Connection: close");
      client.println();
  }
  client.flush();
  client.stop();
   iot = A + "U" + B+'0'+C+'0'+D+'0'+ Z;
  sndit ();
  //client.println(postStr);
 buz();
 delay(1000);
 lcd.setCursor(0,0);
 lcd.print("SMART        ");
 lcd.setCursor(0,1);
 lcd.print("VOTING MACHINE");
  Serial.println(F("4TH GENERATION VOTING MACHINE"));
 delay(2000);
 lcd.clear();

Serial.print(F("A:"));
//Serial.print("\t");
Serial.print(a);

Serial.print(F("\t"));
Serial.print(F("B:"));
//Serial.print("\t");
Serial.print(b);

Serial.print(F("\t"));
Serial.print(F("C:"));
//Serial.print("\t");
Serial.print(c);

Serial.print(F("\t"));
Serial.print(F("D:"));
//Serial.print("\t");
Serial.print(d);


/*
///////////////////
lcd.setCursor(3,1);
lcd.print(a);
lcd.setCursor(6,1);
lcd.print(b);

lcd.setCursor(10,1);
lcd.print(c);
lcd.setCursor(15,1);
lcd.print(d);
////////////////////
*/

}


uint8_t readnumber(void) {
  uint8_t num = 0;
  
  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}

void voting()
{
 
while (flagg == 1)
        {
          Serial.println("in while");
         if(digitalRead(p1)==0){
         lcd.setCursor(0,0);    
         lcd.print("THANKS!");
         delay(1000);
         lcd.setCursor(0,0);    
         lcd.print("VOTE CAST TO P1");
          inc_a();
          Serial.print(F("A:"));
          Serial.print(F("\t"));
          Serial.print(a);
          flagg = 0;
        }
        
        else if(digitalRead(p2)==0){
         lcd.setCursor(0,0);    
         lcd.print("THANKS!");
         delay(1000);
         lcd.setCursor(0,0);    
         lcd.print("VOTE CAST TO P2");
        inc_b();
        Serial.print(F("\t"));
        Serial.print(F("B:"));
          Serial.print(F("\t"));
          Serial.print(b);
          flagg = 0;
        }

        else  if(digitalRead(p3)==0){
         lcd.setCursor(0,0);    
         lcd.print("THANKS!");
         delay(1000);
         lcd.setCursor(0,0);    
         lcd.print("VOTE CAST TO P3");
         inc_c();
         Serial.print(F("\t"));
        Serial.print(F("C:"));
          Serial.print(F("\t"));
          Serial.print(c);
          flagg = 0;
        }

       else  if(digitalRead(p4)==0){
         lcd.setCursor(0,0);    
         lcd.print("THANKS!");
         delay(1000);
         lcd.setCursor(0,0);    
         lcd.print("VOTE CAST TO P4");
        inc_d();
        Serial.print(F("\t"));
        Serial.print(F("D:"));
          Serial.print(F("\t"));
          Serial.println(d);
        flagg = 0;
        }
            /////////////////////
        }
}

void inc_a()
{
  a++;
}

void inc_b()
{
  b++;
}

void inc_c()
{
  c++;
}

void inc_d()
{
  d++;
}

void upload2_webpage()
{
  
  Serial.println(F("Please Wait...."));
  delay(500);
  Serial.println(F("Uploading Data Over Webpage...!"));
  delay(1000);
  Serial.println(a);
  Serial.println(b);
  Serial.println(c);
  Serial.println(d);
  iot = A+a + B+b + C+c + D+d + Z;
  sndit ();
  Serial.println(F("DATA SUCCESSFULLY UPLOADED....!"));
}


void loop()                     // run over and over again
{
      if(digitalRead(en_sw)==0)
      {
      id++;
      Serial.print(F("Enrolling ID #"));
      Serial.println(id);
      lcd.setCursor(0,0);
      lcd.print("Enrolling.......");
      delay(500);
      while (!  getFingerprintEnroll() );
      }

      if(digitalRead(ver_sw)==0)
      {
            lcd.setCursor(0,0);
            lcd.print("Ver.Finger To Acc");
            delay(2000);
            flagg = 1;
            finger.getTemplateCount();
            Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
            Serial.println("Waiting for valid finger..."); 
            int ID;
            ID=getFingerprintIDez();//returns  Finger Id
            delay(500);            //don't ned to run this at full speed.
     //     ID = 2;
            if(ID==1){
            Serial.println(F("Match Found With ID"));
            lcd.setCursor(0,1);                                
            lcd.print("MATCH FOUND 1");

            lcd.setCursor(0,0);                                
            lcd.print("ELECTION OFFICER");                   
            Serial.println("ELECTION OFFICER!");
             upload2_webpage();  
  delay(500);
  lcdstring (0,0,"DATA UPLOADED         ");
  lcdstring (0,1,"                      ");
            
               
                                }   
          else if(ID==2){
            u2++;
            if(u2==1){
            Serial.println("Match Found With ID");
            lcd.setCursor(0,1);                                
            lcd.print("MATCH FOUND 2");
           
            lcd.setCursor(0,0);                                
            lcd.print("CAST YOUR VOTE. ");
      
            voting();
            /////////////////////
            
            lcd.setCursor(0,1);                                
            lcd.print("                    ");
         
          }
          else{
            Serial.println("Match Found With ID");
            lcd.setCursor(0,1);                                
            lcd.print("PLEASE CHECK    ");
           
            lcd.setCursor(0,0);                                
            lcd.print("INVALID USER    ");
            digitalWrite(bz,HIGH);delay(1500);digitalWrite(bz,LOW);      
          }
          } 
          
          else if(ID==3){
            u3++;
            if(u3==1){
            Serial.println("Match Found With ID");
            lcd.setCursor(0,1);                                
            lcd.print("MATCH FOUND 3");
            lcd.setCursor(0,0);                                
            lcd.print("CAST YOUR VOTE. ");
            voting();
            lcd.setCursor(0,1);                                
            lcd.print("                    ");
          }
          else{
            Serial.println("Match Found With ID");
            lcd.setCursor(0,1);                                
            lcd.print("PLEASE CHECK    ");
           
            lcd.setCursor(0,0);                                
            lcd.print("INVALID USER    ");
            digitalWrite(bz,HIGH);delay(1500);digitalWrite(bz,LOW);      
          }
          }
          else if(ID==4){
            u4++;
            if(u4==1){
            Serial.println("Match Found With ID");
            lcd.setCursor(0,1);                                
            lcd.print("MATCH FOUND 4");
            lcd.setCursor(0,0);                                
            lcd.print("CAST YOUR VOTE. ");
            voting();
            lcd.setCursor(0,1);                                
            lcd.print("                    ");
          }
          else{
            Serial.println("Match Found With ID");
            lcd.setCursor(0,1);                                
            lcd.print("PLEASE CHECK    ");
           
            lcd.setCursor(0,0);                                
            lcd.print("INVALID USER    ");
            digitalWrite(bz,HIGH);delay(1500);digitalWrite(bz,LOW);      
          } 
          }
          
          else if(ID==5){
            u5++;
            if(u5==1){
            Serial.println("Match Found With ID");
            lcd.setCursor(0,1);                                
            lcd.print("MATCH FOUND 5");
            lcd.setCursor(0,0);                                
            lcd.print("CAST YOUR VOTE. ");
            voting();
          }
          else{
            Serial.println("Match Found With ID");
            lcd.setCursor(0,1);                                
            lcd.print("PLEASE CHECK    ");
           
            lcd.setCursor(0,0);                                
            lcd.print("INVALID USER    ");
            digitalWrite(bz,HIGH);delay(1500);digitalWrite(bz,LOW);      
          }
          }
         
          else{
            Serial.println("Match Not Found");
            digitalWrite(bz,HIGH);delay(1500);digitalWrite(bz,LOW);      
            lcd.setCursor(0,0);
            lcd.print("PLS. TRY AGAIN  ");
            }     
      }//VERIFICATION SWITCH

   if(digitalRead(ps_bt)==0)
      {
        lcd.clear ();
  lcdstring (0,0,"PLEASE ENTR PSWD");
  lcdstring (0,1,"****************");
  delay(2500);
 
  lcd.clear ();
  lcdstring (0,0,"    PASSWORD    ");

Serial.println("in password while loop");
rr = 0;
while(rr<4)
{
  Serial.println("rr = "+String(rr));
  
  if (digitalRead(button1) == HIGH)

  {
      Serial.println("BUTTON --1");
    passs[rr]='1';
    lcd.setCursor(rr,1);
    lcd.print(passs[rr]);
    rr++;
    delay(100);
    while(digitalRead(button1)==HIGH);
  }
  else if (digitalRead(button2) == HIGH)
  {
      Serial.println("BUTTON --2");
    passs[rr]='2';
    lcd.setCursor(rr,1);
    lcd.print(passs[rr]);
    rr++;
    delay(100);
    while(digitalRead(button2)==HIGH);
  }
   else if (digitalRead(button3) == HIGH)
  {
      Serial.println("BUTTON --3");
    passs[rr]='3';
    lcd.setCursor(rr,1);
    lcd.print(passs[rr]);
    rr++;
    delay(100);
    while(digitalRead(button3)==HIGH);
  }
  else if (digitalRead(button4) == HIGH)
  {
      Serial.println("BUTTON --4");
    passs[rr]='4';
    lcd.setCursor(rr,1);
    lcd.print('4');
    rr++;
    delay(100);
    while(digitalRead(button4)==HIGH);
  } 
      }// otp while
passs[4] = '\0';
Serial.print(F("enterred password = ")); Serial.println(passs);
i = 0;

   if(strcmp(passs,pass1)==0)  
  {    
    Serial.println("pasworddd  matched Election officer.....");
  lcdstring (0,0,"PASSWORD MATCHED     ");
  lcdstring (0,1,"ELECTION OFFICER      ");
  delay(1000);
  upload2_webpage();  
  delay(500);
  lcdstring (0,0,"DATA UPLOADED         ");
  lcdstring (0,1,"                      ");
  }
else if(strcmp(passs,pass2)==0)
{
  flagg = 1;
    Serial.println("pasworddd  matched PERSON-1 .....");
  u2++;
            if(u2==1){
              
            
  lcdstring (0,0,"PERSON - 1              ");
  lcdstring (0,1,"CAST YOUR VOTE.         ");
      
            voting();
            /////////////////////
            
            lcd.setCursor(0,1);                                
            lcd.print("                    ");
         
          }
          else{
            Serial.println("Match Found With ID");
            lcd.setCursor(0,1);                                
            lcd.print("PLEASE CHECK    ");
           
            lcd.setCursor(0,0);                                
            lcd.print("INVALID USER    ");
            digitalWrite(bz,HIGH);delay(1500);digitalWrite(bz,LOW);      
          }
}//1st person
/////////////////////////////////////
else if(strcmp(passs,pass3)==0)
{
  flagg = 1;
    Serial.println("pasworddd  matched PERSON-2 .....");
  u3++;
            if(u3==1){
            Serial.println("Match Found With ID");
   
  lcdstring (0,0,"PERSON - 2              ");
  lcdstring (0,1,"CAST YOUR VOTE.         ");
      
            voting();
            /////////////////////
            
            lcd.setCursor(0,1);                                
            lcd.print("                    ");
         
          }
          else{
            Serial.println("Match Found With ID");
            lcd.setCursor(0,1);                                
            lcd.print("PLEASE CHECK    ");
           
            lcd.setCursor(0,0);                                
            lcd.print("INVALID USER    ");
            digitalWrite(bz,HIGH);delay(1500);digitalWrite(bz,LOW);      
          }
}// 2ND person
/////////////////////////////////////
else if(strcmp(passs,pass4)==0)
{
  flagg = 1;
    Serial.println("pasworddd  matched PERSON-3 .....");
  u4++;
            if(u4==1){
            Serial.println("Match Found With ID");

  lcdstring (0,0,"PERSON - 3              ");
  lcdstring (0,1,"CAST YOUR VOTE.         ");
      
            voting();
            /////////////////////
            
            lcd.setCursor(0,1);                                
            lcd.print("                    ");
         
          }
          else{
            Serial.println("Match Found With ID");
            lcd.setCursor(0,1);                                
            lcd.print("PLEASE CHECK    ");
           
            lcd.setCursor(0,0);                                
            lcd.print("INVALID USER    ");
            digitalWrite(bz,HIGH);delay(1500);digitalWrite(bz,LOW);      
          }
}// 3RD person
///////////////////////////////////////////////////////////
else if(strcmp(passs,pass5)==0)
{
  u5++;
  flagg = 1;
    Serial.println("pasworddd  matched PERSON-4 .....");
    
            if(u5==1){
            Serial.println("Match Found With ID");
           
  lcdstring (0,0,"PERSON - 4              ");
  lcdstring (0,1,"CAST YOUR VOTE.         ");
      
            voting();
            /////////////////////
            
            lcd.setCursor(0,1);                                
            lcd.print("                    ");
         
          }
          else{
            Serial.println("Match Found With ID");
            lcd.setCursor(0,1);                                
            lcd.print("PLEASE CHECK    ");
           
            lcd.setCursor(0,0);                                
            lcd.print("INVALID USER    ");
            digitalWrite(bz,HIGH);delay(1500);digitalWrite(bz,LOW);      
          }
}// 4TH person
else
{
  lcdstring (0,0,"WRONG PASSWORD        ");
  lcdstring (0,1,"PLEASE TRY AGAIN         ");
  delay(1000);       
}
      }//ps_bt
} // Loop End
//////////////////////// INIT GSM/SMS SENDING START //////////////////////////////
void buz() 
{
  digitalWrite(bz,1);
  delay(200);
  digitalWrite(bz,0);
  delay(10);
  digitalWrite(bz,1);
  delay(200);
  digitalWrite(bz,0); 
}
/////////////////////////////////////////////////////////////////////////                          

//////////////  Enroll   ///////////////////

uint8_t getFingerprintEnroll() {

  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  Serial.println("Remove finger");
  lcd.setCursor(0,0);
  lcd.print("Remove Finger   ");
  buz(); 
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
 // lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Put Finger Again");
  delay(2000);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
 //   lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enroll Success  ");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
}
//////////////  Enroll End  ///////////////////

//////////////   Verify    ///////////////////

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}
////////////// Verify End ////////////////////
//___________________________________________//
void sndit ()
{

  Serial.print(F("A = ")); Serial.println(iot);

  // if the server's disconnected, stop the client
  if (!client.connected()) {
    Serial.println(F("Disconnecting from server..."));
    client.stop();

    // do nothing forevermore
    //while (true);
  }
  client.stop();
  client.flush();

  for (int x = 0; x < 2; x++)
  {
    delay(1000);
    Serial.println(x, DEC);
  }
  Serial.println(F("Starting connection to server..."));
  // if you get a connection, report back via serial
  if (client.connect(server, 80)) {
    Serial.println(F("Connected to server"));
    // Make a HTTP request

    //client.println("GET /IoTProjects/TollBooth/tollbooth.php?a=A&b=5&c=6&d=3 HTTP/1.1");

    client.println(iot);

    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
    iot = "\0";
  }
}


//---------------------------------------------//
void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
//---------------------------------------------//
void lcdstring(int a,int b, String data1)
{
  lcd.setCursor(a,b);
  lcd.print(data1);
}
