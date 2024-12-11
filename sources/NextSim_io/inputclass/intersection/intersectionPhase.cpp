/**
 * NextSim Captain
 * @file : intersectinoPhase.cpp
 * @version : 1.0
 * @author : ???
 */

#include <NextSim_io/inputclass/intersection/intersectionPhase.hpp>

namespace NextSimIO
{
intersectionPhase::intersectionPhase(int id) : m_id(id) {};

void intersectionPhase::PushConnection(int conn)
{
    m_connectionVector.push_back(conn);
};

void intersectionPhase::PushPriority(double priority)
{
    m_priorityVector.push_back(priority);
};
} // namespace NextSimIO