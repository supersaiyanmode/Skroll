#include "PictureTile.h"
#include <iostream>

PictureTile::PictureTile(const std::string& filename):fileName(filename){
    
}

void PictureTile::initialise(){
    TextureManager *t = getTextureManager();
    if (!t){
        std::cout<<"TextureManager not set.\n";
        exit(1);
    }
    t->addTexture(fileName,"");
    normal[0] = 0; normal[1] = 0; normal[2] = -1.0;
    points[0][0] = -1.0; points[0][1] =  1.0; points[0][2] =  0.0; 
    points[1][0] =  1.0; points[1][1] =  1.0; points[1][2] =  0.0; 
    points[2][0] =  1.0; points[2][1] = -1.0; points[2][2] =  0.0; 
    points[3][0] = -1.0; points[3][1] = -1.0; points[3][2] =  0.0; 
}

void PictureTile::paint(){
    TextureManager *t = getTextureManager();
    if (!t){
        std::cout<<"TextureManager not set.\n";
        exit(1);
    }
    static int i=0;
    if (!i++){
        std::cout<<"["<<points[0]<<","<<points[1]<<","<<points[2]<<","<<points[3]<<"]"<<std::endl;
    }
    t->bindFilename(fileName);
    glBegin(GL_QUADS);
        glNormal3dv(&normal[0]);
        glTexCoord2f(0.0,1.0); glVertex3dv(&points[0][0]);
        glTexCoord2f(1.0,1.0); glVertex3dv(&points[1][0]);
        glTexCoord2f(1.0,0.0); glVertex3dv(&points[2][0]);
        glTexCoord2f(0.0,0.0); glVertex3dv(&points[3][0]);
    glEnd();
}

PictureTile::~PictureTile(){
    
}