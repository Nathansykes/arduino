int switchState = 0;
int oldSwitch = 1;
int state = 0;

void setup() 
{
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(2, INPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  switchState = digitalRead(2);
  if(switchState && !oldSwitch)
  {
    //we have a new button press
    if(state == 0) // if the state is off, turn it on
    {
      //do stuff
      state = 1;
    }
    else // if the state is on, turn it off
    {
      //do stuff
      state = 0; 
    }
    oldSwitch=1;
  }
  else if((!switchState) && oldSwitch)
  {
    oldSwitch = 0;
  }

  if (state == HIGH) 
  {
    // the buton is not pressed
    digitalWrite(3, HIGH);  // green LED
    digitalWrite(4, LOW);   // red LED
    digitalWrite(5, LOW);   // red LED
  } 
  else 
  {                  // the buton is pressed
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    delay(50);  // wait for a quarter second
    // toggle the LEDs
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    delay(50);  // wait for a quarter second
  }
}  // go back to the beginning of the loop
