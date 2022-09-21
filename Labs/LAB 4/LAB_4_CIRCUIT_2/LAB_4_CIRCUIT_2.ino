/*
  Lab 4 Circuit 2
  By: Mohammad Alwan, Colton
  Created: 2/21/2022
  I/O Pins
  A0: Photoresistor Sensor input
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
  const unsigned char n = 60;

  //An array to save the light value from the 
  static unsigned int arrayLight[n];

  static unsigned long x = 0;
  
  unsigned int sensorValue = result;

  arrayLight[x%n] = sensorValue;
  

  unsigned int avg = average(arrayLight, n); // ADC result
  
  
  //Equation of Light level, 0% (6) to 100% (927)
  
  float lightLevel = (((1/9L) * avg) - (2/3));
  
  // Local variables
  const char m = 3;
  int base = 10;
  

  // Display on LCD "Light Level"
  lcd_puts("Light Level:");

  // Go to line 2
  lcd_goto(0x40);
  

  // Create an array that will store each ASCII character
  char charBuffer[m];

  // Converts value, in the given, into the variable charBuffer[]
  itoa(lightLevel, charBuffer, base);

  // Display result string
  lcd_puts(charBuffer);

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
