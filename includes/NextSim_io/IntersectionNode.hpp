/**
 * NextSim Captain
 * @file : IntersectionNode.hpp
 * @version : 1.0
 * @author : ???
 */

#include <string>
#include <iostream>
#include <vector>

#include "intersection/port.hpp"
#include "intersection/connection.hpp"
#include "intersection/intersectionPhase.hpp"

#pragma once

namespace NextSimIO
{
/**
 * @class IntersectionNode
 * @brief Class for each intersection node information
*/
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

    /**
     * @details Node type (0: Intersection, 1: Normal, 2: Diverging, 3: Terminal, 4: Garage)
    */
    int type; 

    /**
     * @details Node ID
    */
    int id;

    /**
     * @details Number of connections between links
    */
    int numConnections;

    /**
     * @details Number of connected links
    */
    int numLinks;

    /**
     * @details Whether V2X is active or not
    */
    bool v2xActive;

    /**
     * @details Sequence of connected links
    */
    std::vector<port> connectedLinks;

    /**
     * @details Sequence of connections between links
    */
    std::vector<connection> connectionTable;

    /**
     * @details Sequence of signal phases
    */
    std::vector<intersectionPhase> phaseTable;

    /**
     * @details Sequence of signal phase lengths
    */
    std::vector<int> phaseLength;

    /**
     * @details Sequence of signal phase orders
    */
    std::vector<int> phaseOrder;

    /**
     * @details Signal cycle [s]
    */
    int cycle = 0;

    /**
     * @details Signal offset [s]
    */
    int offset = 0;
    
    
    //signalSequence: order(list), phase_length
    //may have to make this into a Pointer Loop

public:
    /**
     * @details Constructor
     * @param type Node type
     * @param id Node ID
     * @param num_connection Number of connections between links
     * @param num_port Number of connected links
     * @param v2xActive Whether V2X is active or not
    */
    IntersectionNode(int type, int id, int num_connection, int num_port, bool v2xActive);

    /**
     * @details Set node type
     * @param _type Node type (0: Intersection, 1: Normal, 2: Diverging, 3: Terminal, 4: Garage)
    */
    void setType( int _type );

    /**
     * @details Initiate signal phase
    */
    void initPhase(); //set all priority to 0 for all connections;

    /**
     * @details Set current signal phase
     * @param phase Signal phase ID
    */
    void setPhase( int phase ); //set priority according to chosen phase number

    /**
     * @details Set signal cycle
     * @param cycle Signal cycle [s]
    */
    void setCycle ( int cycle );

    /**
     * @details Set signal offset
     * @param offset Signal offset [s]
    */
    void setOffset ( int offset );

    /**
     * @details Add connection between links into sequence
     * @param conn Connection between links
    */
    void pushConnection( connection conn );

    /**
     * @details Add connected link into sequence
     * @param link Connected link
    */
    void pushLink( port link );

    /**
     * @details Add signal phase into sequence
     * @param phase Signal phase
    */
    void pushPhase ( intersectionPhase phase );

    /**
     * @details Add signal phase length into sequence
     * @param length Signal phase length
    */
    void pushPhaseLength ( int length );

    /**
     * @details Add signal phase order into sequence
     * @param order Signal phase order
    */
    void pushPhaseOrder ( int order );

    //Check Functions
    /**
     * @details Get node ID
     * @return Node ID
    */
    int getId() const { return id; }

    /**
     * @details Get node type
     * @return Node type (0: Intersection, 1: Normal, 2: Diverging, 3: Terminal, 4: Garage)
    */
    int getType() { return type; }

    /**
     * @details Get number of connections between links
     * @return Number of connections between links
    */
    int getNumConn() { return numConnections; }

    /**
     * @details Get number of connected links
     * @return Number of connected links
    */
    int getNumLink() { return numLinks; }

    /**
     * @details Get whether V2X is active or not
     * @return True(V2X is active) or False(not)
    */
    bool getV2XActive() { return v2xActive; }

    /**
     * @details Get signal cycle
     * @return Signal cycle [s]
    */
    int getCycle() { return cycle; }

    /**
     * @details Get signal offset
     * @return Signal offset [s]
    */
    int getOffset() { return offset; }
    
    /**
     * @details Get connected links
     * @return Sequence of connected links
    */
    std::vector<port> getLinks() { return connectedLinks; }

    /**
     * @details Get connections between links
     * @return Sequence of connections between links
    */
    std::vector<connection> getConnections() { return connectionTable; }

    /**
     * @details Get signal phases
     * @return Sequence of signal phases
    */
    std::vector<intersectionPhase> getPhaseTable() { return phaseTable; }

    /**
     * @details Get signal phase lengths
     * @return Sequence of signal phase lengths
    */
    std::vector<int> getPhaseLength() { return phaseLength; }

    /**
     * @details Get signal phase orders
     * @return Sequence of signal phase orders
    */
    std::vector<int> getPhaseOrder() { return phaseOrder; }

    //???
    void freeConnectedLinks() { std::vector<port>().swap(connectedLinks); }
    void freeConnectedTable() { std::vector<connection>().swap(connectionTable); }
    void freePhaseTable() { std::vector<intersectionPhase>().swap(phaseTable); }
    void freePhaseLength() { std::vector<int>().swap(phaseLength); }
    void freePhaseOrder() { std::vector<int>().swap(phaseOrder); }

    /**
     * @details Check whether node has signal phase or not
     * @return True(has signal phase) or False(not)
    */
    bool hasPhase() {return !phaseTable.empty();}
};
} // namespace NextSimIO