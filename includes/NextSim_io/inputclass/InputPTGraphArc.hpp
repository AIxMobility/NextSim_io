/**
 * @file InputPTGraphArc.hpp
 * @version 1.1
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
 * @enum Arc Type
 * @brief Enum to classify arc types (InVehicle, Transfer, Footpath)
 */
enum class ArcType {
    InVehicle,
    Transfer,
    Footpath
};

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
     * @param footpathCost Walking distance on the arc
     * @param transferCost Number of transfers on the arc
     * @param fare Fare for the arc (optional, default is 0)
     */
    PTCost(double timeCost, double footpathCost, int transferCost, int fare);

    /**
     * @details Get time cost
     * @return Time cost (total time; min)
     */
    double GetTimeCost() const { return m_timeCost; }

    /**
     * @details Get footpath cost
     * @return Footpath cost (walking distance)
     */
    double GetFootpathCost() const { return m_footpathCost; }

    /**
     * @details Get transfer cost
     * @return Transfer cost (number of transfers)
     */
    int GetTransferCost() const { return m_transferCost; }

    /**
     * @details Get fare
     * @return Fare (in currency units, e.g., KRW)
     */
    int GetFare() const { return m_fare; }

    /**
     * @details Set time cost
     * @param timeCost calculated time cost
     */
    void SetTimeCost(double timeCost) { m_timeCost = timeCost; }

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
     * @brief Walking distance on the arc
     */
    double m_footpathCost;

    /**
     * @brief Number of transfers on the arc
     */
    int m_transferCost;

    /**
     * @brief Fare for the arc
     */
    int m_fare;
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
     * @param fromLineId From line ID 
     * @param toStopId To stop ID 
     * @param toLineId To line ID 
     * @param type Arc type
     * @param depTime Departure time
     * @param ptCost Arc cost
     */
    InputPTGraphArc(std::size_t arcId,
                    std::size_t fromStopId,
                    std::string fromLineId,
                    std::size_t toStopId,
                    std::string toLineId,
                    double depTime,
                    ArcType type, 
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
     * @details Get from line ID
     * @return From line ID 
     */
    std::string GetFromLineId() const { return m_fromLineId; }

    /**
     * @details Get to stop ID
     * @return To stop ID
     */
    std::size_t GetToStopId() const { return m_toStopId; }

    /**
     * @details Get to line ID
     * @return To line ID 
     */
    std::string GetToLineId() const { return m_toLineId; }
    
    /**
     * @details Get departure time from Stop
     * @return Departure time
     */
    double GetDepTime() const { return m_depTime; }

    /**
     * @details Set departure time
     * @param time Departure time to set
     */
    void SetDepTime(double time) { m_depTime = time; }

    /**
     * @details Get arc type
     * @return Arc type (now ArcType enum)
     */
    ArcType GetType() const { return m_type; } // Changed return type

    /**
     * @details Add arc cost into vector
     * @param ptCost Public transport arc cost
     */
    void PushArcCost(PTCost ptCost); 

    /**
     * @details Get vector of arc cost
     * @return Vector of public transport arc cost
     */
    const std::vector<PTCost>& GetCost() const { return m_cost; }

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
     * @details From line ID 
     */
    std::string m_fromLineId;

    /**
     * @details To stop ID 
     */
    std::size_t m_toStopId;

    /**
     * @details To line ID 
     */
    std::string m_toLineId;

    /**
     * @details Departure time 
     */
    double m_depTime;

    /**
     * @details Arc type
     */
    ArcType m_type; // Changed from std::string

    /**
     * @details Vector of public transport arc cost
     */
    std::vector<PTCost> m_cost;

}; 
} // namespace NextSimIO

#endif