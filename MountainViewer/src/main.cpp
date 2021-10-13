#include <Arduino.h>
/*#include <NMEAGPS.h>
#include <GPSport.h>
#include <Streamers.h>
static NMEAGPS  gps;
static gps_fix  fix;

void setup() {
  Serial1.begin(9600);
}
void loop(){
  // put your main code here, to run repeatedly:

}*/

#include <NMEAGPS.h>

#include <GPSport.h>

#include <Streamers.h>


static NMEAGPS  gps;

static gps_fix  fix;


static void doSomeWork()
{
  // Print all the things!

  trace_all( DEBUG_PORT, gps, fix );

} // doSomeWork

static void GPSloop()
{
  while (gps.available( gpsPort )) {
    fix = gps.read();
    doSomeWork();
  }

} // GPSloop


void setup()
{
  DEBUG_PORT.begin(9600);
  while (!DEBUG_PORT)
    ;


  trace_header( DEBUG_PORT );
  DEBUG_PORT.flush();

  gpsPort.begin( 9600 );
}


void loop()
{
  GPSloop();
}
