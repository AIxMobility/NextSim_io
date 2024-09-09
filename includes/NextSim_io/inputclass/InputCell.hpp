/**
 * NextSim Captain
 * @file : InputCell.hpp
 * @version : 1.0
 * @author : ???
 */

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
    private:
        /**
         * @details Location of starting point of cell
        */
        double offset;

    public:
        /**
         * @details Constructor
         * @param id_val Cell ID
         * @param offset_val Location of starting point of cell
         * @param length_val Cell length
        */
        InputCell(std::size_t id_val, double offset_val, double length_val);

        /** @cond EXCLUDE */
        ~InputCell() = default;
        InputCell(const InputCell& cell) = default;
        InputCell& operator=(const InputCell& cell) = default;
        /** @endcond */

        /**
         * @details Set offset of cell
         * @param offset_val Location of starting point of cell
        */
        void setOffset(double offset_val) { offset = offset_val; }

        /**
         * @details Get offset of cell
         * @return Location of starting point of cell
        */
        const double getOffset() const { return offset; }

};
} // namespace NextSimIO

#endif