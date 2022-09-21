/*
  Lab 9, Circuit 3 Secondary Device
  By: Jack, Cesar, Mohammed
  Written: 4/6/22
  Edited: 4/6/22
  I/O Pins
  A0: pin A from BCD to 7-seg
  A1: pin B from BCD to 7-seg
  A2: pin C from BCD to 7-seg
  A3: pin D from BCD to 7-seg
  A4:
  A5:
  D0:
  D1:
  D2: Debounced Pushbutton
  D3: Red Cathode of RGB LED
  D4: Green Cathode of RGB LED
  D5: Blue Cathode of RGB LED
  D6:
  D7:
  D8:
  D9:
  D10: GND
  D11: MOSI on Primary
  D12: MISO on Primary
  D13: SCK on Primary
*/
volatile unsigned char rNum = 0;

void setup() {
  // Create a random seed for random function
  randomSeed(12);
  // configure MISO as output pins
  DDRB = 0x10;
  // configure BCD pins as output
  DDRC = 0x0F;
  // configure RGB cathode pins as output
  DDRD = 0x38;

  cli();
  // Enable SPI, LSB first, primary mode, default prescaler
  SPCR = 0x60;
  // Enable external interrupts on D2 on a rising edge only
  EIMSK = 0x01;
  EICRA = 0x03;
  sei();

}

void loop() {
  static unsigned char winCondition = 0; // Data we will recieve from primary Arduino
  winCondition = SPIRx(rNum);            // Sending & recieving data to primary Arduino
  switch (winCondition) {                // Using data recieved from primary Arduino, check win condition on this Arduino
    case 1: { // Red Lights (Lose)
        PORTD &= 0xC7;
        PORTD |= 0x10;
        break;
      }
    case 2: { // Green Lights (Win)
        PORTD &= 0xC7;
        PORTD |= 0x08;
        break;
      }
    case 3: { // Blue Lights (Tie)
        PORTD &= 0xC7;
        PORTD |= 0x20;
        break;
      }
    default: { // No Lights
        PORTD &= 0xC7;
        break;
      }
  }
}

unsigned char SPIRx(unsigned char dataToSend) {
  // Data will transfer when SPDR is written to
  SPDR = dataToSend;

  // Wait until transfer is complete
  while (!(SPSR & (1 << 7)));
  return SPDR;
}

ISR(INT0_vect) {
  rNum = random(1, 10);
  PORTC = (PORTC &= 0x0F) = rNum;
}
