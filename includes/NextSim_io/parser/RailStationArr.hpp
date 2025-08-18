/**
 * NextSim Captain
 * @file : RailStation.hpp
 * @version : 1.2
 * @author : Yuseock Hwang, Yeonwoo Yu
 */

#ifndef RAILSTATIONARR_H
#define RAILSTATIONARR_H

#include <vector>
#include <map>
#include <optional>
#include <stdexcept>

#include <NextSim_io/inputclass/InputRailStation.hpp>
#include <NextSim_io/inputclass/InputPTGraphVertex.hpp>

namespace NextSimIO
{
/**
 * @class RailStationArr
 * @brief Class for whole rail station information from railStation.xml
 */
class RailStationArr
{
public:
    /**
     * @details Constructor
    */
   RailStationArr();

    /**
     * @details Constructor
     * @param dayOfWeek The day of the week for which to load rail stations (e.g., "weekdays", "weekends")
    */
   RailStationArr(const std::string& dayOfWeek);

    /**
     * @details Get vector of all rail stations
     * @return Vector of all rail stations
    */
   const std::vector<InputRailStation>& GetRailStations() const { return m_railstations; }

    /**
     * @brief Checks if a stop with the given ID exists in this collection. Used for pt routing. 
     * @param stopId The ID of the stop to check
     * @return True if the stop exists, false otherwise
     */
    bool HasStop(int stopId) const;

    /**
     * @brief Retrieves a const reference to the Stop object by its ID. Used for pt routing.
     * @param stopId The ID of the stop to retrieve.
     * @return A const reference to the Stop object.
     * @throws std::out_of_range if the stop with the given ID is not found.
     */
    const Stop& GetStopById(int stopId) const;


private:
    /**
     * @brief Load rail stations
     */
    void LoadRailStations(const std::optional<std::string>& dayOfWeekFilter = std::nullopt);

    /**
     * @details Vector of all rail stations
    */
   std::vector<InputRailStation> m_railstations;

    /**
     * @brief Map for quick lookup of Stop objects by their ID. Used for pt routing.
     * @details Stores Stop objects derived from InputRailStation, mapping their IDs to the Stop objects.
     */
    std::map<int, Stop> m_stopMap;
    
};
} // namespace NextSimIO



#endif