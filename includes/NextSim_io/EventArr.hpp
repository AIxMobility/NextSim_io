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

namespace NextSimIO
{
/**
 * @class EventArr
 * @brief Class for event scenario from events.xml
*/
class EventArr
{
private:
    /**
     * @details Vector of events
    */
    std::vector<InputEvent> Events;

public:
    /**
     * @details Constructor (Parse events from eventdata.xml)
     */
    EventArr();

    /**
     * @details Get vector of events
     * @return Vector of events
     */
    std::vector<InputEvent> getEvents()  { return Events; }
};
} // namespace NextSimIO

#endif