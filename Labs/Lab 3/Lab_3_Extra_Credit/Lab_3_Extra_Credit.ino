/*
  Lab 3 Extra Credit
  Display potentiometer results on 7 Segment display
  By: Cesar & Mohammad
  I/O Pins
  A0: Potentiometer input
  A1:
  A2:
  A3:
  A4:
  A5:
  D0: 
  D1: Segment G output
  D2: Segment F output
  D3: Segment E output
  D4: Segment D output
  D5: Segment C output
  D6: Segment B output
  D7: Segment A output
  D8: Toggle switch input
  D9:  
  D10: 
  D11: 
  D12: 
  D13: 
*/

// Global variables
volatile unsigned int result = 0;

// Interrupt when ADC has a result
ISR(ADC_vect) {
  result = ADC;
}

void setup() {
  // Setting up ADCSRA, ADCSRB and ADMUX
  ADCSRA = 0xEF;
  ADCSRB = 0x00;

  
  ADMUX = 0x40;
  
  // Configure DDRD using the pins you've chosen to connect to the 7-segment display
  DDRD = 0xFE;

  // Configure DDRB for cathode pins
  DDRB = 0x01;
}

void loop() {
 
  // Local variables
  unsigned int y = 10;
  unsigned int z = 1;

  unsigned char x = PORTB;
  
  
  // Define a constant value equal to the number of values in the arrays.
  const unsigned char n = 10;
  
  // Define an array with display values for each numeral from 0-9
  unsigned char numArray[n] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xE6};


  if(x == 1) z++;
  else z--;

  _delay_ms(result);
  

  

  


}
