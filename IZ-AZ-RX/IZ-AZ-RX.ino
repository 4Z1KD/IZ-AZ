/*
 * IZ-AZ
 * Easy Azimuth display for amature radio antenna rotators
 * 
 * RX module
 * You can find the required libraries on https://github.com/4Z1KD/IZ-AZ
 * 
 * Assembly info:
 * By default
 * Receiver data pin is D11
 * LCD SDA pin is A4
 * LCD CLK pin is A5
 */
#include <RH_ASK.h>
#include "DisplayService.h"
#include <LiquidCrystal_I2C.h>
#include <SPI.h> // Not actualy used but needed to compile

#define PACKET_SIZE sizeof(int)

int OFFSET = 0;

RH_ASK driver;
LiquidCrystal_I2C lcdx(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);
DisplayService dispServe(&lcdx);

typedef union I2C_Packet_t {
  int heading;
  uint8_t heading_bytes[PACKET_SIZE];
};

void setup()
{
  dispServe.Init();
  pinMode(2,OUTPUT);
  digitalWrite(2, HIGH);
  Serial.begin(9600);  // Debugging only
  if (!driver.init())
    Serial.println("init failed");
  dispServe.Blink(1);
  dispServe.Log11("IZ-AZ       v1.1 ", 0, 0, 0, 500);
}

void loop()
{
  I2C_Packet_t compassInfo;

  uint8_t byteArray[PACKET_SIZE];
  uint8_t data[PACKET_SIZE];
  uint8_t len = sizeof(data);

  if (driver.recv(data, &len))
  {
    for (int k = 0; k < PACKET_SIZE; k++)
    {
      compassInfo.heading_bytes[k] = data[k];
    }
    // Correct for when signs are reversed.
    if (compassInfo.heading < 0)
      compassInfo.heading += 2 * 180;

    String az = String((compassInfo.heading + OFFSET) % 360);
    dispServe.Log("                ", 0, 1, 0);
    dispServe.Log("Azimuth: " + az, 0, 1, 0);
    Serial.println("AZ:" + az + ".0");
  }
}
