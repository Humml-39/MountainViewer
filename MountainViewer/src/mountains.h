#ifndef MOUNTAINS_H
#define MOUNTAINS_H


typedef struct 
{
    char *name;
    double posX;
    double posY;
    int height;
}mountain;

extern mountain mountainss[];
extern int mountains_length;

#endif