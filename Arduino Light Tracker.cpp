#include <Servo.h>

Servo servoTB;  // Servo for Top-Bottom (Vertical)
Servo servoLR;  // Servo for Left-Right (Horizontal)

// Analog pins for the photoresistors
int sensorTopR = A2;
int sensorBottomR = A1;
int sensorTopL = A3;
int sensorBottomL = A0;
int const margin = 10;
// Analog pins for Solar panal voltage
// int SolarP = A4;

// Servo degree variables
int posTB = 90;  // Initial position TB Servo in the center
int posLR = 90;  // Initial position LR servo in the center

const int safeRest = 90; // Saftey for the design

void setup() {
  // Connect the servos to the listed pins
  servoTB.attach(3);
  servoLR.attach(5);
  
  // Start servos at the center position (90).
  servoTB.write(posTB);
  servoLR.write(posLR);
  
  // Lets us read the voltage from the solar panel, remove slashes for your own use
  //pinMode(SolarP, input);

  Serial.begin(9600);  // Allows us to read analog output in the serial monitor. Helpful for debugging.
}

void loop() {
  // Read light from each sensor
  int TopR = analogRead(sensorTopR);
  int BottomR = analogRead(sensorBottomR);
  int TopL = analogRead(sensorTopL);
  int BottomL = analogRead(sensorBottomL);
  
  int Top = TopR + TopL;
  int Bottom = BottomR + BottomL;

int Left = TopL + BottomL;
int Right = TopR + BottomR;

  int TBDifference = Top - Bottom; // Measures the difference in light intensity on an axis
  int LRDifference = Left - Right;

  // Design protection
  if (posTB > 180 || posTB < 20){
    servoTB.write(safeRest);
  }

// Adjust servo incrementally
  if (TBDifference > margin) {
    posTB -= 1;
  } else if (TBDifference < margin) {
    posTB += 1;
  } else {}
   servoTB.write(posTB);

if (LRDifference > margin) {
    posLR -= 1;
  } else if (LRDifference < margin) {
    posLR += 1;
  } else {}
  
   servoLR.write(posLR);

// This is a block of code you should use to make sure your photoresistors are connected correctly
Serial.println(TBDifference);
Serial.println(TopR);
Serial.println(BottomR);


// This block will plot the voltage from the solar panel. Add "//" to remove overhead if not tracking solar panel data.
//SolarVolt = analogRead(SolarP);
//serial.print(SolarVolt);

  delay(50);  // Delay, adjust as needed
}
