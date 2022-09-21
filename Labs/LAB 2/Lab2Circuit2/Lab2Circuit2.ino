/*
  Lab 2, Circuit 2
  Use two pushbuttons and a toggle switch to switch between two logic gates(pushbuttons are input)
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
  D8:
  D9: TRUE/FALSE toggle //0000 0010
  D10: 
  D11: INPUT A //0000 1000
  D12: INPUT B //0001 0000
  D13: LED //0010 0000
*/

void setup()
{
  // Set DDRB bit 5
  // This causes Arduino pin D13 to be an output
  DDRB = 0x20;
}

void loop()
{
  unsigned char a = PINB; //store value of PINB

  //AND gate
  if ((a & 0x02) == 0x02) //check if D9 is on
  {
    if ((a & 0x08) && (a & 0x10)) //AND D11 and D12(INPUTS a and b)
    {
      PORTB |= 0x20; //turn on LED
    } else
    {
      PORTB &= 0xDF; //turn off LED
    }
  }

  else //if D9 is off
  {
    if ((a & 0x08) || (a & 0x10)) //OR D11 and D12(INPUTS a and b)
    {
      PORTB |= 0x20; //turn on LED
    } else
    {
      PORTB &= 0xDF; //turn off LED
    }
  }


}
