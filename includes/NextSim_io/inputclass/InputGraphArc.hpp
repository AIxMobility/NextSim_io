/**
 * @file InputGraphArc.hpp
 * @version 1.0
 * @author Dongheon Lee
 */

#pragma once
#ifndef INPUTGRAPHARC_H
#define INPUTGRAPHARC_H

#include <vector>
#include <string>

namespace NextSimIO
{
/**
 * @class ArcCost
 * @brief Class for each arc cost information
 */
class ArcCost
{
public:
    /**
     * @details Default Constructor
     */
    ArcCost() : m_timeCost(0), m_distanceCost(0), m_financialCost(0), m_trafficCost(0) {}

    /**
     * @details Constructor
     * @param timeCost Time to pass the arc with freeflow speed
     * @param distanceCost Length of the arc
     * @param financialCost Financial cost of the arc
     * @param trafficCost Time to pass the arc with traffic speed
     */
    ArcCost(double timeCost, double distanceCost, double financialCost, double trafficCost);

    /**
     * @details Get time cost
     * @return Time cost
     */
    double GetTimeCost() { return m_timeCost; }

    /**
     * @details Get distance cost
     * @return Distance cost
     */
    double GetDistanceCost() { return m_distanceCost; }

    /**
     * @details Get financial cost
     * @return Financial cost
     */
    double GetFinancialCost() { return m_financialCost; }

    /**
     * @details Get traffic cost
     * @return Traffic cost
     */
    double GetTrafficCost() { return m_trafficCost; }

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
     * @details Set financial cost
     * @param financialCost calculated financial cost
     */
    void SetFinancialCost(double financialCost) { m_financialCost = financialCost; }

    /**
     * @details Set traffic cost
     * @param trafficCost calculated traffic cost
     */
    void SetTrafficCost(double trafficCost) { m_trafficCost = trafficCost; }

private:
    /**
     * @brief Time to pass the arc with freeflow speed
     */
    double m_timeCost;

    /**
     * @brief length of the arc
     */
    double m_distanceCost;

    /**
     * @brief Financial cost of the arc
     */
    double m_financialCost;

    /**
     * @brief Time to pass the arc with traffic speed
     */
    double m_trafficCost;

}; // class ArcCost

/**
 * @class InputGraphArc
 * @brief Class for each graph arc information
 */
class InputGraphArc
{
public:
    /**
     * @details Constructor
     */
    InputGraphArc();

    /**
     * @details Constructor
     * @param id Arc ID
     * @param fromNode From node ID (connected with arc start point)
     * @param toNode To node ID (connected with arc end point)
     * @param numLane Number of lanes in the arc
     * @param length Length of the arc
     * @param ffSpeed Free flow speed of the arc
     */
    InputGraphArc(std::size_t id, std::size_t fromNode, std::size_t toNode, std::size_t numLane, double length, double ffSpeed);

    /**
     * @details Set arc ID
     * @param id Arc ID
     */
    void SetID(int id) { m_id = id; }

    /**
     * @details Sed from node ID
     * @param fromNode From node ID
     */
    void SetFromNode(std::size_t fromNode) { m_fromNode = fromNode; }

    /**
     * @details Set to node ID
     * @param toNode To node ID
     */
    void SetToNode(std::size_t toNode) { m_toNode = toNode; }

    /**
     * @details Set numlane
     * @param numLane Number of lanes in the arc
     */
    void SetNumLane(std::size_t numLane) { m_numLane = numLane; }

    /**
     * @details Set length of the arc
     * @param length Length of the arc
     */
    void SetLength(double length) { m_length = length; }

    /**
    * @details Set free flow speed of the arc
    * @param ffSpeed Free flow speed of the arc
    */
    void SetFreeFlowSpeed(double ffSpeed) { m_ffspeed = ffSpeed; }

    /**
     * @details Set available lanes in the arc when it is connected to a sink node
     * @param availableLanes Available lanes in the arc
     */
    void SetAvailableLanes(std::vector<int> availableLanes) { m_availableLanes = availableLanes; }

    /**
     * @details Set arc cost
     * @param arcCost Arc cost object
     */
    void SetArcCost(ArcCost arcCost) { m_arcCost = arcCost; }

    /**
     * @details Set PT lane list
     * @param ptlane PT lane nmber
     */
    void PushPTLaneList(int ptlane) {m_ptlanelist.push_back(ptlane);} 

    /**
     * @details Get arc ID
     * @return Arc ID
     */
    int GetID() { return m_id; }

    /**
     * @details Get from node ID
     * @return From node ID
     */
    std::size_t GetFromNode() { return m_fromNode; }

    /**
     * @details Get to node ID
     * @return To node ID
     */
    std::size_t GetToNode() { return m_toNode; }

    /**
     * @details Get number of lanes in the arc
     * @return number of lanes in the arc
     */
    std::size_t GetNumLane() { return m_numLane; }

    /**
     * @details Get length of the arc
     * @return Length of the arc
     */
    double GetLength() { return m_length; }

    /**
     * @details Get free flow speed of the arc
     * @return Free flow speed of the arc
     */
    double GetFreeFlowSpeed() { return m_ffspeed; }

    /**
     * @details Get available lanes in the arc when it is connected to a sink node
     * @return Available lanes in the arc
     */
    std::vector<int> GetAvailableLanes() { return m_availableLanes; }

    /**
     * @details Get vector of arc cost
     * @return Vector of arc cost
     */
    ArcCost GetArcCost() { return m_arcCost; }

    /**
     * @details Get whether the arc is controlled within control range
     * @return Whether the arc is controlled within control range
    */
    bool GetControlled() { return m_controlled; }

    /**
     * @details Set whether the arc is controlled within control range
     * @param controlled Whether the arc is controlled within control range
    */
    void SetControlled(bool controlled) { m_controlled = controlled; }

    /**
     * @details Get PT lane list
     * @return PT lane list
     */
    std::vector<int> GetPTLaneList() { return m_ptlanelist; }

private:
    /**
     * @details Arc ID 
     */
    int m_id;

    /**
     * @details From node ID (connected with arc start point)
     */
    std::size_t m_fromNode;

    /**
     * @details To node ID (connected with arc end point)
     */
    std::size_t m_toNode;

    /**
     * @details Number of lanes in the arc
     */
    std::size_t m_numLane;

    /**
     * @details Length of the arc
     */
    double m_length;

    /**
    * @details Free flow speed of the arc
    */
    double m_ffspeed;

    /**
     * @details Available lanes in the arc when it is connected to a sink node
     */
    std::vector<int> m_availableLanes;

    /**
     * @details Arc cost 
     */
    ArcCost m_arcCost;

    /**
     * @details Whether the arc is controlled within control range
     */
    bool m_controlled = false;

    /**
     * @details Vector of PT lane list
     */
    std::vector<int> m_ptlanelist = {};
}; // class InputGraphArc
} // namespace NextSimIO

#endif