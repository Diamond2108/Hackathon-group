const int SENSOR = A0;
const int Buttonpin = 4; //D4 is the pin
bool sensor_on = false;
int lastButtonState = LOW;

void setup() 
{
  Serial.begin(9600);
  pinMode(Buttonpin, INPUT_PULLUP); //Establishes Button as an input & ensures constant HIGH reading instead of junk values
  pinMode(LED_BUILTIN, OUTPUT); //Establishes built-in LED as an output
  pinMode(SENSOR, INPUT);
}

void loop() 
{
  
  int buttonState = digitalRead(Buttonpin);

  // Detect a new button press
  if (buttonState == HIGH && lastButtonState == LOW)
  {
    sensor_on = !sensor_on;
    delay(50); // Simple debounce
  }

  lastButtonState = buttonState;

  if (sensor_on)
  {
    digitalWrite(LED_BUILTIN, LOW);
    angle_sensor();
  }
  else
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

void angle_sensor()
{
  int value = analogRead(SENSOR);

  float angle = value * 300/1020;


  Serial.print("Sensor value: ");
  Serial.print(value);

  Serial.print("| Angle ");
  Serial.print(angle, 1);
  Serial.println("Degrees");

  delay(200);
}
