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
SoftwareSerial Serial1(2, 3); // RX, TX
#endif

LiquidCrystal lcd (A0, A1, A2, A3, A4, A5);

#define m11 4
#define m12 5
#define buzzer 6
#define gled 7
#define rled 8

int count1 = 0;                                          // count = 0
char input[12];

int amount = 200;
int amount1 = 200;
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

String A = "GET /IoTProjects/TollBooth/tollbooth.php?a=";
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
  lcd.print(" RFID BSD TOLL ");
  lcd.setCursor( 0, 1);
  lcd.print(" BOOTH MNGR S/M ");
  delay(1000);

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
      client.println("GET /IoTProjects/TollBooth/tollbooth.php?a=U&b=0&c=0&d=0 HTTP/1.1");
      client.println("Host: projectsiot.xyz");
      client.println("Connection: close");
      client.println();
    }
    client.flush();
     client.stop();
     
delay(6000);
     
   iot = A + 'A' + "&b=" + '0' + "&c=" + String(amount) + "&d=" + 'N' + Z;
        sndit ();

  
  /*  
    /////////////////////////////////////////
    ////////// initial message .......
    Serial.println(F("Starting connection to SMS server..."));
    delay(2000);

    // if you get a connection, report back via serial
    if (client.connect(server1, 80)) {
      Serial.println(F("Connected to server"));
      // Make a HTTP request
      client.println("GET /api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=WELCOME%20MESSAGE HTTP/1.1");
      client.println("Host: sms.scubedigi.com");
      client.println("Connection: close");
      client.println();
    }
    //client.flush();
    //  client.stop();

  */
  while (1);
Serial.println(F("PLEASE SHOW CARD "));
}

void loop()
{
  // ****************************************
R:
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

  // if (input[10]=='1')
  if (input[10] == '6')
    {

      input[10] = '0';

      if (amount < 5)
      {

        digitalWrite(gled, LOW);
        digitalWrite(rled, HIGH);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("UR BALENCE IS 0");
        lcd.setCursor(0, 1);
        lcd.print(" PLZ RECHARGE  ");
        delay(2000);


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
    client.println(msg+"9652490222"+"&from=MYDREM&message="+"CARD1MATCHED%20NO%20BALANCE"+Z);
    
    client.println("Host: sms.scubedigi.com");
    client.println("Connection: close");
    client.println();
    
  }
// *****************************************
        delay(2000);

        // str = A+"A"+B+"0"+C+String(amount)+D+"N"+Z;
        iot = A + 'A' + "&b=" + '0' + "&c=" + String(amount) + "&d=" + 'N' + Z;
        /*
          A += "A";
          A += "&b=";
          A += "0";
          A += "&c=";
          A += String(amount);
          A += "&d=";
          A += "N";
          A += Z;
        */
        Serial.println(iot);
        sndit ();

        delay(1000);

        goto R;
      }

      else if (amount > 49)
      {


        digitalWrite(rled, LOW);
        digitalWrite(gled, HIGH);
        amount = amount - 50 ;
        Serial.print(F("remaining bal == ")); Serial.println(amount);

        if (amount < 51)
        {

          lcd.setCursor(4, 1);
          lcd.print("LOW BALENCE");

        }

        iot = A +  'A' + "&b=" + "50" + "&c=" + String(amount) + "&d=" + 'Y' + Z;
       
        Serial.println(iot);
        sndit ();

        delay(1000);



//******************* CARD-1 MESSAGE ****************
 
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
    client.println(msg+"9652490222"+"&from=MYDREM&message="+"CARD1MATCHED%20REMAINING%20BALANCE="+String(amount)+Z);
    
    client.println("Host: sms.scubedigi.com");
    client.println("Connection: close");
    client.println();
    
  }
// ******************  CARD-1 MESSAGE ***********************
        delay(1000);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  CARD1 MATCHED   ");
        lcd.setCursor(0, 1);
        lcd.print("RE BAL:");
        lcd.setCursor(8, 1);
        lcd.print(amount);
        delay(500);
        forward ();
        delay(2000);
        stop_motor ();
        delay(1000);
        backward ();
        delay(2000);
        stop_motor();
        delay(1500);

        delay(500);
      }

    } // 1st card
  else if (input[10] == '9')
    {
      Serial.println(F("card-2 matched"));

      input[10] = '0';

      if (amount1 < 5)
      {

        digitalWrite(gled, LOW);
        digitalWrite(rled, HIGH);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("UR BALENCE IS 0");
        lcd.setCursor(0, 1);
        lcd.print(" PLZ RECHARGE  ");
        delay(2000);


       

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
    client.println(msg+"9652490222"+"&from=MYDREM&message="+"CARD2MATCHED%20NO%20BALANCE"+Z);
    
    client.println("Host: sms.scubedigi.com");
    client.println("Connection: close");
    client.println();
    
  }
// *****************************************
        delay(1000);

        //str = A+"B"+B+"0"+C+String(amount1)+D+"N"+Z;
        iot = A +  'B' + "&b=" + '0' + "&c=" + String(amount1) + "&d=" + 'N' + Z;
        /*
          A += "B";
          A += "&b=";
          A += "0";
          A += "&c=";
          A += String(amount1);
          A += "&d=";
          A += "N";
          A += Z;
        */
        Serial.println(iot);
        sndit ();

        delay(1000);

        goto R;
      }

      else if (amount1 > 49)
      {

        digitalWrite(rled, LOW);
        digitalWrite(gled, HIGH);

        amount1 = amount1 - 50 ;
        Serial.print(F("remaining bal == ")); Serial.println(amount1);
        if (amount1 < 51)
        {

          lcd.setCursor(4, 1);
          lcd.print("LOW BALENCE");

        }

 
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
    client.println(msg+"9652490222"+"&from=MYDREM&message="+"CARD2MATCHED%20REMAINING%20BALANCE="+String(amount1)+Z);
    
    client.println("Host: sms.scubedigi.com");
    client.println("Connection: close");
    client.println();
    
  }
