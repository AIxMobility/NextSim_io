#ifndef STATIONARR_H
#define STATIONARR_H

#include <vector>
#include "InputStation.hpp"

class StationArr
{
private:
    std::vector<InputStation> Stations;
    std::vector<InputDRTStation> DRTStations;

public:
    StationArr();

    //access functions
    std::vector<InputStation> getStations() { return Stations; }
    std::vector<InputDRTStation> getDRTStations() { return DRTStations; }
};

#endif