/*
  WiFiEsp example: WebClient

  This sketch connects to google website using an ESP8266 module to
  perform a simple web search.

  For more details see: http://yaab-arduino.blogspot.com/p/wifiesp-example-client.html
*/

#include "WiFiEsp.h"
#include<String.h>
#include <LiquidCrystal.h>

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif

LiquidCrystal lcd (A0, A1, A2, A3, A4, A5);


int count1 = 0;                                          // count = 0
char input[12];

int flag1 = 0;
int flag2 = 0;

String s1 = "N";
String s2 = "N";

char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";

String A = "GET /IoTProjects/SchoolTransport/upload.php?a=";
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
        lcd.setCursor( 0,1);
         lcd.print("SCHOOL CHILDREN");
         delay(1000);

lcd.clear();
lcd.setCursor(0,0);
        lcd.print("TRANSPORTAION S/M ");
        lcd.setCursor( 0,1);
         lcd.print("--BSD ON RFID---");
         delay(1500);


  // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println(F("WiFi shield not present"));
    // don't continue
//    while (true);
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
      client.println("GET /IoTProjects/SchoolTransport/upload.php?a=U&b=0 HTTP/1.1");
      client.println("Host: projectsiot.xyz");
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

   if (input[10]=='4')
    {

if (flag1 == 0)
{
  flag1++;
  
  s1 = "A";
  
  input[10]='\0';

  lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("STUDENT-1 MATCHED");  
    lcd.setCursor(0,1);
    lcd.print("ENTERRED TO BUS   ");
      delay(2000);


        iot = A + s1 + "&b=" + s2 + Z;

        Serial.println(iot);
        sndit ();

}//IF FLAG1 == 0   
else if (flag1 == 1)
{
  flag1++;
  
  flag1 = 0;
  
  s1 = "B";
  
  input[10]='\0';

  lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("STUDENT-1 MATCHED");  
    lcd.setCursor(0,1);
    lcd.print("EXIT FROM BUS    ");
      delay(2000);

        iot = A + s1 + "&b=" + s2 + Z;

        Serial.println(iot);
        sndit ();

}//IF FLAG2 == 1
    }
 else if (input[10]=='B')
    {

if (flag2 == 0)
{
  flag2++;
  
  s2 = "A";
  
  input[10]='\0';

  lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("STUDENT-2 MATCHED");  
    lcd.setCursor(0,1);
    lcd.print("ENTERRED TO BUS   ");
      delay(2000);


        iot = A + s1 + "&b=" + s2 + Z;

        Serial.println(iot);
        sndit ();

}//IF FLAG1 == 0   
else if (flag2 == 1)
{
  flag2++;
  flag2 = 0;
  s2 = "B";
  
  input[10]='\0';

  lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("STUDENT-2 MATCHED");  
    lcd.setCursor(0,1);
    lcd.print("EXIT FROM BUS    ");
      delay(2000);

        iot = A + s1 + "&b=" + s2 + Z;

        Serial.println(iot);
        sndit ();

}//IF FLAG2 == 1
    }
    
  }// Serial.available   
 

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
    delay(10);
    Serial.println(x, DEC);
  }
  Serial.println(F("Starting connection to server..."));
  // if you get a connection, report back via serial
  if (client.connect(server, 80)) {
    Serial.println(F("Connected to server"));
    // Make a HTTP request

    client.println(iot);
    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
    iot = "\0";
  }

}
