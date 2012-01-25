#ifndef COVERFLOW_H
#define COVERFLOW_H

#include <vector>
#include "PictureTile.h"
#include "TextureManager.h"
#include "Vector3D.h"
#include "TilePopulator.h"

class TileDisplay {
protected:
    std::vector<Tile*> tiles;
    std::vector<double>* camera;
    TextureManager tm;
    std::vector<std::vector<Vector3D> > tileOrientations;
public:
    virtual void initialise() = 0;
    virtual void paint() = 0;
    virtual void setCamera(std::vector<double>*) = 0;
    virtual void scroll(int) = 0;   //1 for right dir, -1 for left
};

class Coverflow : public TileDisplay{
    int currentPosition,nextPosition,direction;
    int length;
public:
    Coverflow();
    void initialise();
    void paint();
    void setCamera(std::vector<double>*);
    void scroll(int);
    ~Coverflow();
};

class Cooliris : public TileDisplay{
    int rows,length,direction;
    double curHorizLookAt, curHorizPos,maxHorizPos;
public:
    Cooliris();
    void initialise();
    void paint();
    void setCamera(std::vector<double>*);
    void scroll(int);
    ~Cooliris();
};

#endif //COVERFLOW_H