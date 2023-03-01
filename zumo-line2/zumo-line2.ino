#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;

int blackLineMaxValue = 1100;
int blackLineMinValue = 200;
int blackLineTargetValue = 700;

unsigned int lineSensorValues[5];
#define leftSensor lineSensorValues[0]
#define middleSensor lineSensorValues[2]
#define rightSensor lineSensorValues[4]

void setup()
{
    Serial.begin(9600);
    lineSensors.initFiveSensors();
}

void loop()
{
    lineSensors.read(lineSensorValues);
    followLines();
}

void printSensorValues()
{
    Serial.print("Left: ");
    Serial.println(leftSensor);
    Serial.print("Middle: ");
    Serial.println(middleSensor);
    Serial.print("Right: ");
    Serial.println(rightSensor);
    Serial.println("======================");
}

void followLines()
{
    delay(25);
    if (rightSensor > blackLineTargetValue || middleSensor > blackLineTargetValue)
    {
        motors.setSpeeds(-100, -100);
        delay(200);
        motors.setSpeeds(200, -200);
        delay(400);
    }
    else if (leftSensor < blackLineMaxValue && leftSensor > blackLineMinValue)
    {
        motors.setSpeeds(100, 100);
    }
    else if (leftSensor > blackLineMaxValue)
    {
        motors.setSpeeds(130, -130);
    }
    else if (leftSensor < blackLineMinValue)
    {
        motors.setSpeeds(100, 100);
        delay(50);
        motors.setSpeeds(-130, 130);
        delay(50);
    }
}
