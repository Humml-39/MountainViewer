#include <Wire.h> //including library for I2C communication
#include <Arduino.h>
#include <CMPS2.h>


//unsigned char CMPS2_address = 0x30; //I2C address of the device
//void CMPS2_decodeHeading(float angle);
//float CMPS2_getHeading(void);
//void CMPS2_read_XYZ(void);
//void CMPS2_init(void);

void setup() {
  Serial.begin(9600,SERIAL_8N1); //serial initialization
  Wire.setClock(10000);
  delay(10);
  Compass.CMPS_init(); //initialize the compass
  
}

void loop() {
  delay(250);
  
  //retrieving and displaying the heading of the compass
  float angle = CMPS_getHeading();
  Serial.print("Heading = ");
  Serial.print(angle);
  Serial.print("°");
  Serial.print('\t');

  Compass.CMPS_decodeHeading(angle);  //get direction
}