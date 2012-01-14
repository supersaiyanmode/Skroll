#ifndef COVERFLOW_H
#define COVERFLOW_H

#include <vector>
#include "PictureTile.h"
#include "TextureManager.h"
#include "Vector3D.h"

class Coverflow{
    std::vector<Tile*> tiles;
    TextureManager tm;
    std::vector<std::vector<Vector3D> > tileOrientations;
    int currentPosition,nextPosition,direction;
public:
    Coverflow();
    void initialise();
    void paint();
    ~Coverflow();
};

#endif //COVERFLOW_H