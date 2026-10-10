int Buttonpin = 4; //D4 is the pin
int State = LOW; //Initalizes State as being off
int LastInput = HIGH; //Initializes the Last Input as being on
unsigned long PreviousMillis = 0; //Stores the last recorded time in milliseconds since the program started
const long Interval = 100; //Establishes the Interval as always being 100 milliseconds
int LED = LOW; //Initalizes LED as being off
void setup() {
  pinMode(Buttonpin, INPUT_PULLUP); //Establishes Buttonpin as an Input Pull-up
  pinMode(LED_BUILTIN, OUTPUT); //Establishes Built-in LED as an Output
  digitalWrite(LED_BUILTIN, State); //Sets Built-in LED to State, which is off
}

void loop() {
  int CurrentInput = digitalRead(Buttonpin); //Sets Current Input equal to Current Value of Buttonpin
  if(CurrentInput == LOW && LastInput == HIGH) //If statement that runs when Current Input is off and Last Input is on
  {
    State = !State; //Reverses State (off to on)
    PreviousMillis = millis(); //Sets the Previous Millis equal to the number of milliseconds at this point
    digitalWrite(LED_BUILTIN, !State); //Sets Built-in LED to opposite of State
    delay(100); //Sets a delay of 100 milliseconds before the operation continues
  }
  LastInput = CurrentInput; //Sets the Current Input as the Last Input;
  if(State == LOW) //Nested If Statement for when the State is off
  {
    unsigned long CurrentMillis = millis(); //Sets the Current Millis equal to the current state in time through the Millis Function
    if(CurrentMillis - PreviousMillis >= Interval) //Calculates if enough time has passed for the light to turn off or on again
    {
      PreviousMillis = CurrentMillis; //Sets Current Millis as Previous Millis for next iteration
      LED = !LED; //Sets LED equal to the opposite
      digitalWrite(LED_BUILTIN, LED); //Sets the Built-in light equal to the LED
    }
  }
  else
  {
    LED = HIGH; //Sets the LED as on
    digitalWrite(LED_BUILTIN, LOW); //Sets the Built-in LED to off
  }
}