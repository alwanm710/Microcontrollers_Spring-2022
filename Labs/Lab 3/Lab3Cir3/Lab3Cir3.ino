/*
  Lab 3, Circuit 3
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
  D8: Cathode 4 output
  D9: Cathode 3 output
  D10:Cathode 2 output
  D11:Cathode 1 output
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
  DDRB = 0x0F;
}

void loop() {
 
  // Local variables
  unsigned int y = 10;
  unsigned int z = 1;
  //unsigned int DELAY = 2;
  PORTB |= 0x0E;
  
  // Define a constant value equal to the number of values in the arrays.
  const unsigned char n = 10;
  const unsigned char m = 4;
  
  // Define an array with display values for each numeral from 0-9
  unsigned char numArray[n] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xE6};

  // Define an array with display values from potentiometer
  unsigned char valueArray[m] = {};

  // Create a loop to store values of potentiometer to array
  for (unsigned int x = 0; x < m; x++) {
    valueArray[x] = (result % y) / z;
    y *= 10;
    z *= 10;
  }

 // Create a loop to display vales to 7 segment display
  for (unsigned int x = 0; x < m; x++) {
    // Set PORTD to be number from value array
    PORTD = numArray[valueArray[x]];

    // Delay of 5 ms, works best
     _delay_ms(5);

    // Toggle PORTB, bitshift, Toggle again
    PORTB ^= 0x0F;
    PORTB <<= 1;
    PORTB ^= 0x0F;
   
  }
  // Clear all pins from PORTB 
  PORTB &= 0x00;
}
