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

std::vector<std::vector<float> > InputLink::get2DFreeFlowSpeed(){

    std::vector<std::vector<float>> matrix;
    matrix.resize(numLane);
    for (int i = 0; i < numLane; i++)
    {
        matrix[i].resize(NumCell_in_Lanes[i]);
        for (int j = 0; j  < NumCell_in_Lanes[i]; j++)
        {
            matrix[i][j] = LaneArr[i].getCells()[j].getFreeFlowSpeed();
        }
        
    }
    return matrix;
    

}
std::vector<std::vector<float> > InputLink::get2DQmax2D(){

    std::vector<std::vector<float>> matrix;
    matrix.resize(numLane);
    for (int i = 0; i < numLane; i++)
    {
        matrix[i].resize(NumCell_in_Lanes[i]);
        for (int j = 0; j  < NumCell_in_Lanes[i]; j++)
        {
            matrix[i][j] = LaneArr[i].getCells()[j].getQmax();
        }
        
    }
    return matrix;


}       
std::vector<std::vector<float> > InputLink::get2DWaveSpeed(){

    std::vector<std::vector<float>> matrix;
    matrix.resize(numLane);
    for (int i = 0; i < numLane; i++)
    {
        matrix[i].resize(NumCell_in_Lanes[i]);
        for (int j = 0; j  < NumCell_in_Lanes[i]; j++)
        {
            matrix[i][j] = LaneArr[i].getCells()[j].getWaveSpeed();
        }
        
    }
    return matrix;

}
std::vector<std::vector<size_t> > InputLink::get2DMaxVehicle(){
    
    std::vector<std::vector<size_t>> matrix;
    matrix.resize(numLane);
    for (int i = 0; i < numLane; i++)
    {
        matrix[i].resize(NumCell_in_Lanes[i]);
        for (int j = 0; j  < NumCell_in_Lanes[i]; j++)
        {
            matrix[i][j] = LaneArr[i].getCells()[j].getMaxVehicle();
        }
        
    }
    return matrix;


}



