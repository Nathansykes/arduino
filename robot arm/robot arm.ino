//#include <Arduino.h>
#include <Servo.h>

Servo Left, Middle, Right, Claw;
const int LeftPin = 6;
const int MiddlePin = 11;
const int RightPin = 9;
const int ClawPin = 10;

int LeftValue;
int MiddleValue;
int RightValue;


void setup() { /* add setup code here */
  Serial.begin(9600);
  // Left.attach(LeftPin);
  // Middle.attach(MiddlePin);
  // Right.attach(RightPin);
  // Claw.attach(ClawPin);
  pinMode(2, INPUT);
  Serial.println("running...");
}  // end setup...

void loop() {

  void moveServo(Servo, int, int);  // function prototype...

  int left = analogRead(A0);
  LeftValue = map(left, 0, 1023, 0, 130);
  Serial.print("left = ");
  Serial.println(LeftValue);

  int middle = analogRead(A1);
  MiddleValue = map(middle, 0, 1023, 0, 130);
  Serial.print("middle = ");
  Serial.println(MiddleValue);

  int right = analogRead(A2);
  RightValue = map(right, 0, 1023, 0, 130);
  Serial.print("right = ");
  Serial.println(RightValue);
  
  int button = digitalRead(2);

  if(button == LOW)
  {
    moveServo(Claw, ClawPin, 0);
  }
  else
  {
    moveServo(Claw, ClawPin, 120);
  }

  moveServo(Left, LeftPin, LeftValue);
  moveServo(Middle, MiddlePin, MiddleValue);
  moveServo(Right, RightPin, RightValue);

  
}  // end loop

void moveServo(Servo m, int pin, int value) {
  
  m.attach(pin);
  delay(15);
  m.write(value);
  delay(15);
  m.detach();

  delay(100);
}  //end moveServo

