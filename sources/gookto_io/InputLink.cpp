#include <gookto_io/InputLink.hpp>
#include <gookto_io/Temporal.hpp>
// #include <gookto_io/InputCell.hpp>
// #include <gookto_io/InputLane.hpp>
// #include <gookto_io/InputSegment.hpp>

#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/tinyapi/tinystr.h>

#include <string>
#include <iostream>

InputLink::InputLink(u_ll id, int lane, float length, float width):MetadataBase(id, length, width)
{
    numLane = lane;
}

void InputLink::setFromNode(u_ll val){ _fromNode = val;}
u_ll InputLink::getFromNode(){return _fromNode;}
void InputLink::setToNode(u_ll val){_toNode = val;}
u_ll InputLink::getToNode(){return _toNode;}
void InputLink::setNumLane(int num){numLane = num;}

void InputLink::pushLaneId(InputLane *lane)
{
    LaneIds.push_back(lane->getID());
    LaneArr.push_back(lane);
    NumCell_in_Lanes.push_back(lane->getNumCell());


}
InputLink::~InputLink(){
    LaneArr.clear();
    LaneIds.clear();
    NumCell_in_Lanes.clear();

    //Also, release the rest of the 2_D vectors
}




// FREE FUNCTIONS

