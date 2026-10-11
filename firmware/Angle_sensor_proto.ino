const int SENSOR = A0;

void setup()
{
  Serial.begin(9600);
  pinMode(SENSOR, INPUT);
}

void loop()
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