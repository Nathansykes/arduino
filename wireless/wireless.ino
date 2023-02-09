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
  Serial1.begin(9600);
}



void SpinMe(int speed)
{
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(-speed);
}

void loop() 
{
  Serial1.write('C');
  if(Serial1.available() > 0)
  {
    char c = Serial1.read();
    Serial.write("Serial1: \n");
    Serial.write(c);
    Serial.write("\n");
    if(c == 's')
    {
      SpinMe(100);
      delay(500);   
    }
  }
  SpinMe(0);
  delay(500);
}