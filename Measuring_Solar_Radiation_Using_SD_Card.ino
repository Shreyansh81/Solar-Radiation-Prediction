/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/ReadAnalogVoltage
*/
#define ANALOG_PIN A0 // Analog pin
#define RESISTANCE 10 // Resistance in thousands of ohms
#define RADIUS 40 // Length of solar cell in mm
#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
}

// the loop routine runs over and over again forever:
void loop() {
   // make a string for assembling the data to log:
  String dataString = "";

  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  float Area= 16*3.14;
  float volatile Power= (sensorValue*sensorValue)/10;
  float volatile radiation = (Power/Area);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  Serial.print(voltage);
  Serial.println(" V ");
  Serial.print(abs(radiation));
  Serial.println(" W/m2 ");
  delay(1000);
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}
