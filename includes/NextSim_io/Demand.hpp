/**
 * NextSim Captain
 * @file : Demand.hpp
 * @version : 1.0
 * @author : ???
 */

#ifndef DEMAND_H
#define DEMAND_H

#include <vector>
#include <string>
#include <iostream>

/**
 * @class Demand
 * @brief Class for each demand (per OD) information from demand.xml
 */
class Demand
{
private:

    /**
     * @details Vehicle type ID (0: Normal Vehicle, 1: Autonomous Vehicle, 2: Truck)
    */
    int type;  // 0: NV, 1: AV, 2: TR

    /**
     * @details Demand flow [veh/hr]
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
    // ??? (0: Normal, 1: LogNormal) 인가 잘 모르겠음
    int dist;

public:

    /**
     * @details Constructor
     * @param type Vehicle type
     * @param flow Demand flow
     * @param sink Sink node ID
     * @param source Source node ID
     * @param dist Estimated distribution ID of departure time
    */
    Demand(int type, int flow, int sink, int source, int dist);

    //access functions

    /**
     * @details Get vehicle type
     * @return Vehicle type ID (0: Normal Vehicle, 1: Autonomous Vehicle, 2: Truck)
    */
    int getType() { return type; }

    /**
     * @details Get demand flow
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
#endif