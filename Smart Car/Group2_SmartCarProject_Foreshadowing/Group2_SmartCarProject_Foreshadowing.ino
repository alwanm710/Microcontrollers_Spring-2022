
/*
  Barrier Detector
  xxxx
  By: Gary and Colton
  Written: March 21, 2022
  Edited: March 21, 2022
  I/O Pins
  A0:
  A1:
  A2:
  A3:
  A4:
  A5:
  //PORT D
  D0:
  D1:
  D2: Left Whisker
  D3: PWM 4 (OC2B) - Left Motor Backward
  D4: Right Whisker
  D5: PWM 1 (OC0B) - Right Motor Backward
  D6: PWM 2 (OC0A) - Right Motor Forward
  D7: Enable Right motor
  //PORT B
  D8: Enable Left motor
  D9:
  D10:
  D11: PWM 3 (OC2A) - Left Motor Forward
  D12:
  D13:

*/

volatile unsigned int adcResult = 0;
static unsigned char whiskerLeft = 0;
static unsigned char whiskerRight = 0;

void setup() {
  cli();
  DDRD = 0x68; //Pin D6 Output (OC0A)  //0110-1000
  DDRB = 0x08;

  PIND |= 0x80; // D7 - Enable Right motor control
  PINB |= 0x01; // D8 - Enable Left motor control

  TCCR0A = 0xA1; //Routes PWM signal to OC0B in non-inverting mode; 1010-0001
  TCCR0B = 0x01; //Prescalar of 1                                   0000-0001

  TCCR2A = 0xA1; //Phase correct PWM //OC0B non-Inverting// Top OCR2A; 1010-0001
  TCCR2B = 0x01; //PreScaler of 1                                      0000-0001

  ADCSRA = 0xEF;
  ADCSRB = 0x00;
  ADMUX = 0x60; //ADLAR = 1

  EICRA = 0x03; // External interrupt for rising edge
  EIMSK = 0x01; // Enable interrup for D2
  PCICR = 0x04; // Enable interrupt I/O pins on PORTD
  PCMSK2 = 0x10; // Enables interrupt on D4
  sei();
  Serial.begin(9600);
}

void turnRight()
{
  OCR0A = 0;   // stop moving forward
  OCR2A = 0;   // stop moving forward
  OCR0B = adcResult; // move backwards
  OCR2B = adcResult; // move backwards
  _delay_ms(100);
  OCR2B = 0;        // Left Wheel stationary while right wheel turns
  _delay_ms(500);
  OCR0B = 0;
  OCR0A = adcResult;
  OCR2A = adcResult;
  whiskerLeft = 0;
  whiskerRight = 0;
}
void turnLeft()
{
  OCR0A = 0;   // stop moving forward
  OCR2A = 0;   // stop moving forward
  OCR0B = adcResult; // move backwards
  OCR2B = adcResult; // move backwards
  _delay_ms(100);
  OCR0B = 0;        // Right Wheel stationary while Left wheel turns
  _delay_ms(500);
  OCR2B = 0;
  OCR0A = adcResult;
  OCR2A = adcResult;
  whiskerLeft = 0;
  whiskerRight = 0;
}

void turnRight30()
{
  OCR0A = 0;   // stop moving forward
  OCR2A = 0;   // stop moving forward
  OCR0B = adcResult; // move backwards
  OCR2B = adcResult; // move backwards
  _delay_ms(50);
  OCR2B = 0;        // Left Wheel stationary while right wheel turns
  _delay_ms(450);
  OCR0B = 0;
  OCR0A = adcResult;
  OCR2A = adcResult;
  whiskerLeft = 0;
  whiskerRight = 0;
}
void turnLeft30()
{
  OCR0A = 0;   // stop moving forward
  OCR2A = 0;   // stop moving forward
  OCR0B = adcResult; // move backwards
  OCR2B = adcResult; // move backwards
  _delay_ms(50);
  OCR0B = 0;        // Right Wheel stationary while Left wheel turns
  _delay_ms(450);
  OCR2B = 0;
  OCR0A = adcResult;
  OCR2A = adcResult;
  whiskerLeft = 0;
  whiskerRight = 0;
}

void loop()
{
  static unsigned char entanglements = 0;
  Serial.println(adcResult);
  if (whiskerLeft == 0 && whiskerRight == 0) // Moves forward
  {
    OCR0A = adcResult;
    OCR0B = 0;
    OCR2A = adcResult;
    OCR2B = 0;
  }
  else if (whiskerLeft == 1 && whiskerRight == 1)
  {
    if (entanglements == 0)
    {
      turnRight();
      ++entanglements;
    }
    else if (entanglements == 1)
    {
      turnLeft();
    }
  }
  else if (whiskerLeft == 1) {
    turnRight30();
  }
  else if ( whiskerRight == 1) {
    turnLeft30();
  }

}

ISR(ADC_vect)
{
  adcResult = ADCH;
}

ISR(INT0_vect)
{
  whiskerLeft = 1;
  _delay_ms(25);
}

ISR(PCINT2_vect)
{
  if (PIND & 0x10)
  {
    whiskerRight = 1;
  }
  _delay_ms(25);
}
