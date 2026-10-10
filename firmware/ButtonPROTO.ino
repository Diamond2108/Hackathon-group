int Buttonpin = 4; //D4 is the pin

void setup() {
  pinMode(Buttonpin, INPUT_PULLUP); //Establishes Button as an input & ensures constant HIGH reading instead of junk values
  pinMode(LED_BUILTIN, OUTPUT); //Establishes built-in LED as an output

}

void loop() {
  if(digitalRead(Buttonpin) == HIGH) //If loop for when the button is pressed and receives Voltage
  {
    digitalWrite(LED_BUILTIN, HIGH); //Built-in light turns on for half a second
    delay(500);
    digitalWrite(LED_BUILTIN, LOW); //Built-in light turns off for half a second
    delay(500);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW); //Built-in light does not turn on
  }

}
