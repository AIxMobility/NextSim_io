#ifndef AGENTTYPESARR_H
#define AGENTTYPESARR_H

#include <vector>
#include "InputAgentTypes.hpp"

class AgentTypesArr
{
private:
    std::vector<InputAgentTypes> vehTypes;

public:
    AgentTypesArr();

    //access function
    InputAgentTypes getAgentType(int type) { return vehTypes.at(type); }
};


#endif