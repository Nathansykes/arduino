#include <Zumo32U4.h>

char readInput[5];

int CurrentSpeed = 0;
int CurrentTurn = 90;

Zumo32U4Motors motors;

void setup()
{
  // put your setup code here, to run once:

  Serial.begin(9600);
}

void loop()
{
  int newSpeed = CurrentSpeed;
  int newTurn = CurrentTurn;
  GetInput();
  if(!(newTurn == CurrentTurn && newSpeed == CurrentSpeed))
  {
    SetMotors();
  }
  delay(2000);
}

void GetInput()
{
  delay(5);
  if (Serial.available() > 0)
  {
    int availableBytes = Serial.available();
    Serial.println(availableBytes);
    for (int i = 0; i < availableBytes; i++)
    {
      readInput[i] = Serial.read();
    }
    Serial.println(readInput);

    char command = readInput[0];
    int spaceI = indexOf(readInput, ' ');
    int val = atoi(readInput + spaceI + 1);

    switch(command)
    {
      case 't':
        Turn(val);
        break;
      case 's':
        Speed(val);
        break;
    }
  }
}

void Turn(int val)
{
  Serial.println("T-----------------");
  PrintValues(CurrentSpeed, CurrentTurn);
  Serial.println("Setting Turn");
  CurrentTurn = val;
  PrintValues(CurrentSpeed, CurrentTurn);
  Serial.println("/T----------------");
}

void Speed(int val)
{
  Serial.println("S----------------");
  PrintValues(CurrentSpeed, CurrentTurn);
  Serial.println("Setting Speed");
  CurrentSpeed = val;
  PrintValues(CurrentSpeed, CurrentTurn);
  Serial.println("/S----------------");
}

void SetMotors(){
  int midpoint = 90;
  int baseSpeed = CurrentSpeed;
  int baseTurn = CurrentTurn; //between 0 and 180

  Serial.println("A-----------------");
  Serial.println("Setting Motors - start");
  PrintValues(baseSpeed, baseTurn);
  Serial.println("A-----------------");
  if(baseTurn == midpoint)
  {
    motors.setSpeeds(baseSpeed, baseSpeed);
    return;
  }

  float amount = flMap(baseTurn, 0, 180, 0, 1);
  bool directionIsLeft = baseTurn < midpoint;

  Serial.println("B-----------------");
  Serial.println("Setting Motors - after calculate turn multipler");
  PrintValues(baseSpeed, baseTurn, amount, directionIsLeft);
  Serial.println("/B----------------");
  if(baseSpeed == 0)
  {
    float speed = flMap(amount, 0, 1, 0, 400);
    if(directionIsLeft)
    {
      motors.setSpeeds(-speed, speed);
    }
    else
    {
      motors.setSpeeds(speed, -speed);
    }
  }
  else
  {
    float left;
    float right;
    if(directionIsLeft)
    {
      left = baseSpeed * (amount / 2);
      right = baseSpeed * (1 - (amount / 2));
    }
    else
    {
      left = baseSpeed * (1 - (amount / 2));
      right = baseSpeed * (amount / 2);
    }
    Serial.println("C-----------------");
    Serial.println("Setting Motors - end");
    PrintValues(baseSpeed, baseTurn, amount, directionIsLeft);
    Serial.println("/C----------------");

    Serial.print("Left: ");
    Serial.println(left);
    Serial.print("Right: ");
    Serial.println(right);
    motors.setSpeeds(left, right);
  }
  delay(100);
}

int indexOf(char *arr, char find)
{
  for (int i = 0; i < sizeof(arr); i++)
  {
    if (arr[i] == find)
    {
      return i;
    }
  }
  return -1;
}


float flMap(float num, float oldMin, float oldMax, float newMin, float newMax)
{
  return ((num - oldMin) * (newMax - newMin)) / (oldMax - oldMin) + newMin;  
}

void PrintValues(int speed, int turn)
{
  Serial.print("Speed: ");
  Serial.println(speed);
  Serial.print("Turn: ");
  Serial.println(turn);
}

void PrintValues(int speed, int turn, float amount, bool directionIsLeft)
{
  Serial.print("Speed: ");
  Serial.println(speed);
  Serial.print("Turn: ");
  Serial.println(turn);
  Serial.print("Turn Multiplier: ");
  Serial.println(amount);
  Serial.print("Direction: ");
  Serial.println(directionIsLeft ? "Left" : "Right");
}