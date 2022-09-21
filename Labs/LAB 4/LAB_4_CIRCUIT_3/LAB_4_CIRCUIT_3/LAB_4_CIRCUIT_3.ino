/*
  Lab 4 Circuit 3
  By: Mohammad Alwan, Colton
  Created: 2/21/2022
  I/O Pins
  A0: Soft Pot Sensor input
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


// Global variable for result
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

  //configure ADCSRA and ADCSRB to desired values
  ADCSRA = 0xEF;
  ADCSRB = 0x00; //technically not needed
  //configure ADMUX to use A0 for Photoresistor sensor
  ADMUX = 0x40;
  
  // Initialize LCD screen
  lcd_init();

}


void loop()
{
  // Clear LCD screen
  lcd_clrscr();

  //Circular Buffer value is n
  const unsigned char n = 40;

  //An array to save the Soft Pot value from the 
  static unsigned int arraySoftPot[n];

  static unsigned long x = 0;
  
  unsigned int sensorValue = result;

  arraySoftPot[x%n] = sensorValue;
  

  unsigned int avg = average(arraySoftPot, n); // ADC result
  
  
  //Equation of distance, 50 mm (0) to 0 mm (1023)
  float distance = (((-5L * (avg)) + 5350)/107);
  // Local variables
  const char m = 5;
  int base = 10;
  

  // Display on LCD "Light Level"
  lcd_puts("Distance Level:");

  // Go to line 2
  lcd_goto(0x40);
  

  // Create an array that will store each ASCII character
  char charBuffer[m];

  // Converts value, in the given, into the variable charBuffer[]
  itoa(distance, charBuffer, base);

  // Display result string
  lcd_puts(charBuffer);

  //Display a unit after result
  lcd_goto(0x43);
  lcd_puts("mm");

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
