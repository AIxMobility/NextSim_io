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

void InputGraphVertex::pushLink(port link)
{
    m_connectedLinks.emplace_back(link);
}
} // namespace NextSimIO
