const int input = A0;
int soundOutput = 8;
int potVal;
int angle;

int sensorLow = 1023;
int sensorHigh = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  potVal = analogRead(input);
  Serial.print("\r\nPot Val: ");
  Serial.print(potVal);
  tone(soundOutput, potVal, 100);
}
