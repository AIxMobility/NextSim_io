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
     * @param startPos Start offset
     * @param endPos End offset
     * @param laneVector Lane IDs
     * @param sTime Start time
     * @param eTime End time
     * @param type Event type
     * @param sern Event seriousness (severity)
    */
    InputEvent(int id, std::size_t linkID, double startPos, double endPos,
               std::vector<int> laneVector, double sTime, double eTime, 
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
     * @details Get start position
     * @return Start position of event occurrence (from link start point)
    */
    double GetStartPos() { return m_startPos; }

    /**
     * @details Get end position
     * @return End position of event occurrence (from link start point)
    */
    double GetEndPos() { return m_endPos; }

    /**
     * @details Get position
     * @return Start position of event occurrence (from link start point)
    */
    double GetPos() { return m_startPos; }

    /**
     * @details Get lane ID
     * @return Lane ID of event occurrence
    */
    int GetLane() { return m_lane; }

    /**
     * @details Get lane IDs
     * @return Lane IDs of event occurrence
    */
    const std::vector<int>& GetLaneVector() const { return m_laneVector; }

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
     * @details Start position of event occurrence (from link start point)
    */
    double m_startPos;

    /**
     * @details End position of event occurrence (from link start point)
    */
    double m_endPos;

    /**
     * @details Lane ID of event occurrence
    */
    int m_lane;

    /**
     * @details Lane IDs of event occurrence
    */
    std::vector<int> m_laneVector;

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
