/*
  Lab 2, Circuit 1b
  Using a pushbutton to turn on/off an LED
  By: Mohammad & Martin
  Created: 2/9/2022
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
  D7:
  D8: Pushbutton
  D9:
  D10:
  D11:
  D12:
  D13: LED
*/

void setup()
{
  // Set DDRB bit 5
  // This causes Arduino pin D13 to be an output
  DDRB = 0x20;
  PORTB |= 0x01;//turn on internal resistor on pin D8
}

void loop()
{
  //Read value from pushbutton (D8)
  unsigned char buttonState = PINB & 0x01;

  if (buttonState) {
    //Turn on LED
    PORTB &= 0xDF;
  }
  else {
    // Turn off LED
    PORTB |= 0x20;
  }

}
