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
}

void loop()
{
  PORTD = PORTD & 0b00000000;
  //Set PORTD bit 7, causing pin D7 to toggle
  PORTD = PORTD ^ 0b00110000;
  //wait for 1000 ms
  _delay_ms(5000);

  PORTD = PORTD ^ 0b01100000;
  //wait for 1000 ms                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
  _delay_ms(2000);

   PORTD = PORTD ^ 0b11010100;
  //wait for 1000 ms
  _delay_ms(5000);

  PORTD = PORTD ^ 0b00001100;
  //wait for 1000 ms
  _delay_ms(2000);

  

}
