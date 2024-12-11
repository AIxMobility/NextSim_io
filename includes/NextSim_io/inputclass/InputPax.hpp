/**
 * NextSim Captain
 * @file : InputPax.hpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#pragma once
#ifndef INPUTPAX_H
#define INPUTPAX_H

#include <vector>
#include <string>

namespace NextSimIO
{
/**
 * @class InputODPax
 * @brief Class for each origin-destination passenger information
 */
class InputODPax
{
public:
    /**
     * @details Constructor
     * @param origin Origin station ID
     * @param dest Destination station ID
     * @param flow Passenger flow
     * @param dist Estimated distribution of passenger generation
    */
    InputODPax(int origin, int dest, int flow, std::string dist);

    /**
     * @details Get origin station ID
     * @return Origin station ID
    */
    int GetOrigin() { return m_origin; }

    /**
     * @details Get destination station ID
     * @return Destination station ID
    */
    int GetDest() { return m_dest; }

    /**
     * @details Get passenger flow
     * @return Passenger flow [pax/hr]
    */
    int GetFlow() { return m_flow; }

    /**
     * @details Get estimated distribution of passenger generation
     * @return Estimated distribution of passenger generation
    */
    std::string GetDist() { return m_dist; }

private:

    /**
     * @details Origin station ID
     */
    int m_origin;

    /**
     * @details Destination station ID
     */
    int m_dest;

    /**
     * @details Passenger flow [pax/hr]
     */
    int m_flow;

    /**
     * @details Estimated distribution of passenger generation
     */
    std::string m_dist;
};

/**
 * @class InputAgentPax
 * @brief Class for each agent passenger information
 */
class InputAgentPax
{
public:
    /**
     * @details Constructor
     * @param id Agent Passenger ID
     * @param originStation Origin station ID
     * @param destStation Destination station ID
     * @param dptTime Departure time
     * @param type Reservation type
    */
    InputAgentPax(int id, int origin_station, int destStation, 
                  double dptTime, std::string type);

    /**
     * @details Get agent passenger ID
     * @return Agent passenger ID
    */
    int GetId() { return m_id; }

    /**
     * @details Get origin station ID
     * @return Origin station ID
    */
    int GetOriginStation() { return m_originStation; }

    /**
     * @details Get destination station ID
     * @return Destination station ID
    */
    int GetDestStation() { return m_destStation; }

    /**
     * @details Get departure time
     * @return Departure time
    */
    double GetDptTime() { return m_dptTime; }

    /**
     * @details Get reservation type
     * @return Reservation type
    */
    std::string GetReserveType() { return m_type; }

private:
    /**
     * @details Agent Passenger ID
     */
    int m_id;

    /**
     * @details Origin station ID
     */
    int m_originStation;

    /**
     * @details Destination station ID
     */
    int m_destStation;

    /**
     * @details Departure time
     */
    double m_dptTime;

    /**
     * @details Reservation type
     */
    std::string m_type;
};
} // namespace NextSimIO

#endif