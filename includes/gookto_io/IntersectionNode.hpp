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
        Terminal = 2
     */
    int type; 
    int id;
    int numConnections; //num_connection
    /**
     * numConnections: Applicable only for IntersectionNode
     */
    int numLinks; //num_port
    std::vector<port> connectedLinks;//port:  linkId, direction, type(in / out)
    /**
     * port: Intersection, Terminal
     */
    std::vector<connection> connectionTable; //connection:  connectionId (index), to_lane, to_link, from_lane, from_link, length
    /**
     * connection: Intersection, Normal
     */
    std::vector<intersectionPhase> phaseTable; //intersectionPhase:  id, connectionId (list), priority(list)
    /**
     * intersectionPhase: Intersection
     */
    
    //signalSequence: order(list), phase_length
    //may have to make this into a Pointer Loop

public:
    IntersectionNode(int type, int id, int num_connection, int num_port);

    void initPhase(); //set all priority to 0 for all connections;
    void setPhase( int phase ); //set priority according to chosen phase number

    void pushConnection( connection conn );
    void pushLink( port link );
    void pushPhase ( intersectionPhase phase );

    //Check Functions
    int getId() { return id; }
    int getType() { return type; }
    int getNumConn() { return numConnections; }
    int getNumLink() { return numLinks; }

    std::vector<port> getLinks() { return connectedLinks; }
    std::vector<connection> getConnections() { return connectionTable; }
    std::vector<intersectionPhase> getPhaseTable() { return phaseTable; }

    void freeConnectedLinks() { std::vector<port>().swap(connectedLinks); }
    void freeConnectedTable() { std::vector<connection>().swap(connectionTable); }
    void freePhaseTable() { std::vector<intersectionPhase>().swap(phaseTable); }
};