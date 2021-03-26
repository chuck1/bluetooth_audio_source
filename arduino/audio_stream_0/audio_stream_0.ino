#include "rate.h"
#include "serial_send.h"

int analogPin = A3;

long sample_rate = 44100 / 10;

struct Sample
{
  byte val;
};

Sample sample;

SerialSend<Sample> serial_write(false, 32);

Rate rate(sample_rate);

void setup() {
  Serial.begin(128000);
}

void loop() {
  if(rate.ready())
  {
    int x16 = analogRead(analogPin);

    x16 -= 270 - 128;
    
    sample.val = x16;
    serial_write.send(sample);
  }
}
