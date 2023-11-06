#ifndef PTROUTEARR_H
#define PTROUTEARR_H

#include <vector>
#include "InputPTline.hpp"

class PTlineArr
{
private:
    std::vector<InputPTline> ptlineArr;

public:
    PTlineArr(const std::string& userName);
    // Creates a vector of Links

    // vector check
    void parseArr(const std::string& userName);

    //access function
    std::vector<InputPTline> getPTlines()
    {
        return ptlineArr;
    }
};

#endif