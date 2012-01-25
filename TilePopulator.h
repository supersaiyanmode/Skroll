#ifndef TILEPOPULATOR_H
#define TILEPOPULATOR_H

#include <vector>
#include <string>
#include "PictureTile.h"

class TilePopulator{
protected:
    std::vector<Tile*> tiles;
    TextureManager& tm;
public:
    TilePopulator(TextureManager&);
    virtual void populate() = 0;
    std::vector<Tile*> get() const;
    int size() const;
};

class SingleImageTilePopulator: public TilePopulator{
    std::string filename;
    int count;
public:
    SingleImageTilePopulator(TextureManager&, const std::string&,int);
    void populate();
};

class FolderImageTilePopulator: public TilePopulator{
    std::vector<std::string> fileNames;
    std::string baseDir;
public:
    FolderImageTilePopulator(TextureManager&, const std::string&);
    void populate();
};


#endif