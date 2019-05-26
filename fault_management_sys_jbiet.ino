#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>

LiquidCrystal lcd (15,2,4,16,17,5);

#define temp 34
#define soilPin 35
#define humPin 32
#define ldrPin 33
#define relay1 25
#define relay2 26

float temp1=0.0;
unsigned temp2 = 0;
int soil  = 0;
int hum = 0;
int ldr = 0;
String L = " ";
String S = " ";
String H = " ";

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig 

String q = "http://projectsiot.xyz/IoTProjects/AirQuality/airupload.php?";
String iot = "\0";
String p = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9493206867&from=MYDREM&message=";
String msg = "\0";

 
void setup(void) { 
  Serial.begin(9600);
  Serial.print("Bezig met verbinden");
 WiFi.begin(ssid, password); // Connect to WiFi
 lcd.begin(16,2);
 
lcd.clear();
lcd.setCursor(0,0);
        lcd.print("  GREEN HOUSE   ");
        lcd.setCursor( 2,1);
         lcd.print(" MONITORING S/M ");
         delay(2000);
         
          pinMode(humPin,INPUT);
          pinMode(ldrPin,INPUT);
          pinMode(soilPin,INPUT);
          pinMode(temp,INPUT);
          pinMode(relay1,OUTPUT);
          pinMode(relay2,OUTPUT);
          
  while (WiFi.status() != WL_CONNECTED) {
     lcd.clear();
     lcdstring(0,0,"connecting to ");
     lcdstring(0,1,ssid);
     delay(500);
     Serial.print(".");
  }
  lcd.clear();
     lcdstring(0,0,"connected to");
     lcdstring(0,1,ssid);
  // Verbonden.
  Serial.println("OK!");
  
  // Access Point (SSID).
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  
  // IP adres.
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
 
  // Signaalsterkte.
  long rssi = WiFi.RSSI();
  Serial.print("Signaal sterkte (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
  Serial.println("");

 
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

  http.begin("http://projectsiot.xyz/IoTProjects/AirQuality/airupload.php?a=U&b=N&c=N&d=N&e=N");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
/*
Serial.println("sending welcome message............");
 
 if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=WELCOME%20TO%20PROJECT"); //Specify request destination

  //http.begin("http://projectsiot.xyz/IoTProjects/PrepaidCardPetrol/petrolcard.php?a=U&b=0&c=0");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
*/

}
 
void loop() {

temp2 = analogRead(temp); //read data from analog pin A1. 
float V=temp2*(5/(4095.00)); //conversion of analog voltage to digital voltage. 
  temp1=V*100; //temperature in centigrade scale. 

Serial.print("temperature is = "); Serial.println(temp1);
delay(50);

ldr = analogRead(ldrPin);
delay(50);
soil = analogRead(soilPin);
delay(50);
hum = analogRead(humPin);
delay(50);

Serial.println("soil = "+String(soil));
Serial.println("ldr = "+String(ldr));
Serial.println("hum = "+String(hum));


if (temp1 > 55)
{
  lcd.clear();
  lcdstring(0,0,"TEMPERATURE ALERT");
  lcdstring(0,1,"T: "+String(temp1));
  delay(20);
  digitalWrite(relay1,HIGH);
  delay(2000);
}
else
{
  delay(100);
  digitalWrite(relay1,LOW);
  delay(100);
}
 if (soil < 2500)
{
  S = "H";
   lcd.clear();
  lcdstring(0,0,"SOIL WET DETECTED");
  lcdstring(0,1,"WATER MOTOR OFF");
  delay(20);
  digitalWrite(relay2,HIGH);
  delay(2000);
}

else
{
  S = "L";
  delay(100);
  digitalWrite(relay2,LOW);
  delay(100);
}
 if (hum < 4000)
{
  H = "H";
  lcd.clear();
  lcdstring(0,0," HUMIDITY ALERT");
  lcdstring(0,1,"PLEASE CHECK....");
  delay(20);
  delay(2000);
}
else
{
  H = "L";
}
if (ldr < 2000)
{
  L = "D";
}
else
{
  L = "N";  
}

if ((temp1 < 55)&&(H == "L")&&(S == "L"))
{
  lcd.clear();
  lcdstring(0,0,"T: "+String(temp1));
  lcdstring(9,0,"H: "+ String(H));
  lcdstring(0,1,"S: "+ String(S));
  lcdstring(9,1,"L: "+ String(L));
  delay(100);
  iot  = q + "a=" + String(temp1) + "&b=" + L +"&c=" + H + "&d=" + S;
  send2server ();
}
else
{
  
  iot  = q + "a=" + String(temp1) + "&b=" + L +"&c=" + H + "&d=" + S;
  send2server ();
}
}// LOOP

void send2server ()
{
   Serial.println(iot);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
  
   http.begin(iot);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(100);
}
}
void sendmsg ()
{
  Serial.println("sending message-----------");

 Serial.print("msg = "); Serial.println(msg);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
    
  http.begin(msg);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(100);
}

}
void lcdstring (int a, int b, String w)
{
  lcd.setCursor(a,b);
  lcd.print(w);
}
