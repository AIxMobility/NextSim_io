/**
 * NextSim Captain
 * @file : InputODMatrix.hpp
 * @version : 1.0
 * @author : ???
 */

#pragma once
#ifndef INPUTODMATRIX_H
#define INPUTODMATRIX_H

#include "InputFlow.hpp"

namespace NextSimIO
{
/**
 * @class InputODMatrix
 * @brief Class for each OD matrix from odmatrix.xml
*/
class InputODMatrix
{
public:

    /**
     * @details Constructor
     * @param id OD matrix ID
     * @param odMatrix Vector of OD flow
    */
    InputODMatrix(int id, std::vector<InputFlow> odMatrix);
    
    /**
     * @details Get OD matrix ID
     * @return OD matrix ID
    */
    int GetId() { return m_id; }

    /**
     * @details Get OD matrix
     * @return OD matrix (Vector of OD flow)
    */
    std::vector<InputFlow> GetODMatrix() { return m_odMatrix; }

private:

    /**
     * @details OD matrix ID
    */
    int m_id;

    /**
     * @details Vector of OD flow
    */
    std::vector<InputFlow> m_odMatrix;
};
} // namespace NextSimIO

#endif