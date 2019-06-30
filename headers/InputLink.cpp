#include "InputLink.hpp"
#include <string>


InputLink::InputLink(int id, int lane, int sect) :
id(id), numLane(lane), numSect(sect)
{
}



// Function declarations with reference to the name space
void InputLink::setLink(int id, int lane, int sect)
{
    this->id = id;
    numLane = lane;
    numSect = sect;
}