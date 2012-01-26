#include "PictureTile.h"
#include "soil/SOIL.h"
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
    SOIL_last_image_dimensions(&width, &height);
    
    normal[0] = 0; normal[1] = 0; normal[2] = -1.0;
    points[0][0] = -1.0; points[0][1] =  1.0; points[0][2] =  0.0;
    points[1][0] =  1.0; points[1][1] =  1.0; points[1][2] =  0.0;
    points[2][0] =  1.0; points[2][1] = -1.0; points[2][2] =  0.0;
    points[3][0] = -1.0; points[3][1] = -1.0; points[3][2] =  0.0;
    
    double newHeight,newWidth;
    //maintain aspect ratio
    if (width > height){
        newWidth = 2.0;
        newHeight = newWidth*double(height)/width;
        points[0][1] = points[1][1] = newHeight/2.0;
        points[3][1] = points[2][1] = -newHeight/2.0;
    }else {
        newHeight = 2.0;
        newWidth = newHeight*double(width)/height;
        points[0][0] = points[1][0] = newWidth/2.0;
        points[3][0] = points[2][0] = -newWidth/2.0;
    }
}

void PictureTile::paint(){
    TextureManager *t = getTextureManager();
    if (!t){
        std::cout<<"TextureManager not set.\n";
        exit(1);
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