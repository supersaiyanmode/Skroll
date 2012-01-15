#include "Coverflow.h"
#include <iostream>
#include <cmath>

Coverflow::Coverflow():currentPosition(0),nextPosition(0),direction(0){
    
}

void Coverflow::initialise(){
    double face[]= {0,0,1};
    double  up[] = {0,1,0};
    
    length = 7;
    currentPosition = length/2;
    
    for (int x=-length+1; x<=length-1; x++){
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
    for (int i=0; i<length; i++){
        tiles.push_back(new PictureTile("e.bmp"));
    }
    for (int i=0,len=tiles.size(); i<len; i++){
        tiles[i]->setTextureManager(&tm);
        tiles[i]->initialise();
        tiles[i]->setOrientation(tileOrientations[currentPosition+i][0],
            tileOrientations[currentPosition+i][1],tileOrientations[currentPosition+i][2]);
    }
}

void Coverflow::paint(){
    static double progress = 0.0;
    const double incrementProgress = 0.1;
    if (direction){
        std::cout<<"Direction: "<<direction<<"\tCurrentPostion"<<currentPosition;
        if (direction < 0 && currentPosition < length-1){ //move right
            nextPosition = currentPosition + 1;
        }else if (direction > 0 && currentPosition>0){
            nextPosition = currentPosition - 1;
        }
        progress = incrementProgress;
        std::cout<<" => "<<currentPosition<<std::endl;
    }
    
    if (progress > 1e-2){
        progress += incrementProgress;
        if (progress>1.0){
            progress = 0.0;
            currentPosition = nextPosition;
        }
        std::cout<<"Cur: "<<currentPosition<<"\tNext: "<<nextPosition<<std::endl;
        for (int i=0,len=tiles.size(); i<len; i++){
            tiles[i]->setOrientation(
                Vector3D::getRatioVector(tileOrientations[currentPosition+i][0],tileOrientations[nextPosition+i][0],progress),
                Vector3D::getRatioVector(tileOrientations[currentPosition+i][1],tileOrientations[nextPosition+i][1],progress),
                Vector3D::getRatioVector(tileOrientations[currentPosition+i][2],tileOrientations[nextPosition+i][2],progress)
            );
            tiles[i]->paint();
        }
        
        direction = 0;
    }else{
        for (int i=0,len=tiles.size(); i<len; i++){
            tiles[i]->setOrientation(tileOrientations[currentPosition+i][0],
                tileOrientations[currentPosition+i][1],tileOrientations[currentPosition+i][2]);
            tiles[i]->paint();
        }
    }
}

void Coverflow::scroll(int dir){
    direction = dir;
}

Coverflow::~Coverflow(){
    for (std::vector<Tile*>::iterator it = tiles.begin(); it  != tiles.end(); it++){
        delete *it;
    }
}