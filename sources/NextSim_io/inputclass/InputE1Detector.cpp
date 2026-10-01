/**
 * NextSim Captain
 * @file : InputE1Detector.cpp
 * @version : 1.0
 * @author : Keunhee Cho
 */

#include <NextSim_io/inputclass/InputE1Detector.hpp>
#include <utility>

namespace NextSimIO
{
InputE1Detector::InputE1Detector(std::string id,
                                 int linkId,
                                 int laneIndex,
                                 double pos,
                                 double begin,
                                 double end,
                                 double freq,
                                 bool friendlyPos,
                                 std::string vTypes)
    : m_id(std::move(id)),
      m_linkId(linkId),
      m_laneIndex(laneIndex),
      m_pos(pos),
      m_begin(begin),
      m_end(end),
      m_freq(freq),
      m_friendlyPos(friendlyPos),
      m_vTypes(std::move(vTypes))
{
}
} // namespace NextSimIO
