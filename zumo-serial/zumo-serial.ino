#include <Zumo32U4.h>

Zumo32U4Motors motors;

int speed = 80;
float boostMultiplier = 1.3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0) {
    char c = Serial.read();

    switch(c)
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
}
