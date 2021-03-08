int analog_pin_inv_input = A5;
int analog_pin_non_inv_input = A4;
int analog_pin_output = A3;

//long baud_rate = 115200;
long baud_rate = 9600;

const int buffer_size = 64;

struct Sample
{
  int V_inv_input;
  int V_non_inv_input;
  int V_output;
};

struct Sample buf[buffer_size];
int write_head = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(baud_rate);
}

void loop() {
  // put your main code here, to run repeatedly:
    
  
  
  buf[write_head].V_inv_input = analogRead(analog_pin_inv_input);
  buf[write_head].V_non_inv_input = analogRead(analog_pin_non_inv_input);
  buf[write_head].V_output = analogRead(analog_pin_output);

  write_head += 1;

  if(write_head == buffer_size)
  {
    write_head = 0;
    Serial.write((byte*)buf, sizeof(buf));
  }

  
  
}
