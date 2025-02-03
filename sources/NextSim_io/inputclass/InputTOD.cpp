/**
 * NextSim Captain
 * @file : InputTOD.cpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#include <NextSim_io/inputclass/InputTOD.hpp>

namespace NextSimIO
{
InputTOD::InputTOD(int nodeId, std::vector<table> table) 
    : m_nodeId(nodeId), m_table(table) {};
} // namespace NextSimIO