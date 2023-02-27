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

int blackLineValue = 250;

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
    if (oldMode == SelectedMode)//if the mode has changed we skip and get user input again
    {
        RunMode(input);//some modes don't require input so we handle empty input in the method
    }
}

String GetInput()
{
    String input = "";
    delay(10);//delay to allow all the data to get to the zumo
    if (Serial.available() > 0)
    {
        input = Serial.readStringUntil('\n');//read the next line

        Serial.print("Received Input: ");
        Serial.println(input);
    }
    return input;
}

void ModeSelect(String input)
{
    if (input.length() == 0)//no input so we don't change the mode
        return;
    char c = input.charAt(0);
    if (c == Mode::ModeSelect)// ModeSelect acts like a main menu **
    {
        SelectedMode = Mode::ModeSelect;
        motors.setSpeeds(0, 0);//stop the robot when this mode is active
        Serial.println("Selected Mode: ModeSelect");
    }

    if (SelectedMode == Mode::ModeSelect)//** mode can't be changed unless mode select is selected
    {
        switch (c)// change the mode based on the char entered
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
                SetMotorsFromSerial(input);//only needs to be hit when new input received
            }
            break;
        case Mode::WASD:
            if (input.length() > 0)
            {
                SetWASD(input);//only needs to be hit when new input received
            }
            break;
        case Mode::Automated:
            // AutomatedMode(); // this needs to be hit continuously in a loop
            motors.setSpeeds(100, -100);
            break;
        }
    }
}


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
    char c = input.charAt(0);//get the first character for the direction
    int speed = input.substring(1).toInt();//get the remainder of the string and convert to int
    const float boostMultiplier = 1.3;

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
    // if black line detected in front then turn
    if (leftSensor > blackLineValue && leftSensor > (blackLineValue - 100) && rightSensor > blackLineValue)
    {
        ReverseAndTurnRight(100, delaySmallTurn);
    }
    // if lines detected on both sides, were in a corner so do a large turn
    if (leftSensor > blackLineValue && leftSensor < blackLineValue && rightSensor > blackLineValue)
    {
        ReverseAndTurnRight(50, delayXLargeTurn);
    }
    // if no black line is detected, go forward
    if (leftSensor < blackLineValue && rightSensor < blackLineValue)
    {
        motors.setSpeeds(100, 100);
        forwardCount++;//keep track of how far we have gone forward
        if (forwardCount > 1000)// if we have gone forward for a while, turn to check if there is a room
        {
            ReverseAndTurnLeft(0, delayLargeTurn);
            forwardCount = 0;
        }
    }
    // if only black line on the right is detected, turn left
    if (leftSensor < blackLineValue && rightSensor > blackLineValue)
    {
        ReverseAndTurnLeft(50, delaySmallTurn);
    }
    // if only black line on the left is detected, turn right
    if (leftSensor > blackLineValue && rightSensor < blackLineValue)
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