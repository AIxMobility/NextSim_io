/**
 * NextSim Captain
 * @file : PaxArr.hpp
 * @version : 1.0
 * @author : ???
 */

#pragma once
#include <vector>
#include <string>

#include "InputPax.hpp"

/**
 * @class PaxArr
 * @brief Class for whole passenger information from passenger.xml
 */
class PaxArr
{
private:

    /**
     * @details Sequence of OD passengers
    */
    std::vector<ODPax> ODPaxVec;

    /**
     * @details Sequence of agent passengers
    */
    std::vector<AgentPax> AgentPaxVec;

public:

    /**
     * @details Constructor
    */
    PaxArr();

    /**
     * @details Get sequence of OD passengers
     * @return Sequence of OD passengers that has origin and destination
    */
    std::vector<ODPax> getODPax() { return ODPaxVec; }

    /**
     * @details Get sequence of agent passengers
     * @return Sequence of agent passengers that has fixed route
    */
    std::vector<AgentPax> getAgentPax() { return AgentPaxVec; }
};