#pragma once
#include <vector>
#include <string>

#include "InputPax.hpp"

class PaxArr
{
private:
    std::vector<ODPax> ODPaxVec;
    std::vector<AgentPax> AgentPaxVec;

public:
    PaxArr(const std::string& userName);

    //access functions
    std::vector<ODPax> getODPax() { return ODPaxVec; }
    std::vector<AgentPax> getAgentPax() { return AgentPaxVec; }
};