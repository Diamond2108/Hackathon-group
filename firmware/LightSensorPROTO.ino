const int lightPin = A1;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  int lightlevel = analogRead(lightPin);
  Serial.println(lightlevel);

  if(lightlevel > 350)
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(200);
}