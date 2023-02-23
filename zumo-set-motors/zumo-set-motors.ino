#include <Zumo32U4.h>

Zumo32U4Motors motors;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  String input = "";
  delay(9);
  if (Serial.available() > 0)
  {
    //expecting a string like "-120,300"
    int availableBytes = Serial.available();
    input = Serial.readStringUntil('\n');

    Serial.print("input: ");
    Serial.println(input);

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