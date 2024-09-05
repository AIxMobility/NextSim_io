/**
 * NextSim Captain
 * @file : InputPax.hpp
 * @version : 1.0
 * @author : ???
 */

#pragma once
#include <vector>
#include <string>

/**
 * @class ODPax
 * @brief Class for each origin-destination passenger information
 */
class ODPax
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
    // ??? InputDataTable.xlsx 에는 veh/hr로 되어있음
    int flow; // pax/hr

    /**
     * @details Estimated distribution of departure time
     */
    std::string dist;
    
public:
    /**
     * @details Constructor
     * @param origin Origin station ID
     * @param dest Destination station ID
     * @param flow Passenger flow
     * @param dist Estimated distribution of departure time
    */
    ODPax(int origin, int dest, int flow, std::string dist);

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
     * @details Get estimated distribution of departure time
     * @return Estimated distribution of departure time (Normal, Lognormal) ???
    */
    std::string getDist() { return dist; }
};

/**
 * @class AgentPax
 * @brief Class for each agent passenger information
 */
class AgentPax
{
private:
    /**
     * @details Agent ID
     */
    int id;

    /**
     * @details Origin station ID
     */
    // ??? agent pax인데 OD로 잘못 코드 작성돼있음 (input table 내에는 origin link, pos를 사용)
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
     * @param id Agent ID
     * @param origin_station Origin station ID
     * @param dest_station Destination station ID
     * @param dpt_time Departure time
     * @param type Reservation type
    */
    AgentPax(int id, int origin_station, int dest_station, 
             double dpt_time, std::string type);

    /**
     * @details Get agent ID
     * @return Agent ID
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