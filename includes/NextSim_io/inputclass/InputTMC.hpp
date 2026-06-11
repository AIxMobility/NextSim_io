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
    InputTMCFeature(bool active = false, double interval = 1.0)
        : m_active(active), m_interval(interval)
    {
    }

    bool m_active = false;
    double m_interval = 1.0;
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

    void SetSignalTMCInfo(bool active, double interval) { if (interval < 1e-6) interval = 1.0; m_signalTMCInfo = InputTMCFeature(active, interval); }

    void SetV2XTMCInfo(bool active, double interval) { if (interval < 1e-6) interval = 1.0; m_v2xTMCInfo = InputTMCFeature(active, interval); }

private:

    InputTMCFeature m_signalTMCInfo;
    InputTMCFeature m_v2xTMCInfo;
};
} // namespace NextSimIO

#endif