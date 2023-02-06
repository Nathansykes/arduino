/* This example uses the front proximity sensor on the Zumo 32U4
Front Sensor Array to locate an opponent robot or any other
reflective object. Using the motors to turn, it scans its
surroundings. If it senses an object, it turns on its yellow LED
and attempts to face towards that object. */

#include <Wire.h>
#include <Zumo32U4.h>

// Change next line to this if you are using the older Zumo 32U4
// with a black and green LCD display:
// Zumo32U4LCD display;
Zumo32U4OLED display;

Zumo32U4Motors motors;
Zumo32U4ProximitySensors proxSensors;


// A sensors reading must be greater than or equal to this
// threshold in order for the program to consider that sensor as
// seeing an object.
const uint8_t sensorThreshold = 1;

// The maximum speed to drive the motors while turning.  400 is
// full speed.
const uint16_t turnSpeedMax = 300;

// The minimum speed to drive the motors while turning.  400 is
// full speed.
const uint16_t turnSpeedMin = 150;

// The amount to decrease the motor speed by during each cycle
// when an object is seen.
const uint16_t deceleration = 10;

// The amount to increase the speed by during each cycle when an
// object is not seen.
const uint16_t acceleration = 10;

//constant speed the robot moves at
const uint16_t speed = 80;

#define LEFT 0
#define RIGHT 1

// Stores the last indication from the sensors about what
// direction to turn to face the object.  When no object is seen,
// this variable helps us make a good guess about which direction
// to turn.
bool senseDir = RIGHT;

// True if the robot is turning left (counter-clockwise).
bool turningLeft = false;

// True if the robot is turning right (clockwise).
bool turningRight = false;

// If the robot is turning, this is the speed it will use.
uint16_t turnSpeed = turnSpeedMax;

// The time, in milliseconds, when an object was last seen.
uint16_t lastTimeObjectSeen = 0;

void setup()
{
  proxSensors.initFrontSensor();

}

void turnRight()
{
  motors.setSpeeds(turnSpeed, -turnSpeed);
  turningLeft = false;
  turningRight = true;
}

void turnLeft()
{
  motors.setSpeeds(-turnSpeed, turnSpeed);
  turningLeft = true;
  turningRight = false;
}

void stop()
{
  motors.setSpeeds(80, 80);
  turningLeft = false;
  turningRight = false;
}

void move()
{
  motors.setSpeeds(50, 50);
}

void loop()
{
  // Read the front proximity sensor and gets its left value (the
  // amount of reflectance detected while using the left LEDs)
  // and right value.
  proxSensors.read();
  uint8_t leftValue = proxSensors.countsFrontWithLeftLeds();
  uint8_t rightValue = proxSensors.countsFrontWithRightLeds();

  // Determine if an object is visible or not.
  bool objectSeen = leftValue >= sensorThreshold || rightValue >= sensorThreshold;

  if (objectSeen)
  {
    // An object is visible, so we will start decelerating in
    // order to help the robot find the object without
    // overshooting or oscillating.
    turnSpeed -= deceleration;
  }
  else
  {
    // An object is not visible, so we will accelerate in order
    // to help find the object sooner.
    turnSpeed += acceleration;
  }

  // Constrain the turn speed so it is between turnSpeedMin and
  // turnSpeedMax.
  turnSpeed = constrain(turnSpeed, turnSpeedMin, turnSpeedMax);

  if (objectSeen)
  {
    // An object seen.
    ledYellow(1);

    lastTimeObjectSeen = millis();

    if (leftValue < rightValue)
    {
      // The right value is greater, so the object is probably
      // closer to the robot's right LEDs, which means the robot
      // is not facing it directly.  Turn to the right to try to
      // make it more even.
      turnRight();
      senseDir = RIGHT;
    }
    else if (leftValue > rightValue)
    {
      // The left value is greater, so turn to the left.
      turnLeft();
      senseDir = LEFT;
    }
    else
    {
      move();
    }
  }
  else
  {
    // No object is seen, so just keep turning in the direction
    // that we last sensed the object.
    ledYellow(0);

    if (senseDir == RIGHT)
    {
      turnRight();
    }
    else
    {
      turnLeft();
    }
  }

  display.gotoXY(0, 0);
  display.print(leftValue);
  display.print(' ');
  display.print(rightValue);
  display.gotoXY(0, 1);
  display.print(turningRight ? 'R' : (turningLeft ? 'L' : ' '));
  display.print(' ');
  display.print(turnSpeed);
  display.print(' ');
  display.print(' ');
}
