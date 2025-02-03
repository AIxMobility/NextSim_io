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
     * @param green green time of the phase
     * @param yellow yellow time of the phase
     */
    phase(int id, int green, int yellow);

    /**
     * @details Get phase ID
     * @return phase ID
     */
    int GetId() { return m_id; }

    /**
     * @details Get green time of the phase
     * @return green time of the phase
     */
    int GetGreenTime() { return m_greenTime; }

    /**
     * @details Get yellow time of the phase
     * @return yellow time of the phase
     */
    int GetYellowTime() { return m_yellowTime; }

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
     * @details green time of the phase
    */
    int m_greenTime;

    /**
     * @details yellow time of the phase
    */
    int m_yellowTime;

    /**
     * @details turn list
    */
    std::vector<int> m_turnList;
};
} // namespace NextSimIO

#endif