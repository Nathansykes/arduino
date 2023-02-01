#include <Zumo32U4.h>

//Serial1 communicates over XBee
//Serial communicates over USB cable

void setup() {
  // put your setup code here, to run once:
//  Serial1.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  int incomingByte = 0; // for incoming serial data
  
  // send data only when you receive data:
//  if (Serial1.available() > 0) {
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
//    Serial1.print("I received: ");
//    Serial1.println(incomingByte, DEC);
    
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
}
