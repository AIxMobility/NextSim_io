/**
 * NextSim Captain
 * @file InputGraphVertex.cpp
 * @version 1.0
 * @author Dongheon Lee
 */

#include <NextSim_io/inputclass/InputGraphVertex.hpp>

namespace NextSimIO
{
InputGraphVertex::InputGraphVertex(int id, int type, float heuristic, int rank)
    : m_id(id), m_type(type), m_heuristic(heuristic), m_rank(rank) {};

ConnectionInfo::ConnectionInfo(int fromLink, int toLink, double length)
    : m_fromLink(fromLink), m_toLink(toLink), m_length(length) {};

VertexCoord::VertexCoord(float x, float y)
    : m_x(x), m_y(y) {};

void InputGraphVertex::pushLink(port link)
{
    m_connectedLinks.emplace_back(link);
}
} // namespace NextSimIO
