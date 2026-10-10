#define LED 13 // replaces LED with 6, the name for the pin number 'D6'

void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT); // pin is set to output to send signals bc the Arduino will be controlling the LED. 
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED,HIGH); //sets pin 6 to HIGH (5V). Current flows through the LED to turn it on.
  delay(500); //Waits 1000ms(1s) so the LED stays on for a second
  digitalWrite(LED,LOW); //sets pin 6 to LOW (0V) which turns the LED off
  delay(500); //waits another second then loop() starts over
}
