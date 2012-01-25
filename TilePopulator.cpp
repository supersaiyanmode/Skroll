#include "TilePopulator.h"

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
