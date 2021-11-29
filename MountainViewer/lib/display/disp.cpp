#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>
#include "disp.h"

void testdrawchar(char Textsize,char cursor1, char cursor2, String buchstabe);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define splash_width 120      //115
#define splash_height 32       //32

  const uint8_t PROGMEM splash_data [] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x05, 0x00, 0x00, 0x78, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 
  0x00, 0x00, 0x0f, 0x80, 0x00, 0x78, 0x38, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x40, 0x00, 
  0x00, 0x00, 0x18, 0xc0, 0x00, 0x38, 0x78, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x30, 0xc0, 0x00, 0x6c, 0x58, 0x3e, 0x38, 0xc7, 0x78, 0xfc, 0xf8, 0xe3, 0x78, 
  0x00, 0x00, 0x20, 0x40, 0x00, 0x2c, 0x58, 0x63, 0x18, 0x63, 0x98, 0x61, 0x8c, 0x61, 0x8c, 
  0x00, 0x00, 0x60, 0x60, 0x00, 0x66, 0x98, 0xc3, 0x18, 0xc3, 0x18, 0x60, 0x0c, 0x63, 0x8c, 
  0x00, 0x00, 0xc0, 0x60, 0x00, 0x26, 0x98, 0xc1, 0x98, 0x63, 0x0c, 0x60, 0xac, 0x61, 0x8c, 
  0x00, 0x40, 0xc0, 0x30, 0x00, 0x67, 0x98, 0xc3, 0x18, 0xc3, 0x18, 0x61, 0x9c, 0x63, 0x0c, 
  0x00, 0xe1, 0x80, 0x30, 0x00, 0x23, 0x18, 0xe1, 0x98, 0x63, 0x0c, 0x63, 0x0c, 0x61, 0x8c, 
  0x01, 0xb3, 0x00, 0x10, 0x00, 0x61, 0x18, 0x63, 0x1d, 0xc3, 0x18, 0x6b, 0x9c, 0x63, 0x0c, 
  0x03, 0x17, 0x00, 0x18, 0x00, 0x70, 0x1c, 0x3c, 0x0e, 0x67, 0x9c, 0x39, 0xec, 0x73, 0x8e, 
  0x03, 0x1c, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x02, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x06, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x06, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x04, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x0c, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x0c, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x08, 0x00, 0x00, 0x02, 0x00, 0xa0, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x18, 0x00, 0x00, 0x02, 0x00, 0xe0, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x18, 0x00, 0x00, 0x03, 0x00, 0x60, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x10, 0x00, 0x00, 0x01, 0x00, 0x60, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x30, 0x00, 0x00, 0x01, 0x00, 0x31, 0x86, 0x1b, 0x1c, 0x63, 0x8d, 0x8e, 0xe0, 0x00, 0x00, 
  0x30, 0x00, 0x00, 0x01, 0x80, 0x31, 0x06, 0x31, 0x98, 0x61, 0x18, 0xc6, 0x40, 0x00, 0x00, 
  0x20, 0x00, 0x00, 0x00, 0x80, 0x39, 0x06, 0x31, 0xcc, 0xf3, 0x30, 0xc6, 0x00, 0x00, 0x00, 
  0x60, 0x00, 0x00, 0x00, 0x80, 0x1b, 0x06, 0x7f, 0x8c, 0xb2, 0x3f, 0xcc, 0x00, 0x00, 0x00, 
  0x20, 0x00, 0x00, 0x00, 0x00, 0x1a, 0x06, 0x30, 0x06, 0x9a, 0x30, 0x06, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x06, 0x30, 0x07, 0x1c, 0x38, 0x0c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x06, 0x3b, 0x87, 0x1c, 0x1d, 0x86, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x07, 0x0e, 0x02, 0x08, 0x07, 0x0e, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  };



// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup2() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.

  display.clearDisplay();
  display.drawBitmap((SCREEN_WIDTH - splash_width) / 2, (SCREEN_HEIGHT - splash_height) / 2,splash_data, splash_width, splash_height, 1);
  display.display();
  delay(2000); // Pause for 2 seconds
  
  // Clear the buffer
  display.clearDisplay();
  delay(2000);

  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display(). These examples demonstrate both approaches...
  //testdrawchar(2,0,0,"Spar spar");      // Draw characters of the default font
  
}


void testdrawchar(char Textsize,char cursor1, char cursor2, String buchstabe) {
  char x=buchstabe.length()+1;    //lenge des Strings von 1 beginend
  char buf[buchstabe.length()];   //Char array erstellen
  
  display.clearDisplay();   //Dislay clearen

  display.setTextSize(Textsize);        //Textgröße auswählen
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(cursor1, cursor2);  //cursor auf position x y setzen

  buchstabe.toCharArray(buf,x); //Sring in Char array umwandel
  for (int16_t i = 0; i <= buchstabe.length(); i++) //für jedes zeichen ausgeben
  {
    display.write(buf[i]);
  }

  display.display();  //Text im Display ausgeben
  delay(2000);
}