// *****************************************
delay(1000);
        //str = A+"B"+B+"50"+C+String(amount1)+D+"Y"+Z;
        iot = A + 'B' + "&b=" + "50" + "&c=" + String(amount1) + "&d=" + 'Y' + Z;
        /*
          A += "B";
          A += "&b=";
          A += "50";
          A += "&c=";
          A += Stringamount1);
          A += "&d=";
          A += "Y";
          A += Z;
        */
        Serial.println(iot);
        sndit ();

        delay(3000);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  CARD-2 MATCHED   ");
        lcd.setCursor(0, 1);
        lcd.print("RE BAL:");
        lcd.setCursor(8, 1);
        lcd.print(amount1);
        delay(500);
        forward ();
        delay(2000);
        stop_motor ();
        delay(1000);
        backward ();
        delay(2000);
        stop_motor();
        delay(1500);

        delay(500);

      }

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

      //str = A+"H"+B+"0"+C+"0"+D+"N"+Z;

      A += "H";
      A += "&b=";
      A += "0";
      A += "&c=";
      A += "0";
      A += "&d=";
      A += "N";
      A += Z;

      iot = A;
      Serial.println(A);
      sndit ();
      delay(500);

    }
  }
  // ****************************************


  /*
    Serial.println(F("sending data ---1 "));
    Serial.println(F("Starting connection to server..."));
    // if you get a connection, report back via serial
    if (client.connect(server, 80)) {
    Serial.println(F("Connected to server"));
    // Make a HTTP request
    client.println("GET /IoTProjects/SchoolChildSecurity/childupdate.php?a=B&b=N HTTP/1.1");
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
    client.println("GET /api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=person2%20detected HTTP/1.1");
    client.println("Host: sms.scubedigi.com");
    client.println("Connection: close");
    client.println();
    }
    client.flush();
    client.stop();
    //***************************************************
    Serial.println(F("sending data ---1 "));
    Serial.println(F("Starting connection to server..."));
    // if you get a connection, report back via serial
    if (client.connect(server, 80)) {
    Serial.println(F("Connected to server"));
    // Make a HTTP request
    client.println("GET /IoTProjects/SchoolChildSecurity/childupdate.php?a=A&b=Y HTTP/1.1");
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
    client.println("GET /api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=person1%20detected HTTP/1.1");
    client.println("Host: sms.scubedigi.com");
    client.println("Connection: close");
    client.println();
    }
    client.flush();
    client.stop();
  */

}
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
/*
void smsit (String q)
{
  //////////  message .......
  // Serial.print(F("q == ")); Serial.println(q);

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
  if (client.connect(server1, 80)) {
    Serial.println(F("Connected to server"));
    // Make a HTTP request

    Serial.print(F("q == ")); Serial.println(q);
    client.println(q);

    client.println("Host: sms.scubedigi.com");
    client.println("Connection: close");
    client.println();
    bulk = "\0";
  }
}
*/
