#ifndef COVERFLOW_H
#define COVERFLOW_H

#include "PictureTile.h"
#include "TextureManager.h"
#include <vector>

struct Point3D{
    double x,y,z;
};

class Coverflow{
    std::vector<Tile*> tiles;
    TextureManager tm;
    std::vector<Point3D> tileLocations;
    int currentPosition;
public:
    Coverflow();
    void initialise();
    void paint();
    ~Coverflow();
};

#endif //COVERFLOW_H