#ifndef INPUTLINK_H
#define INPUTLINK_H


#include <vector>
#include <string>
#include "InputLink.hpp"
#include "Temporal.hpp"

// #include "InputLane.hpp"
// #include "InputCell.hpp"


class InputLink: public MetadataBase
{
private:
    //Data Members -- Micro-sim variables are commented out

    //  <link ffspeed="40.0" 
    // from_node="1000010130" 
    // id="2000010224" 
    // length="207.56" 
    // maxVeh="0" 
    // max_spd="40.0" 
    // min_spd="0.0" 
    // num_lane="3" 
    // qmax="0.0" 
    // sim_type="0" 
    // to_node="1000010109" 
    // type="straight" 
    // waveSpd="0.0" 
    // width="0.0">
    
    u_ll _toNode, _fromNode;
    int numLane;
    std::string _type, _sim_type;


    // float _freeFlowSpeed, _max_spd,  _min_spd, _waveSpeed;
    // float _length, _width, _Qmax;
    // size_t _maxVehicle;


    
    // int numSect; //not used 
    //int startPosition;
    //int endPosition;
    
    //int **freeFlowSpeed; 
    //int **Qmax;          
    //int **waveSpeed;     
    //int **maxVehicle;

    
    // std::vector<std::vector<float> > freeFlowSpeed;
    // std::vector<std::vector<float> > Qmax;
    // std::vector<std::vector<float> > waveSpeed;
    // std::vector<std::vector<size_t> > maxVehicle;

    std::vector<InputLane*> LaneArr;
    std::vector<u_ll> LaneIds;
    std::vector<int> NumCell_in_Lanes;
    

    //int *width;
    //int *length;


public:
    //Constructor
    InputLink(u_ll id, int lane, float length, float width );
    ~InputLink();

    
    

    /**
     * getFreeFlowSpeed()
     * @brief Get the Free Flow Speed of link
     * Value exists for each cell of the link
     * 
     * 2D vector: numLane x numSect
     * 
     * @return std::vector<std::vector<float> > 
     */

    //each cell might have different 4 params
    // std::vector<std::vector<float> > getFreeFlowSpeed() { return freeFlowSpeed; }
    // std::vector<std::vector<float> > getQmax() { return Qmax; }              
    // std::vector<std::vector<float> > getWaveSpeed() { return waveSpeed; }     
    // std::vector<std::vector<size_t> > getMaxVehicle() { return maxVehicle; }    

    std::vector<u_ll> getLaneIds() { return LaneIds; }
    std::vector<InputLane*> getLaneArr(){return LaneArr;}

    int getNumLane() { return numLane; }
    void setNumLane(int num);
    void pushLaneId(InputLane *lane);
    void setFromNode(u_ll val);
    u_ll getFromNode();
    void setToNode(u_ll val);
    u_ll getToNode();
    //Free 2d Vectors

    //Need to make helper functions for Designating cell-by-cell values
};

#endif
