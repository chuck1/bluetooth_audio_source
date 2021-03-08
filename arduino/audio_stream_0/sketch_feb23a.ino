int analogPin = A3;
int val;

long baud_rate = 115200;

long sample_rate = 44100 / 10;

double period = (double)1000000 / (double)sample_rate;
double t = 0;

const int buffer_size = 128;

int buf[buffer_size];
int write_head = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(baud_rate);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(micros() > t)
  {  
    val = analogRead(analogPin);

    buf[write_head] = val;

    write_head += 1;

    if(write_head == buffer_size)
    {
      write_head = 0;
      Serial.write((byte*)buf, sizeof(buf));
    }

    t += period;
  }
}
