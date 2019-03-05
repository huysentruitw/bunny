#include <SoftwareSerial.h>
#include <Servo.h>

Servo servo;
SoftwareSerial serial(4, 5);

#define BASE_ANGLE 77
double actualValue = 0;
String inputString = "";

void setup() {
  serial.begin(9600);
  servo.attach(3);
}

void loop() {
  if (serial.available()) {
    servo.detach();
    char inChar = (char)serial.read();
    servo.attach(3);
    if (inChar == '\r') {
      double newValue = inputString.toInt();
      if (newValue > 1200) newValue = 1200;
      actualValue = actualValue * 0.60f + newValue * 0.40f;
      servo.write(BASE_ANGLE - actualValue / 18.0f);
      inputString = "";
    }
    else inputString += inChar;
  }
}
