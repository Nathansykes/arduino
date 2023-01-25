#include <Servo.h>
//test
const int servoPin = 5;
char readInput[20];
int angle;
bool running = false;

Servo myservo;

void setup() {
  Serial.begin(9600);
  Serial.println("wating");
}

void loop() {
    delay(2000);
    if (Serial.available() > 0)
    {
      int availableBytes = Serial.available();
      Serial.println(availableBytes);
      for(int i = 0; i < availableBytes; i++)
      {
          readInput[i] = Serial.read();
      }
      Serial.println(readInput);
      if (readInput[0] == 'g')
      {
        Serial.println("=STARTED=");
        int spaceI = indexOf(readInput, ' ');
        angle = atoi(readInput + spaceI + 1);
        Serial.println(angle);
        running = true;
      	myservo.attach(servoPin);
      }
      else if (readInput == "s")
      {
        running = false;
        Serial.println("=STOPPED=");
        myservo.detach();
      }
    }
    if (running)
    {
      myservo.write(angle);
      delay(500);
    }
}

//return first index of specified character
//returns -1 if not foun
int indexOf(char* arr, char find)
{
  for(int i = 0; i < sizeof(arr); i++)
  {
    if(arr[i] == find)
    {
      return i;
    }
  }
  return -1;
}
