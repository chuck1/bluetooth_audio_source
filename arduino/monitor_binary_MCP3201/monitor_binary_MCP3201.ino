
#include <SPI.h>

#include "serial_send.h"
#include "MCP3201.h"

struct Sample
{
  unsigned int V;
};

Sample sample;

SerialSend<Sample> serial_write(64);

MCP3201 adc(9);

void setup() 
{
  Serial.begin(115200);

  SPI.begin();
  
  adc.setup();
}

void loop() {

  sample.V = adc.read();

  serial_write.send(sample);
  
}
