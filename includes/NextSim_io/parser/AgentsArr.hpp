/**
 * NextSim Captain
 * @file : AgentsArr.hpp
 * @version : 1.0
 * @author : ???
 */

#ifndef AGENTSARR_H
#define AGENTSARR_H

#include <vector>
#include <NextSim_io/inputclass/InputAgents.hpp>

namespace NextSimIO
{
/**
 * @class AgentsArr
 * @brief Class for whole agents from agents.xml
 */
class AgentsArr
{

public:
    
    /**
     * @details Constructor (Parse agents from agents.xml)
     */
    AgentsArr();

    /**
     * @details Show vector of agents
    */
    void ShowArr();

    /**
     * @details Get vector of agents
     * @return Vector of agents
    */
    std::vector<InputAgents> GetAgents() { return m_agents; }

private:

    /**
     * @details Vector of agents
    */
    std::vector<InputAgents> m_agents;
};
} // namespace NextSimIO

#endif