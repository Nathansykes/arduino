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

  Serial.println("running...");
}  // end setup...

void loop() {

  void moveServo(Servo, int, int);  // function prototype...
  delay(1000);
  Serial.println("=====begin loop======");

  int left = analogRead(A0);
  LeftValue = map(left, 0, 1023, 0, 180);
  Serial.print("left = ");
  Serial.println(LeftValue);
  int middle = analogRead(A1);
  MiddleValue = map(middle, 0, 1023, 0, 180);
  Serial.print("middle = ");
  Serial.println(MiddleValue);
  int right = analogRead(A2);
  RightValue = map(right, 0, 1023, 0, 180);
  Serial.print("right = ");
  Serial.println(RightValue);
  


  moveServo(Left, LeftPin, LeftValue);
  moveServo(Middle, MiddlePin, MiddleValue);
  moveServo(Right, RightPin, RightValue);

  Serial.println("=====end loop======");
  delay(1000);
  
}  // end loop

void moveServo(Servo m, int pin, int value) {
  Serial.println("----moving----");
  Serial.print("pin: ");
  Serial.println(pin);
  Serial.print("value: ");
  Serial.println(value);
  
  m.attach(pin);
  m.write(value);
  m.detach();

  Serial.println("/----done----");
  delay(500);
}  //end moveServo

