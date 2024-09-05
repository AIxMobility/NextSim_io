#include <string>
#include <iostream>

#include <NextSim_io/intersection/intersectionPhase.hpp>

namespace NextSimIO
{
intersectionPhase::intersectionPhase(int id) :
id(id)
{};

void intersectionPhase::pushConnectionRef(int val)
{
    connectionRef.push_back(val);
};

void intersectionPhase::pushPriority(double val)
{
    priority.push_back(val);
};
} // namespace NextSimIO