#ifndef INPUTLINK_H
#define INPUTLINK_H


#include <vector>
#include <string>
#include "BaseClass.hpp"
#include "InputLane.hpp"
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
    u_ll linkid;
    int numLane;
    std::string _type, _sim_type;


    std::vector<InputLane> LaneArr;
    std::vector<u_ll> LaneIds;
    std::vector<int> NumCell_in_Lanes;
    


public:
    //Constructors
    InputLink(u_ll id, int lane, float length, float width );
    ~InputLink() = default;
    InputLink(const InputLink& link) = default;
    InputLink& operator=(const InputLink& link) = default;

    
    //each cell might have different 4 params
    std::vector<std::vector<float> > get2DFreeFlowSpeed();
    std::vector<std::vector<float> > get2DQmax2D();        
    std::vector<std::vector<float> > get2DWaveSpeed();
    std::vector<std::vector<size_t> > get2DMaxVehicle();
    std::vector<u_ll> getLaneIds() { return LaneIds; }
    std::vector<InputLane> getLaneArr(){return LaneArr;}

    u_ll getId() const { return linkid; }
    int getNumSect(){ return NumCell_in_Lanes[0]; }
    int getNumLane() {return numLane;}
    void setNumLane(int num);

    void pushLaneId(InputLane lane);

    void setFromNode(u_ll val);
    u_ll getFromNode(){return _fromNode;}

    void setToNode(u_ll val);
    u_ll getToNode(){return _toNode;}

    void setSimType(std::string val){ _sim_type = val;}
    std::string getSimType(){return _sim_type;}
    void setType(std::string val){ _type = val;}
    std::string getType(){return _type;}
    //Free 2d Vectors


    //Need to make helper functions for Designating cell-by-cell values
};

#endif
