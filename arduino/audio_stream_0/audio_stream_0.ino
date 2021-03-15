#include "rate.h"
#include "serial_send.h"

int analogPin = A3;

long sample_rate = 44100 / 10;

struct Sample
{
  int val;
};

Sample sample;

SerialSend<Sample> serial_write(32);

Rate rate(sample_rate);

void setup() {
  Serial.begin(128000);
}

void loop() {
  if(rate.ready())
  {  
    sample.val = analogRead(analogPin);
    serial_write.send(sample);
  }
}
