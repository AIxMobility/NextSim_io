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

    //check
    void showArr();

    //access function
    std::vector<InputAgents> getAgents() { return Agents; }


};


#endif