/**
 * NextSim Captain
 * @file : InputPTline.hpp
 * @version : 1.1
 * @author : Sujae Jeon, Dongheon Lee
 */

#pragma once
#ifndef INPUTPTLINE_H
#define INPUTPTLINE_H

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
     * @param usePTlane usage of PT lane
     */
    InputPTlink(int id, int sequence, bool usePTlane);

    /**
     * @details Get link ID
     * @return link ID
     */
    int GetID() { return m_id; }

    /**
     * @details Get link sequence
     * @return link sequence
     */
    int GetSequence() const { return m_sequence; }

    /**
     * @details Get usage of PT lane
     * @return usage of PT lane
     */
    bool GetUsePTlane() const { return m_usePTlane; }
    
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
     * @details usage of PT lane
     */
    bool m_usePTlane;
};

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

    void PushPTlink(InputPTlink ptlink);

    /**
     * @details Set sequence of stations
     * @param stationSeq Sequence of stations that line passes
     */
    void SetStationSeq(std::string stationSeq);

    /**
     * @details Push a station ID to the station sequence
     * @param stationID Station ID to be added
     */
    void PushStationSeq(int stationID);

    /**
     * @details Set sequence of garages for rail transit
     * @param garageSeq Sequence of garage IDs where rail vehicles are stored
     */
    void SetGarageSeq(std::string garageSeq);

    /**
     * @details Push a garage ID to the garage sequence
     * @param garageID Garage ID to be added
     */
    void PushGarageSeq(int garageID);

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
     * @details Get sequence of links that line passes
     * @return Sequence of links that line passes
     */
    std::vector<InputPTlink> GetLinkSeq() const { return m_PTlinkSeq; }

    /**
     * @details Get sequence of stations
     * @return Sequence of stations that line passes
     */
    std::vector<int> GetStationSeq() const { return m_stationSeq; }

    /**
     * @details Get sequence of garages for rail transit
     * @return Sequence of garage IDs
     */
    std::vector<int> GetGarageSeq() const { return m_garageSeq; }

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

#endif // INPUTPTLINE_H