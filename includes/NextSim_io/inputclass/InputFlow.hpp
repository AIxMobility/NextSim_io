/**
 * NextSim Captain
 * @file : InputFlow.hpp
 * @version : 1.0
 * @author : ???
 */

#pragma once
#ifndef INPUTFLOW_H
#define INPUTFLOW_H

#include <vector>
#include <string>

namespace NextSimIO
{
/**
 * @class InputFlow
 * @brief Class for each flow (per OD) information from odmatrix.xml
 */
class InputFlow
{
public:

    /**
     * @details Constructor
     * @param type Vehicle type
     * @param flow Flow
     * @param sink Sink node ID
     * @param source Source node ID
     * @param dist Estimated distribution ID of departure time
    */
    InputFlow(int type, int flow, int sink, int source, int dist, bool v2xActive = false);

    /**
     * @details Get vehicle type
     * @return Vehicle type ID (0: Normal Vehicle, 1: Autonomous Vehicle, 2: Truck)
    */
    int GetType() { return m_type; }

    /**
     * @details Get flow
     * @return Flow [veh/hr]
    */
    int GetFlow() { return m_flow; }

    /**
     * @details Get sink node ID
     * @return Sink node ID (destination)
    */
    int GetSink() { return m_sink; }

    /**
     * @details Get source node ID
     * @return Source node ID (origin)
    */
    int GetSource() { return m_source; }

    /**
     * @details Get estimated distribution ID of departure time
     * @return Estimated distribution ID of departure time
    */
    int GetDist() { return m_dist; }

    /**
     * @details Get whether V2X is active for this demand
     * @return True(active) or False(not active)
    */
    bool GetV2XActive() { return m_v2xActive; }
    
private:

    /**
     * @details Vehicle type ID (0: Normal Vehicle, 1: Autonomous Vehicle, 2: Truck)
    */
    int m_type;

    /**
     * @details Flow [veh/hr]
    */
    int m_flow;
    
    /**
     * @details Sink node ID (destination)
    */
    int m_sink;

    /**
     * @details Source node ID (origin)
    */
    int m_source;

    /**
     * @details Estimated distribution ID of departure time
    */
    int m_dist;

    /**
     * @details Whether V2X is active for this demand
    */
    bool m_v2xActive = false;
};
} // namespace NextSimIO

#endif
