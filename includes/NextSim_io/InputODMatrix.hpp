/**
 * NextSim Captain
 * @file : InputODMatrix.hpp
 * @version : 1.0
 * @author : ???
 */

#ifndef INPUTODMATRIX_H
#define INPUTODMATRIX_H

#include <vector>
#include <string>
#include <iostream>
#include "InputFlow.hpp"

/**
 * @class InputODMatrix
 * @brief Class for each OD matrix from odmatrix.xml
*/
class InputODMatrix
{
private:

    /**
     * @details OD matrix ID
    */
    int id;

    /**
     * @details Vector of OD flow
    */
    std::vector<InputFlow> odmatrix;

public:

    /**
     * @details Constructor
     * @param id OD matrix ID
     * @param flows Vector of OD flow
    */
    InputODMatrix(int id,
               std::vector<InputFlow> flows);

    /**
     * @details Get OD matrix ID
     * @return OD matrix ID
    */
    int getId() { return id; }

    /**
     * @details Get OD matrix
     * @return OD matrix (Vector of OD flow)
    */
    std::vector<InputFlow> getODmatrix() { return odmatrix; }
};

#endif