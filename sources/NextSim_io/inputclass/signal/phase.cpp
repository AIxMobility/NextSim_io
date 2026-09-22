/**
 * NextSim Captain
 * @file : phase.cpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#include <sstream>
#include <stdexcept>
#include <utility>

#include <NextSim_io/inputclass/signal/phase.hpp>

namespace NextSimIO
{
phase::phase(int id, int duration, std::string kind, std::string phaseType)
    : m_id(id),
      m_duration(duration),
      m_kind(std::move(kind)),
      m_phaseType(std::move(phaseType))
{
    if (m_kind != "UNSPECIFIED" && m_kind != "GREEN" &&
        m_kind != "YELLOW" && m_kind != "ALL_RED")
    {
        throw std::invalid_argument("phase kind must be GREEN, YELLOW, or ALL_RED");
    }
    if (m_phaseType != "VEHICLE" && m_phaseType != "PEDESTRIAN")
    {
        throw std::invalid_argument(
            "phaseType must be VEHICLE or PEDESTRIAN");
    }
}

void phase::SetTurnList(std::string turnString)
{
    std::stringstream ss(turnString);
    int turnId;

    while (ss >> turnId)
        m_turnIdList.push_back(turnId);
}
} // namespace NextSimIO