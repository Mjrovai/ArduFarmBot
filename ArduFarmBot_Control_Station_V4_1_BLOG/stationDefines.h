
// -----------------------  HW: Pin definitions
// Sensors
#define DHTTYPE DHT22                   // DHT 22 (if your sensor is the DHT 11, only change this line by: #define DHTTYPE DHT11) 
const PROGMEM byte DHTPIN = 5;          // DHT data pin connected to Arduino pin 5
const PROGMEM byte LDR_PIN = 0;         // used for Luminosity (LDR) Sensor Input

const PROGMEM byte SOIL_MOIST_1_PIN = 1; // used for Soil Moisture Sensor Input
const PROGMEM byte SOIL_MOIST_2_PIN = 2; // used for Soil Moisture Sensor Input
const PROGMEM byte SMS_VCC = 7;          // used for Soil Moisture Sensor "Power Supply" (VCC)
const PROGMEM byte SMS_GND = 6;          // used for Soil Moisture Sensor "GND"

// Actuators: Buttons and LEDs
const PROGMEM byte PUMP_ON = 11;         //push-button PUMP
const PROGMEM byte PUMP_PIN = 10;
const PROGMEM byte LAMP_ON = 9;          //push-button LAMP
const PROGMEM byte LAMP_PIN = 8;
const PROGMEM byte SENSORS_READ = 12;    // push-button 

// Alert LED/BUZZER
const PROGMEM byte YELLOW_LED = 13; // 
const PROGMEM byte BUZZER = 17;  

// General Definitions 
#define speed8266 9600 // This is the speed that worked with my ESP8266
const PROGMEM byte CH_PD = 4; //ESP8266 reset
const PROGMEM byte DEBUG = true;

// -----------------------  SW: Variables and definitions

// general variables:
boolean turnOffLCD = 0;
boolean error;

//  to be used by DHT Sensor
int humDHT;
int tempDHT; 
boolean errorDHT = 0;
boolean tempLowAlert = 0;
const PROGMEM byte HOT_TEMP = 22;
const PROGMEM byte COLD_TEMP = 12;

// to be used by LDR Sensor
int lumen;
boolean lumenAlert = 0;
const PROGMEM byte DARK_LIGHT = 40;

// to be used by SM Sensor
const PROGMEM byte DRY_SOIL = 30;
const PROGMEM byte WET_SOIL = 60;
const PROGMEM byte numSM = 1; // "numSM" defines number of moisture sensors that are connected
const PROGMEM byte numSamplesSMS = 1; // "numSamplesSMS" defines number of samples of each reading cycle
int soilMoist;
boolean soilMoistAlert = 0;

// to be used by Actuators
boolean pumpStatus = 0;
boolean lampStatus = 0;
const PROGMEM byte timePumpOn = 10; // turn Pump On in seconds

// to be used with timers
long sampleTimingSeconds = 600; // ==> ******** Define Sample time in seconds to read sensores *********
int reverseElapsedTimeSeconds = 0;
long startTiming = 0;
long elapsedTime = 0;
long poolingRemoteCmdSeconds = 57; // ==> ******** Define Pooling time in seconds for new ThingSpeak commands *********
long startRemoteCmdTiming = 0;  
long elapsedRemoteCmdTime = 0;

// Sensor Matrix Definition
boolean snsSts[8]={0, 0, 0, 0, 0, 0, 0, 0}; // SL, SM, SH, LL, LH, TL, TM, TH

 //                                      +---SOIL----+-LIGHT-+---TEMP---+---ACTUAT----+
 //                                       SL  SM  SH  LL  LH  TL  TM  TH   Pump   Lamp
const PROGMEM boolean SDf [18] [10] = {{  1,  0,  0,  0,  1,  0,  0,  1,    1,    0 }, 
                                        { 1,  0,  0,  0,  1,  0,  1,  0,    1,    0 }, 
                                        { 1,  0,  0,  0,  1,  1,  0,  0,    1,    1 }, 
                                        { 1,  0,  0,  1,  0,  0,  0,  1,    1,    0 }, 
                                        { 1,  0,  0,  1,  0,  0,  1,  0,    1,    0 }, 
                                        { 1,  0,  0,  1,  0,  1,  0,  0,    0,    1 }, 
                                        { 0,  1,  0,  0,  1,  0,  0,  1,    0,    0 }, 
                                        { 0,  1,  0,  0,  1,  0,  1,  0,    0,    0 }, 
                                        { 0,  1,  0,  0,  1,  1,  0,  0,    0,    1 }, 
                                        { 0,  1,  0,  1,  0,  0,  0,  1,    0,    0 }, 
                                        { 0,  1,  0,  1,  0,  0,  1,  0,    0,    1 }, 
                                        { 0,  1,  0,  1,  0,  1,  0,  0,    0,    1 }, 
                                        { 0,  0,  1,  0,  1,  0,  0,  1,    0,    0 }, 
                                        { 0,  0,  1,  0,  1,  0,  1,  0,    0,    0 },
                                        { 0,  0,  1,  0,  1,  1,  0,  0,    0,    1 },
                                        { 0,  0,  1,  1,  0,  0,  0,  1,    0,    0 },
                                        { 0,  0,  1,  1,  0,  0,  1,  0,    0,    1 },
                                        { 0,  0,  1,  1,  0,  1,  0,  0,    0,    1 },
                                       };

// EEPROM variables and definitions
String command; 
unsigned int addr = 0;
unsigned int memoAddr = 1;
unsigned int logData;

// ThinksSpeak 
int field7Data = 0;
int field8Data = 0;
String cmd;




