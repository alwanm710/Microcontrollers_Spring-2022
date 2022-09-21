/*
  Lab 5, Circuit 2
  External pin-change interrupt triggered by PBs & Rising edge interrupt triggered adder using a keypad, outputs displays on an LCD screen
  By: Gary, Colton, and Mohammad
  Written: March 2, 2022
  Edited: March 2, 2022
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
  D2:  
  D3:
  D4:  
  D5:  
  D6:  
  D7:  
  // PORT B
  D8:  LED (Setup)
  D9:  LED (Loop)
  D10: 
  D11: 
  D12: 
  D13: 
*/

void setup() 
{
  cli();
  DDRB = 0x03;
  PORTB |= 0x01; // Turn D8 LED on
  _delay_ms(1500);
  PORTB &= 0x00; // Turn D8 LED off

  WDTCSR |= 0x18;
  WDTCSR = 0x20;

  sei();

}

void loop() {
static unsigned char j = 0;
static unsigned char n = 100;
 if ( j =< n){
  asm volatile ("wdr");
  PORTB |= 0x02; // Turn D8 LED on
  _delay_ms(200);
  PORTB &= 0x00; // Turn D8 LED off
  msdelay(j);
  j += 25;
  }
}


void msdelay(unsigned char x){
  
  for(unsigned char i = 0; i < x; i++){
    _delay_ms(40);
  }
}
