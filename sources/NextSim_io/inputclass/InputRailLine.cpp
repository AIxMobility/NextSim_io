/**
 * NextSim Captain
 * @file : InputrailLine.cpp
 * @version : 1.1
 * @author : Yuseock Hwang, Yeonwoo Yu
 */

#include <NextSim_io/inputclass/InputRailLine.hpp>

 namespace NextSimIO
{
InputRailLine::InputRailLine(std::string name, std::string id, std::vector<int> seq) : 
    m_name(name), m_id(id), m_seq(seq) {};
}