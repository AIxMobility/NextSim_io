/**
 * NextSim Captain
 * @file : phase.cpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#include <sstream>

#include <NextSim_io/inputclass/signal/phase.hpp>

namespace NextSimIO
{
phase::phase(int id, int duration) 
    : m_id(id), m_duration(duration) {};

void phase::SetTurnList(std::string turnString)
{
    std::stringstream ss(turnString);
    int turnId;

    while (ss >> turnId)
        m_turnIdList.push_back(turnId);
}
} // namespace NextSimIO