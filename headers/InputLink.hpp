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
    
    //int **freeFlowSpeed; // per cell -- need to add
    //int **Qmax;          // per cell -- need to add
    //int **waveSpeed;     // per cell -- need to add
    //int **maxVehicle;    // per cell -- need to add

    //int width;
    //int length;

public:
    //Constructor
    InputLink(int id, int lane, int sect);

    //Member Functions
    void setLink(int id, int lane, int sect);

    int getId() { return id; }
    int getNumLane() { return numLane; }
    int getNumSect() { return numSect; }


};

#endif