#include <string>
#include <iostream>
#include <vector>

#include "intersection/port.hpp"
#include "intersection/connection.hpp"
#include "intersection/intersectionPhase.hpp"

#pragma once


class IntersectionNode 
{
private:
    /*
    Node Types:
        Intersection = 0
        Normal = 1
        Diverging = 2
        Terminal = 3
        Garage = 4
     */
    int type; 
    int id;
    int numConnections;
    int numLinks;
    bool v2xActive;
    std::vector<port> connectedLinks;
    std::vector<connection> connectionTable;
    std::vector<intersectionPhase> phaseTable;

    std::vector<int> phaseLength;
    std::vector<int> phaseOrder;
    int cycle = 0;
    int offset = 0;
    
    
    //signalSequence: order(list), phase_length
    //may have to make this into a Pointer Loop

public:
    IntersectionNode(int type, int id, int num_connection, int num_port, bool v2xActive);

    void setType( int _type );

    void initPhase(); //set all priority to 0 for all connections;
    void setPhase( int phase ); //set priority according to chosen phase number
    void setCycle ( int cycle );
    void setOffset ( int offset );

    void pushConnection( connection conn );
    void pushLink( port link );
    void pushPhase ( intersectionPhase phase );
    void pushPhaseLength ( int length );
    void pushPhaseOrder ( int order );

    //Check Functions
    int getId() const { return id; }
    int getType() { return type; }
    int getNumConn() { return numConnections; }
    int getNumLink() { return numLinks; }
    bool getV2XActive() { return v2xActive; }
    int getCycle() { return cycle; }
    int getOffset() { return offset; }
    
    std::vector<port> getLinks() { return connectedLinks; }
    std::vector<connection> getConnections() { return connectionTable; }
    std::vector<intersectionPhase> getPhaseTable() { return phaseTable; }
    std::vector<int> getPhaseLength() { return phaseLength; }
    std::vector<int> getPhaseOrder() { return phaseOrder; }

    void freeConnectedLinks() { std::vector<port>().swap(connectedLinks); }
    void freeConnectedTable() { std::vector<connection>().swap(connectionTable); }
    void freePhaseTable() { std::vector<intersectionPhase>().swap(phaseTable); }
    void freePhaseLength() { std::vector<int>().swap(phaseLength); }
    void freePhaseOrder() { std::vector<int>().swap(phaseOrder); }

    bool hasPhase() {return !phaseTable.empty();}
};