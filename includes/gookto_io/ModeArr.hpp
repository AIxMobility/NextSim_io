#ifndef MODEARR_H
#define MODEARR_H

#include <vector>
#include "InputMode.hpp"

class ModeArr
{
private:
    std::vector<InputMode> modeArr;

public:
    ModeArr();
    // Creates a vector of Links

    // vector check
    void parseArr();

    //access function
    std::vector<InputMode> getModeArr()
    {
        return modeArr;
    }
};

#endif