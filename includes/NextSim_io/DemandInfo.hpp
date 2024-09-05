/**
 * NextSim Captain
 * @file : DemandInfo.hpp
 * @version : 1.0
 * @author : ???
 */

#ifndef DEMANDINFO_H
#define DEMANDINFO_H

#include <vector>
#include <string>
#include <iostream>
#include "Demand.hpp"

/**
 * @class DemandInfo
 * @brief Class for each demand (per network) from demand.xml
*/

class DemandInfo
{
private:

    /**
     * @details Demand ID
    */
    int id;

    /**
     * @details Sequence of demands
    */
    std::vector<Demand> demands;

public:

    /**
     * @details Constructor
     * @param id Demand ID
     * @param demands Sequence of demands
    */
    DemandInfo(int id,
               std::vector<Demand> demands);

    /**
     * @details Get demand ID
     * @return Demand ID
    */
    int getId() { return id; }

    /**
     * @details Get sequence of demands
     * @return Sequence of demands
    */
    std::vector<Demand> getDemands() { return demands; }
};

#endif