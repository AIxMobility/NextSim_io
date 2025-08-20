/**
 * NextSim Captain
 * @file : InputPTGraphArc.cpp
 * @version : 1.1
 * @author Yeonwoo Yu
 */

#include <NextSim_io/inputclass/InputPTGraphArc.hpp>
#include <string>
#include <vector>

namespace NextSimIO
{
PTCost::PTCost(double timeCost, double footpathCost, int transferCost, int fare)
    : m_timeCost(timeCost), m_footpathCost(footpathCost), m_transferCost(transferCost), m_fare(fare) {}

    void InputPTGraphArc::PushArcCost(PTCost ptCost)
    {
        m_cost.push_back(ptCost);
    }

InputPTGraphArc::InputPTGraphArc()
    : m_arcId(), m_fromStopId(), m_fromLineId(), m_toStopId(), m_toLineId(), m_type(), m_cost() {}

InputPTGraphArc::InputPTGraphArc(std::size_t arcId,
                       std::size_t fromStopId,
                       std::string fromLineId,
                       std::size_t toStopId,
                       std::string toLineId,
                       double depTime,
                       ArcType type,
                       PTCost ptCost)
    : m_arcId(arcId), m_fromStopId(fromStopId), m_fromLineId(fromLineId),
      m_toStopId(toStopId), m_toLineId(toLineId), m_depTime(depTime), m_type(type), m_cost({ptCost})
{}

} // namespace NextSimIO