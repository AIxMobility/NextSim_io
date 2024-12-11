/**
 * NextSim Captain
 * @file : InputEvent.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <NextSim_io/inputclass/InputEvent.hpp>

namespace NextSimIO
{
InputEvent::InputEvent(int id, std::size_t link_id, double pos, 
               int lane, double stime, double etime, 
               int type, int sern) : 
                 m_id(id), m_linkID(link_id), m_pos(pos),
                m_lane(lane), m_sTime(stime), m_eTime(etime),
                m_type(type), m_sern(sern) {}
} // namespace NextSimIO