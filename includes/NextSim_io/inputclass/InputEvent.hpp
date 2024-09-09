/**
 * NextSim Captain
 * @file : InputEvent.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#ifndef INPUTEVENT_H
#define INPUTEVENT_H

#include <string>
#include <vector>

namespace NextSimIO
{
/**
 * @class InputEvent
 * @brief Class for event information from eventdata.xml
*/
class InputEvent
{
private:

    /**
     * @details Event ID
    */
    int id;

    /**
     * @details Link ID of event occurrence
    */
    std::size_t link_id;

    /**
     * @details Position of event occurrence (from link start point)
    */
    double pos;

    /**
     * @details Lane ID of event occurrence
    */
    int lane;

    /**
     * @details Start time of event occurrence
    */
    double stime;

    /**
     * @details End time of event
    */
    double etime;

    /**
     * @details Event type
    */
    int type;

    /**
     * @details Event seriousness (severity)
    */
    int sern;

public:
    // Constructor
    /**
     * @details Constructor
     * @param id Event ID
     * @param link_id Link ID
     * @param pos Offset
     * @param lane Lane ID
     * @param stime Start time
     * @param etime End time
     * @param type Event type
     * @param sern Event seriousness (severity)
    */
    InputEvent(int id, std::size_t link_id, double pos, 
               int lane, double stime, double etime, 
               int type, int sern);

    /**
     * @details Get event ID
     * @return Event ID
    */
    int getId() { return id; }

    /**
     * @details Get link ID
     * @return Link ID of event occurrence
    */
    std::size_t getLinkId() { return link_id; }

    /**
     * @details Get position 
     * @return Position of event occurrence (from link start point)
    */
    double getPos() { return pos; }

    /**
     * @details Get lane ID
     * @return Lane ID of event occurrence
    */
    int getLane() { return lane; }

    /**
     * @details Get start time
     * @return Start time of event occurrence
    */
    double getStime() { return stime; }

    /**
     * @details Get end time
     * @return End time of event occurrence
    */
    double getEtime() { return etime; }

    /**
     * @details Get event type
     * @return Event type
    */
    int getType() { return type; }

    /**
     * @details Get event seriousness (severity)
     * @return Event seriousness (severity)
    */
    int getSern() { return sern; }
};
} // namespace NextSimIO

#endif