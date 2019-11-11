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
    std::vector<std::vector<size_t> > maxVehicle;

    //int *width;
    //int *length;

    float width;
    float length;

public:
    //Constructor
    InputLink(int id, int lane, int sect);
    

    int getId() { return id; }
    int getNumLane() { return numLane; }
    int getNumSect() { return numSect; }

    /**
     * getFreeFlowSpeed()
     * @brief Get the Free Flow Speed of link
     * Value exists for each cell of the link
     * 
     * 2D vector: numLane x numSect
     * 
     * @return std::vector<std::vector<float> > 
     */
    std::vector<std::vector<float> > getFreeFlowSpeed() { return freeFlowSpeed; }
    std::vector<std::vector<float> > getQmax() { return Qmax; }              
    std::vector<std::vector<float> > getWaveSpeed() { return waveSpeed; }     
    std::vector<std::vector<size_t> > getMaxVehicle() { return maxVehicle; }    
    float getWidth() { return width; }                       
    float getLength() { return length; }                     

    //Setting the Variables
    void setFreeFlowSpeed(float val);
    void setQmax(float val);
    void setWaveSpeed(float val);
    void setMaxVehicle(int val);

    void setLength(float val);
    void setWidth(float val);

    //Free 2d Vectors

    //Need to make helper functions for Designating cell-by-cell values
};

#endif