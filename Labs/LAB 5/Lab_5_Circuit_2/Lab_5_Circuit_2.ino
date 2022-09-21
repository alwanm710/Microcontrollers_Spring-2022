/*
  Lab 5, Circuit 2
  External pin-change interrupt triggered by PBs & Rising edge interrupt triggered adder using a keypad, outputs displays on an LCD screen
  By: Gary, Colton, and Mohammad
  Written: March 2, 2022
  Edited: March 2, 2022
  I/O Pins
  A0: + Input
  A1: - Input
  A2: * Input
  A3: / Input
  A4:
  A5:
  D0:
  D1:
  D2:  Keypad encoder pin 12 (data available)
  D3:
  D4:  Keypad pin A
  D5:  Keypad pin B
  D6:  Keypad pin C
  D7:  Keypad pin D
  D8:  LCD Register Select (RS)
  D9:  LCD Enable (E)
  D10: LCD Data Bit 4 (DB4)
  D11: LCD Data Bit 5 (DB5)
  D12: LCD Data Bit 6 (DB6)
  D13: LCD Data Bit 7 (DB7)
*/

// include the library that contains all of the LCD functions and constants
#include "hd44780.h"

void setup()
{
  // globally disable interrupts while setting up important registers
  cli(); // configure external interrupt registers // rising edge triggered interrupts on pin D2
  EICRA = 0x03; // enable interrupt INT0
  EIMSK = 0x01; // globally re-enable interrupts

  PCICR = 0x02; //PortC PC interrupts
  PCMSK1 = 0x0F; //A0, A1, A2, A3
  sei();

  // initialize the LCD screen (sets the screen size, font, etc.)
  lcd_init();
}

volatile unsigned char a = 0;
volatile unsigned char b = 0;
volatile unsigned char operation = 0;
void loop()
{
  // clear the screen
  lcd_clrscr();

  // convert a to a string, can only be 3 characters (0-11 and terminal character), then display

  char aBuffer[3];
  itoa(a, aBuffer, 10);
  lcd_puts(aBuffer);
  char c = 0;
  switch (operation)
  {
    case 1: // Add
      c = a + b;
      lcd_puts("+");
      break;

    case 2: // Subtract
      c = a - b;
      lcd_puts("-");
      break;
    case 4: // Multiplication
      c = a * b;
      lcd_puts("*");
      break;
    case 8:
      if (b != 0)
      {
        c = a / b;
        lcd_puts("/");
      }
      else
      {
        b = 1;
        lcd_puts("/");
      }
      break;
  }

  // convert b to a string, can only be 3 characters (0-11 and terminal character), then display
  char bBuffer[3];
  itoa(b, bBuffer, 10);
  lcd_puts(bBuffer);
  lcd_puts("=");

  // convert c to a string, can only be 3 characters (0-22 and terminal character), then display
  char cBuffer[4];
  itoa(c, cBuffer, 10);
  lcd_puts(cBuffer);

  // a short delay is used here to eliminate flickering of the LCD screen
  _delay_ms(3);

}

ISR(INT0_vect) {
  static char x = 0;
  if (x) {
    a = PIND >> 4;
  }
  else {
    b = PIND >> 4;
  }
  x ^= 1;
}
static unsigned v = 0;
ISR(PCINT1_vect)
{
  v = PINC & 0x0F;
  if (v != 0)
  {
    operation = v; // Reads the new operation
  }
}
