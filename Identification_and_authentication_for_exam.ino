#include <Adafruit_Fingerprint.h>
#include<LiquidCrystal.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial (2,3);
SoftwareSerial pc (12,13);
LiquidCrystal lcd (A0,A1,A2,A3,A4,A5);

///////////////////// finger print //////////////////////

#define en_sw  4
#define ver_sw 5
#define bz     6

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

uint8_t id=0;
int i=0;
int flagg = 1;

int getFingerprintIDez();

void setup()  
{
  Serial.begin(9600);
  pc.begin(9600);
  pc.listen();
  delay(100);
  pc.println("IDENTITY AUTHENTICATION FOR EXAMINATION SYSTEM  ");
  delay(1000);
  mySerial.listen();
  delay(500); 
  pinMode(en_sw,INPUT_PULLUP);
  pinMode(ver_sw,INPUT_PULLUP);
  pinMode(bz,OUTPUT);
 
 lcd.begin(16,2);

 lcd.clear();
 lcd.setCursor(4,0);
 lcd.print("WELCOME");
 lcd.setCursor(0,1);
 lcd.print(" .............. ");

 Serial.println(F("WELCOME"));

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
  
 buz();
 delay(1000);
 lcd.setCursor(0,0);
 lcd.print("IDENTITY AUTH       ");
 lcd.setCursor(0,1);
 lcd.print("FR EXAMINATION S/M    ");
  Serial.println(F("IDENTITY AUTHENTICATION FOR EXAMINATION SYSTEM  "));
 delay(2000);
 

}


uint8_t readnumber(void) {
  uint8_t num = 0;
  
  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}


void loop()                     // run over and over again
{
  lcd.clear();
      if(digitalRead(en_sw)==0)      {
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
    
            if (ID > 0)
            {
            Serial.println(F("Match Found With ID "));
            
            lcd.setCursor(0,0);                                
            lcd.print("FINGER MATCHED          ");
            lcd.setCursor(0,1);                                
            lcd.print("PERSON - ");                            
            lcd.print(String(ID)+"             ");
            delay(200);
            
  pc.listen();
  delay(100);
  pc.println("FINGER PRINT MATCHED");
  delay(100);
  pc.print("PERSOR-");
  delay(100);
  pc.println(String(ID)+"             ");
  delay(100);
  mySerial.listen();
  delay(500);
            lcd.clear();
          }
         
          else{
            Serial.println("Match Not Found");
            
            lcd.setCursor(0,0);
            lcd.print("FINGER NT MATCHED");
            lcd.setCursor(0,1);
            lcd.print("PLS. TRY AGAIN     ");
            
            digitalWrite(bz,HIGH);delay(1500);digitalWrite(bz,LOW); 
             
             pc.listen();
             delay(100);
  pc.println("FINGER PRINT NOT MATCHED");
  delay(200); 
  mySerial.listen();
  delay(500);
            
            lcd.clear();     
            }     
      }
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
