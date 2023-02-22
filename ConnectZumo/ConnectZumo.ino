#include <Zumo32U4.h>

void setup() {
  // put your setup code here, to run once: 
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  //Serial.println("Start of loop (Serial)");
  //Serial1.println("Start of loop (Serial1)");

  delay(1000);

  if(Serial1.available() > 0)
  {
    delay(200);
    char c = Serial1.read();
    Serial.print("Read from Serial1: ");
    Serial.write(c);
  }

  if(Serial.available() > 0)
  {
    delay(200);
    char c = Serial.read();
    Serial.print("Read from Serial: ");
    Serial.println(c);
  }
}
