/**
 * NextSim Captain
 * @file : MessageArr.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#ifndef MESSAGEARR_H
#define MESSAGEARR_H

#include <vector>
#include "InputMessage.hpp"

/**
 * @class MessageArr
 * @brief Class for whole message information
 */
class MessageArr
{
private:

    /**
     * @details Sequence of region messages
    */
    std::vector<InputMessage> RegionMessage;

    /**
     * @details Sequence of vehicle messages
    */
    std::vector<InputMessage> VehMessage;

public:

    /**
     * @details Constructor
    */
    MessageArr();

    // access function
    /**
     * @details Get sequence of region messages
     * @return Sequence of region messages
    */
    std::vector<InputMessage> getRegionMessage()  { return RegionMessage; }

    /**
     * @details Get sequence of vehicle messages
     * @return Sequence of vehicle messages
    */
    std::vector<InputMessage> getVehMessage()  { return VehMessage; }
};

#endif