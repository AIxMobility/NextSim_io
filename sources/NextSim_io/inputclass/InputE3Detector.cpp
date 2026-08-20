/**
 * NextSim Captain
 * @file : InputE3Detector.cpp
 * @version : 1.0
 * @author : Keunhee Cho
 */

#include <NextSim_io/inputclass/InputE3Detector.hpp>
#include <utility>

namespace NextSimIO
{
InputE3Detector::InputE3Detector(std::string id,
                                 double begin,
                                 double end,
                                 double freq,
                                 bool friendlyPos,
                                 bool openEntry,
                                 std::string vTypes,
                                 std::vector<InputDetectorPoint> entryPoints,
                                 std::vector<InputDetectorPoint> exitPoints)
    : m_id(std::move(id)),
      m_begin(begin),
      m_end(end),
      m_freq(freq),
      m_friendlyPos(friendlyPos),
      m_openEntry(openEntry),
      m_vTypes(std::move(vTypes)),
      m_entryPoints(std::move(entryPoints)),
      m_exitPoints(std::move(exitPoints))
{
}
} // namespace NextSimIO
