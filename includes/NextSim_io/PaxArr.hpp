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
     * @details Sequence of OD passengers
    */
    std::vector<InputODPax> ODPaxVec;

    /**
     * @details Sequence of agent passengers
    */
    std::vector<InputAgentPax> AgentPaxVec;

public:

    /**
     * @details Constructor (Parse passenger information from passenger.xml)
    */
    PaxArr();

    /**
     * @details Get sequence of OD passengers
     * @return Sequence of OD passengers that has origin and destination
    */
    std::vector<InputODPax> getODPax() { return ODPaxVec; }

    /**
     * @details Get sequence of agent passengers
     * @return Sequence of agent passengers that has fixed route
    */
    std::vector<InputAgentPax> getAgentPax() { return AgentPaxVec; }
};
} // namespace NextSimIO