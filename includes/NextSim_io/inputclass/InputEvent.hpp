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
enum class InputEventMsgType
{
    RoadEvent = 4,
    SpeedLimit = 5
};

constexpr int ToInt(InputEventMsgType msgType)
{
    return static_cast<int>(msgType);
}

/**
 * @class InputEvent
 * @brief Class for event information from events.xml
*/
class InputEvent
{
public:
    /**
     * @details Constructor
     * @param id Event ID
     * @param linkID Link ID
     * @param hasPosRange Whether start/end position range is specified
     * @param startPos Start offset
     * @param endPos End offset
     * @param laneVector Lane IDs
     * @param hasStartTime Whether start time is specified
     * @param startTime Start time [s] from 00:00:00
     * @param duration Duration [s], negative value means until scenario end
     * @param msgType V2X message type
     * @param type Event type
     * @param sern Event seriousness (severity)
     * @param speedLimit Speed limit [m/s]
    */
    InputEvent(int id, std::size_t linkID, bool hasPosRange, double startPos, double endPos,
               std::vector<int> laneVector, bool hasStartTime, double startTime, double duration,
               int msgType, int type, int sern, double speedLimit, std::string detail = "");

    /**
     * @details Get event ID
     * @return Event ID
    */
    int GetId() const { return m_id; }

    /**
     * @details Get link ID
     * @return Link ID of event occurrence
    */
    std::size_t GetLinkId() const { return m_linkID; }

    /**
     * @details Check whether the event uses a partial link position range
     * @return true if both start and end position were specified in events.xml
    */
    bool HasPosRange() const { return m_hasPosRange; }

    /**
     * @details Get start position
     * @return Start position of event occurrence (from link start point)
    */
    double GetStartPos() const { return m_startPos; }

    /**
     * @details Get end position
     * @return End position of event occurrence (from link start point)
    */
    double GetEndPos() const { return m_endPos; }

    /**
     * @details Get position
     * @return Start position of event occurrence (from link start point)
    */
    double GetPos() const { return m_startPos; }

    /**
     * @details Get lane ID
     * @return Lane ID of event occurrence
    */
    int GetLane() const { return m_lane; }

    /**
     * @details Get lane IDs
     * @return Lane IDs of event occurrence
    */
    const std::vector<int>& GetLaneVector() const { return m_laneVector; }

    /**
     * @details Check whether the event start time was explicitly specified
     * @return true if stime was provided in events.xml
    */
    bool HasStartTime() const { return m_hasStartTime; }

    /**
     * @details Get lane IDs
     * @return Lane IDs of event occurrence
    */
    const std::vector<int>& GetLaneVector() const { return m_laneVector; }

    /**
     * @details Get start time
     * @return Start time of event occurrence
    */
    double GetStartTime() const { return m_startTime; }

    /**
     * @details Get event duration
     * @return Event duration in seconds, negative value means until scenario end
    */
    double GetDuration() const { return m_duration; }

    /**
     * @details Get msg type
     * @return Msg type
    */
    int GetMsgType() const { return m_msgType; }

    /**
     * @details Get event type
     * @return Event type
    */
    int GetType() const { return m_type; }

    /**
     * @details Get event seriousness (severity)
     * @return Event seriousness (severity)
    */
    int GetSern() const { return m_sern; }

    /**
     * @details Get speed limit
     * @return Speed limit of event in m/s
    */
    double GetSpeedLimit() const { return m_speedLimit; }

    /**
     * @details Get detail text
     * @return Detail text of event
    */
    const std::string& GetDetail() const { return m_detail; }

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
     * @details Whether start/end position was explicitly specified
    */
    bool m_hasPosRange;

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
     * @details Whether start time was explicitly specified
    */
    bool m_hasStartTime;

    /**
     * @details Start time of event occurrence
    */
    double m_startTime;

    /**
     * @details Duration of event
    */
    double m_duration;

    /**
     * @details Msg type
    */
    int m_msgType;

    /**
     * @details Event type
    */
    int m_type;

    /**
     * @details Event seriousness (severity)
    */
    int m_sern;

    /**
     * @details Speed limit of event
     */
    double m_speedLimit;

    /**
     * @details Detail of event
     */
    std::string m_detail;
};
} // namespace NextSimIO

#endif
