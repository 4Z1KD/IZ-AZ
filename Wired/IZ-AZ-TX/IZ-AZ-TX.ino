/*
   IZ-AZ
   Easy Azimuth display for amature radio antenna rotators

   TX module
   You can find the required libraries on https://github.com/4Z1KD/IZ-AZ

   Assembly info:
   compass i2c pins are A4 & A5
   Transmitter data pin is D3

   Developers: Avi 4Z1IZ, Gil 4Z1KD
*/

#include <AltSoftSerial.h>
#include <Wire.h>

#define address 0x1E
#define PACKET_SIZE sizeof(int)

AltSoftSerial altSerial;

int last_heading = -10;
const int THRESHOLD = 2;

typedef union {
  int heading;
  uint8_t heading_bytes[PACKET_SIZE];
} I2C_Packet_t;

void setup() {
  Serial.begin(9600);
  altSerial.begin(9600);

  Wire.begin();
  Wire.beginTransmission(address); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();
}

void loop() {
  I2C_Packet_t compassInfo;  
  compassInfo.heading = getCompassData();

  altSerial.write(compassInfo.heading_bytes, PACKET_SIZE);
  Serial.print(String(compassInfo.heading));

  delay(2000);
}


int getCompassData()
{
  int x, y, z;

  //Tell the HMC5883L where to begin reading data
  Wire.beginTransmission(address);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();

  //Read data from each axis, 2 registers per axis
  Wire.requestFrom(address, 6);
  if (6 <= Wire.available()) {
    x = Wire.read() << 8; //X msb
    x |= Wire.read(); //X lsb
    z = Wire.read() << 8; //Z msb
    z |= Wire.read(); //Z lsb
    y = Wire.read() << 8; //Y msb
    y |= Wire.read(); //Y lsb
  }

  return int(calculateHeading(x, y));
}

float calculateHeading(int x, int y)
{
  float heading = atan2(y, x);

  float declinationAngle = 0.0843;
  heading += declinationAngle;

  // Correct for when signs are reversed.
  if (heading < 0)
    heading += 2 * PI;

  // Check for wrap due to addition of declination.
  if (heading > 2 * PI)
    heading -= 2 * PI;

  // Convert radians to degrees for readability.
  return float(heading * 180 / M_PI);
}
