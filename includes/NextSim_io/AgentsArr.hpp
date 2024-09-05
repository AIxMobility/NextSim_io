/**
 * NextSim Captain
 * @file : AgentsArr.hpp
 * @version : 1.0
 * @author : ???
 */

#ifndef AGENTSARR_H
#define AGENTSARR_H

#include <vector>
#include "InputAgents.hpp"

/**
 * @class AgentsArr
 * @brief Class for whole agents from agents.xml
 */
class AgentsArr
{
private:

    /**
     * @details Sequence of agents
    */
    std::vector<InputAgents> Agents;

    /**
     * @details Sequence of optimal ??? optional ??? agents
    */
    std::vector<InputAgents> Agents_opt;

public:
    
    /**
     * @details Constructor
     */
    AgentsArr();

    //check
    /**
     * @details ???
    */
    void parseAgent(std::string type);

    /**
     * @details Show sequence of agents
    */
    void showArr();

    //access function
    /**
     * @details Get sequence of agents
     * @return Sequence of agents
    */
    std::vector<InputAgents> getAgents() { return Agents; }

    /**
     * @details Get sequence of optimal ??? agents
     * @return Sequence of optimal ??? agents
    */
    std::vector<InputAgents> getAgentsOpt() { return Agents_opt; }

};


#endif