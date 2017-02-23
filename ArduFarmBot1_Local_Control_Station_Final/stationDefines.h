  
// -----------------------  HW: Pin definitions
// Sensors
#define DHTPIN 5         // DHT data pin connected to Arduino pin 5
#define DHTTYPE DHT22    // DHT 22 (if your sensor is the DHT 11, only change this line by: #define DHTTYPE DHT11) 
#define LDR_PIN 0        // used for Luminosity (LDR) Sensor Input

#define SOIL_MOIST_1_PIN 1 // used for Soil Moisture Sensor Input
#define SOIL_MOIST_2_PIN 2 // used for Soil Moisture Sensor Input
#define SMS_VCC 7 // used for Soil Moisture Sensor "Power Supply" (VCC)
#define SMS_GND 6 // used for Soil Moisture Sensor "GND"

// Actuators: Buttons and LEDs
#define PUMP_ON 11  //push-button
#define PUMP_PIN 10
#define LAMP_ON 9  //push-button (9)
#define LAMP_PIN 8
#define SENSORS_READ 12  // push-button 

// Alert LED
#define YELLOW_LED 13 // 13

// -----------------------  SW: Variables and definitionsdefinitions
//  to be used by DHT Sensor
int humDHT;
int tempDHT; 
int tempLowAlert = 0;
int HOT_TEMP = 30;
int COLD_TEMP = 12;

// to be used by LDR Sensor
int lumen;
int lumenAlert = 0;
int DARK_LIGHT = 30;

// to be used by SM Sensor
int soilMoist;
int soilMoistAlert = 0;
int DRY_SOIL = 40;
int WET_SOIL = 60;
int numSM = 1; // "numSM" defines number of moisture sensors that are connected
int numSamplesSMS = 1; // "numSamplesSMS" defines number of samples of each reading cycle

// to be used by Actuators
boolean pumpStatus = 0;
boolean lampStatus = 0;
int timePumpOn = 10; // turn Pump On in minutes

// to be used with timers
long sampleTimingSeconds = 30; // ==> Define Sample time in seconds to read sensores
long startTiming = 0;
long elapsedTime = 0;
