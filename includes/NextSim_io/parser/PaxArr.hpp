/**
 * NextSim Captain
 * @file : PaxArr.hpp
 * @version : 1.0
 * @author : ???
 */

#pragma once
#include <vector>
#include <string>

#include <NextSim_io/inputdata/InputPax.hpp>

namespace NextSimIO
{
/**
 * @class PaxArr
 * @brief Class for whole passenger information from passenger.xml
 */
class PaxArr
{
private:

    /**
     * @details Vector of OD passengers
    */
    std::vector<InputODPax> ODPaxVec;

    /**
     * @details Vector of agent passengers
    */
    std::vector<InputAgentPax> AgentPaxVec;

public:

    /**
     * @details Constructor (Parse passenger information from passenger.xml)
    */
    PaxArr();

    /**
     * @details Get vector of OD passengers
     * @return Vector of OD passengers that has origin and destination
    */
    std::vector<InputODPax> getODPax() { return ODPaxVec; }

    /**
     * @details Get vector of agent passengers
     * @return Vector of agent passengers that has fixed route
    */
    std::vector<InputAgentPax> getAgentPax() { return AgentPaxVec; }
};
} // namespace NextSimIO