/****************************************************************
* ESP8266
* Arduino UNO or NANO Using SoftwareSerial library
* AT commands examples for test:
*    AT     =====> ESP8266 returns OK
*    AT+RST =====> ESP8266 restart and returns OK
*    AT+GMR =====> ESP8266 returns AT Version; SDK version; id; OK
*    AT+CWMODE? => ESP8266 returns mode type
*    AT+CWLAP ===> ESP8266 returs close access points
*    AT+CIFSR ===> ESP8266 returs designided IP
*    AT+CIPMUX=1          ==>Set ESP8266 for multoples conections 
*    AT+CIOBAUD=9600      ==>Change Baudrate ==> ESP8266 returs OK
*    AT+CIPSERVER=1,80    ==> set modo SERVER port: 80
*    AT+CWMODE=3          ==> Conect ESP8266 ascombined mode (Access Point (2) and Server (1))
*    AT+CWSAP="Acc_Point_name","password",wifi_Channel,cript# ==> ej. AT+CWSAP="ESP_8266_AP,"1234",3,0
*    AT+CWJAP="SSID","password" ==> Connect to WiFi network
*
* Marcelo Jose Rovai 18Sept16
******************************************************************/

#include <SoftwareSerial.h>   
SoftwareSerial esp8266(2,3);  //Rx ==> Pin 2; TX ==> Pin3 

#define speed8266 9600 // <==  ********* This is the speed that worked with my ESP8266
#define CH_PD 4 
#define DEBUG true

void setup() 
{
  esp8266.begin (speed8266); 
  Serial.begin(speed8266);
  reset8266(); // Pin CH_PD need a reset before start communication
  Serial.println("ESP8266 Setup test - use AT coomands");
}

void loop() 
{
  while(esp8266.available())
  {
    Serial.write(esp8266.read());
  }
  while(Serial.available())
  {
    esp8266.write(Serial.read());
  }
}

/*************************************************/
// Reset funtion to accept communication
void reset8266 ()
{
  pinMode(CH_PD, OUTPUT);
  digitalWrite(CH_PD, LOW);
  delay(300);
  digitalWrite(CH_PD, HIGH);
}
