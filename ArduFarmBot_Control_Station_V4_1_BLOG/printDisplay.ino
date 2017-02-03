

/***************************************************
* Showing capured data at LCD
****************************************************/
void showDataLCD(void)
{
  lcd.setCursor (0,0);
  lcd.print("TEMP  ");
  lcd.setCursor (6,0);
  if (errorDHT == 1) lcd.print ("DHT with error ");
  else 
  {
    lcd.print("     ");
    lcd.setCursor (6,0);
    lcd.print(tempDHT);
    lcd.print("oC");
    lcd.setCursor (11,0);
    lcd.print("HUM ");
    lcd.setCursor (16,0);
    lcd.print("    ");
    lcd.setCursor (16,0);
    lcd.print(humDHT);
    lcd.print("%  ");
  }
  lcd.setCursor (0,1);
  lcd.print("LIGHT ");
  lcd.setCursor (6,1);
  lcd.print("     ");
  lcd.setCursor (6,1);
  lcd.print(lumen);
  lcd.print("%");
  lcd.setCursor (11,1);
  lcd.print("SOIL ");
  lcd.setCursor (16,1);
  lcd.print("    ");
  lcd.setCursor (16,1);
  lcd.print(soilMoist);
  lcd.print("%");
  lcd.setCursor (0,2);
  lcd.print("PUMP ");
  lcd.setCursor (6,2);
  lcd.print("    ");
  lcd.setCursor (6,2);
  if (soilMoistAlert  == 1) lcd.print ("wait");
  else 
  {
    if (pumpStatus == 1) lcd.print("on");
    if (pumpStatus == 0) lcd.print("off");
  }
  lcd.setCursor (11,2);
  lcd.print("LAMP ");
  lcd.setCursor (16,2);
  lcd.print("    ");
  lcd.setCursor (16,2);
  if (tempLowAlert == 1) lcd.print ("wait");
  else 
  {
    if (lampStatus == 1) lcd.print("on");
    if (lampStatus == 0) lcd.print("off");
  }
  lcd.setCursor (0,3);
  lcd.print("TIME ");
  lcd.setCursor (6,3);
  lcd.print("     ");
  lcd.setCursor (6,3);
  lcd.print(reverseElapsedTimeSeconds);
  lcd.print("s");
  lcd.setCursor (19,3);
}

/***************************************************
* Showing setup at LCD
****************************************************/
void showSetupLCD(void)
{
  lcd.setCursor (0,0);
  lcd.print("COLD ");
  lcd.setCursor (6,0);
    lcd.print("    ");
    lcd.setCursor (6,0);
    lcd.print(COLD_TEMP);
    lcd.print("oC");
    lcd.setCursor (11,0);
    lcd.print("DRY ");
    lcd.setCursor (16,0);
    lcd.print("    ");
    lcd.setCursor (16,0);
    lcd.print(DRY_SOIL);
    lcd.print("%  ");
  lcd.setCursor (0,1);
  lcd.print("DARK ");
  lcd.setCursor (6,1);
  lcd.print("    ");
  lcd.setCursor (6,1);
  lcd.print(DARK_LIGHT);
  lcd.print("%");
  lcd.setCursor (11,1);
  lcd.print("WET ");
  lcd.setCursor (16,1);
  lcd.print("    ");
  lcd.setCursor (16,1);
  lcd.print(WET_SOIL);
  lcd.print("%");
  lcd.setCursor (0,2); 
  lcd.print("P_ON "); 
  lcd.setCursor (6,2); 
  lcd.print("    "); 
  lcd.setCursor (6,2); 
  lcd.print(timePumpOn); 
  lcd.print("s");
  lcd.setCursor (11,2);
  lcd.print("SCAN ");
  lcd.setCursor (16,2);
  lcd.print("    ");
  lcd.setCursor (16,2);
  lcd.print(sampleTimingSeconds);
  lcd.print("s");
  lcd.setCursor (0,3); 
  lcd.print("SW_V "); 
  lcd.print(SW_VERSION);

//  lcd.setCursor (0,3);
//  lcd.print("LOG: ");
//  lcd.setCursor (5,3);
//  lcd.print("          ");
//  lcd.setCursor (5,3);
//  lcd.print(EEPROM.read (memoAddr), BIN);
//  lcd.print(EEPROM.read (memoAddr+1), BIN);
  lcd.setCursor (19,3);

}

