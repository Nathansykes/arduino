#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;

int blackThreshhold =700;

int count = 0;
int forwardCount = 0;

unsigned int lineSensorValues[5];
#define leftSensor lineSensorValues[0]
#define middleSensor lineSensorValues[2]
#define rightSensor lineSensorValues[4]

#define delayXLargeTurn 1000
#define delayLargeTurn 600
#define delaySmallTurn 300

void setup()
{
    Serial.begin(9600);
    lineSensors.initFiveSensors();
}

void loop()
{
    count++;
    lineSensors.read(lineSensorValues);
    followLines();

    // Serial.print("Left: ");
    // Serial.println(leftSensor);
    // Serial.print("Middle: ");
    // Serial.println(middleSensor);
    // Serial.print("Right: ");
    // Serial.println(rightSensor);
    // Serial.println("======================");
}
void ReverseAndTurnLeft(int reverseAmount, int turnAmount, int speed = 100)
{
    motors.setSpeeds(-speed,-speed);
    delay(reverseAmount);
    motors.setSpeeds(-speed,speed);
    delay(turnAmount);
}

void ReverseAndTurnRight(int reverseAmount, int turnAmount, int speed = 100)
{
    motors.setSpeeds(-speed,-speed);
    delay(reverseAmount);
    motors.setSpeeds(speed,-speed);
    delay(turnAmount);
}

void followLines()
{
    // If black line is in front stop
    if (leftSensor > blackThreshhold && leftSensor > (blackThreshhold - 100) && rightSensor > blackThreshhold)
    {
        ReverseAndTurnRight(100, delayXLargeTurn);
    }
    // If robot is in a corner turn clockwise
    if (leftSensor > blackThreshhold && leftSensor < blackThreshhold && rightSensor > blackThreshhold)
    {
        ReverseAndTurnRight(50, delayXLargeTurn);
    }
    // Goes forward if no black lines are detected on either side
    if (leftSensor < blackThreshhold && rightSensor < blackThreshhold)
    {
        motors.setSpeeds(100, 100);
        forwardCount++;
        if(forwardCount > 4000)
        {
            ReverseAndTurnLeft(0, delayLargeTurn);
            forwardCount = 0;
        }
    }
    // If left black line is no longer there and the right black line is, turn left
    if (leftSensor < blackThreshhold && rightSensor > blackThreshhold)
    {
        ReverseAndTurnLeft(50, delaySmallTurn);
    }
    // if right black line is no longer there but left is, turn right
    if (leftSensor > blackThreshhold && rightSensor < blackThreshhold)
    {
        ReverseAndTurnRight(50, delaySmallTurn);
    }
}

