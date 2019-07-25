#include "InputLink.hpp"

#include "tinyxml.h"
#include "tinystr.h"

#include <string>
#include <iostream>

InputLink::InputLink(int id, int lane, int sect) :
id(id), numLane(lane), numSect(sect)
{
    freeFlowSpeed = new int* [sect];
    Qmax = new int* [sect];
    waveSpeed = new int* [sect];
    maxVehicle = new int* [sect];

    for (int i=0; i < sect; i++)
    {
        freeFlowSpeed[i] = new int [lane];
        Qmax[i] = new int [lane];
        waveSpeed[i] = new int [lane];
        maxVehicle[i] = new int [lane]; 

        memset(freeFlowSpeed[i], -1, lane*sizeof(int));
        memset(Qmax[i], -1, lane*sizeof(int));
        memset(waveSpeed[i], -1, lane * sizeof(int));
        memset(maxVehicle[i], -1, lane * sizeof(int));
    }

    width = new int [lane];
    length = new int [sect];

    memset(width, -1, sizeof(int));
    memset(length, -1, sizeof(int));
    
    //fill(freeFlowSpeed.begin(), freeFlowSpeed.end(), vector<int>(sect, lane));
    
}

// Cell variables
void InputLink::setFFspeed(int val)
{
    for (int i = 0; i < numSect; i++)
    {
        for (int j = 0; j < numLane; j++)
        {
            freeFlowSpeed[i][j] = val;
        }
    }
}

void InputLink::setQmax(int val)
{
    for (int i = 0; i < numSect; i++)
    {
        for (int j = 0; j < numLane; j++)
        {
            Qmax[i][j] = val;
        }
    }
}

void InputLink::setWaveSpeed(int val)
{
    for (int i = 0; i < numSect; i++)
    {
        for (int j = 0; j < numLane; j++)
        {
            waveSpeed[i][j] = val;
        }
    }
}

void InputLink::setMaxVehicle(int val)
{
    for (int i = 0; i < numSect; i++)
    {
        for (int j = 0; j < numLane; j++)
        {
            maxVehicle[i][j] = val;
        }
    }
}

//Array set in the order of ID
void InputLink::setLength(int val)
{
    for (int i = 0; i < numSect; i++)
    {
        length[i] = val;    
    }
}

void InputLink::setWidth(int val)
{
    for (int i = 0; i < numLane; i++)
    {
        width[i] = val;
    }
}

// FREE FUNCTIONS

void InputLink::freeFFspeed()
{
    for ( int i=0; i < numSect; i++)
    {
        delete[] freeFlowSpeed[i];
    }
    delete[] freeFlowSpeed;
}

void InputLink::freeQmax()
{
    for (int i = 0; i < numSect; i++)
    {
        delete[] Qmax[i];
    }
    delete[] Qmax;
}

void InputLink::freeWaveSpeed()
{
    for (int i = 0; i < numSect; i++)
    {
        delete[] waveSpeed[i];
    }
    delete[] waveSpeed;
}

void InputLink::freeMaxVehicle()
{
    for (int i = 0; i < numSect; i++)
    {
        delete[] maxVehicle[i];
    }
    delete[] maxVehicle;
}

void InputLink::freeLength()
{
    delete[] length;
}

void InputLink::freeWidth()
{
    delete[] width;
}