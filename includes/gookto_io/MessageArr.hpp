/**
 * STS19 Captain
 * @file : MessageArr.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

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
    MessageArr(const std::string& userName);
    /**
     * Creates a vector of InputMessage
     */

    // access function
    std::vector<InputMessage> getRegionMessage()  { return RegionMessage; }
    std::vector<InputMessage> getVehMessage()  { return VehMessage; }
};

#endif