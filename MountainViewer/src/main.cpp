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
#include <rtc_clock.h>

#include <GPSport.h>

RTC_clock rtc_clock(XTAL);

void modi_kompass();
void modi_normal();
void modi_Uhrzeit();

NMEAGPS  gps; // This parses the GPS characters
gps_fix  fix; // This holds on to the latest values

double angle;

String nameb;

int berg;
int modi = 0;
int Tasterpin = 22;

int hours = 0;
int minutes = 0;
String Uhrzeit = "0:0";

void setup()
{
  
  Serial.begin(9600); // Serial Com

  delay(10);
  CMPS_init(); //initialize the compass
  setup_display();
  
  rtc_clock.init();
  
  //testdrawchar(2,0,0,"Spar spar");      // Draw characters of the default font
  // GPS
  
  while (!DEBUG_PORT)
    ;
  DEBUG_PORT.print( F("Let's GO!\n") );
  
  gpsPort.begin(9600); // Serial GPS
  
  clear_disp();
  to_display(1.5,10,10,"Bitte etwas Geduld");
  to_display(1.5,10,20,"Satellit suchen");
  print_disp();
  
  
  while (!fix.valid.location)
  {
    while (gps.available( gpsPort )) {
      fix = gps.read();
      
      /*DEBUG_PORT.print( F("Location: ") );
      if (fix.valid.location) {
        DEBUG_PORT.print( fix.latitude(), 6 );
        DEBUG_PORT.print( ',' );
        DEBUG_PORT.print( fix.longitude(), 6 );
          
      }*/

    }
  }

   
   
  
  hours = fix.dateTime.hours;
  minutes = fix.dateTime.minutes; 
  new_array(fix.latitude(),fix.longitude()); 

  rtc_clock.set_time(hours+1, minutes,0);

  pinMode(Tasterpin,INPUT);
  digitalWrite(Tasterpin,HIGH);  
}


void loop() {

  delay(250);

  //GPS Routine
  
  while (gps.available( gpsPort )) {
    fix = gps.read();
  }
  

  //retrieving and displaying the heading of the compass
  
  angle = CMPS_getHeading();
  
  berg = auswertung(angle);
  nameb = mountains_new[berg].name;
  
  if(digitalRead(Tasterpin)==LOW){
    modi++;
    delay(200);
    if(modi == 4){
      modi = 0;
    }
  }
  DEBUG_PORT.print(modi);
  if(modi == 0){
    modi_normal();
  }
  else if(modi == 1){
    modi_kompass();
  }
  else{
    modi_Uhrzeit();
  }
  
  

}

void modi_kompass(){
  clear_disp();
  
  if (337.5<angle||angle <22.5)
  {
    to_display(1.5,10,10,"N");
  }
  else if (angle<=67.5)
  {
    to_display(1.5,10,10,"N/O");
  }
  else if (angle<=112.5)
  {
    to_display(1.5,10,10,"O");
  }
  else if (angle<=157.5)
  {
    to_display(1.5,10,10,"S/O");
  }
  else if (angle<=202.5)
  {
    to_display(1.5,10,10,"S");
  }
  else if (angle<=247.5)
  {
    to_display(1.5,10,10,"S/W");
  }
  else if (angle<=292.5)
  {
    to_display(1.5,10,10,"W");
  }
  else //if (292.5<angle||angle<=337.5)
  {
    to_display(1.5,10,10,"N/W");
  }
  

  to_display(1.5,10,20,String(angle));
  print_disp();

}

void modi_normal(){
  
  clear_disp();
  to_display(1.5,10,10,nameb);
  to_display(1.5,10,20,String(mountains_new[berg].height));
  print_disp();

}

void modi_Uhrzeit(){
  clear_disp();
  to_display(1.5,10,10,String(rtc_clock.get_hours())+":"+String(rtc_clock.get_minutes()));
  to_display(1.5,10,20,"MV - V 0.9");
  print_disp();
  
}

