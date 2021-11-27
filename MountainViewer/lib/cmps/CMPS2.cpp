#define DECLINATION 4.55 // declination (in degrees).

/************************************************************************/

#include <Wire.h> //including library for I2C communication

#include "CMPS2.h"

unsigned char CMPS2_address = 0x30; //I2C Caddress of the device

float data[3];
unsigned int raw[3];
float offset[3];


void CMPS_decodeHeading(float angle) {
  //decoding heading angle according to datasheet
  if (angle > 337.25 | angle < 22.5) {
    Serial.println("North");
  }
  else if (angle > 292.5) {
    Serial.println("North-West");
  }
  else if (angle > 247.5) {
    Serial.println("West");
  }
  else if (angle > 202.5) {
    Serial.println("South-West");
  }
  else if (angle > 157.5) {
    Serial.println("South");
  }
  else if (angle > 112.5) {
    Serial.println("South-East");
  }
  else if (angle > 67.5) {
    Serial.println("East");
  }
  else {
    Serial.println("North-East");
  }
}

void CMPS_read_XYZ(void);

float CMPS_getHeading(void) {
  CMPS_read_XYZ();  //read X, Y, Z data of the magnetic field

  //eliminate offset before continuing
  for (int i=0;i<3;i++)
  {
    data[i] = data[i]-offset[i];
  }
  
  //variables for storing partial results
  float temp0 = 0;
  float temp1 = 0;
  //and for storing the final result
  float deg = 0;

  //calculate heading from data of the magnetic field
  //the formula is different in each quadrant
  if (data[0] < 0)
  {
    if (data[1] > 0)
    {
      //Quadrant 1
      temp0 = data[1];
      temp1 = -data[0];
      deg = 90 - atan(temp0 / temp1) * (180 / 3.14159);
    }
    else
    {
      //Quadrant 2
      temp0 = -data[1];
      temp1 = -data[0];
      deg = 90 + atan(temp0 / temp1) * (180 / 3.14159);
    }
  }
  else {
    if (data[1] < 0)
    {
      //Quadrant 3
      temp0 = -data[1];
      temp1 = data[0];
      deg = 270 - atan(temp0 / temp1) * (180 / 3.14159);
    }
    else
    {
      //Quadrant 4
      temp0 = data[1];
      temp1 = data[0];
      deg = 270 + atan(temp0 / temp1) * (180 / 3.14159);
    }
  }

  //correct heading
  deg += DECLINATION;
  if (DECLINATION > 0)
  {
    if (deg > 360) {
      deg -= 360;
    }
  }
  else
  {
    if (deg < 0) {
      deg += 360;
    }
  }

  return deg;
}

//reads measurements in mG
void CMPS_read_XYZ(void) {
  //initialize array for data

  //command internal control register 0 bit 0 (measure)
  Wire.beginTransmission(CMPS2_address);
  Wire.write(0x07);
  Wire.write(0x01);
  Wire.endTransmission();
  delay(8);

  //wait for measurement to be completed
  bool flag = false;
  while (!flag) {
    //jump to status register
    Wire.beginTransmission(CMPS2_address);
    Wire.write(0x06);
    Wire.endTransmission();

    //read its value
    Wire.requestFrom(CMPS2_address, (uint8_t)1);
    int temporal = 0;
    if (Wire.available()) {
      temporal = Wire.read();
    }

    //if the last bit is 1, data is ready
    temporal &= 1;
    if (temporal != 0) {
      flag = true;
    }
  }

  //move CMPS2_address pointer to first CMPS2_address
  Wire.beginTransmission(CMPS2_address);
  Wire.write(0x00);
  Wire.endTransmission();

  //save data
  Wire.requestFrom(CMPS2_address, (uint8_t)6);
  byte tmp[6] = {0, 0, 0, 0, 0, 0}; //array for raw data
  if (Wire.available()) {
    for (int i = 0; i < 6; i++) {
      tmp[i] = Wire.read(); //save it
    }
  }

  //reconstruct raw data
  raw[0] = tmp[1] << 8 | tmp[0]; //x
  raw[1] = tmp[3] << 8 | tmp[2]; //y
  raw[2] = tmp[5] << 8 | tmp[4]; //z

  //convert raw data to mG
  for (int i = 0; i < 3; i++) {
    data[i] = 0.48828125 * (float)raw[i];
  }
}

//initialize the compass
//Update: this should follow Calibration steps
void CMPS_init(void) {
  float out1[3];
  float out2[3];
  int i;
  
  Wire.begin(); // initialization of I2C bus

  //calibration: SET
  Wire.beginTransmission(CMPS2_address);
  Wire.write(0x07);
  Wire.write(0x80);
  Wire.endTransmission();
  delay(60);

  Wire.beginTransmission(CMPS2_address);
  Wire.write(0x07);
  Wire.write(0x20);
  Wire.endTransmission();
  delay(10);

  CMPS_read_XYZ();
  for (i=0;i<3;i++)
  {
    out1[i] = data[i];
  }
  Serial.print("Raw SET = ");
  Serial.print(raw[0]);
  Serial.print("\t");
  Serial.print(raw[1]);
  Serial.print("\t");
  Serial.println(raw[2]);
  
  //calibration: RESET
  Wire.beginTransmission(CMPS2_address);
  Wire.write(0x07);
  Wire.write(0x80);
  Wire.endTransmission();
  delay(60);

  Wire.beginTransmission(CMPS2_address);
  Wire.write(0x07);
  Wire.write(0x40);
  Wire.endTransmission();
  delay(10);

  CMPS_read_XYZ();
  for (i=0;i<3;i++)
  {
    out2[i] = data[i];
  }

  Serial.print("Raw RESET = ");
  Serial.print(raw[0]);
  Serial.print("\t");
  Serial.print(raw[1]);
  Serial.print("\t");
  Serial.println(raw[2]);

  //offset calculation
  for (i=0;i<3;i++)
  {
    offset[i] = (out1[i]+out2[i])*0.5;
  } 

  //command internal control register 0 for set operation
  Wire.beginTransmission(CMPS2_address);
  Wire.write(0x07);
  Wire.write(0x40); //SET
  Wire.endTransmission();
  delay(10);

  //command internal control register 1 to 16 bit resolution, 8ms measurement time
  Wire.beginTransmission(CMPS2_address);
  Wire.write(0x08); 
  Wire.write(0x00);
  Wire.endTransmission();
  delay(10);
}