#include "Coverflow.h"
#include <iostream>
#include <cmath>

Coverflow::Coverflow():currentPosition(0),nextPosition(0),direction(0){
    
}

void Coverflow::initialise(){
    double face[]= {0,0,1};
    double  up[] = {0,1,0};
    
    for (int x=-10; x<=10; x++){
        if (x){
            Vector3D up(0,1,0);
            Vector3D loc(x/3.0 + 4.0*(x>0)-2,0,0);
            Vector3D facing(0,0,0);
            Vector3D arr[] = {loc,facing,up};
            tileOrientations.push_back(std::vector<Vector3D>(arr,arr+3));
        }else{
            Vector3D up(0,1,0);
            Vector3D loc(0,0,2.5);
            Vector3D facing(0,0,100);
            Vector3D arr[] = {loc,facing,up};
            tileOrientations.push_back(std::vector<Vector3D>(arr,arr+3));
        }
        
    }
    for (int x=-10; x<=10; x++){
        tiles.push_back(new PictureTile("e.bmp"));
    }
    for (int i=0,len=tiles.size(); i<len; i++){
        tiles[i]->setTextureManager(&tm);
        tiles[i]->initialise();
        tiles[i]->setOrientation(tileOrientations[i][0], tileOrientations[i][1],
                        tileOrientations[i][2]);
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