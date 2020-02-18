#ifndef AGENTSARR_H
#define AGENTSARR_H

#include <vector>
#include "InputAgents.hpp"

class AgentsArr
{
private:
    std::vector<InputAgents> Agents;

public:
    AgentsArr();
    /**
     * Creates a vector of InputAgents
     */

    //check
    void showArr();

    //access function
    std::vector<InputAgents> getAgents() { return Agents; }


};


#endif