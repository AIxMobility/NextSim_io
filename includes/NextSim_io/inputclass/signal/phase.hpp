/**
 * NextSim Captain
 * @file : phase.hpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#pragma once
#ifndef PHASE_H
#define PHASE_H

#include <vector>
#include <string>

namespace NextSimIO
{
/**
 * @class phase
 * @brief Class for phase information
 */
class phase
{
public:
    phase(int id,
          int duration,
          std::string kind = "UNSPECIFIED",
          std::string phaseType = "VEHICLE");

    int GetId() const { return m_id; }
    int GetDuration() const { return m_duration; }
    const std::vector<int>& GetTurnIdList() const { return m_turnIdList; }
    const std::string& GetKind() const { return m_kind; }
    const std::string& GetPhaseType() const { return m_phaseType; }
    void SetTurnList(std::string turnString);

private:
    int m_id;
    int m_duration;
    std::vector<int> m_turnIdList;
    std::string m_kind;
    std::string m_phaseType;
};
} // namespace NextSimIO

#endif