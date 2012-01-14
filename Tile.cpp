#include "Tile.h"

Tile::Tile():tm(0),aspectRatio(1.0),points(4,Vector3D()), border(4,Vector3D()){
    
}

TextureManager* Tile::getTextureManager(){
    return tm;
}

void Tile::setTextureManager(TextureManager*t){
    tm = t;
}

void Tile::setOrientation(std::vector<double> loc, std::vector<double> face, std::vector<double> upVector){
    normal = Vector3D(face);
    location = Vector3D(loc);
    up = Vector3D(upVector);
    
    Vector3D topMidPoint = location+up;
    Vector3D bottomMidPoint = location+up;
    Vector3D rightSideVector = up*normal;
    
    points[0] = topMidPoint - rightSideVector;
    points[1] = topMidPoint + rightSideVector;
    points[2] = bottomMidPoint + rightSideVector;
    points[3] = bottomMidPoint - rightSideVector;
}

Tile::~Tile(){
    
}
