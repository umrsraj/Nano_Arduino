//Viral science www.youtube.com/c/viralscience
//FireFighter Truck
// http://projectsiot.xyz/IoTProjects/FireRobot/fireupload.php?a=Y&b=Y
// http://projectsiot.xyz/IoTProjects/FireRobot/firestatus.php

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <String.h>

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig
  String g = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9640624444&from=MYDREM&message=";
  String g1 = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=7095667878&from=MYDREM&message=";
String msg = "\0";
String msg1 = "\0";
String r = "http://projectsiot.xyz/IoTProjects/WarField/upload.php?a=";
String rs = "\0";
String obs = "\0";
String fir = "\0";
//#define fire_sensor D1
#define obstacle_sensor D5
//#define trigPin D1
//#define echoPin D2

char a = 'N', b= 'N';

#define m11 D6
#define m12 D7
#define m21 10
#define m22 D4


//#define gled D8
//#define rled 1

unsigned int obstacle = 0;
unsigned int fire = 0;

long duration, distance,duration1,distance1;

void forward ()
{
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
  delay(10);
}

void backward ()
{
  digitalWrite(m12, HIGH);
  digitalWrite(m11, LOW);
  digitalWrite(m22, HIGH);
  digitalWrite(m21, LOW);
  delay(10);
}
void left ()
{
  digitalWrite(m12, LOW);
  digitalWrite(m11, HIGH);
  digitalWrite(m21, LOW);
  digitalWrite(m22, HIGH);
  delay(10);
}

void right ()
{

  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
  delay(10);
}
void stopp ()
{
  digitalWrite(m12, LOW);
  digitalWrite(m11, LOW);
  digitalWrite(m22, LOW);
  digitalWrite(m21, LOW);
  delay(10);
}

void setup() {
  Serial.begin(9600);
  Serial.println("power up");
 
  
pinMode (m11,OUTPUT);
pinMode (m12,OUTPUT);
pinMode (m21,OUTPUT);
pinMode (m22,OUTPUT);
pinMode (obstacle_sensor,INPUT);
  //pinMode(trigPin, OUTPUT);
  //pinMode(echoPin, INPUT);

  Serial.print("Bezig met verbinden");
  WiFi.begin(ssid, password); // Connect to WiFi
 
  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }
  
  // Verbonden.
  Serial.println("OK!");
  
  // Access Point (SSID).
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  
  // IP adres.
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
Serial.println("state---------------1"); 
  // Signaalsterkte.
  long rssi = WiFi.RSSI();
  Serial.print("Signaal sterkte (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
  Serial.println("");


Serial.print("A = "); Serial.println("http://projectsiot.xyz/IoTProjects/HealthCare/healthupload.php?a=U&b=86&c=L");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   
  http.begin("http://projectsiot.xyz/IoTProjects/WarField/upload.php?a=U");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}

}

String read_msg = "\0";

void ShowSerialData()
{
  while(Serial.available()!=0)
   read_msg = Serial.readString();
  Serial.println("read_msg is = "); Serial.println(read_msg);
   delay(1);
}

void loop()
{

  
obstacle = digitalRead(obstacle_sensor);
forward ();
delay(100);
if(obstacle==HIGH)
{
  stopp();
  delay(100);
left();
  delay(500);
  stopp();
  delay(100);
rs=r + 'Y';
send2server ();
  delay(1000);

}

rs=r + 'N';
send2server ();
  
} // LOOP

void send2server ()
{
Serial.print("rs = "); Serial.println(rs);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
 http.begin(rs);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
}
void sendsms1 ()
{
Serial.print("msg1 = "); Serial.println(msg1);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
 http.begin(msg1);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
}
void sendsms ()
{
Serial.print("rs = "); Serial.println(msg);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
 http.begin(msg);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
}
