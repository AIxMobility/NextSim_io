/**
 * NextSim Captain
 * @file : InputPTline.hpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#pragma once
#ifndef INPUTPTROUTE_H
#define INPUTPTROUTE_H

#include <string>
#include <vector>

namespace NextSimIO
{
/**
 * @class InputPTline
 * @brief Class for each public transit line information
 */
class InputPTline
{
public:
    /**
     * @details Constructor
     * @param id Public transit line ID
     * @param interval Dispatch interval
    */
    InputPTline(int id, double interval);

    /**
     * @details Set sequence of links
     * @param linkSeq Sequence of links that line passes
    */
    void SetLinkSeq(std::string linkSeq);

    /**
     * @details Set sequence of nodes
     * @param nodeSeq Sequence of nodes that line passes
    */
    void SetNodeSeq(std::string nodeSeq);

    /**
     * @details Set sequence of stations
     * @param stationSeq Sequence of stations that line passes
    */
    void SetStationSeq(std::string stationSeq);

    /**
     * @details Set sequence of distance between stations
     * @param stationDistanceSeq Sequence of distance between stations
    */
    void SetStationDistanceSeq(std::string stationDistanceSeq);

    /**
     * @details Get public transit line ID
     * @return Public transit line ID
    */
    int GetId() { return m_id; }

    /**
     * @details Get dispatch interval
     * @return Dispatch interval [min]
    */
    int GetInterval() { return m_interval; }

    /**
     * @details Get sequence of links
     * @return Sequence of links that line passes
    */
    std::vector<int> GetLinkSeq() { return m_linkSeq; }

    /**
     * @details Get sequence of nodes
     * @return Sequence of nodes that line passes
    */
    std::vector<int> GetNodeSeq() { return m_nodeSeq; }

    /**
     * @details Get sequence of stations
     * @return Sequence of stations that line passes
    */
    std::vector<int> GetStationSeq() { return m_stationSeq; }

    /**
     * @details Get sequence of distance between stations
     * @return Sequence of distance between stations
    */
    std::vector<double> GetStationDistanceSeq() { return m_stationDistanceSeq; }

private:

    /**
     * @details Public transit line ID
    */
    int m_id;

    /**
     * @details Dispatch interval [min]
    */
    double m_interval;

    /**
     * @details Sequence of links that line passes
    */
    std::vector<int> m_linkSeq;

    /**
     * @details Sequence of nodes that line passes
    */
    std::vector<int> m_nodeSeq;

    /**
     * @details Sequence of stations that line passes
    */
    std::vector<int> m_stationSeq;

    /**
     * @details Sequence of distance between stations
    */
    std::vector<double> m_stationDistanceSeq;
};
} // namespace NextSimIO

#endif