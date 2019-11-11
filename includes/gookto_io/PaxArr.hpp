#pragma once
#include <vector>
#include <string>

#include "InputPax.hpp"

class PaxArr
{
private:
    std::vector<InputPax> Pax;

public:
    PaxArr();

    //access functions
    std::vector<InputPax> getPax() { return Pax; }
};