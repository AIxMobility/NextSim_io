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
    : m_arcId(0), m_fromStopId(0), m_fromTripId(-1), m_toStopId(0), m_toTripId(-1), m_type(""), m_cost() {}

InputPTGraphArc::InputPTGraphArc(std::size_t arcId,
                       std::size_t fromStopId,
                       int fromTripId,
                       std::size_t toStopId,
                       int toTripId,
                       const std::string& type,
                       PTCost ptCost)
    : m_arcId(arcId), m_fromStopId(fromStopId), m_fromTripId(fromTripId),
      m_toStopId(toStopId), m_toTripId(toTripId), m_type(type), m_cost({ptCost})
{}

    std::size_t InputPTGraphArc::GetArcId() const {
        return m_arcId;
    }

    std::size_t InputPTGraphArc::GetFromStopId() const {
        return m_fromStopId;
    }

    int InputPTGraphArc::GetFromTripId() const {
        return m_fromTripId;
    }

    std::size_t InputPTGraphArc::GetToStopId() const {
        return m_toStopId;
    }

    int InputPTGraphArc::GetToTripId() const {
        return m_toTripId;
    }

    std::string InputPTGraphArc::GetType() const {
        return m_type;
    }

    const std::vector<PTCost>& InputPTGraphArc::GetArcCosts() const {
        return m_cost;
    }

} // namespace NextSimIO