/**
 * NextSim Captain
 * @file : connection.cpp
 * @version : 1.0
 * @author : ???
 */

#include <NextSim_io/inputclass/intersection/connection.hpp>

namespace NextSimIO
{
connection::connection(int id, int fromLink, int fromLane, int toLink, int toLane,
            std::string turning, double priority, 
            double length, double width, double ffspeed)
    : connectionId(id),
    from_link(fromLink),
    from_lane(fromLane),
    to_link(toLink),
    to_lane(toLane),
    turning(turning),
    priority(priority),
    length(length),
    width(width),
    ffspeed(ffspeed){};
}  // namespace NextSimIO