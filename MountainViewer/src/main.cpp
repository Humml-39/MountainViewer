#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Disp.h>


void setup() {
  setup2();
  testdrawchar(2,0,0,"Spar spar");      // Draw characters of the default font
  
}

void loop() {
}
