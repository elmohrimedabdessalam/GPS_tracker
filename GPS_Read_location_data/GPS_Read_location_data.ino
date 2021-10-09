#include "Wire.h"

#define EEPROM_I2C_ADDRESS 0x50

int address = 0, y = 0, j = 0;
uint16_t x;
void setup() {

  Wire.begin();
  Serial.begin(115200);

  x = readByte (0) + shiftByte (readByte (1), 1);

  for (int i = 0; i <= x; i++) {

    Serial.print(getData(4 * j + 2) / 1E6, 10);
    Serial.print("  ");
    Serial.println(getData(4 * j + 6) / 1E6, 10);
    j +=2;

  }
}

void loop() {}


unsigned long shiftByte (byte r, byte p) {//shiftByte (NB wanted to shift, how much shift per 8)
  unsigned long f = r;
  for (byte t = 0; t < p; t++) {
    f = f << 8;
  }
  return f;
}
byte readByte (int address) {
  byte y = 0;


  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  Wire.write((int)(address >> 8));   // MSB
  Wire.write((int)(address & 0xFF)); // LSB
  Wire.endTransmission();
  Wire.requestFrom(EEPROM_I2C_ADDRESS, 1);
  y = Wire.read();
  return y;
}

unsigned long getData(int y) {
  unsigned long z, u = 0;
  byte m = 0, x;
  for (int i = y ; i < y + 4; i++ ) {
    x = readByte(i);
    z = shiftByte (x, m);
    u = u + z;
    m++;
  }
  return u;
}
