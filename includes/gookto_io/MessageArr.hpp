#ifndef MESSAGEARR_H
#define MESSAGEARR_H

#include <vector>
#include "InputMessage.hpp"

class MessageArr
{
private:
    std::vector<InputMessage> RegionMessage;
    std::vector<InputMessage> VehMessage;

public:
    MessageArr();
    /**
     * Creates a vector of InputMessage
     */

    // access function
    std::vector<InputMessage> getRegionMessage()  { return RegionMessage; }
    std::vector<InputMessage> getVehMessage()  { return VehMessage; }
};

#endif