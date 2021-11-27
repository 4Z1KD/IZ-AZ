/*
    IZ-AZ
    Easy Azimuth display for amature radio antenna rotators

    RX module
    You can find the required libraries on https://github.com/4Z1KD/IZ-AZ

    Assembly info:
    Receiver data pin is D11
    LCD SDA pin is A4
    LCD CLK pin is A5

    Developers: Avi 4Z1IZ, Gil 4Z1KD
*/

#include "DisplayService.h"
#include <LiquidCrystal_I2C.h>
#include <SPI.h> // Not actualy used but needed to compile
#include <AltSoftSerial.h>

#define PACKET_SIZE sizeof(int)

int OFFSET = 0;
AltSoftSerial altSerial;

LiquidCrystal_I2C lcdx(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);
DisplayService dispServe(&lcdx);

typedef union {
  int heading;
  uint8_t heading_bytes[PACKET_SIZE];
} I2C_Packet_t;

void setup()
{
  dispServe.Init();
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  Serial.begin(9600);  // Debugging only
  altSerial.begin(9600);
  dispServe.Blink(1);
  dispServe.Log11("IZ-AZ       v1.1 ", 0, 0, 0, 100);
}

void loop()
{
  I2C_Packet_t compassInfo;

  if (altSerial.available())
  {
    altSerial.readBytes(compassInfo.heading_bytes, PACKET_SIZE);
    // Correct for when signs are reversed.
    if (compassInfo.heading < 0)
      compassInfo.heading += 2 * 180;

    String az = String((compassInfo.heading + OFFSET) % 360);
    dispServe.Log("                ", 0, 1, 0);
    dispServe.Log("Azimuth: " + az, 0, 1, 0);
    Serial.println("AZ:" + az + ".0");
  }
}
