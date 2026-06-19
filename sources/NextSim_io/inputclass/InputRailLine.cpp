/**
 * NextSim Captain
 * @file : InputrailLine.cpp
 * @version : 2.0
 * @author : Yuseock Hwang, Yeonwoo Yu, Sujae Jeon, Dongheon Lee
 */

#include <NextSim_io/inputclass/InputRailLine.hpp>

namespace NextSimIO
{
InputRailLine::InputRailLine(std::string id, double fee, std::vector<std::string> departureTime, std::vector<stationSeq> stationSeqList)
    : m_id(std::move(id)), m_fee(fee), m_departureTime(std::move(departureTime)), m_stationSeq(std::move(stationSeqList)) {}
}