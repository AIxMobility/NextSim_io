/**
 * NextSim Captain
 * @file : InputEvent.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#pragma once
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
public:
    // Constructor
    /**
     * @details Constructor
     * @param id Event ID
     * @param linkID Link ID
     * @param pos Offset
     * @param lane Lane ID
     * @param sTime Start time
     * @param eTime End time
     * @param type Event type
     * @param sern Event seriousness (severity)
    */
    InputEvent(int id, std::size_t linkID, double pos, 
               int lane, double sTime, double eTime, 
               int type, int sern);

    /**
     * @details Get event ID
     * @return Event ID
    */
    int GetId() { return m_id; }

    /**
     * @details Get link ID
     * @return Link ID of event occurrence
    */
    std::size_t GetLinkId() { return m_linkID; }

    /**
     * @details Get position 
     * @return Position of event occurrence (from link start point)
    */
    double GetPos() { return m_pos; }

    /**
     * @details Get lane ID
     * @return Lane ID of event occurrence
    */
    int GetLane() { return m_lane; }

    /**
     * @details Get start time
     * @return Start time of event occurrence
    */
    double GetStime() { return m_sTime; }

    /**
     * @details Get end time
     * @return End time of event occurrence
    */
    double GetEtime() { return m_eTime; }

    /**
     * @details Get event type
     * @return Event type
    */
    int GetType() { return m_type; }

    /**
     * @details Get event seriousness (severity)
     * @return Event seriousness (severity)
    */
    int GetSern() { return m_sern; }

private:

    /**
     * @details Event ID
    */
    int m_id;

    /**
     * @details Link ID of event occurrence
    */
    std::size_t m_linkID;

    /**
     * @details Position of event occurrence (from link start point)
    */
    double m_pos;

    /**
     * @details Lane ID of event occurrence
    */
    int m_lane;

    /**
     * @details Start time of event occurrence
    */
    double m_sTime;

    /**
     * @details End time of event
    */
    double m_eTime;

    /**
     * @details Event type
    */
    int m_type;

    /**
     * @details Event seriousness (severity)
    */
    int m_sern;

};
} // namespace NextSimIO

#endif