#include <RH_ASK.h>
#include <Wire.h>

#define address 0x1E
#define PACKET_SIZE sizeof(int)

//speed, Rx pin, Tx pin
RH_ASK driver(2000, 4, 3);

typedef union I2C_Packet_t {
  int heading;
  uint8_t heading_bytes[PACKET_SIZE];
};

int last_heading = -10;
const int THRESHOLD = 2;

void setup()
{
  Serial.begin(9600);    // Debugging only
  if (!driver.init())
    Serial.println("init failed");
  else
    Serial.println("init done!");

  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
 
  Wire.begin();
  Wire.beginTransmission(address); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();
}

void loop()
{

  I2C_Packet_t compassInfo;
  compassInfo.heading = getCompassData();
  
  Serial.print("heading: ");
  Serial.println(compassInfo.heading);

  if ((compassInfo.heading > last_heading + THRESHOLD) || (compassInfo.heading < last_heading - THRESHOLD))
  {
    last_heading = compassInfo.heading;
    driver.send(compassInfo.heading_bytes, sizeof(compassInfo.heading_bytes));
    driver.waitPacketSent();
  }
  
  delay(1000);
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
