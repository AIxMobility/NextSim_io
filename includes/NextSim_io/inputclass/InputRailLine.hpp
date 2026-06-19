/**
 * NextSim Captain
 * @file : InputrailLine.hpp
 * @version : 2.0
 * @author : Yuseock Hwang, Yeonwoo Yu, Sujae Jeon, Dongheon Lee
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
    int GetId() const { return m_stationId; }

    /**
     * @details Gets the sequence of the station in the line
     */
    int GetSeq() const { return m_seq; }

    /**
     * @details Gets the time offset from the first station
     */
    int GetTimeOffset() const { return m_timeOffset; }

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
   * @param id Line ID 
   * @param fee Fare for using the rail line
   * @param seq Sequence of station 
  */
  InputRailLine(std::string id, double fee, std::vector<std::string> departureTime, std::vector<stationSeq> stationSeqList);

  /**
  * @details Get ID of rail public transit lines
  * @return ID of rail public transit lines
  */
  std::string GetID() const { return m_id; }

  /**
   * @details Get the Line fee
   * @return Line fee
   */
  double GetFee() const { return m_fee; }

  /**
   * @details Get departure time of rail public transit lines
   * @return Departure time of rail public transit lines
   */
  std::vector<std::string> GetDepartureTime() const { return m_departureTime; }

  /**
   * @details Get station sequence of rail public transit lines
   * @return Station sequence of rail public transit lines
  */
  std::vector<stationSeq> GetRailStationSeq() const { return m_stationSeq; }

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
   * @details Vector of departure time for each line
  */
  std::vector<std::string> m_departureTime;

  /**
   * @details Vector of sequence of stations for each line
  */
  std::vector<stationSeq> m_stationSeq;
};
}

#endif