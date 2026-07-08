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
#include <NextSim_io/inputclass/InputTMC.hpp>

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
     * @param BGTduration Background traffic duration [min]
     * @param odID OD matrix ID
     * @param todID TOD matrix ID
     * @param tmc TMC configuration info
    */
    InputScenario(int id,
                  std::string startTime,
                  int duration,
                  int BGTduration,
                  int odID,
                  int todID,
                  InputTMC tmc,
                  bool dtaActive = false,
                  std::string dtaPath = "");

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
     * @brief Get TMC configuration
     * @return TMC configuration
    */
    InputTMC GetTMC() const { return m_tmc; }

    /**
     * @brief Check whether DTA route choice ratio should be applied
     * @return True if DTA route choice ratio is active
    */
    bool GetDTAActive() const { return m_dtaActive; }

    /**
     * @brief Get DTA route choice ratio file path
     * @return DTA route choice ratio file path
    */
    std::string GetDTAPath() const { return m_dtaPath; }

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
     * @details TMC configuration info
    */
    InputTMC m_tmc;

    /**
     * @details Whether DTA route choice ratio is active
    */
    bool m_dtaActive = false;

    /**
     * @details DTA route choice ratio file path
    */
    std::string m_dtaPath;
};
} // namespace NextSimIO

#endif
