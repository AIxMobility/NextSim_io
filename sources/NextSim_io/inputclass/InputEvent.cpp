/**
 * NextSim Captain
 * @file : InputEvent.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <NextSim_io/inputclass/InputEvent.hpp>

#include <utility>

namespace NextSimIO
{
InputEvent::InputEvent(int id, std::size_t link_id, bool hasPosRange, double startPos, double endPos,
               std::vector<int> laneVector, bool hasStartTime, double startTime, double duration,
               int msgType, int type, int sern, double speedLimit, std::string detail) :
                 m_id(id), m_linkID(link_id), m_hasPosRange(hasPosRange),
                 m_startPos(startPos), m_endPos(endPos),
                 m_lane(laneVector.empty() ? -1 : laneVector.front()),
                 m_laneVector(std::move(laneVector)),
                 m_hasStartTime(hasStartTime), m_startTime(startTime), m_duration(duration),
                 m_msgType(msgType), m_type(type), m_sern(sern),
                 m_speedLimit(speedLimit), m_detail(std::move(detail)) {}
} // namespace NextSimIO
