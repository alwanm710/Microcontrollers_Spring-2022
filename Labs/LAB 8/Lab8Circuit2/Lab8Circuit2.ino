/*
  Lab 8 Circuit 2
  Use Proportional control to keep constant light level
  By: Martin and Mohammad
  Written: 3/23/22
  I/O Pins
  A0: Photoresistor
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
  D8: LED
  D9:
  D10:
  D11:
  D12:
  D13:
*/
volatile unsigned char pV = 0;

//save ADC value to result
ISR(ADC_vect) {
  pV = ADCH;
}

void setup() {
  // put your setup code here, to run once:
  DDRD = 0x40;
  cli();
  ADCSRA = 0xEF;
  ADCSRB = 0x00;
  ADMUX = 0x60;

  TCCR0A = 0x83;
  TCCR0B = 0x03;

  OCR0A = 255;
  
  sei();
  Serial.begin(9600);
}

void loop() {
  unsigned char  sP = 184;
  unsigned char  Kp = 4;

  int err = sP - pV;

  OCR0A += (Kp*err)/10;

  Serial.print(pV);
  Serial.print('\t');
  Serial.println(sP);

}
