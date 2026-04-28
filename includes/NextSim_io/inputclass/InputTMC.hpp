/**
* NextSim Captain
* @file InputTMC.hpp
* @version 1.0
* @author Chaemin Na
*/

#pragma once

#ifndef InputTMC_H
#define InputTMC_H

#include <vector>
#include <string>

namespace NextSimIO
{
struct InputTMCFeature
{
    /**
     * @details default constructor
     */
    InputTMCFeature(bool active = false, double timeStep = 1.0)
        : m_active(active), m_timeStep(timeStep)
    {
    }

    bool m_active = false;
    double m_timeStep = 1.0;
};
/**
 * @class InputTMC
 */
class InputTMC
{
public:

    InputTMC();

    /** @cond EXCLUDE */
    ~InputTMC() = default;
    InputTMC(const InputTMC &other) = default;
    InputTMC &operator=(const InputTMC &other) = default;
    /** @endcond */

    const InputTMCFeature& GetSignalTMCInfo() const { return m_signalTMCInfo; }

    const InputTMCFeature& GetV2XTMCInfo() const { return m_v2xTMCInfo; }

    void SetSignalTMCInfo(bool active, double timestep) { if (timestep < 1e-6) timestep = 1.0; m_signalTMCInfo = InputTMCFeature(active, timestep); }

    void SetV2XTMCInfo(bool active, double timestep) { if (timestep < 1e-6) timestep = 1.0; m_v2xTMCInfo = InputTMCFeature(active, timestep); }

private:

    InputTMCFeature m_signalTMCInfo;
    InputTMCFeature m_v2xTMCInfo;
};
} // namespace NextSimIO

#endif