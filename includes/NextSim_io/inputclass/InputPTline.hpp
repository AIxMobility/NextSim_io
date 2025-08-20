/**
 * NextSim Captain
 * @file : InputPTline.hpp
 * @version : 1.1
 * @author : Sujae Jeon
 */

#pragma once
#ifndef INPUTPTLINE_H
#define INPUTPTLINE_H

#include <string>
#include <vector>

namespace NextSimIO
{
/**
 * @class InputPTline
 * @brief Class for public transit line
 */
class InputPTline
{
public:
    /**
     * @details Constructor
     * @param id Public transit line ID (string)
     * @param fee Public transit line fare
     * @param interval Dispatch interval
     */
    InputPTline(std::string id, double fee, double interval);

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
     * @details Set sequence of garages for rail transit
     * @param garageSeq Sequence of garage IDs where rail vehicles are stored
     */
    void SetGarageSeq(std::string garageSeq);

    /**
     * @details Get public transit line ID
     * @return Public transit line ID
     */
    std::string GetID() const { return m_id; }

    /**
     * @details Get fare for using the public transit line
     * @return Fare for using the public transit line
     */
    double GetFee() const { return m_fee; }

    /**
     * @details Get dispatch interval
     * @return Dispatch interval [min]
     */
     double GetInterval() const { return m_interval; }
 
     /**
      * @details Get sequence of links
      * @return Sequence of links that line passes
     */
    std::vector<int> GetLinkSeq() const { return m_linkSeq; }

    /**
     * @details Get sequence of nodes
     * @return Sequence of nodes that line passes
     */
    std::vector<int> GetNodeSeq() const { return m_nodeSeq; }

    /**
     * @details Get sequence of stations
     * @return Sequence of stations that line passes
     */
     std::vector<int> GetStationSeq() const { return m_stationSeq; }
 
     /**
      * @details Get sequence of distance between stations
      * @return Sequence of distance between stations
     */
     std::vector<double> GetStationDistanceSeq() const { return m_stationDistanceSeq; }
 
     /**
      * @details Get sequence of garages for rail transit
      * @return Sequence of garage IDs
     */
    std::vector<int> GetGarageSeq() { return m_garageSeq; }

private:
    /**
     * @details Public transit line ID
     */
    std::string m_id;

    /**
     * @details Fare for using the public transit line
     */
    double m_fee;

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

    /**
     * @details Sequence of garage IDs for rail transit
     */
    std::vector<int> m_garageSeq;
};
} // namespace NextSimIO

#endif // INPUTPTLINE_H