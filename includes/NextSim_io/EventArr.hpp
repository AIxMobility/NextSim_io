/**
 * NextSim Captain
 * @file : EventArr.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#ifndef EVENTARR_H
#define EVENTARR_H

#include <vector>
#include "InputEvent.hpp"

/**
 * @class EventArr
 * @brief Class for whole event from events.xml
*/
class EventArr
{
private:
    /**
     * @details Sequence of events
    */
    std::vector<InputEvent> Events;

public:
    /**
     * @details Constructor
     */
    EventArr();

    // access function
    /**
     * @details Get sequence of events
     * @return Sequence of events
     */
    std::vector<InputEvent> getEvents()  { return Events; }
};

#endif