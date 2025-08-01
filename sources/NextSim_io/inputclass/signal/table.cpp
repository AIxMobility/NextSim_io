/**
 * NextSim Captain
 * @file : InputTOD.cpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#include <NextSim_io/inputclass/InputTOD.hpp>

namespace NextSimIO
{
table::table(int planId, std::string start, std::string end) 
    : m_planId(planId), m_startTime(start), m_endTime(end) {};
} // namespace NextSimIO