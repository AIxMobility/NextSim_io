/**
 * NextSim Captain
 * @file : StationArr.hpp
 * @version : 1.0
 * @author : ???
*/

#ifndef STATIONARR_H
#define STATIONARR_H

#include <vector>
#include <NextSim_io/inputclass/InputStation.hpp>

namespace NextSimIO
{
/**
 * @class StationArr
 * @brief Class for whole station information from publictransit.xml
 */
class StationArr
{

public:
    /**
     * @details Constructor (Parse station information from publictransit.xml)
    */
    StationArr();

    /**
     * @details Get vector of stations
     * @return Vector of stations
    */
    std::vector<InputStation> GetStations() { return m_stations; }

    /**
     * @details Get vector of DRT stations
     * @return Vector of DRT stations
    */
    std::vector<InputDRTStation> GetDRTStations() { return m_drtStations; }

private:
    /**
     * @details Vector of stations
    */
    std::vector<InputStation> m_stations;

    /**
     * @details Vector of DRT stations
    */
    std::vector<InputDRTStation> m_drtStations;

};
} // namespace NextSimIO

#endif