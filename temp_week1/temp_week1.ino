const float baselineTemp = 19.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int pinNumber = 2; pinNumber < 5; pinNumber++) {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorVal = analogRead(A0);
  float voltage = (sensorVal / 1024.0) * 5.0;
  float temperature = (voltage - .5) * 100;
  delay(300);
  Serial.print("\r\nVal: ");
  Serial.print(sensorVal);
  Serial.print(" Volt: ");
  Serial.print(voltage);
  Serial.print(" Temp: ");
  Serial.print(temperature);
  if (temperature < baselineTemp) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  } else if (temperature >= baselineTemp + 2 && temperature < baselineTemp + 4) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  } else if (temperature >= baselineTemp + 4 && temperature < baselineTemp + 6) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  } else if (temperature >= baselineTemp + 6) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }
  delay(1);
}
