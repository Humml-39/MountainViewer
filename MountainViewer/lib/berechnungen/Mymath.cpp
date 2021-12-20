#include <Arduino.h>
#include <math.h>
#include "Mymath.h"
#include "mountains.h"

void new_array(double X_Me,double Y_Me);
void auswertung(double angel);

void new_array(double X_Me,double Y_Me){
    
    double abstand;
    double phi;
    double X_Berg;
    double Y_Berg;
    int k =0;
    for (int i=0;i<mountains_length;i++){
        X_Berg = mountainss[i].posX;
        Y_Berg = mountainss[i].posY;
        abstand = sqrt(pow(abs(X_Berg-X_Me),2)+pow(abs(Y_Berg-Y_Me),2));
        if(abstand<100000){
            double phi = asin(abs(X_Berg-X_Me)/2*abstand);
            mountains_new[k]={mountainss[i].name,phi,abstand,mountainss[i].height};
            k++;
        }
    }
}

void auswertung(double angel){


}