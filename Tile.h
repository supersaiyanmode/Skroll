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
    int width, height;
    std::vector<Vector3D> points,border;
    Vector3D location,normal,up;
public:
    Tile();
    TextureManager* getTextureManager() const;
    void setTextureManager(TextureManager*);
    
    void setOrientation(Vector3D, Vector3D, Vector3D);
    void resize();
    
    virtual void paint() = 0;
    virtual void initialise()=0;
    virtual ~Tile();
};

#endif //PICTURETILE_H