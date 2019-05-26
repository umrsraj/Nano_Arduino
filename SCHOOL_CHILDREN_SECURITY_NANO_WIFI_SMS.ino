/*
  WiFiEsp example: WebClient

  This sketch connects to google website using an ESP8266 module to
  perform a simple web search.

  For more details see: http://yaab-arduino.blogspot.com/p/wifiesp-example-client.html
*/

// http://sms.scubedigi.com/api.php?username=xxxx&password=xxxx&to=xxxxxxxxx&from=&message=xxxxxxxxxxxx
// http://projectsiot.xyz/IoTProjects/TollBooth/tollbooth.php?a=A&b=5&c=6&d=3
#include "WiFiEsp.h"
#include<String.h>
#include <LiquidCrystal.h>


// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif

LiquidCrystal lcd (A0, A1, A2, A3, A4, A5);

#define m11 4
#define m12 5
#define buzzer 6
#define gled 7
#define rled 8

int count1 = 0;                                          // count = 0
char input[12];

unsigned int flag = 0;
unsigned int flag1 = 0;

void beep ()
{
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(100);
}

void forward ()
{
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  delay(50);
}
void backward ()
{
  digitalWrite(m12, HIGH);
  digitalWrite(m11, LOW);
  delay(50);
}

void stop_motor ()
{
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  delay(50);
}


char ssid[] = "AMBEST Technologies";            // your network SSID (name)
char pass[] = "AmBeSt@@321";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";
char server1[] = "sms.scubedigi.com";

String A = "GET /IoTProjects/SchoolChildSecurity/childupdate.php?a=";
String Z = " HTTP/1.1";
String msg = "GET /api.php?username=Mydreamacd&password=Mydre@m123&to=";
// "GET /api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=WELCOME%20MESSAGE HTTP/1.1"
String iot = "\0";
String bulk = "\0";

// 9652490222&from=MYDREM&message=person1%20detected"

// Initialize the Ethernet client object
WiFiEspClient client;

void setup()
{
  // initialize serial for debugging
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
         lcd.print("   WELCOME TO   ");
        lcd.setCursor( 2,1);
         lcd.print("SCHOOL CHILDREN");
         delay(1000);

lcd.clear();
lcd.setCursor(0,0);
        lcd.print(" SECURITY BASED ");
        lcd.setCursor( 2,1);
         lcd.print("----ON RFID-----");
         delay(100);

  pinMode(buzzer, OUTPUT);
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(gled, OUTPUT);
  pinMode(rled, OUTPUT);

  digitalWrite(rled, LOW);
  digitalWrite(gled, LOW);

  // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println(F("WiFi shield not present"));
    // don't continue
    while (true);
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
    // if you get a connection, report back via serial
    if (client.connect(server, 80)) {
      Serial.println(F("Connected to server"));
      // Make a HTTP request
      client.println("GET /IoTProjects/SchoolChildSecurity/childupdate.php?a=U&b=0 HTTP/1.1");
      client.println("Host: projectsiot.xyz");
      client.println("Connection: close");
      client.println();
    }
    client.flush();
     client.stop();
  
    /////////////////////////////////////////
    ////////// initial message .......
    Serial.println(F("Starting connection to SMS server..."));
    delay(2000);

    // if you get a connection, report back via serial
    if (client.connect(server1, 80)) {
      Serial.println(F("Connected to server"));
      // Make a HTTP request
      client.println("GET /api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=KIT%20STARTED HTTP/1.1");
      client.println("Host: sms.scubedigi.com");
      client.println("Connection: close");
      client.println();
    }
    client.flush();
      client.stop();

  
Serial.println(F("PLEASE SHOW CARD "));
}

