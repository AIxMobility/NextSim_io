/**
 * @file buspath.hpp
 * @version 1.0
 * @author Yeonwoo Yu
 */

#ifndef BUSPATH_HPP
#define BUSPATH_HPP

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include <NextSim_io/parser/PTlineArr.hpp>
#include <NextSim_io/parser/StationArr.hpp>
#include <NextSim_io/parser/LinkArr.hpp>
#include <NextSim_io/inputclass/InputPTline.hpp>

using namespace NextSimIO;
namespace Captain
{
/**
 * @class buspath
 * @brief Generates bus path information according to stationDistanceVector method
 */
class buspath
{
public:
    /** 
     * @brief Constructor 
    */
    buspath(const PTlineArr& ptlinesArr, const StationArr& stationsArr, const LinkArr& linksArr);

    /**
     * @brief Get bus travel distance between two stations for a certain line
     * @param lineId The ID of the bus line
     * @param fromStationId The ID of the starting station (originStopId)
     * @param toStationId The ID of the destination station (destStopId)
     * @return The bus travel distance in meters
     */
    double GetBusTravelDistance(const std::string& lineId, int fromStationId, int toStationId);

    /**
     * @brief Get bus travel time between two stations for a certain line
     * @param lineId The ID of the bus line
     * @param fromStationId The ID of the starting station (originStopId)
     * @param toStationId The ID of the destination station (destStopId)
     * @param busSpeedMps The speed of the bus in meters per second
     * @return The bus travel time in minutes
     */
    double GetBusTravelTime(const std::string& lineId, int fromStationId, int toStationId, double busSpeedMps);
    
    /**
     * @brief Get all bus OD maps
     * @return A map where keys are line IDs and values are maps of OD pairs with distances
     */
    const std::map<std::string, std::map<std::pair<int, int>, double>>& GetBusODMaps() const { return busODMaps; }

private:
    /**
     * @brief Map to store bus OD pairs with distances
     * @details The key is a pair of station IDs (fromStationId, toStationId) and the value is the distance in meters
     */
    std::map<std::string, std::map<std::pair<int, int>, double>> busODMaps;
    
    /**
     * @brief Build OD map for a given public transit line
     * @param ptline The public transit line to process
     * @param stationsArr The station array containing station information
     * @param linksArr The link array containing link information
     */
    void BuildODMap(const InputPTline& ptline, const StationArr& stationsArr, const LinkArr& linksArr);
    
    /** 
     * @struct StationInfo
     * @brief Station info for OD map
     */
    struct StationInfo {
        int id;
        int link;
        double pos;
    };

    /** 
     * @struct LinkInfo
     * @brief Link info for OD map
     */
    struct LinkInfo {
        int id;
        double length;
    };
};

} // namespace Captain
#endif // BUSPATH_H