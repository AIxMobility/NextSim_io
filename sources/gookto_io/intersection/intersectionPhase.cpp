#include <string>
#include <iostream>

#include <gookto_io/intersection/intersectionPhase.hpp>

intersectionPhase::intersectionPhase(int id) :
id(id)
{};

void intersectionPhase::pushConnectionRef(long int val)
{
    connectionRef.push_back(val);
};

void intersectionPhase::pushPriority(float val)
{
    priority.push_back(val);
};