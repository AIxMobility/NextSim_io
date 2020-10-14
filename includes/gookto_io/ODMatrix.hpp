#ifndef ODMATRIX_H
#define ODMATRIX_H

#include <vector>
#include "InputAgents.hpp"
#include "Demand.hpp"

class ODMatrix
{
private:
    std::vector<Demand> Demands;

public:
    ODMatrix();
    /**
     * Creates a vector of InputAgents
     */

    //access function
    std::vector<Demand> getDemands() { return Demands; }
};

#endif