#include <Zumo32U4.h>
#include <Wire.h>
#include <Zumo32U4Buzzer.h>

Zumo32U4ProximitySensors proxSensors;
Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;
Zumo32U4Buzzer buzzer;
Zumo32U4LCD display;
unsigned int sensors[5];
unsigned int pSensors[2];
const int blackThreshhold = 800;
const int redThreshhold = 1000;
const int proxThreshhold = 6;
int count = 0;
bool leftTurnMade = false;

// class Direction{
//   char direction;
//   int duration;

//   Direction(char dir, int dur){
//     this.direction = dir;
//     this.duration = dur;
//   };
// }

void setup() {
  lineSensors.initFiveSensors();
  proxSensors.initFrontSensor();

}

void printDebugVals(){
  
}

void proxSensorsLoop(){
  proxSensors.read();
  float leftValue = proxSensors.countsFrontWithLeftLeds();
  float rightValue = proxSensors.countsFrontWithRightLeds();

  lineSensors.read(sensors);

  if (leftValue == proxThreshhold && rightValue == proxThreshhold){
    buzzer.playNote('C4', 20, 15);
    motors.setSpeeds(0,0);
    display.print(F("Person found"));
    delay(1000);
    display.clear();

    // This is where the program should start a new routine to get the robot not detecting the person found 
  }
  if (leftValue == proxThreshhold && rightValue != proxThreshhold){
    motors.setSpeeds(0, 0);
    motors.setSpeeds(-200, 200);
    proxSensorsLoop();
  }
  if (rightValue == proxThreshhold && leftValue != proxThreshhold){
    motors.setSpeeds(0,0);
    motors.setSpeeds(200, -200);
    proxSensorsLoop();
  }
  
}

void turn90Clockwise(){
  motors.setSpeeds(200, -200);
  delay(425);
  motors.setSpeeds(0, 0);
}
void turn90AntiClockwise(){
  motors.setSpeeds(-200, 200);
  delay(425);
  motors.setSpeeds(0, 0);
}
void turn45Clockwise(){
  motors.setSpeeds(200, -200);
  delay(212.5);
  motors.setSpeeds(0, 0);
}
void turn45AntiClockwise(){
  motors.setSpeeds(-200, 200);
  delay(212.5);
  motors.setSpeeds(0, 0);
}

void stayWithinLines(){
   // If black line is in front stop
    if(sensors[0] > blackThreshhold &&  sensors[2] > (blackThreshhold-200) &&  sensors[4] > blackThreshhold){
      motors.setSpeeds(0, 0);
      motors.setSpeeds(-200, -200);
      delay(100);
      turn45Clockwise();
      leftTurnMade = false;
      // the hug left wall implementation should be here 
      Serial.println("black line in front");
      
    }
    // If robot is in a corner turn clockwise
    if(sensors[0] > blackThreshhold && sensors[2] < blackThreshhold && sensors[4] > blackThreshhold){
      turn90Clockwise();
      Serial.println("in corner");
      
    }
    // Goes forward if no black lines are detected on either side
     if (sensors[0] < blackThreshhold && sensors[4] < blackThreshhold){
        // motors.setSpeeds(100, 100);
        // if(leftTurnMade == false){
        //   turn90AntiClockwise();
        //   leftTurnMade = true;
        // }
        motors.setSpeeds(100, 100);
        Serial.println("goes forward");
        
        // if (sensors[0] > blackThreshhold && sensors[2] > blackThreshhold && sensors[4] > blackThreshhold){
        //   motors.setSpeeds(0, 0);
        // }
     }
     // If left black line is no longer there and the right black line is, turn left
    if(sensors[0] < blackThreshhold && sensors[4] > blackThreshhold){
        motors.setSpeeds(-100, 100);
        //motors.setSpeeds(0, 0);
        Serial.println("left turn");
        
      } 
      // if right black line is no longer there but left is, turn right
    if(sensors[0] > blackThreshhold && sensors[4] < blackThreshhold){
      motors.setSpeeds(100, -100);
      Serial.println("right turn");
      
    }
}

void stayOnLine(){
  if (sensors[0] > blackThreshhold && sensors[2] < blackThreshhold && sensors[4] < blackThreshhold){
    motors.setSpeeds(100, 100);
  }
  if (sensors[0] > blackThreshhold && sensors[2] > blackThreshhold && sensors[4] > blackThreshhold){
    motors.setSpeeds(-200, -200);
    delay(100);
    motors.setSpeeds(100, -100);
  }
  if (sensors[0] < blackThreshhold && sensors[2] < blackThreshhold && sensors[4] < blackThreshhold){
    turn90AntiClockwise();
    do{
      motors.setSpeeds(100, 100);
      lineSensors.read(sensors);
    } while(sensors[0] < blackThreshhold && sensors[2] < blackThreshhold && sensors[4] < blackThreshhold);
  }
}

void loop() {
  // turn90AntiClockwise();
  // turn90AntiClockwise();
  // turn90AntiClockwise();
  // turn90AntiClockwise();

  proxSensorsLoop();
  display.clear();
  
  for (int i = 0; i < 5; i++) {
    Serial.print("Line sensor");
    Serial.print(i);
    Serial.print(" : ");
    Serial.print(sensors[i]);
    Serial.print("\t");
  }
  uint8_t leftValue = proxSensors.countsFrontWithLeftLeds();
  uint8_t rightValue = proxSensors.countsFrontWithRightLeds();
  Serial.print("Left prox: ");
  Serial.print(leftValue);
  Serial.print(" Right prox: ");
  Serial.print(rightValue);
  Serial.print("\t");
  Serial.println();



  //stayOnLine();
  stayWithinLines();
   
 
  count++;
}