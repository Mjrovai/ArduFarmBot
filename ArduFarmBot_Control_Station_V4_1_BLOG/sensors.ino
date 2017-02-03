/***************************************************
* Sensors Matrix
****************************************************/
void defSensorStatus (void)
{
  for (int i = 0; i<8; i++) snsSts[i]=0;
  
  if (soilMoist < DRY_SOIL) snsSts[0] = 1;
  if (soilMoist >= DRY_SOIL && soilMoist < WET_SOIL) snsSts[1] = 1;
  if (soilMoist >= WET_SOIL) snsSts[2] = 1;
  if (lumen < DARK_LIGHT) snsSts[3] = 1;
  if (lumen >= DARK_LIGHT) snsSts[4] = 1; 
  if (tempDHT < COLD_TEMP) snsSts[5] = 1; 
  if (tempDHT >= COLD_TEMP && tempDHT < HOT_TEMP) snsSts[6] = 1; 
  if (tempDHT > HOT_TEMP) snsSts[7] = 1; 
  

//        ----------------------------- SOIL --------------------+-----------------LIGHT-----------+--------------------------TEMPERATURE --------------+
//                     DRY (0)          IDEAL (1)          WET (2)          DARK (3)          LIGHT (4)          COLD (5)        MEDIUM (6)       HOT (7)               PUMP (8)     PUMP (9)
  if      ((snsSts[0]== SDf[0][0] )&&(snsSts[1]== SDf[0][1] )&&(snsSts[2]== SDf[0][2] )&&(snsSts[3]== SDf[0][3] )&&(snsSts[4]== SDf[0][4] )&&(snsSts[5]== SDf[0][5] )&&(snsSts[6]== SDf[0][6] )&&(snsSts[7]== SDf[0][7] ))  {pumpStatus = SDf[0][8]; lampStatus = SDf[0][9];} // roll: 0
  else if ((snsSts[0]== SDf[1][0] )&&(snsSts[1]== SDf[1][1] )&&(snsSts[2]== SDf[1][2] )&&(snsSts[3]== SDf[1][3] )&&(snsSts[4]== SDf[1][4] )&&(snsSts[5]== SDf[1][5] )&&(snsSts[6]== SDf[1][6] )&&(snsSts[7]== SDf[1][7] ))  {pumpStatus = SDf[1][8]; lampStatus = SDf[1][9];} // roll: 1
  else if ((snsSts[0]== SDf[2][0] )&&(snsSts[1]== SDf[2][1] )&&(snsSts[2]== SDf[2][2] )&&(snsSts[3]== SDf[2][3] )&&(snsSts[4]== SDf[2][4] )&&(snsSts[5]== SDf[2][5] )&&(snsSts[6]== SDf[2][6] )&&(snsSts[7]== SDf[2][7] ))  {pumpStatus = SDf[2][8]; lampStatus = SDf[2][9];} // roll: 2
  else if ((snsSts[0]== SDf[3][0] )&&(snsSts[1]== SDf[3][1] )&&(snsSts[2]== SDf[3][2] )&&(snsSts[3]== SDf[3][3] )&&(snsSts[4]== SDf[3][4] )&&(snsSts[5]== SDf[3][5] )&&(snsSts[6]== SDf[3][6] )&&(snsSts[7]== SDf[3][7] ))  {pumpStatus = SDf[3][8]; lampStatus = SDf[3][9];} // roll: 3
  else if ((snsSts[0]== SDf[4][0] )&&(snsSts[1]== SDf[4][1] )&&(snsSts[2]== SDf[4][2] )&&(snsSts[3]== SDf[4][3] )&&(snsSts[4]== SDf[4][4] )&&(snsSts[5]== SDf[4][5] )&&(snsSts[6]== SDf[4][6] )&&(snsSts[7]== SDf[4][7] ))  {pumpStatus = SDf[4][8]; lampStatus = SDf[4][9];} // roll: 4
  else if ((snsSts[0]== SDf[5][0] )&&(snsSts[1]== SDf[5][1] )&&(snsSts[2]== SDf[5][2] )&&(snsSts[3]== SDf[5][3] )&&(snsSts[4]== SDf[5][4] )&&(snsSts[5]== SDf[5][5] )&&(snsSts[6]== SDf[5][6] )&&(snsSts[7]== SDf[5][7] ))  {pumpStatus = SDf[5][8]; lampStatus = SDf[5][9];} // roll: 5
  else if ((snsSts[0]== SDf[6][0] )&&(snsSts[1]== SDf[6][1] )&&(snsSts[2]== SDf[6][2] )&&(snsSts[3]== SDf[6][3] )&&(snsSts[4]== SDf[6][4] )&&(snsSts[5]== SDf[6][5] )&&(snsSts[6]== SDf[6][6] )&&(snsSts[7]== SDf[6][7] ))  {pumpStatus = SDf[6][8]; lampStatus = SDf[6][9];} // roll: 6
  else if ((snsSts[0]== SDf[7][0] )&&(snsSts[1]== SDf[7][1] )&&(snsSts[2]== SDf[7][2] )&&(snsSts[3]== SDf[7][3] )&&(snsSts[4]== SDf[7][4] )&&(snsSts[5]== SDf[7][5] )&&(snsSts[6]== SDf[7][6] )&&(snsSts[7]== SDf[7][7] ))  {pumpStatus = SDf[7][8]; lampStatus = SDf[7][9];} // roll: 7
  else if ((snsSts[0]== SDf[8][0] )&&(snsSts[1]== SDf[8][1] )&&(snsSts[2]== SDf[8][2] )&&(snsSts[3]== SDf[8][3] )&&(snsSts[4]== SDf[8][4] )&&(snsSts[5]== SDf[8][5] )&&(snsSts[6]== SDf[8][6] )&&(snsSts[7]== SDf[8][7] ))  {pumpStatus = SDf[8][8]; lampStatus = SDf[8][9];} // roll: 8
  else if ((snsSts[0]== SDf[9][0] )&&(snsSts[1]== SDf[9][1] )&&(snsSts[2]== SDf[9][2] )&&(snsSts[3]== SDf[9][3] )&&(snsSts[4]== SDf[9][4] )&&(snsSts[5]== SDf[9][5] )&&(snsSts[6]== SDf[9][6] )&&(snsSts[7]== SDf[9][7] ))  {pumpStatus = SDf[9][8]; lampStatus = SDf[9][9];} // roll: 9
  else if ((snsSts[0]== SDf[10][0] )&&(snsSts[1]== SDf[10][1] )&&(snsSts[2]== SDf[10][2] )&&(snsSts[3]== SDf[10][3] )&&(snsSts[4]== SDf[10][4] )&&(snsSts[5]== SDf[10][5] )&&(snsSts[6]== SDf[10][6] )&&(snsSts[7]== SDf[10][7] ))  {pumpStatus = SDf[10][8]; lampStatus = SDf[10][9];} // roll: 10
  else if ((snsSts[0]== SDf[11][0] )&&(snsSts[1]== SDf[11][1] )&&(snsSts[2]== SDf[11][2] )&&(snsSts[3]== SDf[11][3] )&&(snsSts[4]== SDf[11][4] )&&(snsSts[5]== SDf[11][5] )&&(snsSts[6]== SDf[11][6] )&&(snsSts[7]== SDf[11][7] ))  {pumpStatus = SDf[11][8]; lampStatus = SDf[11][9];} // roll: 11
  else if ((snsSts[0]== SDf[12][0] )&&(snsSts[1]== SDf[12][1] )&&(snsSts[2]== SDf[12][2] )&&(snsSts[3]== SDf[12][3] )&&(snsSts[4]== SDf[12][4] )&&(snsSts[5]== SDf[12][5] )&&(snsSts[6]== SDf[12][6] )&&(snsSts[7]== SDf[12][7] ))  {pumpStatus = SDf[12][8]; lampStatus = SDf[12][9];} // roll: 12
  else if ((snsSts[0]== SDf[13][0] )&&(snsSts[1]== SDf[13][1] )&&(snsSts[2]== SDf[13][2] )&&(snsSts[3]== SDf[13][3] )&&(snsSts[4]== SDf[13][4] )&&(snsSts[5]== SDf[13][5] )&&(snsSts[6]== SDf[13][6] )&&(snsSts[7]== SDf[13][7] ))  {pumpStatus = SDf[13][8]; lampStatus = SDf[13][9];} // roll: 13
  else if ((snsSts[0]== SDf[14][0] )&&(snsSts[1]== SDf[14][1] )&&(snsSts[2]== SDf[14][2] )&&(snsSts[3]== SDf[14][3] )&&(snsSts[4]== SDf[14][4] )&&(snsSts[5]== SDf[14][5] )&&(snsSts[6]== SDf[14][6] )&&(snsSts[7]== SDf[14][7] ))  {pumpStatus = SDf[14][8]; lampStatus = SDf[14][9];} // roll: 14
  else if ((snsSts[0]== SDf[15][0] )&&(snsSts[1]== SDf[15][1] )&&(snsSts[2]== SDf[15][2] )&&(snsSts[3]== SDf[15][3] )&&(snsSts[4]== SDf[15][4] )&&(snsSts[5]== SDf[15][5] )&&(snsSts[6]== SDf[15][6] )&&(snsSts[7]== SDf[15][7] ))  {pumpStatus = SDf[15][8]; lampStatus = SDf[15][9];} // roll: 15
  else if ((snsSts[0]== SDf[16][0] )&&(snsSts[1]== SDf[16][1] )&&(snsSts[2]== SDf[16][2] )&&(snsSts[3]== SDf[16][3] )&&(snsSts[4]== SDf[16][4] )&&(snsSts[5]== SDf[16][5] )&&(snsSts[6]== SDf[16][6] )&&(snsSts[7]== SDf[16][7] ))  {pumpStatus = SDf[16][8]; lampStatus = SDf[16][9];} // roll: 16
  else if ((snsSts[0]== SDf[17][0] )&&(snsSts[1]== SDf[17][1] )&&(snsSts[2]== SDf[17][2] )&&(snsSts[3]== SDf[17][3] )&&(snsSts[4]== SDf[17][4] )&&(snsSts[5]== SDf[17][5] )&&(snsSts[6]== SDf[17][6] )&&(snsSts[7]== SDf[17][7] ))  {pumpStatus = SDf[17][8]; lampStatus = SDf[17][9];} // roll: 17
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



