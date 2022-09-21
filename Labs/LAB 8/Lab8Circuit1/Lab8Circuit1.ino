/*
  Lab 8 Circuit 1
  Find LED ADC values
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
volatile unsigned char result = 0;

//save ADC value to result
ISR(ADC_vect) {
  result = ADCH;
}

void setup() {
  // put your setup code here, to run once:
  DDRD = 0x80;
  cli();
  ADCSRA = 0xEF;
  ADCSRB = 0x00;
  ADMUX = 0x60;
  sei();
  Serial.begin(9600);
}

void loop() {
  Serial.println(result);


}
