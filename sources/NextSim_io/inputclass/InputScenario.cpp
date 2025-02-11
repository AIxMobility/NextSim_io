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
InputScenario::InputScenario(int id, int startTime, int duration, int odID, int todID)
    : m_id(id), m_startTime(startTime), m_duration(duration), m_odID(odID), m_todID(todID) {};
} // namespace NextSimIO