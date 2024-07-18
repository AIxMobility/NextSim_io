#include <string>
#include <iostream>

#include <NextSim_io/intersection/intersectionPhase.hpp>

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