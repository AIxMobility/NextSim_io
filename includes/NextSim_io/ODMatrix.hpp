/**
 * NextSim Captain
 * @file : ODMatrix.hpp
 * @version : 1.0
 * @author : ???
 */

#ifndef ODMATRIX_H
#define ODMATRIX_H

#include <vector>
#include "InputAgents.hpp"
#include "DemandInfo.hpp"

/**
 * @class ODMatrix
 * @brief Class for whole demand (per time) information from demand.xml
 */
//??? 뭐라고 해야할지 모르겠음

class ODMatrix
{
private:
    /**
     * @details Sequence of OD matrix
    */
    std::vector<DemandInfo> ODmatrix;

public:
    /**
     * @details Constructor
    */
    ODMatrix();
    
    //access function
    /**
     * @details Get sequence of OD matrix
     * @return Sequence of OD matrix
    */
    std::vector<DemandInfo> getODmatrix() { return ODmatrix; }
};

#endif