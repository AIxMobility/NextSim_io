/**
 * NextSim Captain
 * @file : InputPTGraphArc.cpp
 * @version : 1.0
 * @author Yeonwoo Yu
 */

#include <NextSim_io/inputclass/InputPTGraphArc.hpp>
#include <string>
#include <vector>

namespace NextSimIO
{
PTCost::PTCost(double timeCost, double distanceCost, double footpathCost, int transferCost)
    : m_timeCost(timeCost), m_distanceCost(distanceCost), m_footpathCost(footpathCost), m_transferCost(transferCost) {}

    void InputPTGraphArc::PushArcCost(PTCost ptCost)
    {
        m_cost.push_back(ptCost);
    }

InputPTGraphArc::InputPTGraphArc()
    : m_arcId(), m_fromStopId(), m_fromLineId(), m_toStopId(), m_toLineId(), m_type(), m_cost() {}

InputPTGraphArc::InputPTGraphArc(std::size_t arcId,
                       std::size_t fromStopId,
                       int m_fromLineId,
                       std::size_t toStopId,
                       int m_toLineId,
                       ArcType type,
                       PTCost ptCost)
    : m_arcId(arcId), m_fromStopId(fromStopId), m_fromLineId(m_fromLineId),
      m_toStopId(toStopId), m_toLineId(m_toLineId), m_type(type), m_cost({ptCost})
{}

} // namespace NextSimIO