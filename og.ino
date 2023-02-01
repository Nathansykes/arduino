//#include <Arduino.h>
#include <Servo.h>

Servo Left, Middle, Right, Claw;
const int LeftPin = 6;
const int MiddlePin = 11;
const int RightPin = 9;
const int ClawPin = 10;


void setup() { /* add setup code here */
  Serial.begin(9600);
  // Left.attach(LeftPin);
  // Middle.attach(MiddlePin);
  // Right.attach(RightPin);
  // Claw.attach(ClawPin);

  Serial.println("waiting...");
}  // end setup...

void loop() {
  void moveServo(Servo, int);  // function prototype...
  delay(300);
  if (Serial.available() > 0) {
    char motor = (char)Serial.read();
    int pin;
    Servo movingServo;
    String name = "";
    switch (motor) {
      case 'm':
      case 'M':
        movingServo = Middle;
        pin = MiddlePin;
        name = "middle";
        break;
      case 'l':
      case 'L':
        movingServo = Left;
        pin = LeftPin;
        name = "left";
        break;
      case 'r':
      case 'R':
        movingServo = Right;
        pin = RightPin;
        name = "right";
        break;
      case 'c':
      case 'C':
        movingServo = Claw;
        pin = ClawPin;
        name = "claw";
        break;
    }  // end switch
    Serial.println("Moving " + name);
    moveServo(movingServo, pin);
  }  // end if something read on Serial...
  
}  // end loop

void moveServo(Servo m, int pin) {
  // l and r servo's don't have this range of movement....
  m.attach(pin);
  for (int pos = 90; pos >= 0; pos -= 1) {
    m.write(pos);
    delay(15);
  }  // end sweep down to 0
  for (int pos = 0; pos <= 180; pos += 1) {
    m.write(pos);
    delay(15);

  }  // end sweep over to 180
  for (int pos = 180; pos >= 90; pos -= 1) {
    m.write(pos);
    delay(15);
  }  // end sweep back to 90
  m.detach();
  delay(500);
  Serial.println("\t next command >>> ");
}  //end moveServo