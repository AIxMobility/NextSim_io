/**
 * NextSim Captain
 * @file : EventArr.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#ifndef EVENTARR_H
#define EVENTARR_H

#include <vector>
#include <NextSim_io/inputclass/InputEvent.hpp>

namespace NextSimIO
{
/**
 * @class EventArr
 * @brief Class for event scenario from events.xml
*/
class EventArr
{
public:
    /**
     * @details Constructor (Parse events from eventdata.xml)
     */
    EventArr();

    /**
     * @details Get vector of events
     * @return Vector of events
     */
    std::vector<InputEvent> GetEvents()  { return m_events; }

private:
    /**
     * @details Vector of events
    */
    std::vector<InputEvent> m_events;
};
} // namespace NextSimIO

#endif