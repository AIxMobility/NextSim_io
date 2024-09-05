#pragma once
#include <vector>
#include <string>
#include <iostream>

namespace NextSimIO
{
/**
 * @class port
 * @brief Class for intersection port information
 */
class port
{
private:
    /**
     * @details Link ID that the port is connected to
    */
    int linkId;
    
    /**
     * @details Direction of the port (0: N, 1: E, 2: S, 3: W)
    */
    int direction;

    /**
     * @details Type of the port (1: incoming, -1: outgoing)
    */
    int type;

public:
    /**
     * @details Constructor
     * @param id Link ID that the port is connected to
     * @param dir Direction of the port
     * @param type Type of the port
     */
    port(int id, int dir, int type) :
        linkId(id), direction(dir), type(type) {};

    /**
     * @details Get link ID that the port is connected to
     * @return Link ID
     */
    int getLinkId() { return linkId; }

    /**
     * @details Get direction of the port
     * @return Direction (0: N, 1: E, 2: S, 3: W)
     */
    int getDir() { return direction; }
    
    /**
     * @details Get type of the port
     * @return Type (1: incoming, -1: outgoing)
     */
    int getType() { return type; }

};
} // namespace NextSimIO