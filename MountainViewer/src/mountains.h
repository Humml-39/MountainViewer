#ifndef MOUNTAINS_H
#define MOUNTAINS_H
//https://download.geofabrik.de/europe/alps.html

typedef struct 
{
    char *name;
    double posX;
    double posY;
    int height;
}mountain;

extern mountain mountains[];
extern int mountains_length;

#endif