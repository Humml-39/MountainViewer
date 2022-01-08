#include <Arduino.h>
#include <math.h>
#include "Mymath.h"
#include "mountains.h"

void new_array(double X_Me,double Y_Me);
void auswertung(double angel);

mountain_new mountains_new[];

void new_array(double X_Me,double Y_Me){
    Serial.print("\n");
    double abstand;
    double phi;
    double X_Berg;
    double Y_Berg;
    int k =0;
    double temp0,temp1;

    for (int i=0;i<854;i++){
        X_Berg = mountains[i].posX;
        Y_Berg = mountains[i].posY;
        abstand = sqrt(pow(abs(X_Berg-X_Me),2)+pow(abs(Y_Berg-Y_Me),2));
        if(abstand<0.1){
            if((Y_Berg-Y_Me)>0){
                if ((X_Berg-X_Me) > 0){
                //Quadrant 1
                temp0 = (X_Berg-X_Me);
                temp1 = -(Y_Berg-Y_Me);
                phi = 90 + atan(temp0 / temp1) * (180 / 3.14159);
                }
                else
                {
                //Quadrant 2
                temp0 = -(X_Berg-X_Me);
                temp1 = -(Y_Berg-Y_Me);
                phi = 90 - atan(temp0 / temp1) * (180 / 3.14159);
                }
            }
            else {
                if ((X_Berg-X_Me) < 0)
                {
                //Quadrant 3
                temp0 = -(X_Berg-X_Me);
                temp1 = (Y_Berg-Y_Me);
                phi = 270 + atan(temp0 / temp1) * (180 / 3.14159);
                }
                else
                {
                //Quadrant 4
                temp0 = (X_Berg-X_Me);
                temp1 = (Y_Berg-Y_Me);
                phi = 270 - atan(temp0 / temp1) * (180 / 3.14159);
                }
            }
            mountains_new[k].abstand=abstand;
            mountains_new[k].phi=phi;
            mountains_new[k].height=mountains[i].height;
            mountains_new[k].name=mountains[i].name;
            k++;
        }       
    }
    for(int i=0;i<k;i++){
        Serial.print(mountains_new[i].name);
        Serial.print("  ");
        Serial.print(mountains_new[i].phi);
        Serial.print("\n");
    }
}

void auswertung(double angel){


}