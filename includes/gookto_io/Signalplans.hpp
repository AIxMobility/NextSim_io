#include <string>
#include <iostream>
#include <vector>

#include "intersection/intersectionPhase.hpp"
#include "intersection/signalInfo.hpp"

#pragma once


class Signalplans 
{
private:
    /*
    Node Types:
        Intersection = 0
        Normal = 1
        Terminal = 2
     */
    int id;

    double end; //end time
    
    double start; // start time  

    std::vector<signalInfo> nodeSignal; //intersectionPhase:  ID, connectionId (list), priority(list)

    /**
     * numConnections: Applicable only for IntersectionNode
     */
    // std::vector<intersectionSignal> signalTable; //intersectionPhase:  ID, connectionId (list), priority(list)


public:
    Signalplans(int id, double end, double start);

    void initPhase(); //set all priority to 0 for all connections;
    void setPhase( int phase ); //set priority according to chosen phase number
    void setPhaseOffset ( int offset );

    void pushInfo ( signalInfo node );
    // void pushPhaseLength ( int length );
    // void pushPhaseOrder ( int order );

    //Check Functions
    int getId() const { return id; }
    // int getNode() const { return node; }

    // int getPhaseOffset() { return phaseOffset; }

    // std::vector<intersectionPhase> getPhaseTable() { return phaseTable; }
    // std::vector<int> getPhaseLength() { return phaseLength; }
    // std::vector<int> getPhaseOrder() { return phaseOrder; }

    // void freePhaseTable() { std::vector<intersectionPhase>().swap(phaseTable); }
    // void freePhaseLength() { std::vector<int>().swap(phaseLength); }
    // void freePhaseOrder() { std::vector<int>().swap(phaseOrder); }
};