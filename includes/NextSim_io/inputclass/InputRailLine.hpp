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
    InputRailLine(std::string id, double fee, std::vector<int> seq);

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
     * @details Get the Line sequence of stations
     * @return Line sequence of stations
     */
    std::vector<int> GetRailStationSeq() { return m_seq; }
    

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
     * @details Line sequence of station
    */
    std::vector<int> m_seq;
};
}

#endif