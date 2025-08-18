/**
 * NextSim Captain
 * @file : InputrailLine.hpp
 * @version : 1.2
 * @author : Yuseock Hwang, Yeonwoo Yu, Sujae Jeon
 */

#pragma once
#ifndef INPUTRAILLine_H
#define INPUTRAILLine_H

#include <vector>
#include <string>

namespace NextSimIO
{
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
   InputRailLine(std::string id, double fee, std::vector<int> seq);

    /**
    * @details Get ID of rail public transit lines
    * @return ID of rail public transit lines
    */
   std::string GetID() const { return m_id; }

    /**
     * @details Get the Line fee
     * @return Line fee
     */
    double GetFee() { return m_fee; }

  /**
  * @details Get station sequence of rail public transit lines
  * @return Station sequence of rail public transit lines
  */
   std::vector<int> GetRailStationSeq() const { return m_seq; }

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
   * @details Vector of sequence of stations for each line
  */
   std::vector<int> m_seq;
};
}

#endif