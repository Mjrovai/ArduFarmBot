/****************************************************************
 * Sensors - Setup and Test - LCD incorporated
 *       DHT-22 sensor (pin D4) to read temperature and humidity values 
 *       LDR Sensor (Pin A0) used as luminosity Sensor ==> 0% full dark to 100% full light
 *       SoilSensor (Pin A1) used to read soil Moisture - Humidity  
 *   ==> I2C LCD 4/20 for local monitoring (SDA ==> NANO Pin A4  SCL ==> NANO Pin A5)
 *   
 * MJRoBot 21Aug16
 ****************************************************************/

// Include DHT Library
#include <DHT.h>

// Including Libraries for I2C LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Sensor definitions
#define DHTPIN 5         // DHT data pin connected to Arduino pin 5
#define DHTTYPE DHT22    // DHT 22 (if your sensor is the DHT 11, only change this line by: #define DHTTYPE DHT11) 
#define LDR_PIN 0        // used for Luminosity (LDR) Sensor Input
#define SOIL_MOIST_PIN 1 // used for Soil Moisture Sensor Input
#define SMS_VCC 7 // used for Soil Moisture Sensor "Power Supply" (VCC)
#define SMS_GND 6 // used for Soil Moisture Sensor "GND"

// Variables to be used by Sensor
int tempDHT; 
int humDHT;
int lumen;
int soilMoist;

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE); 

// Initialize LCD
LiquidCrystal_I2C lcd(0x27, 20, 4); // Set the LCD address to 0x27 for a 20 chars and 4 line display (use I2C scan to confirm address)


void setup() 
{
  Serial.begin(9600); 
  Serial.println("ArduFarmBot SENSORS Setup & Test");
  pinMode(SMS_VCC,OUTPUT);
  pinMode(SMS_GND,OUTPUT);
  dht.begin();
  lcd.begin();
}

void loop() 
{
  // Wait a few seconds between measurements.
  delay(2000);
  readSensors();
  printData(); 
  showDataLCD();
}

/***************************************************
* Read data from Sensors
****************************************************/
void readSensors(void)
{
  tempDHT = dht.readTemperature();   //Read temperature and humidity values from DHT sensor:
  humDHT = dht.readHumidity();
  lumen = getLumen(LDR_PIN);
  soilMoist = getSoilMoist();
}

/***************************************************
* Capture luminosity data: 0% full dark to 100% full light
****************************************************/
int getLumen(int anaPin)
{
  int anaValue = 0;
  for(int i = 0; i < 10; i++) // read sensor 10X ang get the average
  {
    anaValue += analogRead(anaPin);   
    delay(50);
  }
  
  anaValue = anaValue/10; //Light under 300; Dark over 800
  anaValue = map(anaValue, 1023, 0, 0, 100); //LDRDark:0  ==> light 100%

  return anaValue;  
}

/***************************************************
* Capture soil Moisture data
****************************************************/
int getSoilMoist()
{
  int anaValue = 0;
  for(int i = 0; i < 10; i++) // read sensor 10X ang get the average
  {
    digitalWrite(SMS_VCC,LOW);   // drive a current through the divider in one direction
    digitalWrite(SMS_GND,HIGH);
    delay(1000);   // wait a moment for capacitance effects to settle
    anaValue += analogRead(SOIL_MOIST_PIN);

    digitalWrite(SMS_VCC,HIGH);   // reverse the current
    digitalWrite(SMS_GND,LOW);
    delay(1000);   // give as much time in 'reverse' as in 'forward'
    digitalWrite(SMS_VCC,LOW);   // stop the current
  }
  anaValue = anaValue/10;
  anaValue = map(anaValue, 1023, 0, 0, 100); //xxx:0  ==> yyy 100%
  return anaValue;
}

/***************************************************
* Showing capured data at Serial Monitor
****************************************************/
void printData(void)
{
  Serial.print("   Temp DHT ==> ");
  Serial.print(tempDHT);
  Serial.print("oC  Hum DHT ==> ");
  Serial.print(humDHT);
  Serial.print("%  Luminosity ==> ");
  Serial.print(lumen);
  Serial.print("%  Soil Moisture ==> ");
  Serial.print(soilMoist);
  Serial.println("%");
}

/***************************************************
* Showing capured data at LCD
****************************************************/
void showDataLCD(void)
{
  lcd.setCursor (0,0);
  lcd.print("ArduFarmBot Ctrl St.");
  lcd.setCursor (0,1);
  lcd.print("                    ");
  lcd.setCursor (0,2);
  lcd.print("Temp: ");
  lcd.print(tempDHT);
  lcd.print("oC  Hum: ");
  lcd.print(humDHT);
  lcd.print("%  ");
  lcd.setCursor (0,3);
  lcd.print("Ligh: ");
  lcd.print(lumen);
  lcd.print("%");
  lcd.print("  Soil: ");
  lcd.print(soilMoist);
  lcd.print("%");
  lcd.setCursor (0,0);
} 
