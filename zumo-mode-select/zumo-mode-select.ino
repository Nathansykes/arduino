#include <Zumo32U4.h>
#include <string.h>

Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;

void ReverseAndTurnLeft(int reverseAmount, int turnAmount, int speed = 100);
void ReverseAndTurnRight(int reverseAmount, int turnAmount, int speed = 100);

class Mode
{
public:
    static const char ModeSelect = 'm';
    static const char SetMotors = 'p';
    static const char WASD = 'o';
    static const char Automated = 'i';
};

char SelectedMode = Mode::ModeSelect;

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
    String input = GetInput();
    char oldMode = SelectedMode;
    ModeSelect(input);
    if (oldMode == SelectedMode)//if the mode has changed we get user input again
    {
        RunMode(input);
    }
}

String GetInput()
{
    String input = "";
    delay(10);
    if (Serial.available() > 0)
    {
        input = Serial.readStringUntil('\n');

        Serial.print("Received Input: ");
        Serial.println(input);
    }
    return input;
}

void ModeSelect(String input)
{
    if (input.length() == 0)
        return;
    char c = input.charAt(0);
    if (c == Mode::ModeSelect)
    {
        SelectedMode = Mode::ModeSelect;
        motors.setSpeeds(0, 0);
        Serial.println("Selected Mode: ModeSelect");
    }

    if (SelectedMode == Mode::ModeSelect)
    {
        switch (c)
        {
        case Mode::SetMotors:
            SelectedMode = Mode::SetMotors;
            Serial.println("Selected Mode: SetMotors");
            break;
        case Mode::WASD:
            SelectedMode = Mode::WASD;
            Serial.println("Selected Mode: WASD");
            break;
        case Mode::Automated:
            SelectedMode = Mode::Automated;
            Serial.println("Selected Mode: Automated");
            break;
        }
    }
}

void RunMode(String input)
{
    if (SelectedMode != Mode::ModeSelect)
    {
        switch (SelectedMode)
        {
        case Mode::SetMotors:
            if (input.length() > 0)
            {
                SetMotorsFromSerial(input);
            }
            break;
        case Mode::WASD:
            if (input.length() > 0)
            {
                SetWASD(input);
            }
            break;
        case Mode::Automated:
            // AutomatedMode();
            motors.setSpeeds(100, -100);
            break;
        }
    }
}

// expecting a string like "-120,300"
void SetMotorsFromSerial(String input)
{
    // Find index of comma
    int commaIndex = input.indexOf(',');
    Serial.print("commaIndex: ");
    Serial.println(commaIndex);

    // Extract first number
    String num1Str = input.substring(0, commaIndex);

    Serial.print("num1Str: ");
    Serial.println(num1Str);

    int num1 = num1Str.toInt();

    // Extract second number
    String num2Str = input.substring(commaIndex + 1);

    Serial.print("num2Str: ");
    Serial.println(num2Str);

    int num2 = num2Str.toInt();

    Serial.print("num1: ");
    Serial.println(num1);
    Serial.print("num2: ");
    Serial.println(num2);

    motors.setSpeeds(num1, num2);
}

// input should be a string like "w90" or "d-120"
void SetWASD(String input)
{
    char c = input.charAt(0);
    int speed = input.substring(1).toInt();
    float boostMultiplier = 1.3;

    Serial.print("c: ");
    Serial.println(c);
    Serial.print("speed: ");
    Serial.println(speed);

    switch (c)
    {
    case 'w':
        motors.setSpeeds(speed, speed);
        break;
    case 's':
        motors.setSpeeds(-speed, -speed);
        break;
    case 'a':
        motors.setSpeeds(-speed, speed);
        break;
    case 'd':
        motors.setSpeeds(speed, -speed);
        break;
    case 'W':
        motors.setSpeeds(speed * boostMultiplier, speed * boostMultiplier);
        break;
    case 'S':
        motors.setSpeeds(-speed * boostMultiplier, -speed * boostMultiplier);
        break;
    case 'A':
        motors.setSpeeds(-speed * boostMultiplier, speed * boostMultiplier);
        break;
    case 'D':
        motors.setSpeeds(speed * boostMultiplier, -speed * boostMultiplier);
        break;
    case 'x':
    case 'X':
        motors.setSpeeds(0, 0);
        break;
    }
}

void AutomatedMode()
{
    lineSensors.read(lineSensorValues);
    FollowLines();
}

void FollowLines()
{
    // If black line is in front stop
    if (leftSensor > blackThreshhold && leftSensor > (blackThreshhold - 100) && rightSensor > blackThreshhold)
    {
        ReverseAndTurnRight(100, delaySmallTurn);
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
        if (forwardCount > 1000)
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

void ReverseAndTurnLeft(int reverseAmount, int turnAmount, int speed = 100)
{
    motors.setSpeeds(-speed, -speed);
    delay(reverseAmount);
    motors.setSpeeds(-speed, speed);
    delay(turnAmount);
}

void ReverseAndTurnRight(int reverseAmount, int turnAmount, int speed = 100)
{
    motors.setSpeeds(-speed, -speed);
    delay(reverseAmount);
    motors.setSpeeds(speed, -speed);
    delay(turnAmount);
}