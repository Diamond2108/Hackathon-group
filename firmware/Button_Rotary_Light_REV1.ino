const int ROTSENSOR = A0; //Establishes analog pin 0 for the Rotary Angle Sensor
const int lightPin = A1; //Establishes analog pin 1 for the Light Sensor

const int Buttonpin = 4; //Establishes digital pin 4 for the Button

bool sensor_on = false; //Defaults the Rotary Angle Sensor to being off
int lastButtonState = LOW; //Defaults the Button to being off

void setup() 
{
  Serial.begin(9600); //Establishes Baud rate of 9600 Bits per second
  pinMode(Buttonpin, INPUT_PULLUP); //Establishes Button as an input & prevents junk values by maintaining voltage
  pinMode(LED_BUILTIN, OUTPUT); //Establishes built-in LED as an output
  pinMode(ROTSENSOR, INPUT); //Establishes the Rotary Angle Sensor as an input
  pinMode(LED_BUILTIN, OUTPUT); //Establishes the Built-in LED as an output
}

void loop() 
{
  
  int buttonState = digitalRead(Buttonpin); //Sets Button State equal to the state of the Buttonpin

  // Detect a new button press
  if (buttonState == HIGH && lastButtonState == LOW)
  {
    sensor_on = !sensor_on; //Switches the Rotary Angle Sensor to the opposite (off to on and vice versa)
    delay(50); // Simple debounce
  }

  lastButtonState = buttonState; //Sets the current button state as the new previous button state

  if (sensor_on) //If statement that runs when the Rotary Angle Sensor is operating
  {
    digitalWrite(LED_BUILTIN, LOW); //Turns the Built-in LED off
    angle_sensor(); //Calls upon the Rotary Angle Sensor Function
    light_sensor(); //Calls upon the Light Sensor Function
  }
  else
  {
    digitalWrite(LED_BUILTIN, HIGH); //Turns the Built-in LED on
  }
}

void angle_sensor() //Rotary Angle Sensor Function
{
  int value = analogRead(ROTSENSOR); //Sets the value integer equal to the Analog of the Rotary Angle Sensor

  float angle = value * 300/1020; //Calculates the Angle


  Serial.print("Sensor value: "); 
  Serial.print(value); //Prints the Sensor Value

  Serial.print("| Angle ");
  Serial.print(angle, 1); //Prints the Calculated Angle
  Serial.println("Degrees");

  delay(100); //Simple debounce
}

void light_sensor() //Light Sensor Function
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