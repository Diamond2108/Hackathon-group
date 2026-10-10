const int SENSOR = A0;
const int lightPin = A1;

const int Buttonpin = 4; //D4 is the pin

bool sensor_on = false;
int lastButtonState = LOW;

void setup() 
{
  Serial.begin(9600);
  pinMode(Buttonpin, INPUT_PULLUP); //Establishes Button as an input & ensures constant HIGH reading instead of junk values
  pinMode(LED_BUILTIN, OUTPUT); //Establishes built-in LED as an output
  pinMode(SENSOR, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
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
    light_sensor();
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

  delay(100);
}

void light_sensor()
{
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
  delay(100); //Delays process by 200 milliseconds
}
