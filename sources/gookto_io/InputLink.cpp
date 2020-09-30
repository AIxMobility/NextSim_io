#include <gookto_io/InputLink.hpp>
#include <string>
#include <iostream>

InputLink::InputLink(u_ll id, int lane, float length, float width): MetadataBase(id, length, width)
{
    numLane = lane;
}

void InputLink::setFromNode(u_ll val){ _fromNode = val;}
void InputLink::setToNode(u_ll val){_toNode = val;}
void InputLink::setNumLane(int num){numLane = num;}

void InputLink::pushLaneId(InputLane lane)
{
    LaneIds.push_back(lane.getID());
    LaneArr.push_back(lane);
    NumCell_in_Lanes.push_back(lane.getNumCell());
}





