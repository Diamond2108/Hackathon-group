#define LED 13 // replaces LED with 6, the name for the pin number 'D6'

int Buttonpin = 4;
const int lightPin = A1;
const int SENSOR = A0;

void setup() { 
  pinMode(Buttonpin, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED,OUTPUT); // pin is set to output to send signals bc the Arduino will be controlling the LED. 
  pinMode(SENSOR, INPUT);
}

void loop() {
  if(digitalRead(Buttonpin) == HIGH)
  {
    digitalWrite(LED,HIGH); //sets pin 6 to HIGH (5V). Current flows through the LED to turn it on.
    delay(500); //Waits 1000ms(1s) so the LED stays on for a second
    digitalWrite(LED,LOW); //sets pin 6 to LOW (0V) which turns the LED off
    delay(500); //waits another second then loop() starts over

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
    int value = analogRead(SENSOR);

    float angle = value * 300/1020;
    Serial.print("Sensor value: ");
    Serial.print(value);

    Serial.print("| Angle ");
    Serial.print(angle, 1);
    Serial.println("Degrees");

    delay(200);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

