/**
 * NextSim Captain
 * @file : ODMatrixArr.hpp
 * @version : 1.0
 * @author : ???
 */

#ifndef ODMATRIXARR_H
#define ODMATRIXARR_H

#include <vector>
#include <NextSim_io/inputclass/InputODMatrix.hpp>

namespace NextSimIO
{
/**
 * @class ODMatrix
 * @brief Class for whole OD matrices information from odmatrix.xml
 */
class ODMatrixArr
{
public:
    /**
     * @details Constructor (Parse OD matrix from odmatrix.xml)
    */
    ODMatrixArr();
    
    /**
     * @details Get vector of OD matrix
     * @return Vector of OD matrix
    */
    std::vector<InputODMatrix> GetODMatrix() { return m_odMatrix; }

private:
    /**
     * @details Vector of OD matrix
    */
    std::vector<InputODMatrix> m_odMatrix;

};
} // namespace NextSimIO

#endif