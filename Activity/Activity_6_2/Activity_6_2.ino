//Activity 6 Circuit 2


//D10: Input
//D9: Input
//D8: Input
//D2: OutputRed
//D1: OutputGreen
//D0: OutputBlue

void setup() {
  // put your setup code here, to run once:
  PCICR = 0x01;
  PCMSK0 = 0x07;
  DDRD = 0x07;
  PORTB = 0x07;
}

void loop() {
}

ISR(PCINT0_vect)
{
  PORTD &= 0x00;
  PORTD |= ((PINB & 0x07) ^ 0x07);
  
}
