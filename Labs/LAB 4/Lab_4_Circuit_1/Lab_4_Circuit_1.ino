/*
  Lab 4 Circuit 1
  By: Mohammad Alwan
  Created: 2/21/2022
  I/O Pins
  A0: Temp. Sensor input
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
  D8: RS pin from LCD
  D9: E pin from LCD
  D10: DB4 from LCD
  D11: DB5 from LCD
  D12: DB6 from LCD
  D13: DB7 from LCD 
*/
// Libraries included
#include "hd44780.h"


// Global variables
volatile unsigned int result = 0;



// Interrupt when ADC has a result
ISR(ADC_vect)
{
  result = ADC;//update result
}


void setup()
{
  // Set DDRB bit 5
  // This causes Arduino pin D13 to be an output
  DDRB = 0x3F;

  // configure ADCSRA and ADCSRB to desired values
  ADCSRA = 0xEF;
  ADCSRB = 0x00; //technically not needed
  // configure ADMUX to use A0 for temp. sensor
  ADMUX = 0x40;
  
  // Initialize LCD screen
  lcd_init();

}


void loop()
{
  // Circular Buffer value is n
  const unsigned char n = 50;
  static unsigned int arrayTemp[n];
  static unsigned long x = 0;

  arrayTemp[x%n] = result;
  

  unsigned int avg = average(arrayTemp, n); // ADC result
  
  
  // Equation of Temp. Sensor TMP36 value in tenth's precision
  int temp = ((5000L*avg)/(1023))-500 + 160;

  int top = temp/10;
  unsigned char bottom = temp%10;
  
  // Local variables
  const char m = 4;
  const char y = 2;
  const char base = 10;
  
  // Clear LCD screen
  lcd_clrscr();

  // Display on LCD "Pot. Value"
  lcd_puts("Temp. Value:");

  // Go to line 2
  lcd_goto(0x40);
  
  // Create an array that will store each ASCII character
  char charBufferTop[m];

  // Create an array that will store each ASCII character
  char charBufferBottom[y];

  // Converts value, in the given, into the variable charBuffer[]
  itoa(top, charBufferTop, base);
  itoa(bottom, charBufferBottom, base);

  // Display result string
  lcd_puts(charBufferTop);
  lcd_puts(".");
  lcd_puts(charBufferBottom);
  lcd_putc(223);
  lcd_puts("C");



  
  _delay_ms(20);

  x++;

}


unsigned int average(unsigned int *array, unsigned char arraySize) { 
  unsigned long sum = 0;
  
  for (unsigned char j = 0; j < arraySize; j++){
    sum += array[j];
  }
  return (sum / arraySize);
  
}
