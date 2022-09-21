volatile unsigned int adcResult = 0;




void setup() {
  cli();

  ADCSRA = 0xEF;
  ADCSRB = 0x00;
  ADMUX = 0x60;

  //DDRD = 0x24;
  DDRD = 0x28;
  
  TCCR0A = 0x21; //Phase correct PWM //OC0B non-Inverting// Top OCR0A
  TCCR0B = 0x09; //0000-1001 //PreScaler of 1
  OCR0A = 160;

  TCCR2A = 0x21; //Phase correct PWM //OC0B non-Inverting// Top OCR2A
  TCCR2B = 0x09; //0000-1001 //PreScaler of 1
  OCR2A = 160;

  sei();
 // Serial.begin(9600);
}

void loop() {
  //Serial.println(adcResult);
  //Serial.println(TCNT2);


  //OCR0B = (adcResult * 160L)  / 1023;
  //OCR2B = (adcResult * 160L) / 1023;
}

ISR(ADC_vect)
{
  adcResult = ADC;
  //OCR0B = (adcResult * 160L) / 1023; //Use ADMUX in 8-Bit operation, assign ADCH to OCRxB
  //OCR2B = (adcResult * 160L) / 1023;
  OCR0B = ADCH;
}
