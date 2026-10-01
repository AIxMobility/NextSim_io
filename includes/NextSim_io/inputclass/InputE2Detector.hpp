/**
 * NextSim Captain
 * @file : InputE2Detector.hpp
 * @version : 1.0
 * @author : Keunhee Cho
 */

#pragma once
#ifndef NEXSIMIO_INPUTE2DETECTOR_HPP
#define NEXSIMIO_INPUTE2DETECTOR_HPP

#include <string>

namespace NextSimIO
{
class InputE2Detector
{
public:
    InputE2Detector(std::string id,
                    int linkId,
                    int laneIndex,
                    double pos,
                    double endPos,
                    double begin,
                    double end,
                    double freq,
                    bool friendlyPos,
                    std::string vTypes);

    const std::string& GetId() const { return m_id; }
    int GetLinkId() const { return m_linkId; }
    int GetLaneIndex() const { return m_laneIndex; }
    double GetPos() const { return m_pos; }
    double GetEndPos() const { return m_endPos; }
    double GetBegin() const { return m_begin; }
    double GetEnd() const { return m_end; }
    double GetFreq() const { return m_freq; }
    bool GetFriendlyPos() const { return m_friendlyPos; }
    const std::string& GetVTypes() const { return m_vTypes; }

private:
    std::string m_id;
    int m_linkId;
    int m_laneIndex;
    double m_pos;
    double m_endPos;
    double m_begin;
    double m_end;
    double m_freq;
    bool m_friendlyPos;
    std::string m_vTypes;
};
} // namespace NextSimIO

#endif
