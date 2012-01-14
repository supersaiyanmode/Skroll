#include "Coverflow.h"
#include <iostream>
#include <cmath>

Coverflow::Coverflow(){
    
}

void Coverflow::initialise(){
    //init tile locations using parabola z = +- sqrt(2x);
    for (int x=-10; x<=10; x++){
        Point3D p = {x,0, (x<0)? -sqrt(2*x) : sqrt(2*x)};
        tileLocations.push_back(p);
    }
    
    PictureTile* p = new PictureTile("e.bmp");
    tiles.push_back(p);
    
    for (std::vector<Tile*>::iterator it = tiles.begin(); it!=tiles.end(); it++){
        (*it)->setTextureManager(&tm);
        (*it)->initialise();
    }
    
    double loc[] = {1,3,-1};
    double face[]= {-2,0,4};
    double  up[] = {0,1,0};
    p->setOrientation(std::vector<double>(loc,loc+3), std::vector<double>(face, face+3),
                        std::vector<double>(up,up+3));
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