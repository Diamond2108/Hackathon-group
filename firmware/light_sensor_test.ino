//test sketch 

int light_sensor = A1; // variable holds pin number of the analog port on the shield that the sensor is plugged in.

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //starts serial communication at 9600 baud(bits per second) to send text to laptop thru USB
}

void loop() {
  // put your main code here, to run repeatedly:
  int raw_light = analogRead(light_sensor); //reads voltage on pin A1 and converts it to a number. (0=0V, 1023=5V)
  int light = map(raw_light, 0, 1023, 0, 100); //map rescales a number from one range to another. Converts it to 0-100

  Serial.print(light);
  Serial.print(",");
  Serial.println(light > 20 ? 1 : 0);

  delay(1000);//Pauses for 1000 milliseconds(1 sec) before next reading
}


