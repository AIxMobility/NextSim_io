#ifndef VEHARR_H
#define VEHARR_H

#include <vector>
#include "InputVeh.hpp"

class VehArr
{
private:
    std::vector<InputVeh> Vehicles;

public:
    VehArr();

    //check
    void showArr();

    //access function
    std::vector<InputVeh> getVeh() { return Vehicles; }


}




#endif