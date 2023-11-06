#ifndef ODMATRIX_H
#define ODMATRIX_H

#include <vector>
#include "InputAgents.hpp"
#include "DemandInfo.hpp"

class ODMatrix
{
private:
    std::vector<DemandInfo> ODmatrix;

public:
    ODMatrix(const std::string& userName);
    
    //access function
    std::vector<DemandInfo> getODmatrix() { return ODmatrix; }
};

#endif