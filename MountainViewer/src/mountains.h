#ifndef MOUNTAINS_H
#define MOUNTAINS_H


typedef struct 
{
    char *name;
    int psoX;
    int posY;
    int height;
}mountain;

extern mountain mountains[];
extern int mountains_length;

#endif