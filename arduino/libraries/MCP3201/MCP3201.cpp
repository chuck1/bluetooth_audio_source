#include "Arduino.h"
#include <SPI.h>
#include "MCP3201.h"

MCP3201::MCP3201(int pin_CS):
	_pin_CS(pin_CS)
{
	
}

void MCP3201::setup()
{
	pinMode(_pin_CS, OUTPUT);
	
	digitalWrite(_pin_CS, HIGH);
}

unsigned int MCP3201::read()
{
  SPI.beginTransaction(SPISettings(1600000, MSBFIRST, SPI_MODE0));

  digitalWrite(_pin_CS, LOW);

  unsigned int val = SPI.transfer16(0);

  val = val >> 1;

  val = val & 0xfff;
  
  digitalWrite(_pin_CS, HIGH);
  
  SPI.endTransaction();

  return val;
}



