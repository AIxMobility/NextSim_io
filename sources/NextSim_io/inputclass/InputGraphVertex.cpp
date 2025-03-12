/**
 * NextSim Captain
 * @file InputGraphVertex.cpp
 * @version 1.0
 * @author Dongheon Lee
 */

#include <NextSim_io/inputclass/InputGraphVertex.hpp>

namespace NextSimIO
{
InputGraphVertex::InputGraphVertex(int id, float heuristic, int rank)
    : m_id(id), m_heuristic(heuristic), m_rank(rank) {};

ConnectionInfo::ConnectionInfo(int fromLink, int toLink, double length)
    : m_fromLink(fromLink), m_toLink(toLink), m_length(length) {};

void InputGraphVertex::pushLink(port link)
{
    m_connectedLinks.emplace_back(link);
}
} // namespace NextSimIO
