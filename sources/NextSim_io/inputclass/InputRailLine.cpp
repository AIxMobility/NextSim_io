/**
 * NextSim Captain
 * @file : InputrailLine.cpp
 * @version : 1.2
 * @author : Yuseock Hwang, Yeonwoo Yu, Sujae Jeon
 */

#include <NextSim_io/inputclass/InputRailLine.hpp>

 namespace NextSimIO
{
InputRailLine::InputRailLine(std::string id, double fee, std::vector<int> seq)
    : m_id(std::move(id)), m_fee(fee), m_seq(std::move(seq)) {};
}