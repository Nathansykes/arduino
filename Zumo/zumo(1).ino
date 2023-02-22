#include <Zumo32U4.h>


Zumo32U4Motors motors;

int TurnValue;
int TurnIncrement;
int TurnMax;
int TurnMin;
int ForwardValue;
int ForwardIncrement;
int ForwardMax;
int ForwardMin;

void setup() 
{
    Serial.begin(9600);
    TurnValue = 0;
    TurnIncrement = 100;
    TurnMax = 600;
    TurnMin = -100;
    ForwardValue = 0;
    ForwardIncrement = 50;
    ForwardMax = 400;
    ForwardMin = -200;
}


void AdjustTurn()
{
    WriteValues();
    if(TurnValue > 0)
    {
        motors.setRightSpeed(ForwardValue + TurnValue);
        motors.setLeftSpeed(ForwardValue - (TurnValue / 2));
    }
    else if(TurnValue < 0)
    {
        motors.setLeftSpeed(ForwardValue + -TurnValue);
        motors.setRightSpeed(ForwardValue - (-TurnValue / 2));
    }
    else
    {
        motors.setRightSpeed(ForwardValue + TurnValue);
        motors.setLeftSpeed(ForwardValue - TurnValue);
    }
}

void AdjustForward()
{
    WriteValues();
    motors.setLeftSpeed(ForwardValue);
    motors.setRightSpeed(ForwardValue);
}

void WriteValues()
{
    Serial.write("\n");
    Serial.write("Forward: ");
    Serial.write(ForwardValue);
    Serial.write("\n");
    Serial.write("Turn: ");
    Serial.write(TurnValue);
}

void ControlMode()
{
  if(Serial.available() > 0)
    {
        char c = Serial.read();
        Serial.write("\n");
        Serial.write("Received: ");
        Serial.write(c);
        switch(c)
        {
            case 'w':
                ForwardValue += ForwardIncrement;
                if(ForwardValue > ForwardMax)
                {
                    ForwardValue = ForwardMax;
                }
                AdjustForward();
                break;
            case 's':
                ForwardValue -= ForwardIncrement;
                if(ForwardValue < ForwardMin)
                {
                    ForwardValue = ForwardMin;
                }
                AdjustForward();
                break;
            case 'a':
                TurnValue += TurnIncrement;
                if(TurnValue > TurnMax)
                {
                    TurnValue = TurnMax;
                }
                AdjustTurn();
                break;
            case 'd':
            TurnValue -= TurnIncrement;
                if(TurnValue < TurnMin)
                {
                    TurnValue = TurnMin;
                }
                AdjustTurn();
                break;
            case 'x':
                ForwardValue = 0;
                TurnValue = 0;
                motors.setLeftSpeed(0);
                motors.setRightSpeed(0);
                break;
        }
    }
}

void SpinMe(int speed)
{
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(-speed);
}

void loop() 
{
    SpinMe(75);
    
}