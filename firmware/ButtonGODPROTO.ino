#define LED 13 // replaces LED with 6, the name for the pin number 'D6'

int Buttonpin = 4; //Button is on digital pin 4
const int lightPin = A1; //Establishes light pin
const int SENSOR = A0; //Sesnor is on analog pin 0

void setup() { 
  pinMode(Buttonpin, INPUT_PULLUP); //Establishes Button as input with internal resistance
  Serial.begin(9600); //Establishes bitrate
  pinMode(LED_BUILTIN, OUTPUT); //Establishes built-in LED as an output
  pinMode(LED,OUTPUT); // pin is set to output to send signals bc the Arduino will be controlling the LED. 
  pinMode(SENSOR, INPUT); //Establishes sensor as input
}

void loop() {
  if(digitalRead(Buttonpin) == HIGH) //When the buttonpin 
  {
    digitalWrite(LED,HIGH); //sets pin 6 to HIGH (5V). Current flows through the LED to turn it on.
    delay(500); //Waits 1000ms(1s) so the LED stays on for a second
    digitalWrite(LED,LOW); //sets pin 6 to LOW (0V) which turns the LED off
    delay(500); //waits half a second then loop() starts over

    int lightlevel = analogRead(lightPin); //Establishes light level to read the analog of the light pin
    Serial.println(lightlevel);

    if(lightlevel > 350) //When light is above 350, this if statement occurs
    {
      digitalWrite(LED_BUILTIN, HIGH); //Turns on built-in LED
    }
    else
    {
      digitalWrite(LED_BUILTIN, LOW); //Turns off built-in LED
    }
    delay(200); //Delays it by 200 milliseconds 
    int value = analogRead(SENSOR); //Sets value equal to the analog of the sensor

    float angle = value * 300/1020; //Establishes the equation for the angle
    Serial.print("Sensor value: "); //Prints sensor value
    Serial.print(value);

    Serial.print("| Angle "); //Prints angle
    Serial.print(angle, 1);
    Serial.println("Degrees");

    delay(200); //Delays it by 200 milliseconds
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW); //Turns off built-in LED
  }
}

