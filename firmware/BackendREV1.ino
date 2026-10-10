const int ROTSENSOR = A0; //Establishes analog pin 0 for the Rotary Angle Sensor.

const int lightPin = A1; //Establishes analog pin 1 for the Light Sensor.

const int Buttonpin = 4; //Establishes digital pin 4 for the Button.

const int timerLED = 2; //Establishes digital pin 2 for the LED Socket Kit.

unsigned long timerStart = 0; //Establishes the Starting Time for the timer function.

bool sensor_on = false; //Defaults the Button to being off.

bool timerStarted = false; //Defaults the timer to not be started yet.

bool timerEnded = false; //Defaults the timer to not be finished yet.

int lastButtonState = HIGH; //Defaults the Last Button Press to being off.

int timerLength = 0; //Initializes timer length variable.

int Minutes = 0; //Initializes minutes variable.

unsigned long selectionStart = 0; //Initializes the selection start variable.

unsigned long lastPrint = 0; //Initializes the last print variable.

bool selectionStarted = false; //Establishes that time selection has not started.

bool selectionComplete = false; //Establishes that time selection has not finished.

bool systemStarted = false; //Establishes that the system has not started.

bool timePrinted = false; //Establishes that the time has not been printed yet.


void setup() 
{
  Serial.begin(9600); //Establishes Baud rate of 9600 Bits per second.

  pinMode(Buttonpin, INPUT_PULLUP); //Establishes Button as an input & prevents junk values by maintaining voltage.

  pinMode(LED_BUILTIN, OUTPUT); //Establishes built-in LED as an output.

  pinMode(ROTSENSOR, INPUT); //Establishes the Rotary Angle Sensor as an input.

  pinMode(timerLED, OUTPUT); //Establishes the LED Socket Kit as an output.

  digitalWrite(timerLED, LOW); //Sets the LED Socket Kit to be off when the operation begins.
}

void loop() 
{
  timer(); //Calls upon the LED Socket Kit Function. 

  if(!systemStarted) //If loop for if the system has not started.
  {
    Button(); //Runs the Button function.
  }
  else
  {
    light_sensor(); //Otherwise, runs the light sensor function.
  }
}
void Button() //Defines the Button function.
{
  int buttonState = digitalRead(Buttonpin); //Sets Button State equal to the state of the Buttonpin.
  // Detect a new button press.
  if (buttonState == LOW && lastButtonState == HIGH)
  {
    if (selectionComplete && !systemStarted) //If statement for if time has been selected and the system has started.
    {
      systemStarted = true; 

      sensor_on = true;
    }
    delay(50); // Simple debounce.
  }

  lastButtonState = buttonState; //Sets the current button state as the new previous button state.
  
  if (sensor_on) //If statement that runs when the Button is on.
  {
    digitalWrite(LED_BUILTIN, LOW); //Turns the Built-in LED off.

  }
  else
  {
    digitalWrite(LED_BUILTIN, HIGH); //Turns the Built-in LED on.
  }
}

int angle_sensor() //Rotary Angle Sensor Function.
{
  if(selectionComplete) //If statement for if the time has been selected.
  {
    return Minutes; //Returns minutes. 
  }
  if(!selectionStarted) //If statement for if the time selection has not started.
  {
    selectionStart = millis(); //Sets selection start variable equal to the millis function.

    selectionStarted = true; //Starts the time selection process.

  }
  int value = analogRead(ROTSENSOR); //Sets the value equal to the analog input of the Rotary Angle Sensor.

  value = constrain(value, 0, 1023); //Limits the value to be between 0 and 1023. 

  if(millis() - selectionStart >= 5000) //If statement for if five seconds have passed since the time selection process started.
  {
    Minutes = map(value, 0, 1023, 15, 240); //Maps the values onto a range of 15 and 240 minutes for the timer.

    selectionComplete = true; //Establishes that the time has been successfully selected.

    if(!timePrinted) //If statement for if the time has not been printed.
    {
      Serial.print("Time"); //Prints Time.

      Serial.print(",");

      Serial.println(Minutes); //Prints the time. 

      timePrinted = true; //Establishes that the time has been printed. 
    }
    return Minutes; //Returns Minutes for the timer function.
  }
  return 0; //Ends the function operation and returns the integer 0 to the calling function.
}

void light_sensor() //Light Sensor Function.
{
  int lightlevel = analogRead(lightPin); //Establishes light level as an analog of the light pin.

  if(lightlevel > 50) //Establishes minimum light level for the loop to run.
  {
    digitalWrite(LED_BUILTIN, HIGH); //Built-in LED turns on.

    Serial.print("light"); //Prints light.

    Serial.print(",");

    Serial.print(lightlevel); //Prints the lightlevel value.

    Serial.print(",");

    Serial.println("1"); //Prints 1.
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW); //Built in LED turns off.

    Serial.print("light");

    Serial.print(",");

    Serial.print(lightlevel); //Prints the lightlevel value.

    Serial.print(",");

    Serial.println("0"); //Prints 0.
  }
  delay(100); //Delays process by 100 milliseconds.
}

void timer() //Timer function.
{
  int selectedMinutes = angle_sensor(); //Calls the angle sensor function to define the local integer selectedMinutes.

  if(!timerStarted && systemStarted && selectionComplete && selectedMinutes > 0) //If statement runs if the timer has not started, the system has started, the selection has been completed, and the selected minutes are greater than zero.
  {
    timerLength = selectedMinutes * 60; //Converts minutes to seconds.

    timerStart = millis(); 

    timerStarted = true;
  }
  if(timerStarted && !timerEnded) //If statement that runs when the timer has started but not ended.
  {
    unsigned long elapsedSeconds = (millis() - timerStart) / 1000UL; //Calculates how much time has elapsed.

    if(elapsedSeconds >= (unsigned long)timerLength) //Calculates when the Timer reaches zero.
    {
      timerEnded = true; //Establishes that the timer has ended.

      digitalWrite(timerLED, HIGH); //Turns the timer LED on.

      Serial.println("done"); //Prints done. 
    }
  }
}
