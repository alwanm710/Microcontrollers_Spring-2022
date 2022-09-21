/*
  Lab 2, Circuit 2 Extra
  Use two pushbuttons and a toggle switch to switch between six logic gates(pushbuttons are input)
  By: Mohammad & Martin
  Created: 2/9/2022
  Edited: 2/18/2022
  I/O Pins
  A0:
  A1:
  A2:
  A3:
  A4:
  A5:
  D0:
  D1:
  D2: NOR Gate
  D3: NAND Gate
  D4: XNOR Gate
  D5: XOR Gate
  D6: OR Gate
  D7: AND Gate
  D8:
  D9:
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
  unsigned char b = PINB;
  unsigned char a = PIND & 0xFC; //store value of PIND and selectively clear floating pins 
  switch (a) {
    case 0x80: //AND
      if ((b & 0x08) && (b & 0x10)) //AND D11 and D12(INPUTS a and b)
      {
        PORTB |= 0x20; //turn on LED
      } else
      {
        PORTB &= 0xDF; //turn off LED
      }
      break;
    case 0x40: //OR
      if ((b & 0x08) || (b & 0x10)) //OR D11 and D12(INPUTS a and b)
      {
        PORTB |= 0x20; //turn on LED
      } else
      {
        PORTB &= 0xDF; //turn off LED
      }
      break;
    case 0x20: //XOR
      if ((b & 0x08) != ((b & 0x10) >> 1)) //OR D11 and D12(INPUTS a and b)
      {
        PORTB |= 0x20; //turn on LED
      } else
      {
        PORTB &= 0xDF; //turn off LED
      }
      break;
    case 0x10: //XNOR
      if ((b & 0x08) == ((b & 0x10) >> 1)) //AND D11 and D12(INPUTS a and b)
      {
        PORTB |= 0x20; //turn on LED
      } else
      {
        PORTB &= 0xDF; //turn off LED
      }
      break;
    case 0x08: //NAND
      if (!((b & 0x08) && (b & 0x10))) //AND D11 and D12(INPUTS a and b)
      {
        PORTB |= 0x20; //turn on LED
      } else
      {
        PORTB &= 0xDF; //turn off LED
      }
      break;
    case 0x04: //NOR
      if (!((b & 0x08) || (b & 0x10))) //AND D11 and D12(INPUTS a and b)
      {
        PORTB |= 0x20; //turn on LED
      } else
      {
        PORTB &= 0xDF; //turn off LED
      }
      break;
    default:
      PORTB &= 0xDF; //turn off LED
      break;
      
  }
}
