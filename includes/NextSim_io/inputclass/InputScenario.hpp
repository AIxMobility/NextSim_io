/**
* NextSim Captain
* @file InputScenario.hpp
* @version 1.0
* @author Sujae Jeon
*/

#pragma once

#ifndef InputSCENARIO_H
#define InputSCENARIO_H

#include <vector>
#include <string>

namespace NextSimIO
{
/**
 * @class InputScenario
 * @brief Class for each simulation mode information
 */
class InputScenario
{
public:
    /**
     * @brief Constructor
     * @param id Scenario ID
     * @param startTime Start time of scenario
     * @param duration Duration of scenario [min]
     * @param odID OD matrix ID
     * @param todID TOD matrix ID
    */
    InputScenario(int id, std::string startTime, int duration, int odID, int todID);

    /** @cond EXCLUDE */
    ~InputScenario() = default;
    InputScenario(const InputScenario &other) = default;
    InputScenario &operator=(const InputScenario &other) = default;
    /** @endcond */

    /**
     * @brief Get scenario ID
     * @return Scenario ID
    */
    int GetId() { return m_id; }

    /**
     * @brief Get start time
     * @return Start time of scenario
    */
    std::string GetStartTime() { return m_startTime; }

    /**
     * @brief Get duration
     * @return Duration of scenario [min]
    */
    int GetDuration() { return m_duration; }

    /**
     * @brief Get OD matrix ID
     * @return OD matrix ID
    */
    int GetODID() { return m_odID; }

    /**
     * @brief Get TOD matrix ID
     * @return TOD matrix ID
    */
    int GetTODID() { return m_todID; }


private:
    /**
     * @details Scenario ID
    */
    int m_id;

    /**
     * @details Start time of scenario (24 hours 기준)
    */
    std::string m_startTime;

    /**
     * @details Duration of scenario [min]
    */
    int m_duration;

    /**
     * @details OD matrix ID
    */
    int m_odID;

    /**
     * @details TOD matrix ID
    */
    int m_todID;
};
} // namespace NextSimIO

#endif