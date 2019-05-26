
#include "WiFiEsp.h"
#include<String.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd (2, 3, 4, 5, 6, 7);

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(12, 13); // RX, TX
#endif


#define button 8
#define buzzer 9
#define irsensor 10



void beep ()
{
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(100);
}
void beep1 ()
{
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(100);
}
char ssid[] = "project12";            // your network SSID (name)
char pass[] = "project123456";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "projectsiot.xyz";
String A = "GET /IoTProjects/TransportTicket/upload.php?a=";
String Z = " HTTP/1.1";
String iot = "\0";
WiFiEspClient client;


int count1 = 0;
// count = 0
char input[12];

String mode = "N";

String rbal = "N";

int amount1 = 1000;
int amount2 = 1000;
int amount3 = 1000;
int amount4 = 1000;

int flag;
int cost = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.println("power up");
  pinMode(buzzer, OUTPUT);
  pinMode(irsensor, INPUT);
  pinMode(button, INPUT);




  lcd.begin(16, 2);
  lcd.clear();
  lcdstring(0, 0, "TRANSPORTATION         ");
  lcdstring(0, 1, "TICKETING SYSTEM       ");
  delay(3000);


  Serial1.begin(9600);

  Serial1.listen (); delay(1000);

  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println(F("WiFi shield not present"));
    // don't continue
    //while (true);
  }
  lcd.clear ();
  lcd.setCursor(0, 0);
  lcd.print("CONNECTING TO");
  lcd.setCursor(0, 1);
  lcd.print(ssid);
  delay(300);
  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print(F("Attempting to connect to WPA SSID: "));
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }
  lcd.clear ();
  lcd.setCursor(0, 0);
  lcd.print("CONNECTED TO");
  lcd.setCursor(0, 1);
  lcd.print("WI - FI ");
  delay(2000);
  // you're connected now, so print out the data
  Serial.println(F("You're connected to the network"));

  lcd.clear ();
  lcd.setCursor(0, 0);
  lcd.print("server init.   ");
  lcd.setCursor(0, 1);
  lcd.print("please wait    ");
  delay(2000);

  Serial.println(F("sending data ---1 "));
  Serial.println(F("Starting connection to server..."));
  // if you get a connection, report back via serial
  if (client.connect(server, 80)) {
    Serial.println(F("Connected to server"));
    // Make a HTTP request
    client.println("GET /IoTProjects/TransportTicket/upload.php?a=U HTTP/1.1");
    client.println("Host: projectsiot.xyz");
    client.println("Connection: close");
    client.println();
  }
  client.flush();
  client.stop();

  lcd.clear ();
  lcd.setCursor(0, 0);
  lcd.print("server init.   ");
  lcd.setCursor(0, 1);
  lcd.print("done             ");
  delay(1000);

  Serial.println(F("PLEASE SHOW CARD "));

  Serial1.listen (); delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 0);
  lcd.print("Please show card          ");
  lcd.setCursor(0, 1);
  lcd.print("                             ");

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
///////////////////////////////////////////////////
      if (input[10] == '5')
      {
        input[10] = 'R';
        if (digitalRead(button)==HIGH)
        {

        lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("CARD-1 MATCHED     ");
        lcd.setCursor(0, 1);
        lcd.print("MODE: BUS           ");
        delay(2000);
        cost = 50;
        if (amount1 > cost)
        {

                  Serial.println("amount1 = " + String(amount1));
        amount1 = amount1 - 50;
        cost = "50";
        rbal = String(amount1);
        Serial.println("amount1 = " + String(amount1));
                 
                 lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("T.Bill: "+String(cost));
        lcd.setCursor(0, 1);
        lcd.print("R.Bal: "+String(rbal)); 
        
        iot = A + mode + "&b=" + String(cost) + "&c=" + rbal + Z;
        Serial.println(iot);
        sndit ();
        delay(1000);
        }
        else
        {
            lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("NO BALANCE     ");
        lcd.setCursor(0, 1);
        lcd.print("R.Bal: "+String(amount1));
        delay(3000);
        
        }
        }
        //*************************************
        else if (digitalRead(button)==LOW)
        {
                 lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("CARD-1 MATCHED     ");
        lcd.setCursor(0, 1);
        lcd.print("MODE: TRAIN           ");
        delay(2000);
        
        cost = 100;
        if (amount1 > cost)
        {

                  Serial.println("amount1 = " + String(amount1));
        amount1 = amount1 - 100;
        rbal = String(amount1);
        Serial.println("amount1 = " + String(amount1));
                 
                 lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("T.Bill: "+String(cost));
        lcd.setCursor(0, 1);
        lcd.print("R.Bal: "+String(rbal)); 
        
        iot = A + mode + "&b=" + String(cost) + "&c=" + rbal + Z;
        Serial.println(iot);
        sndit ();
        delay(1000);
        }
        else
        {
            lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("NO BALANCE     ");
        lcd.setCursor(0, 1);
        lcd.print("R.Bal: "+String(amount1));
        delay(3000);
        
        }
      }
      }
      //////////////////////////////////////////////////
