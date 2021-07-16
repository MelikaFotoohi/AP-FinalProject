#include "tile.h"

Tile::Tile(tileType _type, int numToken, Location* _location)
{
    type = _type;
    numberToken = numToken;
    location = _location;
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

Location* Tile::getLocation(){
    return location;

}

tileType Tile::getType(){
    return type;
}

void Tile::getRobber(){
    robberIsHere = !robberIsHere;
}
bool Tile::checkRobber(){
    return robberIsHere;
}
