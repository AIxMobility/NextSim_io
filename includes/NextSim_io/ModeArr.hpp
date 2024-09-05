/**
 * NextSim Captain
 * @file : ModeArr.hpp
 * @version : 1.0
 * @author : ???
*/

#ifndef MODEARR_H
#define MODEARR_H

#include <vector>
#include "InputMode.hpp"

/**
 * @class ModeArr
 * @brief Class for whole simulation modes from mode.xml
 */
class ModeArr
{
private:
    /**
     * @details Sequence of simulation modes
    */
    std::vector<InputMode> modeArr;

public:
    /**
     * @details Constructor
    */
    ModeArr();
    // Creates a vector of Links

    // vector check
    // ???
    void parseArr();

    //access function
    /**
     * @details Get sequence of simulation modes
     * @return Sequence of simulation modes
    */
    std::vector<InputMode> getModeArr()
    {
        return modeArr;
    }
};

#endif