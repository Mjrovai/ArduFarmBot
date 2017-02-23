
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
  if (soilMoistAlert  == 1) Serial.print ("X");
  else Serial.print(pumpStatus);
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
  lcd.setCursor (6,1);
  lcd.print("    ");
  lcd.setCursor (6,1);
  lcd.print(tempDHT);
  lcd.print("oC Hum: ");
  lcd.setCursor (16,1);
  lcd.print("    ");
  lcd.setCursor (16,1);
  lcd.print(humDHT);
  lcd.print("%  ");
  lcd.setCursor (0,2);
  lcd.print("Lght: ");
  lcd.setCursor (6,2);
  lcd.print("    ");
  lcd.setCursor (6,2);
  lcd.print(lumen);
  lcd.print("%");
  lcd.print(" Soil: ");
  lcd.setCursor (16,2);
  lcd.print("    ");
  lcd.setCursor (16,2);
  lcd.print(soilMoist);
  lcd.print("%");
  lcd.setCursor (0,3);
  lcd.print("Pump: ");
  if (soilMoistAlert  == 1) lcd.print ("X");
  else lcd.print(pumpStatus);
  lcd.print("   Lamp: ");
  if (tempLowAlert == 1) lcd.print ("X");
  else lcd.print(lampStatus);
  lcd.setCursor (0,0);
}
