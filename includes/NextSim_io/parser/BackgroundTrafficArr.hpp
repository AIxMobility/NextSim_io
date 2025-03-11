/**
 * NextSim Captain
 * @file : BackgroundTrafficArr.hpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#ifndef BACKGROUNDTRAFFICARR_H
#define BACKGROUNDTRAFFICARR_H

#include <vector>
#include <NextSim_io/inputclass/InputBackgroundTraffic.hpp>

namespace NextSimIO
{
/**
 * @class BackgroundTrafficArr
 * @brief Class for background traffic array
 */
class BackgroundTrafficArr
{
public:
    /**
     * @details Constructor
     * @param BackgroundTraffic Background traffic information
     */
    BackgroundTrafficArr();
    
    /**
     * @details Get Background traffic information
     * @return Background traffic information
     */
    std::vector<InputBackgroundTraffic> GetBackgroundTraffics() { return m_BackgroundTraffics; }

private:
    /**
     * @details Background traffic information
     */
    std::vector<InputBackgroundTraffic> m_BackgroundTraffics;
};
} // namespace NextSimIO

#endif