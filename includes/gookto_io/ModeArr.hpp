#ifndef MODEARR_H
#define MODEARR_H

#include <vector>
#include "InputMode.hpp"

class ModeArr
{
private:
    std::vector<InputMode> modeArr;

public:
    ModeArr(const std::string& userName);
    // Creates a vector of Links

    // vector check
    void parseArr(const std::string& userName);

    //access function
    std::vector<InputMode> getModeArr()
    {
        return modeArr;
    }
};

#endif