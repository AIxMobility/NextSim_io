/**
 * NextSim Captain
 * @file : InputFlow.hpp
 * @version : 1.0
 * @author : ???
 */

#ifndef INPUTFLOW_H
#define INPUTFLOW_H

#include <vector>
#include <string>
#include <iostream>

namespace NextSimIO
{
/**
 * @class InputFlow
 * @brief Class for each flow (per OD) information from odmatrix.xml
 */
class InputFlow
{
private:

    /**
     * @details Vehicle type ID (0: Normal Vehicle, 1: Autonomous Vehicle, 2: Truck)
    */
    int type;

    /**
     * @details Flow [veh/hr]
    */
    int flow;
    
    /**
     * @details Sink node ID (destination)
    */
    int sink;

    /**
     * @details Source node ID (origin)
    */
    int source;

    /**
     * @details Estimated distribution ID of departure time
    */
    int dist;

public:

    /**
     * @details Constructor
     * @param type Vehicle type
     * @param flow Flow
     * @param sink Sink node ID
     * @param source Source node ID
     * @param dist Estimated distribution ID of departure time
    */
    InputFlow(int type, int flow, int sink, int source, int dist);


    /**
     * @details Get vehicle type
     * @return Vehicle type ID (0: Normal Vehicle, 1: Autonomous Vehicle, 2: Truck)
    */
    int getType() { return type; }

    /**
     * @details Get flow
     * @return Flow [veh/hr]
    */
    int getFlow() { return flow; }

    /**
     * @details Get sink node ID
     * @return Sink node ID (destination)
    */
    int getSink() { return sink; }

    /**
     * @details Get source node ID
     * @return Source node ID (origin)
    */
    int getSource() { return source; }

    /**
     * @details Get estimated distribution ID of departure time
     * @return Estimated distribution ID of departure time
    */
    int getDist() { return dist; }
};
} // namespace NextSimIO

#endif