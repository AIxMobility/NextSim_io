#ifndef PTROUTEARR_H
#define PTROUTEARR_H

#include <vector>
#include "InputPTRoute.hpp"

class PTRouteArr
{
private:
    std::vector<InputPTRoute> ptrouteArr;

public:
    PTRouteArr();
    // Creates a vector of Links

    // vector check
    void parseArr();

    //access function
    std::vector<InputPTRoute> getPTRoutes()
    {
        return ptrouteArr;
    }
};

#endif