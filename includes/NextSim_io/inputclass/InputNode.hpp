/**
 * NextSim Captain
 * @file : InputNode.hpp
 * @version : 1.0
 * @author : ???
 */

#pragma once
#ifndef INPUTNODE_H
#define INPUTNODE_H

#include "intersection/port.hpp"
#include "intersection/connection.hpp"
#include "intersection/intersectionPhase.hpp"

namespace NextSimIO
{
/**
 * @class InputNode
 * @brief Class for each intersection node information
*/
class InputNode 
{
public:
    /**
     * @details Constructor
     * @param type Node type
     * @param id Node ID
     * @param numConnection Number of connections between links
     * @param numPort Number of connected links
     * @param v2xActive Whether V2X is active or not
    */
    InputNode(int type, int id, int numConnection, 
              int numPort, bool v2xActive);

    /**
     * @details Set node type
     * @param _type Node type (0: Intersection, 1: Normal, 2: Diverging, 3: Terminal, 4: Garage)
    */
    void SetType( int type ) { m_type = type; }

    /**
     * @details Set signal cycle
     * @param cycle Signal cycle [s]
    */
    void SetCycle( int cycle ) { m_cycle = cycle; }

    /**
     * @details Set signal offset
     * @param offset Signal offset [s]
    */
    void SetOffset( int offset ) { m_offset = offset; }

    /**
     * @details Add connection between links into vector
     * @param conn Connection between links
    */
    void pushConnection( connection conn ) { m_connectionTable.push_back(conn); }

    /**
     * @details Add connected link into vector
     * @param link Connected link
    */
    void pushLink( port link ) { m_connectedLinks.push_back(link); }

    /**
     * @details Add signal phase into sequence
     * @param phase Signal phase
    */
    void pushPhase( intersectionPhase phase ) { m_phaseTable.push_back(phase); }

    /**
     * @details Add signal phase length into sequence
     * @param length Signal phase length
    */
    void pushPhaseLength( int length ) { m_phaseLength.push_back(length); }

    /**
     * @details Add signal phase order into sequence
     * @param order Signal phase order
    */
    void pushPhaseOrder( int order ) { m_phaseOrder.push_back(order); }

    /**
     * @details Get node ID
     * @return Node ID
    */
    int GetId() const { return m_id; }

    /**
     * @details Get node type
     * @return Node type (0: Intersection, 1: Normal, 2: Diverging, 3: Terminal, 4: Garage)
    */
    int GetType() { return m_type; }

    /**
     * @details Get number of connections between links
     * @return Number of connections between links
    */
    int GetNumConn() { return m_numConnections; }

    /**
     * @details Get number of connected links
     * @return Number of connected links
    */
    int GetNumLink() { return m_numLinks; }

    /**
     * @details Get whether V2X is active or not
     * @return True(V2X is active) or False(not)
    */
    bool GetV2XActive() { return m_v2xActive; }

    /**
     * @details Get signal cycle
     * @return Signal cycle [s]
    */
    int GetCycle() { return m_cycle; }

    /**
     * @details Get signal offset
     * @return Signal offset [s]
    */
    int GetOffset() { return m_offset; }
    
    /**
     * @details Get connected links
     * @return Vector of connected links
    */
    std::vector<port> GetLinks() { return m_connectedLinks; }

    /**
     * @details Get connections between links
     * @return Vector of connections between links
    */
    std::vector<connection> GetConnections() { return m_connectionTable; }

    /**
     * @details Get signal phases
     * @return Sequence of signal phases
    */
    std::vector<intersectionPhase> GetPhaseTable() { return m_phaseTable; }

    /**
     * @details Get signal phase lengths
     * @return Sequence of signal phase lengths
    */
    std::vector<int> GetPhaseLength() { return m_phaseLength; }

    /**
     * @details Get signal phase orders
     * @return Sequence of signal phase orders
    */
    std::vector<int> GetPhaseOrder() { return m_phaseOrder; }

    /**
     * @details Free connected links vector
    */
    void FreeConnectedLinks() { std::vector<port>().swap(m_connectedLinks); }

    /**
     * @details Free connected table vector
    */
    void FreeConnectedTable() { std::vector<connection>().swap(m_connectionTable); }

    /**
     * @details Free signal phase sequence
    */
    void FreePhaseTable() { std::vector<intersectionPhase>().swap(m_phaseTable); }

    /**
     * @details Free signal phase length sequence
    */
    void FreePhaseLength() { std::vector<int>().swap(m_phaseLength); }

    /**
     * @details Free signal phase order sequence
    */
    void FreePhaseOrder() { std::vector<int>().swap(m_phaseOrder); }

    /**
     * @details Check whether node has signal phase or not
     * @return True(has signal phase) or False(not)
    */
    bool HasPhase() {return !m_phaseTable.empty();}

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
    int m_type; 

    /**
     * @details Node ID
    */
    int m_id;

    /**
     * @details Number of connections between links
    */
    int m_numConnections;

    /**
     * @details Number of connected links
    */
    int m_numLinks;

    /**
     * @details Whether V2X is active or not
    */
    bool m_v2xActive;

    /**
     * @details Vector of connected links
    */
    std::vector<port> m_connectedLinks;

    /**
     * @details Vector of connections between links
    */
    std::vector<connection> m_connectionTable;

    /**
     * @details Sequence of signal phases
    */
    std::vector<intersectionPhase> m_phaseTable;

    /**
     * @details Sequence of signal phase lengths
    */
    std::vector<int> m_phaseLength;

    /**
     * @details Sequence of signal phase orders
    */
    std::vector<int> m_phaseOrder;

    /**
     * @details Signal cycle [s]
    */
    int m_cycle = 0;

    /**
     * @details Signal offset [s]
    */
    int m_offset = 0;

};
} // namespace NextSimIO

#endif