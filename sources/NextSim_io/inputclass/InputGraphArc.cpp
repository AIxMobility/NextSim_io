/**
 * NextSim Captain
 * @file : InputGraphArc.cpp
 * @version : 1.0
 * @author Dongheon Lee
 */

#include <NextSim_io/inputclass/InputGraphArc.hpp>

namespace NextSimIO
{
ArcCost::ArcCost(double timeCost, double distanceCost, double financialCost, double trafficCost)
    : m_timeCost(timeCost), m_distanceCost(distanceCost), m_financialCost(financialCost), m_trafficCost(trafficCost) {}
// class ArcCost

InputGraphArc::InputGraphArc() : m_id(0), m_fromNode(0), m_toNode(0) {}

InputGraphArc::InputGraphArc(std::size_t id, std::size_t fromNode, std::size_t toNode, std::size_t numLane, double length)
    : m_id(id), m_fromNode(fromNode), m_toNode(toNode), m_numLane(numLane), m_length(length) {}
// class InputGraphArc
}