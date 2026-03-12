/**
 * NextSim Captain
 * @file : MessageArr.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#ifndef V2XMSGARR_HPP
#define V2XMSGARR_HPP

#include <vector>
#include <NextSim_io/inputclass/InputV2XMsg.hpp>

namespace NextSimIO
{
/**
 * @class V2XMsgArr
 * @brief Class for whole msg information from v2xdata.xml
 */
class V2XMsgArr
{
public:
    /**
     * @details Constructor (Parse msg information from v2xdata.xml)
    */
    V2XMsgArr();

    /**
     * @details Get vector of region msgs
     * @return Vector of region msgs
    */
    std::vector<InputV2XMsg> GetRegionMsg()  { return m_regionMsg; }

    /**
     * @details Get vector of vehicle msgs
     * @return Vector of vehicle msgs
    */
    std::vector<InputV2XMsg> GetVehMsg()  { return m_vehMsg; }

private:
    /**
     * @details Vector of region msgs
    */
    std::vector<InputV2XMsg> m_regionMsg;

    /**
     * @details Vector of vehicle msgs
    */
    std::vector<InputV2XMsg> m_vehMsg;
};
} // namespace NextSimIO

#endif