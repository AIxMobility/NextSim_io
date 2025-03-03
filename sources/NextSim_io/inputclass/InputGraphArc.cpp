/**
 * NextSim Captain
 * @file : InputGraphArc.cpp
 * @version : 1.0
 * @author Dongheon Lee
 */

#include <NextSim_io/inputclass/InputGraphArc.hpp>

namespace NextSimIO
{
ArcCost::ArcCost(double length)
    : m_distanceCost(length) {}

ArcCost::ArcCost(double timeCost, double distanceCost, double financialCost, double trafficCost)
    : m_timeCost(timeCost), m_distanceCost(distanceCost), m_financialCost(financialCost), m_trafficCost(trafficCost) {}
// class ArcCost

InputGraphArc::InputGraphArc(std::size_t id, std::size_t fromNode, std::size_t toNode)
    : m_id(id), m_fromNode(fromNode), m_toNode(toNode) {}

void InputGraphArc::PushArcCost(ArcCost arcCost)
{
    m_arcCost.emplace_back(arcCost);
}
// class InputGraphArc
}