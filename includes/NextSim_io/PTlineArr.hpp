/**
 * NextSim Captain
 * @file : PTlineArr.hpp
 * @version : 1.0
 * @author : ???
 */

#ifndef PTROUTEARR_H
#define PTROUTEARR_H

#include <vector>
#include "InputPTline.hpp"

/**
 * @class PTlineArr
 * @brief Class for whole public transit line information from ptline.xml
*/
class PTlineArr
{
private:
    /**
     * @details Sequence of public transit lines
    */
    std::vector<InputPTline> ptlineArr;

public:
    /**
     * @details Constructor
    */
    PTlineArr();

    // vector check
    // ???
    void parseArr();

    //access function
    /**
     * @details Get sequence of public transit lines
     * @return Sequence of public transit lines
    */
    std::vector<InputPTline> getPTlines()
    {
        return ptlineArr;
    }
};

#endif