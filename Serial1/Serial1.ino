void setup() 
{
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() 
{
  delay(200);
  if(Serial1.available() > 0)
  {
    delay(200);
    char c = Serial1.read();
    Serial.print("Received from Serial1: \n");
    Serial.println(c);
    if(c == 's')
    {
      Serial.println("c == s");
      delay(500);   
    }
  }
  delay(200);
}