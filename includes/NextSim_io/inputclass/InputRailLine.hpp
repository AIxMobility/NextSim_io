/**
 * NextSim Captain
 * @file : InputrailLine.hpp
 * @version : 1.1
 * @author : Yuseock Hwang, Yeonwoo Yu 
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
   * @param id Line ID (string)
   * @param seq Sequence of station 
  */
   InputRailLine(std::string name, std::string id, std::vector<int> seq);
  
    /**
    * @details Get name of rail public transit lines
    * @return Name of rail public transit lines
    */
   std::string GetName() const { return m_name; }

    /**
    * @details Get ID of rail public transit lines
    * @return ID of rail public transit lines
    */
   std::string GetID() const { return m_id; }

  /**
  * @details Get station sequence of rail public transit lines
  * @return Station sequence of rail public transit lines
  */
   std::vector<int> GetRailStationSeq() const { return m_seq; }

private:
  /**
   * @details Line names
  */
   std::string m_name;

  /**
   * @details Line ID
  */
   std::string m_id;   

  /**
   * @details Vector of sequence of stations for each line
  */
   std::vector<int> m_seq;
};
}

#endif