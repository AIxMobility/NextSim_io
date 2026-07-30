/**
 * NextSim Captain
 * @file : ODMatrixArr.hpp
 * @version : 1.0
 * @author : ???
 */

#ifndef ODMATRIXARR_H
#define ODMATRIXARR_H

#include <NextSim_io/inputclass/InputODMatrix.hpp>
#include <filesystem>
#include <vector>

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

    explicit ODMatrixArr(const std::filesystem::path& odMatrixPath);
    
    /**
     * @details Get vector of OD matrix
     * @return Vector of OD matrix
    */
    std::vector<InputODMatrix> GetODMatrix() { return m_odMatrix; }

private:
    void parseODMatrix(const std::filesystem::path& odMatrixPath);

    /**
     * @details Vector of OD matrix
    */
    std::vector<InputODMatrix> m_odMatrix;

};
} // namespace NextSimIO

#endif
