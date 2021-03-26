#include "rate.h"
#include "serial_send.h"

int analogPin = A3;

long sample_rate = 44100 / 20;

struct Sample
{
int val;
};

Sample sample;

SerialSend<Sample> serial_write(true, 8);

Rate rate(sample_rate);

long t = 0;
long counter = 0;

void setup()
{
  Serial.begin(115200);
  //Serial.begin(128000);
}

int sine()
{
  //long t0 = micros() % 1000000;
  long t0 = micros() % 10000000;
  
  float t = (float)t0 / 1000000.0;

  float f = 400;

  counter += 1;
  //return counter;

  return 500 * sin(2 * 3.1415 * t * f);
}

void loop() 
{
  if(rate.ready())
  {
    sample.val = sine();
    serial_write.send(sample);
  }
}
