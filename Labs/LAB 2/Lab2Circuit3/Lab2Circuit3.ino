/*
  Lab 2, Circuit 3
  Using a pedometer to change blink rate of LED
  By: Mohammad & Martin
  I/O Pins
  Created: 02/09/2022
  A0: Pedometer
  A1:
  A2:
  A3:
  A4:
  A5:
  D0:
  D1:
  D2:
  D3:
  D4:
  D5:
  D6:
  D7:
  D8:
  D9:
  D10: 
  D11:
  D12:
  D13: LED //0010 0000
*/
volatile unsigned int result = 0; //analog result
void setup()
{
  // Set DDRB bit 5
  // This causes Arduino pin D13 to be an output
  DDRB = 0x20;
  //configure ADCSRA and ADCSRB to desired values
  ADCSRA = 0xEF;
  ADCSRB = 0x00; //technically not needed
  //configure ADMUX to use A0
  ADMUX = 0x40;
}

void loop()
{
  PORTB ^= 0x20; //toggle LED
  for(unsigned int i = 0; i < result; i++) //increases delay based on result
  {
    _delay_us(1000);
  }
}
ISR(ADC_vect)
{
  result = ADC;//update result
}
