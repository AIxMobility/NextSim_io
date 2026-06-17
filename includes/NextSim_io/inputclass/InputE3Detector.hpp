/**
 * NextSim Captain
 * @file : InputE3Detector.hpp
 * @version : 1.0
 * @author : Keunhee Cho
 */

#pragma once
#ifndef NEXSIMIO_INPUTE3DETECTOR_HPP
#define NEXSIMIO_INPUTE3DETECTOR_HPP

#include <string>
#include <vector>

namespace NextSimIO
{
struct InputDetectorPoint
{
    int LinkId = -1;
    int LaneIndex = -1;
    double Pos = 0.0;
};

class InputE3Detector
{
public:
    InputE3Detector(std::string id,
                    double begin,
                    double end,
                    double freq,
                    bool friendlyPos,
                    bool openEntry,
                    std::string vTypes,
                    std::vector<InputDetectorPoint> entryPoints,
                    std::vector<InputDetectorPoint> exitPoints);

    const std::string& GetId() const { return m_id; }
    double GetBegin() const { return m_begin; }
    double GetEnd() const { return m_end; }
    double GetFreq() const { return m_freq; }
    bool GetFriendlyPos() const { return m_friendlyPos; }
    bool GetOpenEntry() const { return m_openEntry; }
    const std::string& GetVTypes() const { return m_vTypes; }
    const std::vector<InputDetectorPoint>& GetEntryPoints() const
    {
        return m_entryPoints;
    }
    const std::vector<InputDetectorPoint>& GetExitPoints() const
    {
        return m_exitPoints;
    }

private:
    std::string m_id;
    double m_begin;
    double m_end;
    double m_freq;
    bool m_friendlyPos;
    bool m_openEntry;
    std::string m_vTypes;
    std::vector<InputDetectorPoint> m_entryPoints;
    std::vector<InputDetectorPoint> m_exitPoints;
};
} // namespace NextSimIO

#endif
