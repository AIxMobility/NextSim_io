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
    
    //int **freeFlowSpeed; 
    //int **Qmax;          
    //int **waveSpeed;     
    //int **maxVehicle;

    std::vector<std::vector<float> > freeFlowSpeed;
    std::vector<std::vector<float> > Qmax;
    std::vector<std::vector<float> > waveSpeed;
    std::vector<std::vector<float> > maxVehicle;

    //int *width;
    //int *length;

    std::vector<float> width;
    std::vector<float> length;

public:
    //Constructor
    InputLink(int id, int lane, int sect);
    

    int getId() { return id; }
    int getNumLane() { return numLane; }
    int getNumSect() { return numSect; }

    std::vector<std::vector<float> > getFreeFlowSpeed() { return freeFlowSpeed; } // float
    std::vector<std::vector<float> > getQmax() { return Qmax; }              // float
    std::vector<std::vector<float> > getWaveSpeed() { return waveSpeed; }     // float
    std::vector<std::vector<float> > getMaxVehicle() { return maxVehicle; }    // int
    std::vector<float> getWidth() { return width; }                       // float
    std::vector<float> getLength() { return length; }                     // float

    //Setting the Variables
    void setFreeFlowSpeed(float val);
    void setQmax(float val);
    void setWaveSpeed(float val);
    void setMaxVehicle(float val);

    void setLength(float val);
    void setWidth(float val);

    //Free 2d Vectors

    //Need to make helper functions for Designating cell-by-cell values
};

#endif