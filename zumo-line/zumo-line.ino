#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;

int blackThreshhold = 250;

int count = 0;
int forwardCount = 0;

unsigned int lineSensorValues[5];
#define leftSensor lineSensorValues[0]
#define middleSensor lineSensorValues[2]
#define rightSensor lineSensorValues[4]

#define delayXLargeTurn 900
#define delayLargeTurn 600
#define delaySmallTurn 350

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
    // if(count > 1000)
    // {
    //     Serial.println("Increasing threshold");
    //     blackThreshhold+=100;
    //     if(blackThreshhold > 900)
    //     {
    //         blackThreshhold = 100;
    //     }
    //     Serial.print("Threshold: ");
    //     Serial.println(blackThreshhold);
    //     count = 0;
    // }

    // Serial.print("Left: ");
    // Serial.println(leftSensor);
    // Serial.print("Middle: ");
    // Serial.println(middleSensor);
    // Serial.print("Right: ");
    // Serial.println(rightSensor);
    // Serial.println("======================");
}
void reverseAndTurnLeft(int reverseAmount, int turnAmount, int speed = 100)
{
    motors.setSpeeds(-speed,-speed);
    delay(reverseAmount);
    motors.setSpeeds(-speed,speed);
    delay(turnAmount);
}

void reverseAndTurnRight(int reverseAmount, int turnAmount, int speed = 100)
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
        reverseAndTurnRight(100, delaySmallTurn);
    }
    // If robot is in a corner turn clockwise
    if (leftSensor > blackThreshhold && leftSensor < blackThreshhold && rightSensor > blackThreshhold)
    {
        reverseAndTurnRight(50, delayXLargeTurn);
    }
    // Goes forward if no black lines are detected on either side
    if (leftSensor < blackThreshhold && rightSensor < blackThreshhold)
    {
        motors.setSpeeds(100, 100);
        forwardCount++;
        if(forwardCount > 1000)
        {
            reverseAndTurnLeft(0, delayLargeTurn);
            forwardCount = 0;
        }
    }
    // If left black line is no longer there and the right black line is, turn left
    if (leftSensor < blackThreshhold && rightSensor > blackThreshhold)
    {
        reverseAndTurnLeft(50, delaySmallTurn);
    }
    // if right black line is no longer there but left is, turn right
    if (leftSensor > blackThreshhold && rightSensor < blackThreshhold)
    {
        reverseAndTurnRight(50, delaySmallTurn);
    }
}

