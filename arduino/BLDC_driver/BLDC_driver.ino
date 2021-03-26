

#define pin_AL  6 // OC0A
#define pin_AH  5 // OC0B
#define pin_BL  9 // OC1A
#define pin_BH 10 // OC1B
#define pin_CL 11 // OC2A
#define pin_CH  3 // OC2B


unsigned int stage_width = 10;
unsigned int stage_width_desired = 10;
unsigned int stage_counter = 0;


void AL_on()
{
  TCCR0A |= _BV(COM0A1);
}
void AL_off()
{
  TCCR0A &= ~_BV(COM0A1);
}
void AH_on()
{
  TCCR0A |= _BV(COM0B1);
}
void AH_off()
{
  TCCR0A &= ~_BV(COM0B1);
}
void BL_on()
{
  TCCR1A |= _BV(COM1A1);
}
void BL_off()
{
  TCCR1A &= ~_BV(COM1A1);
}
void BH_on()
{
  TCCR1A |= _BV(COM1B1);
}
void BH_off()
{
  TCCR1A &= ~_BV(COM1B1);
}
void CL_on()
{
  TCCR2A |= _BV(COM2A1);
}
void CL_off()
{
  TCCR2A &= ~_BV(COM2A1);
}
void CH_on()
{
  TCCR2A |= _BV(COM2B1);
}
void CH_off()
{
  TCCR2A &= ~_BV(COM2B1);
}
void transition_0()
{
  CL_off();
  AL_on();
}
void transition_1()
{
  BH_off();
  CH_on();
}
void transition_2()
{
  AL_off();
  BL_on();
}
void transition_3()
{
  CH_off();
  AH_on();
}
void transition_4()
{
  BL_off();
  CL_on();
}
void transition_5()
{
  AH_off();
  BH_on();
}

SIGNAL(TIMER2_COMPA_vect)
{
  // called every time the PWN signal turns off


  // i think best way to turn off a PWN pin is to clear the COMxy0 and COMxy1 bits and write the pin low
  // i think the interupt will continue to fire

  if(stage_counter == stage_width)
  {
    transition_0();
  }
  else if(stage_counter == stage_width * 2)
  {
    transition_1();
  }
  else if(stage_counter == stage_width * 3)
  {
    transition_2();
  }
  else if(stage_counter == stage_width * 4)
  {
    transition_3(); 
  }
  else if(stage_counter == stage_width * 5)
  {
    transition_4();
  }
  else if(stage_counter == stage_width * 6)
  {
    transition_5();
   
    stage_counter = 0;
    
    if(stage_width != stage_width_desired)
    {
      stage_width = stage_width_desired;
    }
  }
  
  stage_counter += 1;
}

void set_duty(byte duty)
{
  OCR0A = duty;
  OCR0B = duty;
  OCR1A = duty;
  OCR1B = duty;
  OCR2A = duty;
  OCR2B = duty;
}


unsigned long sys_clk = 1000000;
unsigned long timer_ps = 0;

void set_motor_frequency(float motor_freq)
{
  // timer prescaler not set, dont do anything
  if(timer_ps == 0) return;
  
  float divisor = (float)timer_ps * motor_freq * 6;

  // should check to make sure divisor is less than sys_clk
  
  float stage_width_float = (float)sys_clk / divisor;
  
  // should check to make sure stage_width_float is not too small, resulting in large difference between desired motor_freq and actual

  stage_width_desired = stage_width_float;
}

// determining counter value for each motor cycle
// system_clock_freq / timer_prescaler / desired_motor_freq
// 1000000 / 256 / 2 = 1953.125
// then divide by 6 to get stage_width
// 1953.125 / 6 = 325.520833333
// round down
// stage_width = 325

void set_timer_prescaler(int s)
{
  if(s == 256)
  {
    TCCR0B = _BV(CS02);
    TCCR1B = _BV(CS12);
    TCCR2B = _BV(CS22);
    timer_ps = 256;
  }
  else if(s == 1024)
  {
    TCCR0B = _BV(CS02) | _BV(CS00);
    TCCR1B = _BV(CS12) | _BV(CS10);
    TCCR2B = _BV(CS22) | _BV(CS20);
    timer_ps = 1024;
  }
}

void setup() 
{

  pinMode(pin_AL, OUTPUT);
  pinMode(pin_AH, OUTPUT);
  pinMode(pin_BL, OUTPUT);
  pinMode(pin_BH, OUTPUT);
  pinMode(pin_CL, OUTPUT);
  pinMode(pin_CH, OUTPUT);

  // setup PWN on pins 5 and 6
  
  TCCR0A = _BV(WGM01) | _BV(WGM00);
  //TCCR0A = _BV(COM0A1) | _BV(COM0B1);
  
  
  // setup PWN on pins 3 and 11
  
  TCCR1A = _BV(WGM11) | _BV(WGM10);
  //TCCR1A = _BV(COM1A1) | _BV(COM1B1) ;
  
  
  // setup PWN on pins 3 and 11

  TCCR2A = _BV(WGM21) | _BV(WGM20);
  //TCCR2A = _BV(COM2A1) | _BV(COM2B1);

  // enable interupt
  TIMSK2 |= _BV(OCIE2A);
  
  
  set_timer_prescaler(1024);
  
  set_duty(25);
  
  set_motor_frequency(2);
  
}

void loop() 
{


  
}
