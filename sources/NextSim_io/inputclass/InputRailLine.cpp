/**
 * NextSim Captain
 * @file : InputrailLine.cpp
 * @version : 1.0
 * @author : Yuseock Hwang
 */

#include <NextSim_io/inputclass/InputRailLine.hpp>

 namespace NextSimIO
{
InputRailLine::InputRailLine(std::string id, std::vector<int> seq) : 
    m_id(id), m_seq(seq) {};
}