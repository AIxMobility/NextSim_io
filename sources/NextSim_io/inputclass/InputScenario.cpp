/**
* NextSim Captain
* @file InputScenario.cpp
* @version 1.0
* @author Sujae Jeon
*/

#include <sstream>

#include <NextSim_io/inputclass/InputScenario.hpp>

namespace NextSimIO
{
InputScenario::InputScenario(int id, std::string startTime, int duration, int BGTduration, int odID, int todID, InputTMC tmc)
    : m_id(id), m_startTime(std::move(startTime)), m_duration(duration), m_BGTduration(BGTduration), m_odID(odID), m_todID(todID), m_tmc(tmc) {};
} // namespace NextSimIO