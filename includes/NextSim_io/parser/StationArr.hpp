/**
 * NextSim Captain
 * @file : StationArr.hpp
 * @version : 1.1
 * @author : Sujae Jeon, Yeonwoo Yu
*/

#ifndef STATIONARR_H
#define STATIONARR_H

#include <vector>
#include <map> 
#include <stdexcept>

#include <NextSim_io/inputclass/InputStation.hpp>
#include <NextSim_io/inputclass/InputPTGraphVertex.hpp>

namespace NextSimIO
{
/**
 * @class StationArr
 * @brief Class for road public transit and DRT stations
*/

class StationArr
{

public:
    /**
     * @details Constructor
    */
    StationArr();

    /**
     * @details Get vector of stations
     * @return Vector of stations
    */
    const std::vector<InputStation>& GetStations() const { return m_stations; }

    /**
     * @details Get vector of DRT stations
     * @return Vector of DRT stations
    */
    const std::vector<InputDRTStation>& GetDRTStations() const { return m_drtStations; }

    /**
     * @brief Checks if a stop with the given ID exists in this collection. Used for pt routing. 
     * @param stopId The ID of the stop to check
     * @return True if the stop exists, false otherwise
     */
    [[nodiscard]] bool HasStop(int stopId) const;

    /**
     * @brief Retrieves a const reference to the Stop object by its ID. Used for pt routing.
     * @param stopId The ID of the stop to retrieve.
     * @return A const reference to the Stop object.
     * @throws std::out_of_range if the stop with the given ID is not found.
     */
    [[nodiscard]] const Stop& GetStopById(int stopId) const;

private:
    /**
     * @details Vector of stations
    */
    std::vector<InputStation> m_stations;

    /**
     * @details Vector of DRT stations
    */
    std::vector<InputDRTStation> m_drtStations;

    /**
     * @brief Map for quick lookup of Stop objects by their ID. Used for pt routing.
     * @details Stores Stop objects derived from InputStation, mapping their IDs to the Stop objects.
     */
    std::map<int, Stop> m_stopMap;
};

} // namespace NextSimIO

#endif