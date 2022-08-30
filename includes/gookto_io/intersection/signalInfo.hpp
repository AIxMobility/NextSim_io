#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "intersectionPhase.hpp"

class signalInfo
{
private:
    int node;  //node id 

    std::vector<intersectionPhase> phaseTable; //intersectionPhase:  ID, connectionId (list), priority(list)
    /**
     * intersectionPhase: Intersection
     */

    std::vector<int> phaseLength;
    std::vector<int> phaseOrder;
    int phaseOffset;
    
    
    //signalSequence: order(list), phase_length
    //may have to make this into a Pointer Loop


public:

    signalInfo(int node);

    void initPhase(); //set all priority to 0 for all connections;
    void setPhase( int phase ); //set priority according to chosen phase number
    void setPhaseOffset ( int offset );

    void pushPhase ( intersectionPhase phase );
    void pushPhaseLength ( int length );
    void pushPhaseOrder ( int order );

    //Check Functions
    int getNode() const { return node; }
    // int getNode() const { return node; }

    int getPhaseOffset() { return phaseOffset; }

    std::vector<intersectionPhase> getPhaseTable() { return phaseTable; }
    std::vector<int> getPhaseLength() { return phaseLength; }
    std::vector<int> getPhaseOrder() { return phaseOrder; }

    void freePhaseTable() { std::vector<intersectionPhase>().swap(phaseTable); }
    void freePhaseLength() { std::vector<int>().swap(phaseLength); }
    void freePhaseOrder() { std::vector<int>().swap(phaseOrder); }


};