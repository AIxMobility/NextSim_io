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
struct V2XModeData
{
    bool v2i = true;
    bool v2v = true;
};

struct V2XMsgData
{
    bool congestion = true;
    bool danger = true;
};

struct V2XData
{
    V2XModeData mode;
    V2XMsgData msg;
};

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
     * @param BGTduration Background traffic duration [min]
     * @param odID OD matrix ID
     * @param todID TOD matrix ID
     * @param signalControl Whether signal control is active
     * @param v2xData V2X data
    */
    InputScenario(int id, std::string startTime, int duration, int BGTduration, int odID, int todID, bool signalControl = false, V2XData v2xData = V2XData());

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
     * @brief Get background traffic duration
     * @return Background traffic duration [min]
    */
    int GetBGTDuration() { return m_BGTduration; }

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

    /**
     * @brief Check if signal control is active
     * @return True if signal control is active, false otherwise
    */
    bool IsSignalControl() const { return m_signalControl; }

    /**
     * @brief Get V2X data
     * @return V2X data
    */
    V2XData GetV2XData() const { return m_v2xData; }


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
     * @details Background traffic duration [min]
    */
    int m_BGTduration;

    /**
     * @details OD matrix ID
    */
    int m_odID;

    /**
     * @details TOD matrix ID
    */
    int m_todID;

    /**
     * @details Whether signal control is active or not
    */
    bool m_signalControl = false;

    /**
     * @details V2X data
    */
    V2XData m_v2xData;
};
} // namespace NextSimIO

#endif