void loop()
{
  // ****************************************

  lcd.setCursor(0, 0);
  lcd.print("Please show card          ");
  lcd.setCursor(0, 1);
  lcd.print("                          ");

  if (Serial.available())
  {
    count1 = 0;
    while (Serial.available() && count1 < 12)         // Read 12 characters and store them in input array
    {
      input[count1] = Serial.read();
      count1++;
      delay(5);
    }//WHILE
    //

    Serial.println(input);                           // Print RFID tag number
    Serial.print(F("input[10] is ")); Serial.println(input[10]);

   if (input[10]=='C')
//    if (input[10] == '6')
    {

if (flag == 0)
{
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("STUDENT-1 MATCHED"); 
  
 digitalWrite(rled,LOW);
 digitalWrite(gled,HIGH);

  input[10]='\0';


 //*************  0 - BALANCE **********************
 
  // if the server's disconnected, stop the client
  if (!client.connected()) {
    Serial.println(F("Disconnecting from server..."));
    client.stop();

    // do nothing forevermore
    //while (true);
  }
  
   client.stop();
  client.flush();
for(int x = 0; x<2; x++)
{
  delay(1000);
  Serial.println(x,DEC);
}
    Serial.println(F("Starting connection to server..."));
  // if you get a connection, report back via serial
  if (client.connect(server1, 80)) {
    Serial.println(F("Connected to server"));
    // Make a HTTP request
    
 // Serial.print(F("q == ")); Serial.println(q);
    client.println(msg+"9652490222"+"&from=MYDREM&message="+"STUDENT-1%20ENTERING"+Z);
    
    client.println("Host: sms.scubedigi.com");
    client.println("Connection: close");
    client.println();
    
  }
// *****************************************
        delay(2000);

        // str = A+"A"+B+"0"+C+String(amount)+D+"N"+Z;
        iot = A + 'A' + "&b=" + 'Y' + Z;

        Serial.println(iot);
        sndit ();

        delay(3000);

      
      
  lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("STUDENT-1 MATCHED");  
    lcd.setCursor(0,1);
    lcd.print("**** ENTRY *****");
      delay(500);

      forward ();
      delay(1500);
      stop_motor ();
      delay(2000);
      backward ();
      delay(1500);
      stop_motor();

      // digitalWrite(rled,LOW);
      // digitalWrite(gled,LOW);
flag = 1;
}//IF FLAG == 0   
 
else if (flag == 1)
{
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("STUDENT-1 MATCHED"); 
  
 digitalWrite(rled,LOW);
 digitalWrite(gled,HIGH);

  input[10]='\0';


 //*************  0 - BALANCE **********************
 
  // if the server's disconnected, stop the client
  if (!client.connected()) {
    Serial.println(F("Disconnecting from server..."));
    client.stop();

    // do nothing forevermore
    //while (true);
  }
  
   client.stop();
  client.flush();
for(int x = 0; x<2; x++)
{
  delay(1000);
  Serial.println(x,DEC);
}
    Serial.println(F("Starting connection to server..."));
  // if you get a connection, report back via serial
  if (client.connect(server1, 80)) {
    Serial.println(F("Connected to server"));
    // Make a HTTP request
    
 // Serial.print(F("q == ")); Serial.println(q);
    client.println(msg+"9652490222"+"&from=MYDREM&message="+"STUDENT-1%20LEAVING"+Z);
    
    client.println("Host: sms.scubedigi.com");
    client.println("Connection: close");
    client.println();
    
  }
// *****************************************
        delay(2000);

        // str = A+"A"+B+"0"+C+String(amount)+D+"N"+Z;
        iot = A + 'A' + "&b=" + 'N' + Z;

        Serial.println(iot);
        sndit ();

        delay(1000);
          
  lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("STUDENT-1 MATCHED");  
    lcd.setCursor(0,1);
    lcd.print("**** EXIT *****");
      delay(500);

      forward ();
      delay(1500);
      stop_motor ();
      delay(2000);
      backward ();
      delay(1500);
      stop_motor();

       digitalWrite(rled,LOW);
       digitalWrite(gled,LOW);
flag = 0;
}//IF FLAG == 1    
    } // CARD-1

/////////////////  2ND CARD /////////////////////////////////   
  else if (input[10] == 'A')
    {
      if (flag1 == 0)
{
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("STUDENT-2 MATCHED"); 
  
 digitalWrite(rled,LOW);
 digitalWrite(gled,HIGH);

  input[10]='\0';       

 //*************card-2  0 - BALANCE **********************
 
  // if the server's disconnected, stop the client
  if (!client.connected()) {
    Serial.println(F("Disconnecting from server..."));
    client.stop();

    // do nothing forevermore
    //while (true);
  }
  
   client.stop();
  client.flush();
for(int x = 0; x<2; x++)
{
  delay(1000);
  Serial.println(x,DEC);
}
    Serial.println(F("Starting connection to server..."));
  // if you get a connection, report back via serial
  if (client.connect(server1, 80)) {
    Serial.println(F("Connected to server"));
    // Make a HTTP request
    
 // Serial.print(F("q == ")); Serial.println(q);
    client.println(msg+"7396010206"+"&from=MYDREM&message="+"STUDENT-2%20ENTERING"+Z);
    
    client.println("Host: sms.scubedigi.com");
    client.println("Connection: close");
    client.println();
    
  }
// *****************************************
        delay(1000);

        //str = A+"B"+B+"0"+C+String(amount1)+D+"N"+Z;
        iot = A +  'B' + "&b=" + 'Y' + Z;
        
        Serial.println(iot);
        sndit ();

        delay(1000);
  lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("STUDENT-2 MATCHED");  
    lcd.setCursor(0,1);
    lcd.print("**** ENTRY *****");
      delay(500);

      forward ();
      delay(1500);
      stop_motor ();
      delay(2000);
      backward ();
      delay(1500);
      stop_motor();

      // digitalWrite(rled,LOW);
      // digitalWrite(gled,LOW);
flag1 = 1;
}//IF FLAG == 0    

else   if (flag1 == 1)
{
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("STUDENT-2 MATCHED"); 
  
 digitalWrite(rled,LOW);
 digitalWrite(gled,HIGH);

  input[10]='\0';       

 //*************card-2  0 - BALANCE **********************
 
  // if the server's disconnected, stop the client
  if (!client.connected()) {
    Serial.println(F("Disconnecting from server..."));
    client.stop();

    // do nothing forevermore
    //while (true);
  }
  
   client.stop();
  client.flush();
for(int x = 0; x<2; x++)
{
  delay(1000);
  Serial.println(x,DEC);
}
    Serial.println(F("Starting connection to server..."));
  // if you get a connection, report back via serial
  if (client.connect(server1, 80)) {
    Serial.println(F("Connected to server"));
    // Make a HTTP request
    
 // Serial.print(F("q == ")); Serial.println(q);
    client.println(msg+"7396010206"+"&from=MYDREM&message="+"STUDENT-2%20LEAVING"+Z);
    
    client.println("Host: sms.scubedigi.com");
    client.println("Connection: close");
    client.println();
    
  }
// *****************************************
        delay(1000);

        //str = A+"B"+B+"0"+C+String(amount1)+D+"N"+Z;
        iot = A +  'B' + "&b=" + 'N' + Z;
        
        Serial.println(iot);
        sndit ();

        delay(1000);
  lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("STUDENT-2 MATCHED");  
    lcd.setCursor(0,1);
    lcd.print("**** EXIT *****");
      delay(500);

      forward ();
      delay(1500);
      stop_motor ();
      delay(2000);
      backward ();
      delay(1500);
      stop_motor();

       digitalWrite(rled,LOW);
      digitalWrite(gled,LOW);
flag1 = 0;
}//IF FLAG == 1    



    } // 2nd card

    else
    {
      digitalWrite(gled, LOW);
      digitalWrite(rled, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  INVALID CARD  ");
      delay(1600);
      lcd.setCursor(0, 1);
      lcd.print("***PLZ CHECK***");
      beep  ();
      delay(1700);
      
 iot = A + 'H' + "&b=" + 'N' + Z;
        
        Serial.println(iot);
        sndit ();

        delay(1000);
        
    }// else
  }// serial available

}// loop

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