/***************************************************
* LCD on waiting mode - press a key to continue
****************************************************/
void waitModeLCD(void)
{
   lcd.cursor();
   lcd.setCursor (11,3);
   lcd.println("press=>"  );
   lcd.setCursor (19,3);
   lcd.blink();
//   printInitialData();
   while (debounce(SENSORS_READ)) 
   {
//      printLogFile();
   }
   lcd.noBlink();
   lcd.noCursor();
   lcd.noDisplay();
   lcd.noBacklight();
}

//void printLogFile(void)
//{
//
// while (Serial.available()) 
// {
//  delay(10);  
//  if (Serial.available() >0) 
//  {
//   char c = Serial.read();
//   command += c;
//  }
// }
// switch (command.charAt(0))
// {
//   case 'R': // command is to read all EEPROM
//     Serial.println("");
//     Serial.println("Start printing Log");
//     Serial.println("");
//     Serial.println("+---SOIL----+-LIGHT--+---TEMP---+---ACTUAT----+");
//     Serial.println(" SL  SM  SH   LL  LH  TL  TM  TH   Pump  Lamp");
//     Serial.println("  ");   
//     for (int i=1; i<EEPROM.read (0); i=i+2)
//     {
//        Serial.print("Time (min): ");
//        Serial.print(i*sampleTimingSeconds/120);
//        Serial.print("  Sensors: ");
//        Serial.print(EEPROM.read (i), BIN);
//        Serial.print("  ---+--- Actuators: ");
//        Serial.println(EEPROM.read (i+1), BIN);
//     }
//     Serial.println("");
//     Serial.println("End of Printing Log: Press a Update Sensor Key at ArdufarmBot to go on"); 
//     Serial.println("");
//     break;
//  
//  case 'r': // command is to read all EEPROM
//     Serial.println("");
//     Serial.println("Start printing Log");
//     Serial.println("");
//     Serial.println("+---SOIL----+-LIGHT--+---TEMP---+---ACTUAT----+");
//     Serial.println(" SL  SM  SH   LL  LH  TL  TM  TH   Pump  Lamp");
//     Serial.println("  ");   
//     for (int i=1; i<EEPROM.read (0); i=i+2)
//     {
//        Serial.print("Time (min): ");
//        Serial.print(i*sampleTimingSeconds/120);
//        Serial.print("  Sensors: ");
//        Serial.print(EEPROM.read (i), BIN);
//        Serial.print("  ---+--- Actuators: ");
//        Serial.println(EEPROM.read (i+1), BIN);
//     }
//     Serial.println("");
//     Serial.println("End of Printing Log: Press a Update Sensor Key at ArdufarmBot to go on"); 
//     Serial.println("");
//     break;
// } 
// 
// command = "";
//}
//
///***************************************************
//* Showing setup at Serial Monitor
//****************************************************/
//void printInitialData(void)
//{
//  Serial.println("ArduFarmBot Initial Configuration");
//  Serial.println(" "); 
//  Serial.print("DHT Model: ");
//  Serial.println(DHTTYPE);
//  Serial.print("Number of Soil Moister Sensors: ");
//  Serial.println(numSM);
//  Serial.print("TEMP  ==> COLD: ");
//  Serial.print(COLD_TEMP);
//  Serial.print("oC  HOT: ");
//  Serial.print(HOT_TEMP);
//  Serial.println("oC");
//  Serial.print("SOIL  ==> DRY:  ");
//  Serial.print(DRY_SOIL);
//  Serial.print("% ");
//  Serial.print("  WET: ");
//  Serial.print(WET_SOIL);
//  Serial.println("%");
//  Serial.print("LIGHT ==> DARK: ");
//  Serial.print(DARK_LIGHT);
//  Serial.println("%");
//  Serial.print("TIME PUMP ON: ");
//  Serial.print(timePumpOn);
//  Serial.println("s");
//  Serial.print("TIME SENSOR SCAN: ");
//  Serial.print(sampleTimingSeconds);
//  Serial.println("s");
//  Serial.println("  ");
//  Serial.println("Initial mode: Press 'R' or 'r' and 'Send' to print the last Log File"); 
//}
//   

/***************************************************
* Showing capured data at Serial Monitor
****************************************************/
void printData(void)
{
//  Serial.print("   Temp DHT ==> ");
//  Serial.print(tempDHT);
//  Serial.print("oC  Hum DHT ==> ");
//  Serial.print(humDHT);
//  Serial.print("%  Luminosity ==> ");
//  Serial.print(lumen);
//  Serial.print("%  Soil Moisture ==> ");
//  Serial.print(soilMoist);
//  Serial.print("%  Pump: ");
//  if (soilMoistAlert  == 1) Serial.print ("X");
//  else Serial.print(pumpStatus);
//  Serial.print("    Lamp: ");
//  Serial.println(lampStatus);
}

