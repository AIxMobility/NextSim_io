/**
 * @file InputPTGraphArc.hpp
 * @version 1.0
 * @author Yeonwoo Yu
 */

#pragma once
#ifndef INPUTPTGRAPHARC_H
#define INPUTPTGRAPHARC_H

#include <vector>
#include <string>

namespace NextSimIO
{
/**
 * @class PTCost
 * @brief Class for each public transport arc cost information
 */
class PTCost
{
public:
    /**
     * @details Constructor
     * @param timeCost Time to pass the arc
     * @param distanceCost Length of the arc
     * @param footpathCost Time spent walking on the arc
     * @param transferCost Number of transfers on the arc
     */
    PTCost(double timeCost, double distanceCost, double footpathCost, int transferCost);

    /**
     * @details Get time cost
     * @return Time cost
     */
    double GetTimeCost() const { return m_timeCost; }

    /**
     * @details Get distance cost
     * @return Distance cost
     */
    double GetDistanceCost() const { return m_distanceCost; }

    /**
     * @details Get footpath cost
     * @return Footpath cost
     */
    double GetFootpathCost() const { return m_footpathCost; }

    /**
     * @details Get transfer cost
     * @return Transfer cost (number of transfers)
     */
    int GetTransferCost() const { return m_transferCost; }

    /**
     * @details Set time cost
     * @param timeCost calculated time cost
     */
    void SetTimeCost(double timeCost) { m_timeCost = timeCost; }

    /**
     * @details Set distance cost
     * @param distanceCost calculated distance cost
     */
    void SetDistanceCost(double distanceCost) { m_distanceCost = distanceCost; }

    /**
     * @details Set footpath cost
     * @param footpathCost calculated footpath cost
     */
    void SetFootpathCost(double footpathCost) { m_footpathCost = footpathCost; }

    /**
     * @details Set transfer cost
     * @param transferCost calculated transfer cost (number of transfers)
     */
    void SetTransferCost(int transferCost) { m_transferCost = transferCost; }

private:
    /**
     * @brief Time to pass the arc
     */
    double m_timeCost;

    /**
     * @brief Length of the arc
     */
    double m_distanceCost;

    /**
     * @brief Time spent walking on the arc
     */
    double m_footpathCost;

    /**
     * @brief Number of transfers on the arc
     */
    int m_transferCost;

};

/**
 * @class InputPTGraphArc
 * @brief Class for each public transport graph arc information
 */
class InputPTGraphArc
{
public:
    /**
     * @details Constructor
     */
    InputPTGraphArc();

    /**
     * @details Constructor
     * @param arcId Arc ID
     * @param fromStopId From stop ID 
     * @param fromTripId From trip ID 
     * @param toStopId To stop ID 
     * @param toTripId To trip ID 
     * @param type Arc type 
     * @param ptCost Arc cost
     */
    InputPTGraphArc(std::size_t arcId,
               std::size_t fromStopId,
               int fromTripId,
               std::size_t toStopId,
               int toTripId,
               const std::string& type,
               PTCost ptCost);

    /**
     * @details Get arc ID
     * @return Arc ID
     */
    std::size_t GetArcId() const { return m_arcId; }

    /**
     * @details Get from stop ID
     * @return From stop ID
     */
    std::size_t GetFromStopId() const { return m_fromStopId; }

    /**
     * @details Get from trip ID
     * @return From trip ID 
     */
    int GetFromTripId() const { return m_fromTripId; }

    /**
     * @details Get to stop ID
     * @return To stop ID
     */
    std::size_t GetToStopId() const { return m_toStopId; }

    /**
     * @details Get to trip ID
     * @return To trip ID 
     */
    int GetToTripId() const { return m_toTripId; }

    /**
     * @details Get arc type
     * @return Arc type ("trip", "transfer", "footpath")
     */
    std::string GetType() const { return m_type; }

    /**
     * @details Add arc cost into vector
     * @param ptCost Public transport arc cost
     */
    void PushArcCost(PTCost ptCost); 

    /**
     * @details Get vector of arc cost
     * @return Vector of public transport arc cost
     */
    const std::vector<PTCost>& GetArcCosts() const { return m_cost; }

private:
    /**
     * @details Arc ID
     */
    std::size_t m_arcId;

    /**
     * @details From stop ID
     */
    std::size_t m_fromStopId;

    /**
     * @details From trip ID 
     */
    int m_fromTripId;

    /**
     * @details To stop ID 
     */
    std::size_t m_toStopId;

    /**
     * @details To trip ID 
     */
    int m_toTripId;

    /**
     * @details Arc type
     */
    std::string m_type;

    /**
     * @details Vector of public transport arc cost
     */
    std::vector<PTCost> m_cost;

}; 
} // namespace NextSimIO

#endif