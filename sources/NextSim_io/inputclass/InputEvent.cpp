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
        id(id), link_id(link_id), pos(pos), 
        lane(lane), stime(stime), etime(etime), 
        type(type), sern(sern) {};
} // namespace NextSimIO