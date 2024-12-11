/**
 * NextSim Captain
 * @file : PaxArr.hpp
 * @version : 1.0
 * @author : ???
 */

#pragma once
#include <vector>
#include <string>

#include <NextSim_io/inputclass/InputPax.hpp>

namespace NextSimIO
{
/**
 * @class PaxArr
 * @brief Class for whole passenger information from passenger.xml
 */
class PaxArr
{
public:

    /**
     * @details Constructor (Parse passenger information from passenger.xml)
    */
    PaxArr();

    /**
     * @details Get vector of OD passengers
     * @return Vector of OD passengers that has origin and destination
    */
    std::vector<InputODPax> GetODPax() { return m_odPax; }

    /**
     * @details Get vector of agent passengers
     * @return Vector of agent passengers that has fixed route
    */
    std::vector<InputAgentPax> GetAgentPax() { return m_agentPax; }

private:

    /**
     * @details Vector of OD passengers
    */
    std::vector<InputODPax> m_odPax;

    /**
     * @details Vector of agent passengers
    */
    std::vector<InputAgentPax> m_agentPax;

};
} // namespace NextSimIO