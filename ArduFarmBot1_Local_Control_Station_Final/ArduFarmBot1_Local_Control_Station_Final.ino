/********************************************************************************************
 * Sensors/Actuators Local station
 *       DHT-22 sensor (pin D4) to read temperature and humidity values 
 *       LDR Sensor (Pin A0) used as luminosity Sensor ==> 0% full dark to 100% full light
 *       SoilSensor Reading 2 soil Moisture (Humidity) sensors in % at Nano Pin A1 and A2. 
 *          - VCC for both Soil Moister (SM) sensors connected to D7 and GND to D6   
 *          - If only one sensor is connected, Sensor of connected at A2 is ignored
 *       Actuators: Pump/LED Red (Pin 10) and Lamp (Pin 8)
 *   ==> 2 buttons for local activation of Pump (Pin 11) and Lamp (Pin 9)    
 *   ==> 1 button for updating Sensors Reading (Pin A3 ==> equivalent D17)
 *   ==> I2C LCD 4/20 for local monitoring (SDA ==> NANO Pin A4  SCL ==> NANO Pin A5)
 *   
 * MJRoBot 27Aug16
 *********************************************************************************************/

// ------------------------------- Libraries
#include "stationDefines.h"    // Project definitions
#include <DHT.h>               // DHT Library
#include <Wire.h>              // I2C
#include <LiquidCrystal_I2C.h> // LCD

// ------------------------------- Innitializations
DHT dht(DHTPIN, DHTTYPE);           // Initialize the DHT sensor
LiquidCrystal_I2C lcd(0x27, 20, 4); // Set the LCD address to 0x27 for a 20 chars and 4 line display (use I2C scan to confirm address)

// ------------------------------- Setup
void setup() 
{
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(LAMP_PIN, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(PUMP_ON, INPUT_PULLUP); // Button
  pinMode(LAMP_ON, INPUT_PULLUP); // Button
  pinMode(SENSORS_READ, INPUT_PULLUP); // Button
  pinMode(SMS_VCC,OUTPUT);
  pinMode(SMS_GND,OUTPUT);

  iniciateStation(); // initiate some sensors, first readings, display innitial data, etc.
}

// ------------------------------- Main Loop
void loop() 
{
  elapsedTime = millis()-startTiming;   // Start timer for measurements
  readLocalCmd(); //Read local button status
  showDataLCD();
  
  if (elapsedTime > (sampleTimingSeconds*1000)) 
  {
    readSensors();
    autoControlPlantation();
    startTiming = millis();
  }
}

// ------------------------------- Specific Station Functions

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

  digiValue = debounce(SENSORS_READ);
  if (!digiValue) 
  {
    digitalWrite(YELLOW_LED, HIGH); 
    lcd.setCursor (0,0);
    lcd.print("< Updating Sensors >");
    readSensors();
    digitalWrite(YELLOW_LED, LOW); 
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
* Automatically Control the Plantation based on sensors reading
****************************************************/
void autoControlPlantation()
{ 
//--------------------------------- PUMP ------//
  if (soilMoist < DRY_SOIL && lumen > DARK_LIGHT) 
  {
    if (soilMoistAlert == HIGH)
    {
      soilMoistAlert = LOW; 
      turnPumpOn();
    }
    else soilMoistAlert = HIGH;
  }
  else soilMoistAlert = LOW;

//--------------------------------- HEAT ------//
  if (tempDHT < COLD_TEMP && soilMoist < WET_SOIL) 
  {
    if (tempLowAlert == HIGH)
    {
      tempLowAlert = LOW; 
      digitalWrite(LAMP_PIN, HIGH);
      lampStatus = 1;
    }
    else tempLowAlert = HIGH;
  }
  else 
  {
    tempLowAlert = LOW;
    digitalWrite(LAMP_PIN, LOW);
    lampStatus = 0; 
  }
}

/***************************************************
* TurnPumOn 
****************************************************/
void turnPumpOn()
{
  digitalWrite(PUMP_PIN, HIGH);
  pumpStatus = 1;
  showDataLCD();
  delay (timePumpOn*1000);
  digitalWrite(PUMP_PIN, LOW);
  pumpStatus = 0;
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

