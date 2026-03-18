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
    double length, double width, double ffspeed,
    std::vector<std::pair<double, double>> shapePoints)
    : m_connectionId(id), m_fromLink(fromLink), m_fromLane(fromLane), m_toLink(toLink), m_toLane(toLane),
  m_turning(std::move(turning)), m_priority(priority), m_length(length), m_width(width),
  m_ffSpeed(ffspeed), m_shapePoints(std::move(shapePoints)) {};
}  // namespace NextSimIO