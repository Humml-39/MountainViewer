///// Vorlage: https://create.arduino.cc/projecthub/banitama/using-digilent-pmod-cmps2-on-arduino-a2e340

#ifndef CMPS2_h
#define CMPS2_h

#include "Arduino.h"


extern void CMPS_decodeHeading(float angle);
extern float CMPS_getHeading(void);
extern void CMPS_read_XYZ(void);
extern void CMPS_init(void);


#endif
