#include <Wire.h> //including library for I2C communication
#include <Arduino.h>
#include <CMPS2.h>


//unsigned char CMPS2_address = 0x30; //I2C address of the device
//void CMPS2_decodeHeading(float angle);
//float CMPS2_getHeading(void);
//void CMPS2_read_XYZ(void);
//void CMPS2_init(void);
Compass compi;
void setup() {
  
  Serial.begin(9600,SERIAL_8N1); //serial initialization
  Wire.setClock(10000);
  delay(10);
  compi.CMPS_init(); //initialize the compass
  
#include <mountains.h>


#include <NMEAGPS.h>
#include <GPSport.h>
#include <Streamers.h>

#include <SPI.h>
#include <Wire.h>
#include <Disp.h>

NMEAGPS  gps; // This parses the GPS characters
gps_fix  fix; // This holds on to the latest values

void setup()
{
  setup2();
  testdrawchar(2,0,0,"Spar spar");      // Draw characters of the default font
  // GPS
  DEBUG_PORT.begin(9600);
  while (!Serial)
    ;
  DEBUG_PORT.print( F("Let's GO!\n") );

  gpsPort.begin(9600);
  // ------------
}

void loop() {
  delay(250);
  
  //retrieving and displaying the heading of the compass
  float angle = compi.CMPS_decodeHeading();
  Serial.print("Heading = ");
  Serial.print(angle);
  Serial.print("°");
  Serial.print('\t');

  
  Compass.CMPS_decodeHeading(angle);  //get direction
}
