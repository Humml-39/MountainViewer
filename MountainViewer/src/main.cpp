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
  
  Serial.begin(9600); // Serial Com
  new_array(47.272125,9.631086);
  Serial.print("\nberechnung fertig");
  int berg = auswertung(10);
  Serial.print("\n");
  Serial.print(mountains_new[berg].name);
  Serial.print("\n");
  Serial.print(mountains_new[berg].height);
  delay(10);
  CMPS_init(); //initialize the compass
  setup_display();
  
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
  int berg = auswertung(angle);
  String nameb = mountains_new[berg].name;
  clear_disp();
  to_display(1.5,10,10,nameb);
  to_display(1.5,10,20,String(mountains_new[berg].height));
  print_disp();

  CMPS_decodeHeading(angle);  //get direction


  DEBUG_PORT.print("\nberechnung fertig");
  DEBUG_PORT.print("\n");
  DEBUG_PORT.print(mountains_new[berg].name);
  DEBUG_PORT.print("\n");
  DEBUG_PORT.print(mountains_new[berg].height);
}
