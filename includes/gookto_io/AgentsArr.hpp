#ifndef AGENTSARR_H
#define AGENTSARR_H

#include <vector>
#include "InputAgents.hpp"

class AgentsArr
{
private:
    std::vector<InputAgents> Agents;
    std::vector<InputAgents> Shuttles;

public:
    AgentsArr();
    /**
     * Creates a vector of InputAgents
     */

    //check
    void parseAgent(std::string type);
    void showArr();

    //access function
    std::vector<InputAgents> getAgents() { return Agents; }
    std::vector<InputAgents> getShuttles() { return Shuttles; }

};


#endif