/**
 * STS19 Captain
 * @file : EventArr.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#ifndef EVENTARR_H
#define EVENTARR_H

#include <vector>
#include "InputEvent.hpp"

class EventArr
{
private:
    std::vector<InputEvent> Events;

public:
    EventArr(const std::string& userName);
    /**
     * Creates a vector of InputEvent
     */

    // access function
    std::vector<InputEvent> getEvents()  { return Events; }
};

#endif