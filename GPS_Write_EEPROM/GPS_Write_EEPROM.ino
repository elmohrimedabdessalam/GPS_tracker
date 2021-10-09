#include"TinyGPS++.h"
#include<SoftwareSerial.h>
#include <Wire.h>

#define EEPROM_I2C_ADDRESS 0x50           // I2C Buss address of 24LC256 256K EEPROM

SoftwareSerial serial_connection (4, 5); //Tx  Rx
TinyGPSPlus gps;

long x;
int j = 2;
uint16_t PosNb = 1;

void setup() {
  Wire.begin();                        // join I2C bus (address optional for master)
  serial_connection.begin(9600);
}

void loop() {

  while (serial_connection.available()) {
    gps.encode(serial_connection.read());
  }

  if (gps.location.isUpdated()) {

    x = gps.location.lat() * 1E6;
    writeAddress(j, getByte( 1, x));
    j++;
    writeAddress(j, getByte( 2, x));
    j++;
    writeAddress(j, getByte( 3, x));
    j++;
    writeAddress(j, getByte( 4, x));
    j++;

    x = gps.location.lng() * 1E6;
    writeAddress(j, getByte( 1, x));
    j++;
    writeAddress(j, getByte( 2, x));
    j++;
    writeAddress(j, getByte( 3, x));
    j++;
    writeAddress(j, getByte( 4, x));
    j++;

    writeAddress(0, getByte( 1, PosNb));
    writeAddress(1, getByte( 2, PosNb));
    PosNb++;
    delay(20000);
  }
}

void writeAddress(int address, byte val)
{
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  Wire.write((int)(address >> 8));   // MSB
  Wire.write((int)(address & 0xFF)); // LSB
  Wire.write(val);
  Wire.endTransmission();
  delay(5);
}

byte getByte( byte ByteP, long y) { // getByte( the position of byte ,the number wanted to devided)
  long m = 0xFF;
  m = m << (8 * ByteP - 8);
  y = y & m;
  byte b = y >> (8 * ByteP - 8);
  return b;
}
