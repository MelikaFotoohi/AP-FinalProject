#include "tile.h"

Tile::Tile(tileType _type, int numToken, QLabel* p)
{
    type = _type;
    numberToken = numToken;
    location = p;
}

ResourceCard Tile::getResource(){
    if(type == field)
        return ResourceCard(fieldCard);
    if(type == stone)
        return ResourceCard(stoneCard);
    if(type == clay)
        return ResourceCard(clayCard);
    if(type == pasture)
        return ResourceCard(pastureCard);
    if(type == forest)
        return ResourceCard(forestCard);


}

QLabel* Tile::getLocation(){
    return location;
}

tileType Tile::getType(){
    return type;
}
int Tile::getToken(){
    return numberToken;
}
void Tile::changeRobber(bool mode){
    robberIsHere = mode;
}
bool Tile::checkRobber(){
    return robberIsHere;
}

