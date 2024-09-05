/**
 * NextSim Captain
 * @file : MessageArr.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#ifndef MESSAGEARR_H
#define MESSAGEARR_H

#include <vector>
#include <NextSim_io/inputdata/InputMessage.hpp>

namespace NextSimIO
{
/**
 * @class MessageArr
 * @brief Class for whole message information from v2xdata.xml
 */
class MessageArr
{
private:

    /**
     * @details Vector of region messages
    */
    std::vector<InputMessage> RegionMessage;

    /**
     * @details Vector of vehicle messages
    */
    std::vector<InputMessage> VehMessage;

public:

    /**
     * @details Constructor (Parse message information from v2xdata.xml)
    */
    MessageArr();

    /**
     * @details Get vector of region messages
     * @return Vector of region messages
    */
    std::vector<InputMessage> getRegionMessage()  { return RegionMessage; }

    /**
     * @details Get vector of vehicle messages
     * @return Vector of vehicle messages
    */
    std::vector<InputMessage> getVehMessage()  { return VehMessage; }
};
} // namespace NextSimIO

#endif