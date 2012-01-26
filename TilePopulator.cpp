#include "TilePopulator.h"
#include "FileLister.h"
TilePopulator::TilePopulator(TextureManager& t): tm(t){

}

std::vector<Tile*> TilePopulator::get() const{
    return tiles;
}

int TilePopulator::size() const{
    return tiles.size();
}



SingleImageTilePopulator::SingleImageTilePopulator(TextureManager& tm, const std::string& file, int c):
        TilePopulator(tm), filename(file), count(c){
            
}
void SingleImageTilePopulator::populate(){
    for (int i=0; i<count; i++){
        tiles.push_back(new PictureTile(filename));  //will be deleted by coverflow
    }
}


FolderImageTilePopulator::FolderImageTilePopulator(TextureManager& tm, const std::string& dir):
        TilePopulator(tm), baseDir(dir){
}
void FolderImageTilePopulator::populate(){
    FileLister fl(baseDir,"jpg|bmp|png");
    std::vector<std::string> list = fl.list();
    for (std::vector<std::string>::iterator it=list.begin(); it!=list.end(); it++){
        tiles.push_back(new PictureTile(*it));
    }
}