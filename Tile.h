#ifndef TILE_H
#define TILE_H
#include <vector>
#include "TextureManager.h"

class Tile{
    TextureManager* tm;
protected:
    double aspectRatio;
    std::vector<std::vector<double> > points,border;
    std::vector<double> normal;
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