///////////////////////////////////////////////////
      if (input[10] == '1')
      {
        input[10] = 'R';
        if (digitalRead(button)==HIGH)
        {

        lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("CARD-2 MATCHED     ");
        lcd.setCursor(0, 1);
        lcd.print("MODE: BUS           ");
        delay(2000);
        cost = 50;
        if (amount2 > cost)
        {

                  Serial.println("amount2 = " + String(amount2));
        amount2 = amount2 - 50;
        
        rbal = String(amount2);
        Serial.println("amount2 = " + String(amount2));
                 
                 lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("T.Bill: "+String(cost));
        lcd.setCursor(0, 1);
        lcd.print("R.Bal: "+String(rbal)); 
        
        iot = A + mode + "&b=" + String(cost) + "&c=" + rbal + Z;
        Serial.println(iot);
        sndit ();
        delay(1000);
        }
        else
        {
            lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("NO BALANCE     ");
        lcd.setCursor(0, 1);
        lcd.print("R.Bal: "+String(amount2));
        delay(3000);
        
        }
        }
        //*************************************
        else if (digitalRead(button)==LOW)
        {
        input[10] = 'R';
                 lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("CARD-2 MATCHED     ");
        lcd.setCursor(0, 1);
        lcd.print("MODE: TRAIN           ");
        delay(2000);
        cost = 100;
        if (amount2 > cost)
        {

                  Serial.println("amount2 = " + String(amount2));
        amount2 = amount2 - 100;
        rbal = String(amount2);
        Serial.println("amount2 = " + String(amount2));
                 
                 lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("T.Bill: "+String(cost));
        lcd.setCursor(0, 1);
        lcd.print("R.Bal: "+String(rbal)); 
        
        iot = A + mode + "&b=" + String(cost) + "&c=" + rbal + Z;
        Serial.println(iot);
        sndit ();
        delay(1000);
        }
        else
        {
            lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("NO BALANCE     ");
        lcd.setCursor(0, 1);
        lcd.print("R.Bal: "+String(amount2));
        delay(3000);
        
        }
      }
      }
      //////////////////////////////////////////////////
