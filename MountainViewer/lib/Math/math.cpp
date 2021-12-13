#include <Arduino.h>
#include "mountains.h"
#include "math.h"

void new_array(double X_Me,double Y_Me){
    
    
    double abstand;
    double phi;
    double X_Berg = 2;
    X_Me = 3;
    double Y_Berg = 2;
    Y_Me = 4;
    for (int i=0;i<mountains_length;i++){

        abstand = sqrt(pow(abs(X_Berg-X_Me),2)+pow(abs(Y_Berg-Y_Me),2));
        if(abstand>100000){
            double phi = asin(abs(X_Berg-X_Me)/2*abstand);
            mountains_new[i]={mountains->name,phi,abstand,mountains->height}
            

        }

    }
    


}

void auswertung(){


}