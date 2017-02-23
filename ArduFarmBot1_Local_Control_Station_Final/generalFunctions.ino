 
/***************************************************
* Iniciate Station
****************************************************/
void iniciateStation()
{
  dht.begin();
  lcd.begin();
  Serial.begin(9600); 
  Serial.println("ArduFarmBot Local Station Test");
  lcd.println("<<<<< Starting >>>>>");
  readSensors(); // innitial reading
  startTiming = millis(); // starting the "program clock"
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


