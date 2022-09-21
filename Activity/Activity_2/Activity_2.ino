/*
  Lab 1, Circuit 1
  Blinking an LED
  By: Mohammad, Sayan
  Written: Fed, 4 2022
  I/O Pins
  A0:  
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
  D7:  LED
  D8:  
  D9:  
  D10: 
  D11: 
  D12: 
  D13: 
*/

void setup()
{
  // Set DDRD bit 7
  // This causes Arduino pin D7 to be an output
  // We can use it to turn an LED on and off
  DDRD = 0b11111100;
  DDRB = 0b00000111;
}

void loop()
{
  unsigned char a = (PIND & 0B11100000)>>5;
  unsigned char b = (PIND & 0B00011100)>>2;

  if(a > b){
    PORTB = PORTB & 0B00000000;
    PORTB = PORTB | 0B00000001;
  }
  else if(a < b){
    PORTB = PORTB & 0B00000000;
    PORTB = PORTB | 0B00000010;
  }
  else{
    PORTB = PORTB & 0B00000000;
    PORTB = PORTB | 0B00000100;
  }

}
