/*
  Lab 4 Extra Credit
  By: Mohammad Alwan
  Created: 3/9/2022
  I/O Pins
  A0: Photoresistor Sensor input
  A1: Temp. Sensor input
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


// Global variable for Temp. and Light results
volatile unsigned int lightResult = 0;
volatile unsigned int tempResult = 0;


// Interrupt when ADC has a result
ISR(ADC_vect)
{
   // Toggle ADMUX to swtich between AO (Light Sensor) and A1 (Temp. Sensor)
  ADMUX ^= 0x01;
  if (ADMUX == 0x40) lightResult = ADC;//update light result
  else tempResult = ADC;//update temp. result
}


void setup()
{
  // Set DDRB bit 5
  // This causes Arduino pin D8 to D13 to be an output
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
  
  // configure ADMUX to use A0 for temp. sensor
  //ADMUX ^= 0x01;

  //Circular Buffer value is n
  const unsigned char n = 15;

  //An array to save the light value from the 
  static unsigned int arrayLight[n];

  static unsigned long x = 0;

  arrayLight[x%n] = lightResult;
  

  unsigned int avg1 = average1(arrayLight, n); // ADC result
  
  
  //Equation of Light level, 0% (6) to 100% (927)
  
  float lightLevel = ((1L * avg1) - 6)/9;
  
  // Local variables
  const char m = 3;
  int base = 10;
  
  
  lcd_puts("Light Level:"); // Display on LCD "Light Level"
  
  char charBuffer[m]; // Create an array that will store each ASCII character
  
  itoa(lightLevel, charBuffer, base); // Converts value, in the given, into the variable charBuffer[]
  
  lcd_puts(charBuffer); // Display result string
 
  lcd_goto(0x40); // Go to line 2












  

 

  // Circular Buffer value is n2
  const unsigned char n2 = 100;
  static unsigned int arrayTemp[n2];
  
  arrayTemp[x%n2] = tempResult;
  
  unsigned int avg2 = average2(arrayTemp, n2); // ADC result



  // Equation of Temp. Sensor TMP36 value in tenth's precision
  int temp = ((5000L*avg2)/(1023)) - 500;

  int top = temp/10;
  unsigned char bottom = temp%10;
  
  // Local variables
  const char w = 4;
  const char y = 2;

  lcd_puts("Temp.:"); // Display on LCD "Light Level"

  // Create an array that will store each ASCII character
  char charBufferTop[w];

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
  

  
  _delay_ms(30);

      x++;
}


unsigned int average1(unsigned int *array, unsigned char arraySize) { 
  unsigned long sum = 0;
  
  for (unsigned char j = 0; j < arraySize; j++){
    sum += array[j];
  }
  return (sum / arraySize);
  
}



unsigned int average2(unsigned int *array, unsigned char arraySize) { 
  unsigned long sum = 0;
  
  for (unsigned char j = 0; j < arraySize; j++){
    sum += array[j];
  }
  return (sum / arraySize);
  
}
