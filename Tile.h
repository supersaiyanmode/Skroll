#ifndef TILE_H
#define TILE_H
#include <vector>
#include "TextureManager.h"
#include "Vector3D.h"

/*
 * TILE VERTICES:
 * 
 *   0         1
 * 
 * 
 *   3         2
 * 
 * */

class Tile{
    TextureManager* tm;
protected:
    double aspectRatio;
    std::vector<Vector3D> points,border;
    Vector3D location,normal,up;
public:
    Tile();
    TextureManager* getTextureManager();
    void setTextureManager(TextureManager*);
    
    void setOrientation(std::vector<double>, std::vector<double>, std::vector<double>);
    
    virtual void paint() = 0;
    virtual void initialise()=0;
    virtual ~Tile();
};

#endif //PICTURETILE_H