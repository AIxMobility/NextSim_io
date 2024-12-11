/**
 * NextSim Captain
 * @file : MessageArr.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#ifndef MESSAGEARR_H
#define MESSAGEARR_H

#include <vector>
#include <NextSim_io/inputclass/InputMessage.hpp>

namespace NextSimIO
{
/**
 * @class MessageArr
 * @brief Class for whole message information from v2xdata.xml
 */
class MessageArr
{
public:
    /**
     * @details Constructor (Parse message information from v2xdata.xml)
    */
    MessageArr();

    /**
     * @details Get vector of region messages
     * @return Vector of region messages
    */
    std::vector<InputMessage> GetRegionMessage()  { return m_regionMessage; }

    /**
     * @details Get vector of vehicle messages
     * @return Vector of vehicle messages
    */
    std::vector<InputMessage> GetVehMessage()  { return m_vehMessage; }

private:
    /**
     * @details Vector of region messages
    */
    std::vector<InputMessage> m_regionMessage;

    /**
     * @details Vector of vehicle messages
    */
    std::vector<InputMessage> m_vehMessage;
};
} // namespace NextSimIO

#endif