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
private:

    /**
     * @details Vector of stations
    */
    std::vector<InputStation> Stations;

    /**
     * @details Vector of DRT stations
    */
    std::vector<InputDRTStation> DRTStations;

public:
    /**
     * @details Constructor (Parse station information from publictransit.xml)
    */
    StationArr();

    /**
     * @details Get vector of stations
     * @return Vector of stations
    */
    std::vector<InputStation> getStations() { return Stations; }

    /**
     * @details Get vector of DRT stations
     * @return Vector of DRT stations
    */
    std::vector<InputDRTStation> getDRTStations() { return DRTStations; }
};
} // namespace NextSimIO

#endif