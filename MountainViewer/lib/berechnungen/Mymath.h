#ifndef MYMATH_H
    #define MYMATH_H 
    
    typedef struct 
    {
        char *name;
        double phi;
        double abstand;
        int height;
    }mountain_new;
     
    extern mountain_new mountains_new[];
    extern void new_array(double X_Me,double Y_Me);


#endif