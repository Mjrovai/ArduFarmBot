/****************************************************************
 * Sensors/Actuators Local station
 *       DHT-22 sensor (pin D4) to read temperature and humidity values 
 *       LDR Sensor (Pin A0) used as luminosity Sensor ==> 0% full dark to 100% full light
 *       SoilSensor Reading soil Moisture (Humidity) in % at Nano Pin A1. VCC sensor connected to D7 and GND to D6   
 *       Actuators: Pump/LED Red (Pin 10) and Lamp (Pin 8)
 *   ==> 2 buttons for local activation of Pump (Pin 11) and Lamp (Pin 9)    
 *   ==> I2C LCD 4/20 for local monitoring (SDA ==> NANO Pin A4  SCL ==> NANO Pin A5)
 *   
 * MJRoBot 22Aug16
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

// Actuators: Buttons and LEDs
#define PUMP_ON 11  //push-button
#define PUMP_PIN 10
#define LAMP_ON 9  //push-button
#define LAMP_PIN 8

// Alert LED
#define YELLOW_LED 13

// Variables to be used by Sensor
int tempDHT; 
int humDHT;
int lumen;
int soilMoist;

// Variables to be used by Actuators
boolean pumpStatus = 0;
boolean lampStatus = 0;

// Variables to be used with timers
long sampleTimingSeconds = 300; // ==> Define Sample time in seconds to read sensores
long startTiming = 0;
long elapsedTime = 0;

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE); 

// Initialize LCD
LiquidCrystal_I2C lcd(0x27, 20, 4); // Set the LCD address to 0x27 for a 20 chars and 4 line display (use I2C scan to confirm address)


void setup() 
{
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(LAMP_PIN, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(PUMP_ON, INPUT_PULLUP); // Button
  pinMode(LAMP_ON, INPUT_PULLUP); // Button
  pinMode(SMS_VCC,OUTPUT);
  pinMode(SMS_GND,OUTPUT);
  
  Serial.begin(9600); 
  Serial.println("ArduFarmBot Local Station Test");
  dht.begin();
  lcd.begin();
  readSensors(); // innitial reading
  startTiming = millis(); // starting the "program clock"
}

void loop() 
{
  // Start timer for measurements
  elapsedTime = millis()-startTiming; 

  readLocalCmd(); //Read local button status
  showDataLCD();
  
  if (elapsedTime > (sampleTimingSeconds*1000)) 
  {
    readSensors();
    //printData();
    startTiming = millis();
     
  }
}

/****************************************************************
* Read local commands (Pump and Lamp buttons are normally "HIGH"):
****************************************************************/
void readLocalCmd() 
{  
  int digiValue = debounce(PUMP_ON);
  if (!digiValue) 
  {
    pumpStatus = !pumpStatus;
    showDataLCD();
    aplyCmd();
  }

  digiValue = debounce(LAMP_ON);
  if (!digiValue) 
  {
    lampStatus = !lampStatus;
    showDataLCD();
    aplyCmd();
  }
}

/***************************************************
* Receive Commands and act on actuators
****************************************************/
void aplyCmd()
{
    if (pumpStatus == 1) digitalWrite(PUMP_PIN, HIGH);
    if (pumpStatus == 0) digitalWrite(PUMP_PIN, LOW);
  
    if (lampStatus == 1) digitalWrite(LAMP_PIN, HIGH);
    if (lampStatus == 0) digitalWrite(LAMP_PIN, LOW);
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
  int i = 0;
  int anaValue = 0;
  for(i = 0; i < 1; i++) // read sensor i times and get the average
  {
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(SMS_VCC,LOW);   // drive a current through the divider in one direction
    digitalWrite(SMS_GND,HIGH);
    delay(500);   // wait a moment for capacitance effects to settle
    anaValue += analogRead(SOIL_MOIST_PIN);
    //Serial.println (anaValue/(i+1));
    
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(SMS_VCC,HIGH);   // reverse the current
    digitalWrite(SMS_GND,LOW);
    delay(500);   // give as much time in 'reverse' as in 'forward'
    digitalWrite(SMS_VCC,LOW);   // stop the current
    //delay (3000);
  }
    digitalWrite(SMS_VCC,LOW);   // stop the current
  
  anaValue = anaValue/(i);
  anaValue = map(anaValue, 1015, 3, 0, 100); //1015:0 (en el air) ==> 003:100% (poniendo un "short circuit) 
  Serial.println (anaValue);
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
  Serial.print("%  Pump: ");
  Serial.print(pumpStatus);
  Serial.print("    Lamp: ");
  Serial.println(lampStatus);
}

/***************************************************
* Showing capured data at LCD
****************************************************/
void showDataLCD(void)
{
  lcd.setCursor (0,0);
  lcd.print("ArduFarmBot Ctrl St.");
  lcd.setCursor (0,1);
  lcd.print("Temp: ");
  lcd.print(tempDHT);
  lcd.print("oC  Hum: ");
  lcd.print(humDHT);
  lcd.print("%  ");
  lcd.setCursor (0,2);
  lcd.print("Ligh: ");
  lcd.print(lumen);
  lcd.print("%");
  lcd.print("  Soil: ");
  lcd.print(soilMoist);
  lcd.print("%");
  lcd.setCursor (0,3);
  lcd.print("Pump: ");
  lcd.print(pumpStatus);
  lcd.print("    Lamp: ");
  lcd.print(lampStatus);
  lcd.setCursor (0,0);
}


/***************************************************
* Debouncing a key
****************************************************/
boolean debounce(int pin)
{
  boolean state;
  boolean previousState;
  const int debounceDelay = 60;
  
  previousState = digitalRead(pin);
  for(int counter=0; counter< debounceDelay; counter++)
  {
    delay(1);
    state = digitalRead(pin);
    if(state != previousState)
    {
      counter =0;
      previousState = state;
    } 
  }
  return state;
}


