///// Vorlage: https://create.arduino.cc/projecthub/banitama/using-digilent-pmod-cmps2-on-arduino-a2e340

#ifndef CMPS2_h
#define CMPS2_h

#include "Arduino.h"

class Compass
{

  public:
    void CMPS_decodeHeading(float angle);
    float CMPS_getHeading(void);
    void CMPS_read_XYZ(void);
    void CMPS_init(void);
  private:
    int angle;
};


#endif
