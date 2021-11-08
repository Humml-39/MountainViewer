#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>
#include "disp.h"

void testdrawchar(char Textsize,char cursor1, char cursor2, String buchstabe);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
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