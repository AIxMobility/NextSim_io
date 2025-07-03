/**
 * NextSim Captain
 * @file : InputrailLine.hpp
 * @version : 1.1
 * @author : Yuseock Hwang, Yeonwoo Yu */

 
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

   std::string GetName() { return m_name; }

   std::string GetID() const { return m_id; }

   std::vector<int> GetRailStationSeq() const { return m_seq; }



private:
 /**
     * @details Line ID
    */
   std::string m_name;

 /**
     * @details Line ID
    */
   std::string m_id;   

 /**
     * @details Line sequence of station
    */
   std::vector<int> m_seq;

};
}

#endif