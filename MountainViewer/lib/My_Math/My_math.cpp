#include <Arduino.h>
#include <math.h>
#include "My_math.h"
#include <mountains.h>

void new_array(double X_Me,double Y_Me){
    
    double abstand;
    double phi;
    double X_Berg;
    double Y_Berg;
    int k =0;
    for (int i=0;i<mountains_length;i++){
        X_Berg = mountains[i].posX;
        Y_Berg = mountains[i].posY;
        abstand = sqrt(pow(abs(X_Berg-X_Me),2)+pow(abs(Y_Berg-Y_Me),2));
        if(abstand<100000){
            double phi = asin(abs(X_Berg-X_Me)/2*abstand);
            mountains_new[k]={mountains[i].name,phi,abstand,mountains[i].height};
            k++;
        }
    }
}

void auswertung(double angel){


}