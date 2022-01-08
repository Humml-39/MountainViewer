#include <Wire.h> //including library for I2C communication
#include <Arduino.h>
#include <CMPS2.h>
#include <Mymath.h>
#include <mountains.h>
#include <NMEAGPS.h>
#include <Streamers.h>
#include <SPI.h>
#include <Disp.h>
#include <math.h>


#include <GPSport.h>

NMEAGPS  gps; // This parses the GPS characters
gps_fix  fix; // This holds on to the latest values


void setup()
{
  
  DEBUG_PORT.begin(9600); // DEBUG_PORT Com
  new_array(47.353331,9.645514);
  DEBUG_PORT.print("\nberechnung fertig");
  int berg = auswertung(175);
  DEBUG_PORT.print("\n");
  DEBUG_PORT.print(mountains_new[berg].name);
  DEBUG_PORT.print("\n");
  DEBUG_PORT.print(mountains_new[berg].height);
  delay(10);
  CMPS_init(); //initialize the compass
  setup2();
  //testdrawchar(2,0,0,"Spar spar");      // Draw characters of the default font
  // GPS
  
  while (!DEBUG_PORT)
    ;
  DEBUG_PORT.print( F("Let's GO!\n") );

  gpsPort.begin(9600); // DEBUG_PORT GPS
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
  DEBUG_PORT.print("Heading = ");
  DEBUG_PORT.print(angle);
  DEBUG_PORT.print("°");
  DEBUG_PORT.print('\t');
  String anglesss = String(angle,3);
  testdrawchar(2,0,0,anglesss);
  CMPS_decodeHeading(angle);  //get direction


  DEBUG_PORT.print("\nberechnung fertig");
  int berg = auswertung(angle);
  DEBUG_PORT.print("\n");
  DEBUG_PORT.print(mountains_new[berg].name);
  DEBUG_PORT.print("\n");
  DEBUG_PORT.print(mountains_new[berg].height);
}
