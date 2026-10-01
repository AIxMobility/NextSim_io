/**
 * NextSim Captain
 * @file : V2XArr.hpp
 * @version : 1.3
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
 * @brief Class for V2X configuration
 */
class V2XArr
{
public:
    /**
     * @details Constructor (Parse V2X data from parameter_xml/config_v2x.json)
    */
    V2XArr();

    /**
     * @details Get V2X data vector (usually contains 1 consolidated InputV2X)
     * @return Vector of V2X data objects
    */
    std::vector<InputV2X> GetV2Xs() const { return m_v2xs; }

private:
    /**
     * @details V2X data storage
     */
    std::vector<InputV2X> m_v2xs;
};
} // namespace NextSimIO

#endif
