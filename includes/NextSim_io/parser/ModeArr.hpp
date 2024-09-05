/**
 * NextSim Captain
 * @file : ModeArr.hpp
 * @version : 1.0
 * @author : ???
*/

#ifndef MODEARR_H
#define MODEARR_H

#include <vector>
#include <NextSim_io/inputdata/InputMode.hpp>

namespace NextSimIO
{
/**
 * @class ModeArr
 * @brief Class for whole simulation modes from mode.xml
 */
class ModeArr
{
private:
    /**
     * @details Vector of simulation modes
    */
    std::vector<InputMode> modeArr;

public:
    /**
     * @details Constructor (Parse simulation mode information from mode.xml)
    */
    ModeArr();

    /**
     * @details Get vector of simulation modes
     * @return Vector of simulation modes
    */
    std::vector<InputMode> getModeArr()
    {
        return modeArr;
    }
};
} // namespace NextSimIO

#endif