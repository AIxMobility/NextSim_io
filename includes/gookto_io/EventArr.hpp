#ifndef EVENTARR_H
#define EVENTARR_H

#include <vector>
#include "InputEvent.hpp"

class EventArr
{
private:
    std::vector<InputEvent> Events;

public:
    EventArr();
    /**
     * Creates a vector of InputEvent
     */

    // access function
    std::vector<InputEvent> getEvents()  { return Events; }
};

#endif