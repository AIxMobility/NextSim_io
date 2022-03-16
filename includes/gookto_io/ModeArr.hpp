#ifndef MODEARR_H
#define MODEARR_H

#include <vector>
#include "Mode.hpp"

class ModeArr
{
private:
    std::vector<Mode> modeArr;

public:
    ModeArr();
    // Creates a vector of Links

    // vector check
    void parseArr();

    //access function
    std::vector<Mode> getModeArr()
    {
        return modeArr;
    }
};

#endif