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

    
  }
}
