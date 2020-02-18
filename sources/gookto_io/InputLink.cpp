#include <gookto_io/InputLink.hpp>

#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/tinyapi/tinystr.h>

#include <string>
#include <iostream>

InputLink::InputLink(int id, int lane, int sect) :
id(id), numLane(lane), numSect(sect)
{
    freeFlowSpeed.resize(lane);
    Qmax.resize(lane);
    waveSpeed.resize(lane);
    maxVehicle.resize(lane);


    for (int i = 0; i < lane; i++) 
    {
        freeFlowSpeed[i].resize(sect);
        Qmax[i].resize(sect);
        waveSpeed[i].resize(sect);
        maxVehicle[i].resize(sect);
    };

    //fill(freeFlowSpeed.begin(), freeFlowSpeed.end(), vector<int>(sect, lane));
    
}

// Cell variables
void InputLink::setFreeFlowSpeed(float val)
{
    for (int i = 0; i < numLane; i++)
    {
        for (int j = 0; j < numSect; j++)
        {
            freeFlowSpeed[i][j] = val;
        }
    }
}

void InputLink::setQmax(float val)
{
    for (int i = 0; i < numLane; i++)
    {
        for (int j = 0; j < numSect; j++)
        {
            Qmax[i][j] = val;
        }
    }
}

void InputLink::setWaveSpeed(float val)
{
    for (int i = 0; i < numLane; i++)
    {
        for (int j = 0; j < numSect; j++)
        {
            waveSpeed[i][j] = val;
        }
    }
}

void InputLink::setMaxVehicle(int val)
{
    for (int i = 0; i < numLane; i++)
    {
        for (int j = 0; j < numSect; j++)
        {
            size_t new_val = val;
            maxVehicle[i][j] = new_val;
        }
    }
}

//Array set in the order of ID
void InputLink::setLength(float val)
{
    
    length = val;    
    
}

void InputLink::setWidth(float val)
{
    
    width = val;
    
}




// FREE FUNCTIONS

