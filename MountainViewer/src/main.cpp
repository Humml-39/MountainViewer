#include <Wire.h> //including library for I2C communication
#include <Arduino.h>
#include <CMPS2.h>
#include <mountains.h>
#include <NMEAGPS.h>
#include <Streamers.h>
#include <SPI.h>
#include <Disp.h>

#include <GPSport.h>

NMEAGPS  gps; // This parses the GPS characters
gps_fix  fix; // This holds on to the latest values


void setup()
{
  
  Serial.begin(9600); // Serial Com
  Wire.setClock(10000);
  delay(10);
  compi.CMPS_init(); //initialize the compass
  setup2();
  testdrawchar(2,0,0,"Spar spar");      // Draw characters of the default font
  // GPS
  
  while (!Serial)
    ;
  Serial.print( F("Let's GO!\n") );

  Serial1.begin(9600); // Serial GPS
  // ------------
}

void loop() {
  delay(250);
  
  //retrieving and displaying the heading of the compass
  float angle = compi.CMPS_getHeading();
  Serial.print("Heading = ");
  Serial.print(angle);
  Serial.print("°");
  Serial.print('\t');

  compi.CMPS_decodeHeading(angle);  //get direction
}
