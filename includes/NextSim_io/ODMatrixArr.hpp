/**
 * NextSim Captain
 * @file : ODMatrixArr.hpp
 * @version : 1.0
 * @author : ???
 */

#ifndef ODMATRIXARR_H
#define ODMATRIXARR_H

#include <vector>
#include "InputAgents.hpp"
#include "InputODMatrix.hpp"

namespace NextSimIO
{
/**
 * @class ODMatrix
 * @brief Class for whole OD matrices information from odmatrix.xml
 */
class ODMatrixArr
{
private:
    /**
     * @details Vector of OD matrix
    */
    std::vector<InputODMatrix> ODmatrix;

public:
    /**
     * @details Constructor (Parse OD matrix from odmatrix.xml)
    */
    ODMatrixArr();
    
    /**
     * @details Get sequence of OD matrix
     * @return Sequence of OD matrix
    */
    std::vector<InputODMatrix> getODmatrix() { return ODmatrix; }
};
} // namespace NextSimIO

#endif