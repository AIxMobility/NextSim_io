/**
 * NextSim Captain
 * @file : InputrailLine.cpp
 * @version : 1.0
 * @author : Yuseock Hwang
 */

#include <NextSim_io/inputclass/InputRailLine.hpp>

 namespace NextSimIO
{
InputRailLine::InputRailLine(std::string name, int id, std::vector<int> seq) : 
    m_name(name), m_id(id), m_seq(seq) {};
}