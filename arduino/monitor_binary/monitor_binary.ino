#include "serial_send.h"

int analog_pin_inv_input = A5;
int analog_pin_non_inv_input = A4;
int analog_pin_output = A3;

//long baud_rate = 115200;
long baud_rate = 19200;

const unsigned long buffer_size = 64;

struct Sample
{
  int V_inv_input;
  int V_non_inv_input;
  int V_output;
};

Sample sample;

SerialSend<Sample> serial_send(buffer_size);

void setup() {
  Serial.begin(baud_rate);
}

void loop() {
  
  sample.V_inv_input = analogRead(analog_pin_inv_input);
  sample.V_non_inv_input = analogRead(analog_pin_non_inv_input);
  sample.V_output = analogRead(analog_pin_output);

  serial_send.send(sample);
}
