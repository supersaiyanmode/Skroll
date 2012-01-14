#include "Coverflow.h"
#include <iostream>
#include <cmath>

Coverflow::Coverflow(){
    
}

void Coverflow::initialise(){
    double face[]= {0,0,1};
    double  up[] = {0,1,0};
    
    //init tile locations using parabola z = - x*x;
    for (int x=-10; x<=10; x++){
        Vector3D pt(x,0,-x*x/4.0);
        tileLocations.push_back(pt);
        tiles.push_back(new PictureTile("e.bmp"));
    }
    
    for (int i=0,len=tiles.size(); i<len; i++){
        tiles[i]->setTextureManager(&tm);
        tiles[i]->initialise();
        tiles[i]->setOrientation(tileLocations[i], std::vector<double>(face, face+3),
                        std::vector<double>(up,up+3));
    }
}

void Coverflow::paint(){
    for (std::vector<Tile*>::iterator it = tiles.begin(); it  != tiles.end(); it++){
        (*it)->paint();
    }
}

Coverflow::~Coverflow(){
    for (std::vector<Tile*>::iterator it = tiles.begin(); it  != tiles.end(); it++){
        delete *it;
    }
}