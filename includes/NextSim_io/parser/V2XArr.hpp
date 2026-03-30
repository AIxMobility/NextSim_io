/**
 * NextSim Captain
 * @file : V2XArr.hpp
 * @version : 1.1
 * @author : Elena
 */

#ifndef V2XARR_HPP
#define V2XARR_HPP

#include <vector>
#include <NextSim_io/inputclass/InputV2X.hpp>

namespace NextSimIO
{
/**
 * @class V2XArr
 * @brief Class for V2X configuration and event information
 */
class V2XArr
{
public:
    /**
     * @details Constructor (Parse V2X data from config_v2x.json and event_v2x.json)
    */
    V2XArr();

    /**
     * @details Get V2X data
     * @return V2X data object
    */
    V2XData GetV2XData() const { return m_v2xData; }

private:
    /**
     * @details V2X data storage
     */
    V2XData m_v2xData;
};
} // namespace NextSimIO

#endif