///////////////////////////////////////////////////
      if (input[10] == '2')
      {
        input[10] = 'R';
        if (digitalRead(button)==HIGH)
        {

        lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("CARD-3 MATCHED     ");
        lcd.setCursor(0, 1);
        lcd.print("MODE: BUS           ");
        delay(2000);
        cost = 50;
        if (amount3 > cost)
        {

                  Serial.println("amount3 = " + String(amount3));
        amount3 = amount3 - 50;
        
        rbal = String(amount3);
        Serial.println("amount3 = " + String(amount3));
                 
                 lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("T.Bill: "+String(cost));
        lcd.setCursor(0, 1);
        lcd.print("R.Bal: "+String(rbal)); 
        
        iot = A + mode + "&b=" + String(cost) + "&c=" + rbal + Z;
        Serial.println(iot);
        sndit ();
        delay(1000);
        }
        else
        {
            lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("NO BALANCE     ");
        lcd.setCursor(0, 1);
        lcd.print("R.Bal: "+String(amount3));
        delay(3000);
        
        }
        }
        //*************************************
        else if (digitalRead(button)==LOW)
        {
                 lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("CARD-3 MATCHED     ");
        lcd.setCursor(0, 1);
        lcd.print("MODE: TRAIN           ");
        delay(2000);
        cost = 100;
        if (amount3 > cost)
        {

                  Serial.println("amount3 = " + String(amount3));
        amount3 = amount3 - 100;
        rbal = String(amount3);
        Serial.println("amount3 = " + String(amount3));
                 
                 lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("T.Bill: "+String(cost));
        lcd.setCursor(0, 1);
        lcd.print("R.Bal: "+String(rbal)); 
        
        iot = A + mode + "&b=" + String(cost) + "&c=" + rbal + Z;
        Serial.println(iot);
        sndit ();
        delay(1000);
        }
        else
        {
            lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("NO BALANCE     ");
        lcd.setCursor(0, 1);
        lcd.print("R.Bal: "+String(amount3));
        delay(3000);
        
        }
      }
      }
      //////////////////////////////////////////////////
///////////////////////////////////////////////////
      if (input[10] == '3')
      {
        input[10] = 'R';
        if (digitalRead(button)==HIGH)
        {

        lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("CARD-4 MATCHED     ");
        lcd.setCursor(0, 1);
        lcd.print("MODE: BUS           ");
        delay(2000);
        cost = 50;
        if (amount4 > cost)
        {

                  Serial.println("amount4 = " + String(amount4));
        amount4 = amount4 - 50;
        
        rbal = String(amount4);
        Serial.println("amount4 = " + String(amount4));
                 
                 lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("T.Bill: "+String(cost));
        lcd.setCursor(0, 1);
        lcd.print("R.Bal: "+String(rbal)); 
        
        iot = A + mode + "&b=" + String(cost) + "&c=" + rbal + Z;
        Serial.println(iot);
        sndit ();
        delay(1000);
        }
        else
        {
            lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("NO BALANCE     ");
        lcd.setCursor(0, 1);
        lcd.print("R.Bal: "+String(amount4));
        delay(3000);
        
        }
        }
        //*************************************
        else if (digitalRead(button)==LOW)
        {
                 lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("CARD-4 MATCHED     ");
        lcd.setCursor(0, 1);
        lcd.print("MODE: TRAIN           ");
        delay(2000);
        cost = 100;
        if (amount4 > cost)
        {

                  Serial.println("amount4 = " + String(amount4));
        amount4 = amount4 - 100;
        rbal = String(amount4);
        Serial.println("amount4 = " + String(amount4));
                 
                 lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("T.Bill: "+String(cost));
        lcd.setCursor(0, 1);
        lcd.print("R.Bal: "+String(rbal)); 
        
        iot = A + mode + "&b=" + String(cost) + "&c=" + rbal + Z;
        Serial.println(iot);
        sndit ();
        delay(1000);
        }
        else
        {
            lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("NO BALANCE     ");
        lcd.setCursor(0, 1);
        lcd.print("R.Bal: "+String(amount4));
        delay(3000);
        
        }
      }
      }
      //////////////////////////////////////////////////
  
      /*
       * 
       else
        {
            lcd.clear ();
        lcd.setCursor(0, 0);
        lcd.print("INVALID CARD      ");
        lcd.setCursor(0, 1);
        lcd.print("PLEASE CHECK        ");
        delay(3000);
    }
    */
    }//SERIAL AVAILABLE
  }//loop

  void sndit ()
  {

    //Serial1.listen(); delay(1000);

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

      client.println(A + mode + "&b=" +String(cost)+ "&c=" + rbal + Z);

      client.println("Host: projectsiot.xyz");
      client.println("Connection: close");
      client.println();
      iot = "\0";
    }
  }

  void lcdstring(int a, int b, String data)
  {
    lcd.setCursor(a, b);
    lcd.print(data);
  }
