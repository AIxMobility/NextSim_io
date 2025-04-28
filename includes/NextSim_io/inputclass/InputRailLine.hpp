/**
 * NextSim Captain
 * @file : InputrailLine.hpp
 * @version : 1.0
 * @author : Yuseock Hwang
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
     * @param id Station ID
     * @param seq Sequence of station 
    */
   InputRailLine(std::string name, int id, std::vector<int> seq);

   std::string GetName() { return m_name; }

   int GetId() { return m_id; }

   std::vector<int> GetTrailStationSeq() { return m_seq; }



private:
 /**
     * @details Line ID
    */
   std::string m_name;

 /**
     * @details Line ID
    */
   int m_id;   

 /**
     * @details Line sequence of station
    */
   std::vector<int> m_seq;

};
}

#endif