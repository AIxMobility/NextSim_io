/**
 * NextSim Captain
 * @file : InputPax.hpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#pragma once
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
private:

    /**
     * @details Origin station ID
     */
    int origin;

    /**
     * @details Destination station ID
     */
    int dest;

    /**
     * @details Passenger flow [pax/hr]
     */
    int flow;

    /**
     * @details Estimated distribution of passenger generation
     */
    std::string dist;
    
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
    int getOrigin() { return origin; }

    /**
     * @details Get destination station ID
     * @return Destination station ID
    */
    int getDest() { return dest; }

    /**
     * @details Get passenger flow
     * @return Passenger flow [pax/hr]
    */
    int getFlow() { return flow; }

    /**
     * @details Get estimated distribution of passenger generation
     * @return Estimated distribution of passenger generation
    */
    std::string getDist() { return dist; }
};

/**
 * @class InputAgentPax
 * @brief Class for each agent passenger information
 */
class InputAgentPax
{
private:
    /**
     * @details Agent Passenger ID
     */
    int id;

    /**
     * @details Origin station ID
     */
    int origin_station;

    /**
     * @details Destination station ID
     */
    int dest_station;

    /**
     * @details Departure time
     */
    double dpt_time;

    /**
     * @details Reservation type
     */
    std::string type;
    
public:
    /**
     * @details Constructor
     * @param id Agent Passenger ID
     * @param origin_station Origin station ID
     * @param dest_station Destination station ID
     * @param dpt_time Departure time
     * @param type Reservation type
    */
    InputAgentPax(int id, int origin_station, int dest_station, 
             double dpt_time, std::string type);

    /**
     * @details Get agent passenger ID
     * @return Agent passenger ID
    */
    int getId() { return id; }

    /**
     * @details Get origin station ID
     * @return Origin station ID
    */
    int getOriginStation() { return origin_station; }

    /**
     * @details Get destination station ID
     * @return Destination station ID
    */
    int getDestStation() { return dest_station; }

    /**
     * @details Get departure time
     * @return Departure time
    */
    double getDptTime() { return dpt_time; }

    /**
     * @details Get reservation type
     * @return Reservation type
    */
    std::string getReserveType() { return type; }
};
} // namespace NextSimIO