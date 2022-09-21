/*
  By: Mohammad and Cesar
  I/O Pins
  A0: Potentiometer
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
  D5: PWM (OC0B) // A1 on H-bridge
  D6: PWM (OC0A) // A2 on H-bridge
  D7: Toggle switch
  D8:
  D9:
  D10:
  D11:
  D12:
  D13:
*/

volatile unsigned char result; // Global variable to save ADC

void setup() {
  cli();
  DDRD = 0x60; // Pin D5 & D6 set as output
  TCCR0A = 0xA1; // Clear OC0A and OC0B on compare match (non-inverting mode)
  TCCR0B = 0x01; // WGM = 1,0,1 Phase-correct PWM  (top val = 0xFF) // Prescaler = 1


  ADCSRA = 0xEF; // 10-bit //Prescalar 128
  ADCSRB = 0x00; // Free running mode
  ADMUX = 0x60; // Pin A0 as analog input from pot & 8-bit mode on (ADLAR = 1)
  sei();
}

void loop() {
  unsigned char toggle = PIND & 0x80; // Masking and assigning toggle switch value
  
  // Toggle will change the direction of the motor
  if (toggle) {
    OCR0A = 0;
    OCR0B = result;
  }
  else {
    OCR0A = result; 
    OCR0B = 0;
  }
}

ISR(ADC_vect)
{
  result = ADCH;  // Adjusts speed
}
