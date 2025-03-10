/**
 * NextSim Captain
 * @file : StationArr.hpp
 * @version : 1.0
 * @author : 
*/

#ifndef STATIONARR_H
#define STATIONARR_H

#include <vector>
#include <string>
#include <NextSim_io/inputclass/InputStation.hpp>
#include <NextSim_io/util/XMLParser.hpp> // Include XML parser utility

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
     * @details Constructor (Parses station information from publictransit.xml)
     * @param filename Path to the publictransit.xml file
    */
    explicit StationArr(const std::string& filename)
    {
        ParseXML(filename);
    }

    /**
     * @details Get vector of stations
     * @return Vector of stations
    */
    std::vector<InputStation> GetStations() const
    {
        return m_stations;
    }

    /**
     * @details Get vector of DRT stations
     * @return Vector of DRT stations
    */
    std::vector<InputDRTStation> GetDRTStations() const
    {
        return m_drtStations;
    }

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
     * @details Parses station information from an XML file
     * @param filename Path to the publictransit.xml file
    */
    void ParseXML(const std::string& filename)
    {
        // Use XML parser utility to load station and DRT station data
        XMLParser::ParseStations(filename, m_stations, m_drtStations);
    }
};
} // namespace NextSimIO

#endif
