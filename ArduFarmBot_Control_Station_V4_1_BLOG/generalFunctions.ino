 
/***************************************************
* Iniciate Station
****************************************************/
void iniciateStation()
{
  Serial.begin(speed8266); 
  esp8266.begin (speed8266); 
  dht.begin();
  lcd.begin();
  lcd.print("Resetting 8266");
  Serial.println("Resetting 8266");
  reset8266(); // Pin CH_PD need a reset before start communication
  connectWiFi();
  Serial.print("ArduFarmBot ==> "); Serial.print("Sw Version: "); Serial.println(SW_VERSION);
  lcd.clear();
  showSetupLCD(); // show innitial setup
  waitModeLCD();
  turnOffLCD = 1;
  startTiming = millis();
  startRemoteCmdTiming = millis();
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

 
/***************************************************
* Storage of Log data at Arduino EEPROM
****************************************************/
void storeDataLogEEPROM(void)
{
  for (int i = 0; i<8; i++) 
  {
    //Serial.print(snsSts[i]);
    logData = logData + (snsSts[i])<< 1;
  }
//  Serial.print ("LOG_Sensors ==> ");
//  logData = logData >> 1;
//  Serial.print (logData, BIN);
//
//  Serial.print("    EEPROM Adress: ");
//  Serial.print(memoAddr);
    EEPROM.write (memoAddr, logData);
//  Serial.print("   ==> Log Sensors: ");
//  Serial.print(EEPROM.read (memoAddr), BIN);
// 
//  Serial.print ("   PUMP ==> ");
//  Serial.print (pumpStatus);
//  Serial.print ("   LAMP ==> ");
//  Serial.print (lampStatus);

  memoAddr++;
  logData = 0;
  logData = logData + pumpStatus;
  logData = logData << 1;
  logData = logData + lampStatus;
//  Serial.print ("   LOG ==> ");
//  Serial.print(logData, BIN);
  
//  Serial.print("    EEPROM Adress: ");
//  Serial.print(memoAddr);
  EEPROM.write (memoAddr, logData);
//  Serial.print("   ==> Log Actuators: ");
//  Serial.println(EEPROM.read (memoAddr), BIN);
  EEPROM.write (0, memoAddr+1);
  logData = 0; 
  if ((memoAddr+1) == 1023) memoAddr=1;
  else memoAddr++;

} 

