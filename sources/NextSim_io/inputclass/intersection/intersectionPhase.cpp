/**
 * NextSim Captain
 * @file : intersectinoPhase.cpp
 * @version : 1.0
 * @author : ???
 */

#include <NextSim_io/inputclass/intersection/intersectionPhase.hpp>

namespace NextSimIO
{
intersectionPhase::intersectionPhase(int id) : id(id) {};

void intersectionPhase::pushConnectionRef(int conn)
{
    connectionRef.push_back(conn);
};

void intersectionPhase::pushPriority(double priority)
{
    connectionRef.push_back(priority);
};
} // namespace NextSimIO