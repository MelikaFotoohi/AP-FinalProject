#include "location.h"


Location::Location(int _x, int _y, locationType _type)
{
    x = _x;
    y = _y;
    type = _type;
}
Location::Location(){

}
QVector<Location> Location::getADjacent(){


}
int Location::getX(){
    return x;
}
int Location::getY(){
    return y;
}
void Location::findAdjacent(){

}

int Location::distance(Location){

}
