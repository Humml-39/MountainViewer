#include <Wire.h> //including library for I2C communication
#include <Arduino.h>
#include <CMPS2.h>
#include <mountains.h>
#include <NMEAGPS.h>
#include <Streamers.h>
#include <SPI.h>
#include <Disp.h>
#include <math.h>
#include <My_math.h>

#include <GPSport.h>

NMEAGPS  gps; // This parses the GPS characters
gps_fix  fix; // This holds on to the latest values


void setup()
{
  
  Serial.begin(9600); // Serial Com
  new_array(47.272,9.63);
  Serial.print(mountains_new[1].name);
  delay(10);
  CMPS_init(); //initialize the compass
  setup2();
  //testdrawchar(2,0,0,"Spar spar");      // Draw characters of the default font
  // GPS
  
  while (!Serial)
    ;
  Serial.print( F("Let's GO!\n") );

  gpsPort.begin(9600); // Serial GPS
  // ------------
}

void loop() {
  
  delay(250);
  
  while (gps.available( gpsPort )) {
    fix = gps.read();

    DEBUG_PORT.print( F("Location: ") );
    if (fix.valid.location) {
      DEBUG_PORT.print( fix.latitude(), 6 );
      DEBUG_PORT.print( ',' );
      DEBUG_PORT.print( fix.longitude(), 6 );
    }

  }

  //retrieving and displaying the heading of the compass
  float angle = CMPS_getHeading();
  Serial.print("Heading = ");
  Serial.print(angle);
  Serial.print("°");
  Serial.print('\t');
  String anglesss = String(angle,3);
  testdrawchar(2,0,0,anglesss);
  CMPS_decodeHeading(angle);  //get direction

}
