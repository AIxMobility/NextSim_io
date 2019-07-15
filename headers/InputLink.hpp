#ifndef INPUTLINK_H
#define INPUTLINK_H

#pragma once
#include <vector>

class InputLink
{
private:
    //Data Members -- Micro-sim variables are commented out
    int id;
    int numLane;
    int numSect;
    //int startPosition;
    //int endPosition;
    
    int **freeFlowSpeed; // per cell 
    int **Qmax;          // per cell 
    int **waveSpeed;     // per cell 
    int **maxVehicle;    // per cell 

    int *width;
    int *length;

public:
    //Constructor
    InputLink(int id, int lane, int sect);
    

    int getId() { return id; }
    int getNumLane() { return numLane; }
    int getNumSect() { return numSect; }

    int ** getFFSpeed() { return freeFlowSpeed; }
    int ** getQmax() { return Qmax; }
    int ** getWaveSpeed() { return waveSpeed; }
    int ** getMaxVehicle() { return maxVehicle; }
    int * getWidth() { return width; }
    int * getLength() { return length; }


    //Setting the Variables
    void setFFspeed(int val);
    void setQmax(int val);
    void setWaveSpeed(int val);
    void setMaxVehicle(int val);

    void setLength(int val);
    void setWidth(int val);

    //Need to make helper functions for Designating cell-by-cell values
};

#endif