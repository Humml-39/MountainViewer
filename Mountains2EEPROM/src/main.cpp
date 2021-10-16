#include <Arduino.h>
//Program to write the Mountain Data to the EEPROM
//by Johannes Humml
void setup() {
  Serial.begin(9600);
  delay(100);
  Serial.println("Start");
}

String mountain, longitude, latitude, altitude, mountain2, longitude2, latitude2, altitude2;
int lon, lat, alt;

void loop() {
  while(Serial.available()){
    if (Serial.readStringUntil(',')=="st")
    {    
      //Daten1
      mountain = Serial.readStringUntil(',');
      Serial.println(mountain);
      longitude = Serial.readStringUntil(',');
      Serial.println(longitude);
      latitude = Serial.readStringUntil(',');
      Serial.println(latitude);
      altitude = Serial.readStringUntil(',');
      Serial.println(altitude);
      //Daten2
      mountain2 = Serial.readStringUntil(',');
      Serial.println(mountain2);
      longitude2 = Serial.readStringUntil(',');
      lon = longitude2.toDouble() * 10000;
      Serial.println(lon);
      latitude2 = Serial.readStringUntil(',');
      lat = latitude2.toDouble() * 10000;
      Serial.println(lat);
      altitude2 = Serial.readStringUntil(',');
      alt = altitude2.toInt();
      Serial.println(alt);

      if(mountain==mountain2 && longitude==longitude2 && altitude==altitude2 && latitude==(latitude2)){
        Serial.println("OK");
        
      }else{
        Serial.println("Error trying again...");
      }
    }
  }
}