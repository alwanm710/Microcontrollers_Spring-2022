/*
  Lab 9, Circuit 2
  By: Jack, Cesar, Mohammed
  Written: 4/6/22
  Edited: 4/11/22
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
  D9:
  D10: SH/LD on 74165
  D11:
  D12: QH on 74165
  D13: CLK on 74165
*/

void setup() {
  // configure SCK, MOSI and SS as output pins
  DDRB = 0x24;
  // write secondary select high (inhibits data transfer)
  PORTB &= 0xFB;

  cli();
  // Enable SPI, LSB first, primary mode, default prescaler
  SPCR = 0x70;
  sei();
}

void loop() {
  static unsigned char dipData = 0;
  static unsigned char oldDipData = 0;

  // Set D10
  PORTB |= 0x04;

  dipData = SPIRx(0);
  if (dipData != oldDipData)
  {
    oldDipData = dipData;
  }
  // Clear D10
  PORTB &= 0xFB;
}

unsigned char SPIRx(unsigned char dataToWrite) {


  // Data will transfer when SPDR is written to
  SPDR = dataToWrite;

  // Wait until transfer is complete
  //Serial.println(SPSR & 0x80);
  while (!(SPSR & (1 << 7)));
  return SPDR;

}
