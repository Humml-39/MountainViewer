#include <Arduino.h>
#include <math.h>
#include "Mymath.h"
#include "mountains.h"

void new_array(double X_Me,double Y_Me);
void auswertung(double angel);

mountain_new mountains_new[];

void new_array(double X_Me,double Y_Me){
    double abstand;
    double phi;
    double X_Berg;
    double Y_Berg;
    int k =0,ks=0;
    for (int i=0;i<854;i++){
        X_Berg = mountains[i].posX;
        Y_Berg = mountains[i].posY;
        abstand = sqrt(pow(abs(X_Berg-X_Me),2)+pow(abs(Y_Berg-Y_Me),2));
        if(abstand<0.1){
            phi = asin(abs(X_Berg-X_Me)/2*abstand);
            mountains_new[k].abstand=abstand;
            mountains_new[k].phi=phi;
            mountains_new[k].height=mountains[i].height;
            mountains_new[k].name=mountains[i].name;
            //Serial.print(mountains_new[k].name);
            k++;
        } 
        ks++;      
    }
    Serial.print(mountains[5].posX);
    Serial.print("\n");
    Serial.print(ks);
}

void auswertung(double angel){


}