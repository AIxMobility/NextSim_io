/**
 * NextSim Captain
 * @file : InputrailLine.hpp
 * @version : 2.0
 * @author : Yuseock Hwang, Dongheon Lee
 */

 
#pragma once
#ifndef INPUTRAILLine_H
#define INPUTRAILLine_H

#include <vector>
#include <string>

namespace NextSimIO
{
/**
 * @class stationSeq
 * @brief Class for station sequence information in a rail line
 */
class stationSeq
{
public:
    /**
     * @details Constructor
     * @param id Station ID
     * @param seq Sequence of station 
     * @param timeOffset Time offset from the first station
    */
    stationSeq(int id, int seq, int timeOffset) : m_stationId(id), m_seq(seq), m_timeOffset(timeOffset) {};

    /**
     * @details Gets the station ID
     */
    int GetId() { return m_stationId; }

    /**
     * @details Gets the sequence of the station in the line
     */
    int GetSeq() { return m_seq; }

    /**
     * @details Gets the time offset from the first station
     */
    int GetTimeOffset() { return m_timeOffset; }

private:
    /**
     * @details Station ID
     */
    int m_stationId;

    /**
     * @details Sequence of the station in the line
     */
    int m_seq;

    /**
     * @details Time offset from the first station
     */
    int m_timeOffset;
}; // class stationSeq

/**
 * @class InputrailLine
 * @brief Class for rail line information
 */
class InputRailLine
{
public:
    /**
     * @details Constructor
     * @param id Station ID
     * @param fee Line fee
     * @param departureTime Departure time of the line
     * @param stationSeq Sequence of stations in the line
    */
    InputRailLine(std::string id, double fee, std::vector<std::string> departureTime, std::vector<stationSeq> stationSeqList);

    /**
     * @details Get the Line ID
     * @return Line ID
     */
    std::string GetID() { return m_id; }

    /**
     * @details Get the Line fee
     * @return Line fee
     */
    double GetFee() { return m_fee; }

    /**
     * @details Get the departure time of the line
     * @return departure time of the line
     */
    std::vector<std::string> GetDepartureTime() { return m_departureTime; }

    /**
     * @details Get the station sequence of the line
     * @return station sequence of the line
     */
    std::vector<stationSeq> GetStationSeq() { return m_stationSeq; }

private:
    /**
     * @details Line ID
    */
    std::string m_id;

    /**
     * @details Line fee
    */
    double m_fee;

    /**
     * @details departure time of the line
    */
    std::vector<std::string> m_departureTime;

    /**
     * @details Sequence of stations in the line
     */
    std::vector<stationSeq> m_stationSeq;
};
}

#endif