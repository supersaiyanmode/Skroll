#ifndef PICTURETILE_H
#define PICTURETILE_H

#include <GL/gl.h>
#include <string>
#include "Tile.h"

class PictureTile : public Tile{
    std::string fileName;
public:
    PictureTile(const std::string&);
    void initialise();
    void paint();
    ~PictureTile();
};

#endif //PICTURETILE_H