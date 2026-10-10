const int lightPin = A1; //Establishes light pin on analog pin 1

void setup() {
  Serial.begin(9600); //Establishes bit rate
  pinMode(LED_BUILTIN, OUTPUT); //Establishes built-in LED as an output
}

void loop() {
  int lightlevel = analogRead(lightPin); //Establishes light level as an analog of the light pin
  Serial.println(lightlevel); //Prints light level constantly

  if(lightlevel > 350) //Establishes minimum light level for the loop to run
  {
    digitalWrite(LED_BUILTIN, HIGH); //Built-in LED turns on
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW); //Built in LED turns off
  }
  delay(200); //Delays process by 200 milliseconds
}