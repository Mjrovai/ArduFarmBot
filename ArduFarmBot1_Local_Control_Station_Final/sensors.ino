
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
  int anaValue1 = 0;
  int anaValue2 = 0;
  for(i = 0; i < numSamplesSMS; i++) // // "numSamplesSMS" defines number of samples of each reading cycle
  {
    digitalWrite(SMS_VCC,LOW);   // drive a current through the divider in one direction
    digitalWrite(SMS_GND,HIGH);
    delay(500);   // wait a moment for capacitance effects to settle
    anaValue1 += analogRead(SOIL_MOIST_1_PIN);
    delay(500);   // wait a moment for ADC settle-up
    anaValue2 += analogRead(SOIL_MOIST_2_PIN);
    
    digitalWrite(SMS_VCC,HIGH);   // reverse the current
    digitalWrite(SMS_GND,LOW);
    delay(1000);   // give as much time in 'reverse' as in 'forward'
    digitalWrite(SMS_VCC,LOW);   // stop the current
    //delay (3000);
  }
  
  anaValue1 = anaValue1/(i);
  anaValue2 = anaValue2/(i);
  if (numSM == 2) anaValue1 = (anaValue1+anaValue2)/2; // "numSM" variable, defines number of moisture sensors that are connected
  
  anaValue1 = map(anaValue1, 1015, 3, 0, 100); //1015:0 (en el air) ==> 003:100% (poniendo un "short circuit) 
  //Serial.println(anaValue1);
  return anaValue1;
}


