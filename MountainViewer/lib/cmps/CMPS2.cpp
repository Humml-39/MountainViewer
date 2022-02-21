//Based on: "Using Digilent PMOD CMPS2 on Arduino" by banitama
//https://create.arduino.cc/projecthub/banitama/using-digilent-pmod-cmps2-on-arduino-a2e340

#include <Wire.h> //Arduino I²C Library
#include "CMPS2.h"

#define declination 3.4 // Deklination in Grad

unsigned char CMPS2_address = 0x30; // Adresse des CMPS2

unsigned int raw[3]; //Variable für die so empfangenen Daten
float data[3]; //Variable für die laut Datenblatt in mG umgewandelten Daten
float offset[3];
//Größe von [3], da -> X,Y,z

 //Umwandlung Grad -> Himmelsrichtung laut Datenblatt
void CMPS_decodeHeading(float angle) {
  
  if (angle > 337.25 | angle < 22.5) {
    Serial.println("Nord");
  }
  else if (angle > 292.5) {
    Serial.println("Nord-West");
  }
  else if (angle > 247.5) {
    Serial.println("West");
  }
  else if (angle > 202.5) {
    Serial.println("Süd-West");
  }
  else if (angle > 157.5) {
    Serial.println("Süd");
  }
  else if (angle > 112.5) {
    Serial.println("Süd-Ost");
  }
  else if (angle > 67.5) {
    Serial.println("Ost");
  }
  else {
    Serial.println("Nord-Ost");
  }

}

void CMPS_read_XYZ(void);

float CMPS_getHeading(void) {
  CMPS_read_XYZ();  //Auslesen der X,Y,Z - Werte des magnetometer

  //Offset entfernen
  for (int i=0;i<3;i++)
  {
    data[i] = data[i]-offset[i];
  }
  
  // Variablen für die temporären Ergebnisse
  float temp0 = 0;
  float temp1 = 0;

  float deg = 0; //Variable für das Ergebnis

  //Für die Berechnung der Richtung muss berücksichtigt werden in welchem Quadrant sich die Blickrichung befindetet.
  if (data[0] < 0)
  {
    if (data[1] > 0)
    {
      //Quadrant 1
      temp0 = data[1];
      temp1 = -data[0];
      deg = 90 - atan(temp0 / temp1) * (180 / 3.14159);
    }
    else
    {
      //Quadrant 4
      temp0 = -data[1];
      temp1 = -data[0];
      deg = 90 + atan(temp0 / temp1) * (180 / 3.14159);
    }
  }
  else {
    if (data[1] < 0)
    {
      //Quadrant 3
      temp0 = -data[1];
      temp1 = data[0];
      deg = 270 - atan(temp0 / temp1) * (180 / 3.14159);
    }
    else
    {
      //Quadrant 2
      temp0 = data[1];
      temp1 = data[0];
      deg = 270 + atan(temp0 / temp1) * (180 / 3.14159);
    }
  }

  //Richtungskorrektur
  deg += declination;
  if (declination > 0)
  {
    if (deg > 360) {
      deg -= 360;
    }
  }
  else
  {
    if (deg < 0) {
      deg += 360;
    }
  }

  return deg;
}

//liest die Messung in mG
void CMPS_read_XYZ(void) {

  //control register 0 bit 0 (measure)
  Wire.beginTransmission(CMPS2_address);
  Wire.write(0x07);
  Wire.write(0x01);
  Wire.endTransmission();
  delay(8);

  //warten bis Messung fertig
  bool flag = false;
  while (!flag) {

    Wire.beginTransmission(CMPS2_address);
    Wire.write(0x06); //Status Register
    Wire.endTransmission();

    //Auslesen
    Wire.requestFrom(CMPS2_address, (uint8_t)1);
    int temporal = 0;
    if (Wire.available()) {
      temporal = Wire.read();
    }

    //ist das letzte Bit 1?
    temporal &= 1;
    if (temporal != 0) {
      flag = true;
    }
  }

  //der Erste Wert auslesen
  Wire.beginTransmission(CMPS2_address);
  Wire.write(0x00);
  Wire.endTransmission();

  //Daten abspeichern
  Wire.requestFrom(CMPS2_address, (uint8_t)6);
  byte tmp[6] = {0, 0, 0, 0, 0, 0}; //array for raw data
  if (Wire.available()) {
    for (int i = 0; i < 6; i++) {
      tmp[i] = Wire.read(); //save it
    }
  }

  //LSB mit MSB zusammenführen
  raw[0] = tmp[1] << 8 | tmp[0]; //x
  raw[1] = tmp[3] << 8 | tmp[2]; //y
  raw[2] = tmp[5] << 8 | tmp[4]; //z

  //in mG umrechnen
  for (int i = 0; i < 3; i++) {
    data[i] = 0.48828125 * (float)raw[i];
  }
}

void CMPS_init(void) {
  float out1[3];
  float out2[3];
  int i;
  
  Wire.begin(); // I²C initialisieren

  //calibration: SET
  Wire.beginTransmission(CMPS2_address);
  Wire.write(0x07);
  Wire.write(0x80);
  Wire.endTransmission();
  delay(60);

  Wire.beginTransmission(CMPS2_address);
  Wire.write(0x07);
  Wire.write(0x20);
  Wire.endTransmission();
  delay(10);

  CMPS_read_XYZ();
  for (i=0;i<3;i++)
  {
    out1[i] = data[i];
  }
  Serial.print("Raw SET = ");
  Serial.print(raw[0]);
  Serial.print("\t");
  Serial.print(raw[1]);
  Serial.print("\t");
  Serial.println(raw[2]);
  
  //calibration: RESET
  Wire.beginTransmission(CMPS2_address);
  Wire.write(0x07);
  Wire.write(0x80);
  Wire.endTransmission();
  delay(60);

  Wire.beginTransmission(CMPS2_address);
  Wire.write(0x07);
  Wire.write(0x40);
  Wire.endTransmission();
  delay(10);

  CMPS_read_XYZ();
  for (i=0;i<3;i++)
  {
    out2[i] = data[i];
  }

  Serial.print("Raw RESET = ");
  Serial.print(raw[0]);
  Serial.print("\t");
  Serial.print(raw[1]);
  Serial.print("\t");
  Serial.println(raw[2]);

  //offset berechnen
  for (i=0;i<3;i++)
  {
    offset[i] = (out1[i]+out2[i])*0.5; //Offset entfernen laut Datenblatt
  } 

  //control register 0 für SET
  Wire.beginTransmission(CMPS2_address);
  Wire.write(0x07);
  Wire.write(0x40); //SET
  Wire.endTransmission();
  delay(10);

  //control register 1 bis 16 bit auflösung, 8ms messzeit
  Wire.beginTransmission(CMPS2_address);
  Wire.write(0x08); 
  Wire.write(0x00);
  Wire.endTransmission();
  delay(10);
}