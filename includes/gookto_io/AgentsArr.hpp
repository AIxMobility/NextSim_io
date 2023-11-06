#ifndef AGENTSARR_H
#define AGENTSARR_H

#include <vector>
#include "InputAgents.hpp"

class AgentsArr
{
private:
    std::vector<InputAgents> Agents;
    std::vector<InputAgents> Agents_opt;

public:
    AgentsArr(const std::string& userName);
    /**
     * Creates a vector of InputAgents
     */

    //check
    void parseAgent(std::string type, const std::string& userName);
    void showArr();

    //access function
    std::vector<InputAgents> getAgents() { return Agents; }
    std::vector<InputAgents> getAgentsOpt() { return Agents_opt; }

};


#endif