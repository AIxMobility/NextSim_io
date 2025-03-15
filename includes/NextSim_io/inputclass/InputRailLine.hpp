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
   InputRailLine(std::string id, std::vector<int> seq);

   std::string GetId() { return m_id; }

   std::vector<int> GetTrailStatuinSeq() { return m_seq; }



private:
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