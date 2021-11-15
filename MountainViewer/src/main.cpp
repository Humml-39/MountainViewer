#include <Arduino.h>
#include <mountains.h>


#include <NMEAGPS.h>
#include <GPSport.h>
#include <Streamers.h>

#include <Wire.h>

NMEAGPS  gps; // This parses the GPS characters
gps_fix  fix; // This holds on to the latest values

void setup()
{
  Serial.begin(9600);
  // GPS
  DEBUG_PORT.begin(9600);
  while (!Serial)
    ;
  DEBUG_PORT.print( F("Let's GO!\n") );

  gpsPort.begin(9600);
  // ------------

  Wire.begin();

}
unsigned int X=0;
int ready;
char c=0;
/*
//String berge[];
void loop(){
  //mountains[0].name;
//--------------------------
*/


void loop()
{
  /*
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
  
  */
  // ------------
  delay(10);
  Wire.beginTransmission(0x30); //start transmission with Adress 0x30 = Compass
  Wire.write(0x07); //Control Register 0
  Wire.write(0x01); //initiate data acquisition
  Wire.endTransmission(); //stop
  delay(9);


  while (ready==0)
  {
    Wire.beginTransmission(0x30); //start transmission with Adress 0x30 = Compass
    Wire.write(0x06); //Status Register      //0x06 im datenblatt ????
    Wire.requestFrom(0x31,1);
    while (Wire.available())
    {
      int c = Wire.read();
    }
    if ((c&0x1)==0x1)
    {
      ready=1;
    }
    //Serial.println(ready);
  }
  ready=0;

  Wire.beginTransmission(0x30); //start transmission with Adress 0x30 = Compass
  Wire.write(0x00); //Status Register

  Wire.requestFrom(0x31,1);
  while (Wire.available()){
    X = Wire.read();
  }
  Wire.endTransmission();
  /*
  X = Wire.read()<<8;
  unsigned int Y = Wire.read();
  Y = Wire.read()<<8;

  DEBUG_PORT.println(X);*/
  DEBUG_PORT.println(X);
}