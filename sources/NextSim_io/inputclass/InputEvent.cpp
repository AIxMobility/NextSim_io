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
InputEvent::InputEvent(int id, std::size_t link_id, double startPos, double endPos,
               std::vector<int> laneVector, double stime, double etime, 
               int type, int sern) : 
                 m_id(id), m_linkID(link_id), m_startPos(startPos), m_endPos(endPos),
                m_lane(laneVector.empty() ? -1 : laneVector.front()),
                m_laneVector(std::move(laneVector)),
                m_sTime(stime), m_eTime(etime),
                m_type(type), m_sern(sern) {}
} // namespace NextSimIO
