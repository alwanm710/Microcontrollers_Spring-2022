/*
  Activity 5
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
  D8:
  D9:
  D10:
  D11: 
  D12: 
  D13: 
*/

//I know temperature can be negative. 
//But to make enough room for the tenth's place in 10-bit memory I made it unsigned.

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
  DDRB = 0x20;

  //configure ADCSRA and ADCSRB to desired values
  ADCSRA = 0xEF;
  ADCSRB = 0x00; //technically not needed
  //configure ADMUX to use A0 for temp. sensor
  ADMUX = 0x40;
  
  Serial.begin(9600);

}


void loop()
{
  //Circular Buffer value is n
  const unsigned char n = 10;
  static unsigned int arrayTemp[n];
  static unsigned long x = 0;
  
  unsigned int sensorValue = result;

  arrayTemp[x%n] = sensorValue;
  

  unsigned int avg = average(arrayTemp, n); // ADC result
  
  
  //Equation of Temp. Sensor TMP36 value in tenth's precision
  int temp = ((5000*avg)/(1023))-500;

  
  _delay_ms(100);
  
  x++;
  
  Serial.print(temp/10);
  Serial.print (".");
  Serial.println(temp%10);
}



unsigned int average(unsigned int *array, unsigned char arraySize) { 
  unsigned long sum = 0;
  
  for (unsigned char j = 0; j < arraySize; j++){
    sum += array[j];
  }
  return sum / arraySize;
  
}
