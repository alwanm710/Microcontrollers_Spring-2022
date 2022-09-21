/*
  Smart Car
  Test
  By:Mohammad
  I/O Pins
  A0: Potentiometer input
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
  Serial.begin(9600);
}

void loop() {
  Serial.println(result);



  
}
