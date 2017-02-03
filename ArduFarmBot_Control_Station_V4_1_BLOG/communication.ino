

/***************************************************
* Transmit data to thingspeak.com
****************************************************/
void updateDataThingSpeak(void)
{
  startThingSpeakCmd ();
  
  cmd = msg ;
  cmd += "&field1=";     //field 1 for DHT temperature
  cmd += tempDHT;
  cmd += "&field2=";    //field 2 for DHT humidity
  cmd += humDHT;
  cmd += "&field3=";    //field 3 for LDR luminosity
  cmd += lumen;
  cmd += "&field4=";    //field 4 for Soil Moisture data 
  cmd += soilMoist;
  cmd += "&field5=";    //field 5 for PUMP Status
  cmd += pumpStatus;
  cmd += "&field6=";    //field 6 for LAMP Status
  cmd += lampStatus;
  cmd += "\r\n";

  sendThingSpeakCmd();
  //startTiming = millis();
}

/***************************************************
* Transmit local command to thingspeak.com
****************************************************/
void updateCmdThingSpeak(void)
{
  digitalWrite(YELLOW_LED, HIGH);
  for (int i = 0; i < 2; i++)
  {
    startThingSpeakCmd ();
    cmd = msg ;
    cmd += "&field5=";    //field 5 for RED_LED Status
    cmd += pumpStatus;
    cmd += "&field6=";    //field 6 for GREEN_LED Status
    cmd += lampStatus;
    cmd += "&field7=";    //field 5 for RED_LED Status
    cmd += pumpStatus;
    cmd += "&field8=";    //field 6 for GREEN_LED Status
    cmd += lampStatus;
    cmd += "\r\n";
    sendThingSpeakCmd();
    delay (500);
  }
  digitalWrite(YELLOW_LED, LOW);
  // startTiming = millis();
}


/***************************************************
* Read data from field7 of thingspeak.com
****************************************************/
int readLastDataField7()
{
  startThingSpeakCmd ();

  // "GET /channels/CHANNEL_ID/fields/7/last";
  cmd = msgReadLastDataField7; 
  cmd += "\r\n";

  String messageDown = sendThingSpeakCmd();
  Serial.print("Command received: ");
  Serial.println(messageDown[7]);
  
  int command = messageDown[7]-48; 
  return command;
}

/***************************************************
* Read data from field8 of thingspeak.com
****************************************************/
int readLastDataField8()
{
  startThingSpeakCmd();

  // "GET /channels/CHANNEL_ID/fields/8/last";
  cmd = msgReadLastDataField8; 
  cmd += "\r\n";
 
  String messageDown = sendThingSpeakCmd();
  
  Serial.print("Command received: ");
  Serial.println(messageDown[7]);
  int command = messageDown[7]-48; 
  return command;
}

/***************************************************
* Start communication with ThingsSpeak.com
****************************************************/
void startThingSpeakCmd(void)
{
  cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += IP;
  cmd += "\",80";
  esp8266.println(cmd);
  delay(2000);
  if(esp8266.find("Error"))
  {
    Serial.println("ESP8266 START ERROR");
    return;
  }
  cmd ="";
}

/***************************************************    
* Update channel ThingsSpeak.com
****************************************************/
String sendThingSpeakCmd(void)
{
  esp8266.print("AT+CIPSEND=");
  esp8266.println(cmd.length());
  if(esp8266.find(">")){
    esp8266.print(cmd);
    Serial.println("");
    Serial.println("");
    Serial.println(cmd);
    delay(500);
   
    String messageBody = "";
    while (esp8266.available()) 
    {
      String line = esp8266.readStringUntil('\n');
      if (line.length() == 1) 
      { //actual content starts after empty line (that has length 1)
        messageBody = esp8266.readStringUntil('\n');
        Serial.print("Message received: ");
        Serial.println(messageBody);
      }
    }
    return messageBody;
  }
  else{
    esp8266.println("AT+CIPCLOSE");
    Serial.println("ESP8266 CIPSEND ERROR: RESENDING"); //Resend...
    error=1;
    return "error";
  }
}



/***************************************************
* Reset funtion to accept communication
****************************************************/
void reset8266(void)
{
  pinMode(CH_PD, OUTPUT);
  digitalWrite(CH_PD, LOW);

  delay(300);
  digitalWrite(CH_PD, HIGH);
  Serial.print("8266 reset OK");
  lcd.clear();
  lcd.println("8266 reset OK       ");
}

/***************************************************
* Connect WiFi
****************************************************/
void connectWiFi(void)
{
  sendData("AT+RST\r\n", 2000, DEBUG); // reset
  sendData("AT+CWJAP=\"YOUR USERNAME\",\"YOUR PASSWORD\"\r\n", 2000, DEBUG); //Connect network
  delay(3000);
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG);
  sendData("AT+CIFSR\r\n", 1000, DEBUG); // Show IP Adress
  lcd.clear();
  lcd.print("8266 Connected");
  Serial.println("8266 Connected");
}

/***************************************************
* Send AT commands to module
****************************************************/

String sendData(String command, const int timeout, boolean debug)
{
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {
      // The esp has data so display its output to the serial window
      char c = esp8266.read(); // read the next character.
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}
