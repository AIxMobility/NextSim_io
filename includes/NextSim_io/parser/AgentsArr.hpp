/**
 * NextSim Captain
 * @file : AgentsArr.hpp
 * @version : 1.0
 * @author : ???
 */

#ifndef AGENTSARR_H
#define AGENTSARR_H

#include <vector>
#include <NextSim_io/inputdata/InputAgents.hpp>

namespace NextSimIO
{
/**
 * @class AgentsArr
 * @brief Class for whole agents from agents.xml
 */
class AgentsArr
{
private:

    /**
     * @details Vector of agents
    */
    std::vector<InputAgents> Agents;

public:
    
    /**
     * @details Constructor (Parse agents from agents.xml)
     */
    AgentsArr();

    /**
     * @details Show vector of agents
    */
    void showArr();

    /**
     * @details Get vector of agents
     * @return Vector of agents
    */
    std::vector<InputAgents> getAgents() { return Agents; }

};
} // namespace NextSimIO

#endif