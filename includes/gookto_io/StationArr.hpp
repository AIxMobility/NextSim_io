#ifndef STATIONARR_H
#define STATIONARR_H

#include <vector>
#include "InputStation.hpp"

class StationArr
{
private:
    std::vector<InputStation> Stations;

public:
    StationArr();
    ~StationArr() = default;
    StationArr(const StationArr &link) = default;
    StationArr &operator=(const StationArr &link) = default;

    void showArr();

    //access functions
    std::vector<InputStation> getStations() { return Stations; }
};

#endif