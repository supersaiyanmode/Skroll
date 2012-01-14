#include "Tile.h"

Tile::Tile():tm(0),points(4, std::vector<double>(3, 0.0)),border(points),normal(3,0.0),aspectRatio(0.0){
    
}

TextureManager* Tile::getTextureManager(){
    return tm;
}

void Tile::setTextureManager(TextureManager*t){
    tm = t;
}

void Tile::setOrientation(std::vector<double> location, std::vector<double> normal, std::vector<double> up){
    this->normal = normal;
    
}

Tile::~Tile(){
    
}
