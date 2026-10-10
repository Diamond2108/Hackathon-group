int Buttonpin = 4; //D4 is the pin
int State = LOW; //Initalizes State as being off
int LastInput = HIGH; //Initializes the Last Input as being on

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
    digitalWrite(LED_BUILTIN, !State); //Sets Built-in LED to opposite of State
  }
  LastInput = CurrentInput; //Sets the Current Input as the Last Input;
}