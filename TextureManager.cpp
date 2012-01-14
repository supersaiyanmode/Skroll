#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <GL/glu.h>
#include "soil/SOIL.h"
#include "TextureManager.h"
std::string getNewRandomID(){
    static int init = 0;
    static std::vector<std::string> Ids;
    if (!init++)
        std::srand((unsigned)time(0));
    bool unique = false;
    std::string id;
    while (!unique){
        std::stringstream ss;
        ss<<rand();
        id = ss.str();
        unique = std::find(Ids.begin(), Ids.end(), id)==Ids.end();
    }
    Ids.push_back(id);
    return id;    
}

bool fileExists(std::string fileName){
    FILE* img = NULL;
    img = fopen(fileName.c_str(),"rb");
    if (img) return fclose(img),true;
    return false;
}
GLuint loadImageFromFileAsTexture(std::string s){
    //std::cout<<"Loading: "<<s<<std::endl;
    if (!fileExists(s)){
        std::cout<<"Image file: "<<s<<" doesn't exist!"<<std::endl;
        exit(1);
    }
    GLuint texture = SOIL_load_OGL_texture(s.c_str(),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
        );
    glBindTexture( GL_TEXTURE_2D, texture ); //bind the texture to it's array
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    return texture;
}


TextureManager::~TextureManager(){
    //need to unbind glTextures here..
}

TextureManager::TextureManager():glTextureEnabled(false){
    std::cout<<"TM CTOR!"<<std::endl;
}

void TextureManager::clear(){
    textures.clear();
    file2idMap.clear();
}
std::string TextureManager::addTexture(const std::string& fileName, const std::string& _id){
    std::string id = _id;
    if (!glTextureEnabled){
        glTextureEnabled = true;
        glEnable(GL_TEXTURE_2D);
    }
    
    if (id == ""){
        id = "$$!!texture_" + getNewRandomID();
    }
    
    if (IDExists(id)){
        std::cout<<"ID already exists: "<<id<<std::endl;
        exit(1);
    }
    
    //File-texture map..
    if (file2idMap.find(fileName) != file2idMap.end()){
        textures[id] =  file2idMap[fileName];
        return id;
    }
    if (!fileExists(fileName)){
        std::cout<<"File doesn't exist: "<<fileName<<std::endl;
        exit(1);
    }
    
    GLuint temp = loadImageFromFileAsTexture(fileName);
    textures[id] = temp;
    file2idMap[fileName] = temp;
    return id;
}

bool TextureManager::IDExists(const std::string& _id) const{
    return textures.find(_id) != textures.end();
}

GLuint TextureManager::getTextureFromID(const std::string& _id) const{
    if(!_id.compare("NONE"))
        return 0;
    if (!IDExists(_id)){
        std::cout<<"Texture ID: "<<_id<<" doesnt exist!"<<std::endl;
        exit(1);
    }
    return (*textures.find(_id)).second;
}

GLuint TextureManager::getTextureFromFilename(const std::string& fname) const{
    if (file2idMap.find(fname) == file2idMap.end()){
        std::cout<<"Filename: "<<fname<<" doesnt have corresponding texture!"<<std::endl;
        exit(1);
    }
    return (*file2idMap.find(fname)).second;
}

void TextureManager::bindTextureID(const std::string& _id) const{
    if (!this || _id == "NONE")
        glBindTexture(GL_TEXTURE_2D,0);
    else
        glBindTexture(GL_TEXTURE_2D,getTextureFromID(_id));
    //std::cout<<"balh!\n";
}

void TextureManager::bindFilename(const std::string& filename) const{
    if (!this || filename == "")
        glBindTexture(GL_TEXTURE_2D,0);
    else
        glBindTexture(GL_TEXTURE_2D,getTextureFromFilename(filename));
}

#if 0
#include "GLQuad.cpp"
#include "GLObject.cpp"

GLQuad glq;
void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glq.paint();
    glutSwapBuffers();
    glutPostRedisplay();
}
int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("FPS!");
    
    TextureManager tm;
    tm.addTexture("images/BoxTexture.bmp","quad_face");
    
    glq.setTexturePrefix("quad");
    
    glutDisplayFunc(display);
    
    glutMainLoop();
}
#endif
