/********************************************************************************************
 *             
 *   ==> Sending analog Data to https://thingspeak.com/channels/CHANNEL_ID 
 *       DHT-22 sensor (pin D4) to read temperature and humidity values (upload at Fields 1 and 2)
 *       LDR Sensor (Pin A0) used as luminosity Sensor ==> 0% full dark to 100% full light (upload Field 3) 
 *       SoilSensor Reading 2 soil Moisture (Humidity) sensors in % at Nano Pin A1 and A2. (upload Field 4) 
 *          - "VCC" for both Soil Moister (SM) sensors connected to D7 and "GND" to D6   
 *          - If only one sensor is connected, Sensor of connected at A2 is ignored
 *   ==> Actuators: Pump/LED Red (Pin 10) and Lamp (Pin 8)
 *         2 buttons for local activation of Pump (Pin 11) and Lamp (Pin 9)    
 *         1 button for updating Sensors Reading (Pin 12)
 *   ==> Receiving data from https://thingspeak.com/channels/CHANNEL_ID: fields 7 (PUMP) and 8 (LAMP) 
 *         Based on those commands, Relays to activate PUMP (Pin 10) & LAMP (Pin 8)
 *   ==> I2C LCD 4/20 for local monitoring (SDA ==> NANO Pin A4  SCL ==> NANO Pin A5)
 *   ==> Remote Control Panel at: http://mjrobot.byethost7.com/ArduFarmBot/
 *   
 *   V 3.4.1  Including Configuration Setup Display at start-up
 *            LCD status default is OFF with PGM running. Need to press the Sensor Update Key to turn-ON LCD (and update sensors reading)
 *            IF pgm is running with LCD ON, press the SensorUpdate Key to turn OFF LCD and keep pgm running
 *   V 3.4.2  Automatic storage Log data at Arduino EEPROM (address (I): 8 bits (SL, SM, SH, LL, LH, TL, TM, TH); address (I+1): 2 bits (Pump, Lamp)
 *            Adrress 0: storage of last address used + 1
 *            For reading storage LOG, connect ArduFarmBot at Serial Monito and send "r" or "R" at Serial Monitor
 *   V 4.1    Including ESP8266 and SRAM Memory optimization
 *   
 *********************************************************************************************   
 *   MJRoBot 17Sept16 - ArduFarmBot Control Station Version 4.1 "IoT"
 *********************************************************************************************/
#define SW_VERSION " 4.1" // SW version will appears at innitial LCD Display


// ------------------------------- Libraries
#include <avr/pgmspace.h>
#include "stationDefines.h"    // Project definitions
#include "stationCredentials.h"
#include <SoftwareSerial.h>
#include <EEPROM.h>            // Internal EEPROM to be used for LOG data
#include <DHT.h>               // DHT Library
#include <Wire.h>              // I2C
#include <LiquidCrystal_I2C.h> // LCD

// ------------------------------- Innitializations
DHT dht(DHTPIN, DHTTYPE);           // Initialize the DHT sensor
LiquidCrystal_I2C lcd(0x27, 20, 4); // Set the LCD address to 0x27 for a 20 chars and 4 line display (use I2C scan to confirm address)
SoftwareSerial esp8266(2,3); // NANO RX Pin2  NANO TX Pin3 (via voltage lever)

