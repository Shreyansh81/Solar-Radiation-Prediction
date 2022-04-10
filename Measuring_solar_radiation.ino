  void setup() {
  Serial.begin(9600);
}
  // initialize serial communication at 9600 bits per second:

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float  irradaiation = sensorValue ;
  // print out the value you read:
  Serial.print(irradiation);
  Serial.println("  W/m2");
  delay(1000);
}
