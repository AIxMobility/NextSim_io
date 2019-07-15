#include <string>
#include <iostream>
#include "intersectionPhase.hpp"

intersectionPhase::intersectionPhase(int id) :
id(id)
{};

void intersectionPhase::pushConnectionRef(int val)
{
    connectionRef.push_back(val);
};

void intersectionPhase::pushPriority(int val)
{
    priority.push_back(val);
};