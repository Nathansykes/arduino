#include <arduinoFFT.h>
#include <Servo.h>


#define SAMPLES 128
#define SAMPLING_FREQUENCY 2048

arduinoFFT FFT = arduinoFFT();

double vReal[SAMPLES];
double vImag[SAMPLES];

unsigned int SamplingPeriod;
unsigned long Microseconds;
double PeakFrequency;
byte Divider = 1;

//continuous servo
Servo servo;

void setup()
{
  Serial.begin(9600);
  SamplingPeriod = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
}

void loop()
{
  // setString();
  // sampleAudio();
  setMotor();
  delay(500);
}


void setMotor() {
  servo.attach(9); 
  servo.write(-200);
  delay(200);
  for(int i = -200; i < 200; i++) {
    servo.write(i);
    delay(10);
  }
  for(int i = 200; i > -200; i--) {
    servo.write(i);
    delay(10);
  }
  servo.detach();
}


void setString()
{
  delay(10);
  if (Serial.available() > 0)
  {
    char c = Serial.read();
    Serial.write(c);
    // each string on a guitar
    if (c == 'E')
    {
      Serial.println("Switched to E");
      Divider = 3;
    }
    if (c == 'A')
    {
      Serial.println("Switched to A");
      Divider = 3;
    }
    if (c == 'D')
    {
      Serial.println("Switched to D");
      Divider = 2;
    }
    if (c == 'G')
    {
      Serial.println("Switched to G");
      Divider = 1;
    }
    if (c == 'B')
    {
      Serial.println("B");
      Divider = 1;
    }
    if (c == 'e')
    {
      Serial.println("Switched to e");
      Divider = 1;
    }
  }
}

void sampleAudio()
{
  delay(10);
  for (int i = 0; i < SAMPLES; i++)
  {
    Microseconds = micros();
    vReal[i] = analogRead(A0);
    vImag[i] = 0;
    while (micros() < Microseconds + SamplingPeriod) { }
  }

  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

  PeakFrequency = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
  
  //get the amplitde
  double amplitude = vReal[0]; //this might work
  Serial.print("amplitude = ");
  Serial.println(amplitude);

  


  Serial.print(PeakFrequency / Divider);
  Serial.println("hz");
}
