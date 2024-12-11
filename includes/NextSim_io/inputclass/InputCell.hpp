/**
 * NextSim Captain
 * @file : InputCell.hpp
 * @version : 1.0
 * @author : ???
 */

#pragma once
#ifndef INPUTCELL_H
#define INPUTCELL_H

#include "BaseClass.hpp"

namespace NextSimIO
{
/**
 * @class InputCell
 * @brief Class for each cell information
*/
class InputCell: public MetaData
{
public:
    /**
     * @details Constructor
     * @param id Cell ID
     * @param offset Location of starting point of cell
     * @param length Cell length
    */
    InputCell(std::size_t id, double offset, double length);

    /** @cond EXCLUDE */
    ~InputCell() = default;
    InputCell(const InputCell& cell) = default;
    InputCell& operator=(const InputCell& cell) = default;
    /** @endcond */

    /**
     * @details Set offset of cell
     * @param offset Location of starting point of cell
    */
    void SetOffset(double offset) { m_offset = offset; }

    /**
     * @details Get offset of cell
     * @return Location of starting point of cell
    */
    const double GetOffset() const { return m_offset; }

private:
    /**
     * @details Location of starting point of cell
    */
    double m_offset;

};
} // namespace NextSimIO

#endif