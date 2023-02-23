#include <Zumo32U4.h>

Zumo32U4Motors motors;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  char input[9];
  delay(9);
  if (Serial.available() > 0)
  {
    //expecting a string like "-120,300"
    int availableBytes = Serial.available();
    Serial.println(availableBytes);
    for (int i = 0; i < availableBytes; i++)
    {
      input[i] = Serial.read();
    }

    Serial.print("input: ");
    Serial.println(input);
    
    String str = String(input);

    // Find index of comma
    int commaIndex = str.indexOf(',');

    // Extract first number
    String num1Str = str.substring(0, commaIndex);
    int num1 = num1Str.toInt();

    // Extract second number
    String num2Str = str.substring(commaIndex + 1);
    int num2 = num2Str.toInt();


    Serial.print("num1: ");
    Serial.println(num1);
    Serial.print("num2: ");
    Serial.println(num2); 

    motors.setSpeeds(num1, num2);  

  }

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