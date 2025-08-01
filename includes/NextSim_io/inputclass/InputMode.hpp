/**
* NextSim Captain
* @file InputMode.hpp
* @version 1.0
* @author Jae Hwan Jung, Justin Kim
*/

#pragma once

#ifndef INPUTMODE_H
#define INPUTMODE_H

#include <vector>
#include <string>

namespace NextSimIO
{
/**
 * @class InputMode
 * @brief Class for each simulation mode information
 */
class InputMode
{
public:
    /**
     * @brief Constructor
     * @param id Period ID
     * @param stime Application Start time
    */
    InputMode(int id, int stime);

    /** @cond EXCLUDE */
    ~InputMode() = default;
    InputMode(const InputMode &other) = default;
    InputMode &operator=(const InputMode &other) = default;
    /** @endcond */

    /**
     * @brief Set vector of micro link IDs
     * @param linkVector Vector of microscopic link IDs ("Link1 Link2 Link3 Link4")
    */
    void SetMicroLinkVector(std::string linkVector);

    /**
     * @brief Set vector of meso link IDs
     * @param linkVector Vector of mesoscopic link IDs ("Link1 Link2 Link3 Link4")
    */
    void SetMesoLinkVector(std::string linkVector);

    /**
     * @brief Get period ID
     * @return Period ID of mode setting application
    */
    int GetId() { return m_id; }

    /**
     * @brief Get start time
     * @return Start time for applying the corresponding mode setting
    */
    int GetStime() { return m_sTime; }

    /**
     * @brief Get vector of micro link IDs
     * @return Vector of microscopic link IDs
    */
    std::vector<int> GetMicroLinkVector() { return m_microLinkVector; }

    /**
     * @brief Get vector of meso link IDs
     * @return Vector of mesoscopic link IDs
    */
    std::vector<int> GetMesoLinkVector() { return m_mesoLinkVector; }

private:
    /**
     * @details Period ID of mode setting application
    */
    int m_id;

    /**
     * @details Start time for applying the corresponding mode setting [min]
    */
    int m_sTime;

    /**
     * @details Vector of microscopic link IDs
    */
    std::vector<int> m_microLinkVector;

    /**
     * @details Vector of mesoscopic link IDs
    */
    std::vector<int> m_mesoLinkVector;

};
} // namespace NextSimIO

#endif