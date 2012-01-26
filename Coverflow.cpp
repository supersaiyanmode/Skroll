#include "Coverflow.h"
#include <iostream>
#include <cmath>

Coverflow::Coverflow():currentPosition(0),nextPosition(0),direction(0){
    
}

void Coverflow::initialise(){
    //add the tiles..
    SingleImageTilePopulator s(tm,"e.bmp",10);
    s.populate();
    tiles = s.get();
    
    
    length = s.size();
    currentPosition = length-1;
    nextPosition = length/2;
    //nextPosition = currentPosition;
    
    
    for (int x=-length+1; x<=length-1; x++){
        if (x){
            Vector3D up(0,1,0);
            Vector3D loc(x/3.0 + 4.0*(x>0)-2,0,0);
            Vector3D facing(0,0,0);
            Vector3D arr[] = {loc,(facing-loc).normalise(),up};
            tileOrientations.push_back(std::vector<Vector3D>(arr,arr+3));
        }else{
            Vector3D up(0,1,0);
            Vector3D loc(0,0,2.5);
            Vector3D facing(0,0,100);
            Vector3D arr[] = {loc,(facing-loc).normalise(),up};
            tileOrientations.push_back(std::vector<Vector3D>(arr,arr+3));
        }
    }
    
    for (int i=0,len=tiles.size(); i<len; i++){
        tiles[i]->setTextureManager(&tm);
        tiles[i]->initialise();
        tiles[i]->setOrientation(tileOrientations[currentPosition+i][0],
            tileOrientations[currentPosition+i][1],tileOrientations[currentPosition+i][2]);
    }
    
    return;
    //set up lighting..
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 0.0, 0.0, 10.0, 0.0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void Coverflow::paint(){
    static double progress = 0.0;
    static double incrementProgress = 0.05;
    if (direction){
        if (nextPosition == currentPosition)
            progress = incrementProgress;
        else
            progress += incrementProgress;
        
        if (direction < 0 && currentPosition < length-1){ //move right
            nextPosition = currentPosition + 1;
        }else if (direction > 0 && currentPosition>0){
            nextPosition = currentPosition - 1;
        }
        direction = 0;
    }
    
    if (currentPosition != nextPosition){
        if (progress>1.0){
            progress = 0.0;
            currentPosition = nextPosition;
        }
        for (int i=0,len=tiles.size(); i<len; i++){
            tiles[i]->setOrientation(
                Vector3D::getRatioVector(tileOrientations[currentPosition+i][0],tileOrientations[nextPosition+i][0],progress),
                Vector3D::getRatioVector(tileOrientations[currentPosition+i][1],tileOrientations[nextPosition+i][1],progress),
                Vector3D::getRatioVector(tileOrientations[currentPosition+i][2],tileOrientations[nextPosition+i][2],progress)
            );
            tiles[i]->paint();
        }
        progress += incrementProgress;
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

void Coverflow::setCamera(std::vector<double>* c){
    camera = c;
    double arr[] = {0,0,5, 0,0,0, 0,1,0};
    *camera = std::vector<double>(arr,arr+9);
}

Coverflow::~Coverflow(){
    for (std::vector<Tile*>::iterator it = tiles.begin(); it  != tiles.end(); it++){
        delete *it;
    }
}


//############ COOLIRIS #########################

Cooliris::Cooliris():rows(3),direction(0){
    
}

void Cooliris::initialise(){
    FolderImageTilePopulator s(tm,".");
    s.populate();
    tiles = s.get();
    
    
    int length = s.size();
    double gap = 0.1;
    std::vector<double> vertPos;
    for (int i=rows/2; i>=-rows/2; i--){
        vertPos.push_back(i*2*(1.0+gap));
    }

    for (int i=0; i<length; i++){
        Vector3D up(0,1,0);
        Vector3D dir(0,0,1);
        Vector3D loc((i/rows)*2*(1+gap),vertPos[i%rows],0);
        Vector3D arr[] = {loc,dir,up};
        tileOrientations.push_back(std::vector<Vector3D>(arr,arr+3));
    }
    maxHorizPos = tileOrientations[length-1][0][0];
    
    for (int i=0,len=tiles.size(); i<len; i++){
        tiles[i]->setTextureManager(&tm);
        tiles[i]->initialise();
        tiles[i]->setOrientation(tileOrientations[i][0],tileOrientations[i][1],
                        tileOrientations[i][2]);
    }
}
void Cooliris::paint(){
    //cameraMove => steps taken by camera to come to rest to the point of lookAt
    //userMove => lookat Point steps
    
    static double cameraMove = 0.1, userMove = 5.0;
    
    if (direction){
        curHorizLookAt += direction/userMove;
        if (curHorizLookAt < 0.5){
            curHorizLookAt = 0.5;
        }
        if (curHorizLookAt > Cooliris::maxHorizPos){
            curHorizLookAt = Cooliris::maxHorizPos;
        }
        direction = 0;
    }
    (std::cout<<".").flush();
    if (std::abs(curHorizLookAt-curHorizPos) > 1e-2){
        curHorizPos += curHorizLookAt > curHorizPos? cameraMove : -cameraMove;
        
        double arr[] = {curHorizPos,0,8,curHorizLookAt,0,0,0,1,0};
        *camera = std::vector<double>(arr,arr+9);
    }
    
    for (int i=0,len=tiles.size(); i<len; i++){
        tiles[i]->setOrientation(tileOrientations[i][0],tileOrientations[i][1],
                        tileOrientations[i][2]);
        tiles[i]->paint();
    }
}
void Cooliris::setCamera(std::vector<double>* c){
    camera = c;
    double arr[] = {0.5,0,8,0.5,0,0, 0,1,0};
    *camera = std::vector<double>(arr,arr+9);
    curHorizLookAt = curHorizPos = 0.5;
}

void Cooliris::scroll(int dir){
    direction = dir;
}

Cooliris::~Cooliris(){
    for (std::vector<Tile*>::iterator it = tiles.begin(); it  != tiles.end(); it++){
        delete *it;
    }    
}
