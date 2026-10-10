const int ROTSENSOR = A0; //Establishes analog pin 0 for the Rotary Angle Sensor.

const int lightPin = A1; //Establishes analog pin 1 for the Light Sensor.

const int Buttonpin = 4; //Establishes digital pin 4 for the Button.

bool sensor_on = false; //Defaults the Button to being off.

int lastButtonState = HIGH; //Defaults the Last Button Press to being off.

void setup() 
{
  Serial.begin(9600); //Establishes Baud rate of 9600 Bits per second.

  pinMode(Buttonpin, INPUT_PULLUP); //Establishes Button as an input & prevents junk values by maintaining voltage.

  pinMode(LED_BUILTIN, OUTPUT); //Establishes built-in LED as an output.

  pinMode(ROTSENSOR, INPUT); //Establishes the Rotary Angle Sensor as an input.

  pinMode(LED_BUILTIN, OUTPUT); //Establishes the Built-in LED as an output.
}

void loop() 
{
  
  int buttonState = digitalRead(Buttonpin); //Sets Button State equal to the state of the Buttonpin.

  angle_sensor(); //Calls upon the Rotary Angle Sensor Function.

  // Detect a new button press.
  if (buttonState == LOW && lastButtonState == HIGH)
  {
    sensor_on = !sensor_on; //Switches the Button to the opposite (off to on and vice versa).

    delay(50); // Simple debounce.
  }

  lastButtonState = buttonState; //Sets the current button state as the new previous button state.
  
  if (sensor_on) //If statement that runs when the Button is on.
  {
    digitalWrite(LED_BUILTIN, LOW); //Turns the Built-in LED off.

    light_sensor(); //Calls upon the Light Sensor Function.
  }
  else
  {
    digitalWrite(LED_BUILTIN, HIGH); //Turns the Built-in LED on.
  }
}

void angle_sensor() //Rotary Angle Sensor Function.
{
  int value = analogRead(ROTSENSOR); //Sets the value integer equal to the Analog of the Rotary Angle Sensor.

  static unsigned long Start = 0; //A non-negative number that cannot change to serve as a time reliant starting point for this function.

  static bool finished = false; //True False Statement to break the loop for this function.

  if(finished)
  {
    return; //Leaves function once finished is true.
  }

  if(Start == 0)
  {
    Start = millis(); //Calls the millis function to keep track of time.
  }
  if(millis() - Start < 5000) //As long as five seconds have not passed, it will not progress from this function.
  {
    int value = analogRead(ROTSENSOR); //Sets value equal to the analog of the Rotary Angle Sensor.

    Serial.print("time"); 
    Serial.print(",");

    Serial.println(value); //Prints the Sensor Value and then adds new line

    delay(3000); //Simple debounce for three seconds, to give the user ample time to designate a study session length.
  }
  else //Once five seconds have passed, finished becomes true and the loop breaks. 
  {
    finished = true;
    
    //Serial.println("Rotary Readings Complete.");
  }
}

void light_sensor() //Light Sensor Function.
{
  int lightlevel = analogRead(lightPin); //Establishes light level as an analog of the light pin.


  if(lightlevel > 50) //Establishes minimum light level for the loop to run.
  {
    digitalWrite(LED_BUILTIN, HIGH); //Built-in LED turns on.

    Serial.print("light");
    Serial.print(",");
    Serial.print(lightlevel);
    Serial.print(",");
    Serial.println("1");
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW); //Built in LED turns off.

    Serial.print("light");
    Serial.print(",");
    Serial.print(lightlevel);
    Serial.print(",");
    Serial.println("0");
  }
  delay(100); //Delays process by 100 milliseconds.
}