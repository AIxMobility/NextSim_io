/**
 * NextSim Captain
 * @file : InputAgents.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#pragma once
#ifndef INPUTAGENTS_H
#define INPUTAGENTS_H

#include <string>
#include <vector>

namespace NextSimIO
{
/**
 * @class InputAgents
 * @brief Class for information of each agent from agents.xml
 */
class InputAgents
{
public:
    /**
     * @details Constructor
     * @param id Agent ID
     * @param type Agent type ID
     * @param dpt_time Departure time
     */
    InputAgents(int id, int typeID, double dptTime);

    /**
     * @details Set sequence of links
     * @param linkSeq Sequence of links
     */
    void SetLinkSeq(std::string linkSeq);

    /**
     * @details Set sequence of nodes
     * @param nodeSeq Sequence of nodes
     */
    void SetNodeSeq(std::string nodeSeq);

    /**
     * @details Set sequence of stations
     * @param stationSeq Sequence of stations
     */
    void SetStationSeq(std::string stationSeq);

    /**
     * @details Set sequence of distance between stations
     * @param stationDistanceSeq Sequence of distance between stations
     */
    void SetStationDistanceSeq(std::string stationDistanceSeq);

    /**
     * @details Get agent ID
     * @return Agent ID
     */
    int GetId() { return m_id; }

    /**
     * @details Get agent type ID
     * @return Agent type ID
     */
    int GetTypeId() { return m_typeID; }

    /**
     * @details Get Departure time
     * @return Departure time [s]
     */
    double GetDepartureTime() { return m_dptTime; }

    /**
     * @details Get sequence of links
     * @return Sequence of links that agent passes
     */
    std::vector<int> GetLinkSeq() { return m_linkSeq; }

    /**
     * @details Get sequence of nodes
     * @return Sequence of nodes that agent passes
     */
    std::vector<int> GetNodeSeq() { return m_nodeSeq; }

    /**
     * @details Get sequence of stations
     * @return Sequence of stations that agent passes
     */
    std::vector<int> GetStationSeq() { return m_stationSeq; }

    /**
     * @details Get sequence of distance between stations
     * @return Sequence of distance between stations
     */
    std::vector<double> GetStationDistanceSeq() { return m_stationDistanceSeq; }

private:

    /**
     * @details Agent ID
     */
    int m_id;

    /**
     * @details Agent type ID
     */
    int m_typeID;

    /**
     * @details Departure time [s]
     */
    double m_dptTime;

    /**
     * @details Sequence of links that agent passes
     */
    std::vector<int> m_linkSeq;

    /**
     * @details Sequence of nodes that agent passes
     */
    std::vector<int> m_nodeSeq;

    /**
     * @details Sequence of stations that agent passes
     */
    std::vector<int> m_stationSeq;

    /**
     * @details Sequence of distance between stations
     */
    std::vector<double> m_stationDistanceSeq;
};
} // namespace NextSimIO

#endif