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
    /**
     * @details Constructor
     * @param id phase ID
     * @param duration duration of the phase
     */
    phase(int id, int duration);

    /**
     * @details Get phase ID
     * @return phase ID
     */
    int GetId() { return m_id; }

    /**
     * @details Get duration of the phase
     * @return duration of the phase
     */
    int GetDuration() { return m_duration; }

    /**
     * @details Get turn list
     * @return turn List
     */
    std::vector<int> GetTurnList() { return m_turnList; }

    /**
     * @brief Set list of turn ids 
     * @param turnString List of turn ids as a string
    */
    void SetTurnList(std::string turnString);

private:
    /**
     * @details phase ID
    */
    int m_id;
    
    /**
     * @details duration of the phase
    */
    int m_duration;

    /**
     * @details turn list
    */
    std::vector<int> m_turnList;
};
} // namespace NextSimIO

#endif