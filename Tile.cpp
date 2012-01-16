#include "Tile.h"
#include <iostream>

Tile::Tile():tm(0),aspectRatio(1.0),points(4,Vector3D()), border(4,Vector3D()){
    
}

TextureManager* Tile::getTextureManager() const{
    return tm;
}

void Tile::setTextureManager(TextureManager*t){
    tm = t;
}

void Tile::setOrientation(Vector3D loc, Vector3D dir, Vector3D upVector){
    location = loc;
    normal = dir.normalise();
    up = normal*(upVector.normalise()*normal);
    
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
