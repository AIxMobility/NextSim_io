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
class InputPTlink
{
public:
    /**
     * @details Constructor
     * @param id link ID
     * @param sequence link sequence
     * @param preferLane prefer lane in the link
     */
    InputPTlink(int id, int sequence, int preferLane);

    /**
     * @details Get link ID
     * @return link ID
     */
    int GetID() { return m_id; }

    /**
     * @details Get link sequence
     * @return link sequence
     */
    int GetSequence() { return m_sequence; }

    /**
     * @details Get prefer lanes in the link
     * @return prefer lanes in the link
     */
    int GetPreferLane(){ return m_preferLane; }
    
private:
    /**
     * @details link ID
     */
    int m_id;

    /**
     * @details link sequence
     */
    int m_sequence;

    /**
     * @details prefer lanes in the link
     */
    int m_preferLane;
};

/**
 * @class InputPTline
 * @brief Class for each public transit line information
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

    void PushPTlink(InputPTlink ptlink);

    /**
     * @details Set sequence of stations
     * @param stationSeq Sequence of stations that line passes
     */
    void SetStationSeq(std::string stationSeq);

    /**
     * @details Set sequence of garages for rail transit
     * @param garageSeq Sequence of garage IDs where rail vehicles are stored
     */
    void SetGarageSeq(std::string garageSeq);

    /**
     * @details Get public transit line ID
     * @return Public transit line ID
     */
    std::string GetID() { return m_id; }

    /**
     * @details Get fare for using the public transit line
     * @return Fare for using the public transit line
     */
    double GetFee() { return m_fee; }

    /**
     * @details Get dispatch interval
     * @return Dispatch interval [min]
     */
    double GetInterval() { return m_interval; }

    /**
     * @details Get sequence of links that line passes
     * @return Sequence of links that line passes
     */
    std::vector<InputPTlink> GetLinkSeq() { return m_PTlinkSeq; }

    /**
     * @details Get sequence of stations
     * @return Sequence of stations that line passes
     */
    std::vector<int> GetStationSeq() { return m_stationSeq; }

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
    std::vector<InputPTlink> m_PTlinkSeq = {};

    /**
     * @details Sequence of stations that line passes
     */
    std::vector<int> m_stationSeq;

    /**
     * @details Sequence of garage IDs for rail transit
     */
    std::vector<int> m_garageSeq;
};
} // namespace NextSimIO

#endif