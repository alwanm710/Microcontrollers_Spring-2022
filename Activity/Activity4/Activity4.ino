void setup() {
  // put your setup code here, to run once:
  DDRD = 0x7F;
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned char a[16] = {0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B, 0x77, 0x1F, 0x4E, 0x3D, 0x4F, 0x47};
  for (unsigned char i=0; i < 16; i++)
  {
    PORTD &= 0x00;
    PORTD ^= a[i];
    _delay_ms(1000);
  }






}