// ------------------------------- Setup
void setup() 
{
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(LAMP_PIN, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(PUMP_ON, INPUT_PULLUP); // Button
  pinMode(LAMP_ON, INPUT_PULLUP); // Button
  pinMode(SENSORS_READ, INPUT_PULLUP); // Button
  pinMode(SMS_VCC,OUTPUT);
  pinMode(SMS_GND,OUTPUT);

  iniciateStation(); // initiate some sensors, first readings, display innitial data, etc.
  lcd.noDisplay();
}

// ------------------------------- Main Loop
void loop() 
{
  start: //label 
  error=0;
  digitalWrite(BUZZER, LOW);
  elapsedRemoteCmdTime = millis()-startRemoteCmdTiming;   // Start timer for pooling remote commands
  elapsedTime = millis()-startTiming;   // Start timer for measurements
  reverseElapsedTimeSeconds = round (sampleTimingSeconds - elapsedTime/1000);

  readLocalCmd(); //Read local button status
  showDataLCD();

  if (elapsedRemoteCmdTime > (poolingRemoteCmdSeconds*1000)) 
  {
    receiveCommands();
    updateDataThingSpeak();
    startRemoteCmdTiming = millis();
  }
  
  if (elapsedTime > (sampleTimingSeconds*1000)) 
  {
    readSensors();
    autoControlPlantation();
    storeDataLogEEPROM();
    updateDataThingSpeak();
    startTiming = millis();
  }
   
  if (error==1){       //Resend if transmission is not completed 
    digitalWrite(BUZZER, HIGH);
    lcd.clear();
    lcd.print(" <<<< ERROR >>>>");
    Serial.println(" <<<< ERROR >>>>");
    delay (2000);
    goto start; //go to label "start"
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
    field7Data = pumpStatus;
    showDataLCD();
    aplyCmd();
    updateCmdThingSpeak();  
  }

  digiValue = debounce(LAMP_ON);
  if (!digiValue) 
  {
    lampStatus = !lampStatus;
    field8Data = lampStatus;
    showDataLCD();
    aplyCmd();
    updateCmdThingSpeak();
  }

  digiValue = debounce(SENSORS_READ);
  if (!digiValue) 
  {
    if (turnOffLCD) 
    {
      lcd.display();
      lcd.backlight();
      lcd.setCursor (0,3);
      lcd.print("< updating sensors >");
      digitalWrite(YELLOW_LED, HIGH);    
      readSensors();
      digitalWrite(YELLOW_LED, LOW); 
      lcd.clear();
      showDataLCD();
      turnOffLCD = 0;
      // waitModeLCD();
      lcd.setCursor (11,3);
      lcd.println("press=> ");
      lcd.setCursor (19,3);
      lcd.cursor();
      lcd.blink();
    }
    else
    {
      lcd.noBlink();
      lcd.noCursor();
      lcd.noDisplay();
      lcd.noBacklight();
      turnOffLCD = 1;
    }
    
  }
}

/***************************************************
* Receive Commands and act on actuators
****************************************************/
void aplyCmd()
{
  if (field7Data == 1) digitalWrite(PUMP_PIN, HIGH);
  if (field7Data == 0) digitalWrite(PUMP_PIN, LOW);
  
  if (field8Data == 1) digitalWrite(LAMP_PIN, HIGH);
  if (field8Data == 0) digitalWrite(LAMP_PIN, LOW);
}


/***************************************************
* Automatically Control the Plantation based on sensors reading
****************************************************/
void autoControlPlantation()
{ 
//--------------------------------- PUMP ------//
  defSensorStatus();
  if (pumpStatus) 
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
  if (lampStatus) 
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
  lumen = getLumen(LDR_PIN);
  soilMoist = getSoilMoist(); 
  
  tempDHT = dht.readTemperature();   //Read temperature and humidity values from DHT sensor:
  humDHT = dht.readHumidity();
  if (isnan(humDHT) || isnan(tempDHT))   // Check if any reads failed and exit early (to try again).
  {
    Serial.println("Failed to read from DHT sensor!");
    errorDHT = 1;
    tempDHT = 0;
    humDHT = 0;
  }
}

// ------------------------------- Specific Remote Station Functions

/***************************************************
* Receive Commands from thingSpeak.com
****************************************************/
void receiveCommands()
{
  digitalWrite(YELLOW_LED, HIGH);
  field7Data = readLastDataField7();
  if (field7Data == 1) 
  {
    digitalWrite(PUMP_PIN, HIGH);
    pumpStatus = 1;
    showDataLCD();
  }
  if (field7Data == 0) 
  {
    digitalWrite(PUMP_PIN, LOW);
    pumpStatus = 0;
    showDataLCD();
  }

  delay (500); 
  
  field8Data = readLastDataField8();
  if (field8Data == 1) 
  {
    digitalWrite(LAMP_PIN, HIGH);
    lampStatus = 1;
    showDataLCD();
  }
  if (field8Data == 0) 
  {
    digitalWrite(LAMP_PIN, LOW);
    lampStatus = 0;
    showDataLCD();
  }
  delay (500); 
  digitalWrite(YELLOW_LED, LOW);
}

