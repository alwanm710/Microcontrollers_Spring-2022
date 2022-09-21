/*
  Lab 8 Circuit 3
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
  unsigned char  Ki = 10;
  unsigned char  tau = 7;
  static unsigned char x = 0;
  int errHist[tau];


  int err = sP - pV;

  errHist[x % tau] = err;
  int histSum = sum(errHist, tau);

  OCR0A += (Kp * err) / 10;
  OCR0A += (Ki * histSum) / 100;

  x++;

  Serial.print(pV);
  Serial.print('\t');
  Serial.println(sP);

}

int sum(int r[], unsigned char n) {
  int tempVar = 0;
  for (char j = 0; j < n; j++) {
    tempVar += r[j];
  }
  return tempVar;
}
