#include <Arduino.h>
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
/*
//String berge[];
void loop(){
  //mountains[0].name;
//--------------------------
*/
void loop()
{
  // GPS
  while (gps.available( gpsPort )) {
    fix = gps.read();

    DEBUG_PORT.print( F("Location: ") );
    if (fix.valid.location) {
      DEBUG_PORT.print( fix.latitude(), 6 );
      DEBUG_PORT.print( ',' );
      DEBUG_PORT.print( fix.longitude(), 6 );
    }

    DEBUG_PORT.println();

  // ------------
  }
}
