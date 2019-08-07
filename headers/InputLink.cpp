#include "InputLink.hpp"

#include "tinyxml.h"
#include "tinystr.h"

#include <string>
#include <iostream>

InputLink::InputLink(int id, int lane, int sect) :
id(id), numLane(lane), numSect(sect)
{
    freeFlowSpeed.resize(numLane);
    Qmax.resize(numLane);
    waveSpeed.resize(numLane);
    maxVehicle.resize(numLane);

    for (int i = 0; i < numLane; ++i) 
    {
        freeFlowSpeed[i].resize(numSect);
        Qmax[i].resize(numSect);
        waveSpeed[i].resize(numSect);
        maxVehicle[i].resize(numSect);
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

void InputLink::setMaxVehicle(float val)
{
    for (int i = 0; i < numLane; i++)
    {
        for (int j = 0; j < numSect; j++)
        {
            maxVehicle[i][j] = val;
        }
    }
}

//Array set in the order of ID
void InputLink::setLength(float val)
{
    for (int i = 0; i < numSect; i++)
    {
        length[i] = val;    
    }
}

void InputLink::setWidth(float val)
{
    for (int i = 0; i < numLane; i++)
    {
        width[i] = val;
    }
}




// FREE FUNCTIONS

