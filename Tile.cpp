#include "Tile.h"
#include <iostream>

Tile::Tile():tm(0),aspectRatio(1.0),points(4,Vector3D()), border(4,Vector3D()){
    
}

TextureManager* Tile::getTextureManager(){
    return tm;
}

void Tile::setTextureManager(TextureManager*t){
    tm = t;
}

void Tile::setOrientation(std::vector<double> loc, std::vector<double> facing, std::vector<double> upVector){
    location = Vector3D(loc);
    normal = (Vector3D(facing) - location).normalise();
    up = normal*(Vector3D(upVector).normalise()*normal); //fix this up!
    
    Vector3D topMidPoint = location+up;
    Vector3D bottomMidPoint = location-up;
    Vector3D rightSideVector = up*normal;
    
    points[0] = topMidPoint - rightSideVector;
    points[1] = topMidPoint + rightSideVector;
    points[2] = bottomMidPoint + rightSideVector;
    points[3] = bottomMidPoint - rightSideVector;
}

Tile::~Tile(){
    
}
