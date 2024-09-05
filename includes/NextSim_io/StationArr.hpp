/**
 * NextSim Captain
 * @file : StationArr.hpp
 * @version : 1.0
 * @author : ???
*/

#ifndef STATIONARR_H
#define STATIONARR_H

#include <vector>
#include "InputStation.hpp"

namespace NextSimIO
{
/**
 * @class StationArr
 * @brief Class for whole station information
 */
class StationArr
{
private:

    /**
     * @details Sequence of stations
    */
    std::vector<InputStation> Stations;

    /**
     * @details Sequence of DRT stations
    */
    std::vector<InputDRTStation> DRTStations;

public:
    /**
     * @details Constructor
    */
    StationArr();

    /**
     * @details Get sequence of stations
     * @return Sequence of stations
    */
    std::vector<InputStation> getStations() { return Stations; }

    /**
     * @details Get sequence of DRT stations
     * @return Sequence of DRT stations
    */
    std::vector<InputDRTStation> getDRTStations() { return DRTStations; }
};
} // namespace NextSimIO

#endif