
#include <SPI.h>

#include "serial_send.h"
#include "MCP3201.h"
#include "rate.h"

struct Sample
{
  unsigned int val;
};

Sample sample;

SerialSend<Sample> serial_write(64);

MCP3201 adc(9);

Rate rate(44100.0 / 2);

void setup() 
{
  Serial.begin(500000);
  SPI.begin();  
  adc.setup();
}

void loop() 
{
  if(rate.ready())
  {
    sample.val = adc.read();
    serial_write.send(sample);
  }
}
