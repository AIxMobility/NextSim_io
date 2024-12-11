/**
 * NextSim Captain
 * @file : port.hpp
 * @version : 1.0
 * @author : ???
 */

#pragma once
#ifndef PORT_H
#define PORT_H

#include <vector>
#include <string>

namespace NextSimIO
{
/**
 * @class port
 * @brief Class for intersection port information
 */
class port
{
public:
    /**
     * @details Constructor
     * @param id Link ID that the port is connected to
     * @param dir Direction of the port
     * @param type Type of the port
     */
    port(int id, int dir, int type);

    /**
     * @details Get link ID that the port is connected to
     * @return Link ID
     */
    int GetLinkId() { return m_linkId; }

    /**
     * @details Get direction of the port
     * @return Direction (0: N, 1: E, 2: S, 3: W)
     */
    int GetDirection() { return m_direction; }
    
    /**
     * @details Get type of the port
     * @return Type (1: incoming, -1: outgoing)
     */
    int GetType() { return m_type; }

private:
    /**
     * @details Link ID that the port is connected to
    */
    int m_linkId;
    
    /**
     * @details Direction of the port (0: N, 1: E, 2: S, 3: W)
    */
    int m_direction;

    /**
     * @details Type of the port (1: incoming, -1: outgoing)
    */
    int m_type;
};
} // namespace NextSimIO

#endif