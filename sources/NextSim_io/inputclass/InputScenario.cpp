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
InputScenario::InputScenario(int id, std::string startTime, int duration, int BGTduration, int odID, int todID, bool signalControl, V2XData v2xData)
    : m_id(id), m_startTime(std::move(startTime)), m_duration(duration), m_BGTduration(BGTduration), m_odID(odID), m_todID(todID), m_signalControl(signalControl), m_v2xData(std::move(v2xData)) {};
} // namespace NextSimIO