#include "rate.h"

int analogPin = A3;

long sample_rate = 44100 / 10;

struct Sample
{
  int val;
}

Sample sample;

SerialSend serial_write(64);

Rate rate(sample_rate);

void setup() {
  Serial.begin(115200);
}

void loop() {
  if(rate.ready())
  {  
    sample.val = analogRead(analogPin);
    serial_write.send(sample);
  }
}
