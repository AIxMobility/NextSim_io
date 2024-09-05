/**
 * NextSim Captain
 * @file : InputEvent.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#ifndef INPUTEVENT_H
#define INPUTEVENT_H

#include <iostream>
#include <string>
#include <vector>

//**
// * @class InputEvent
// * @brief Class for event information from events.xml
// */
class InputEvent
{
private:

    /**
     * @details Event ID
    */
    int id;

    /**
     * @details Link ID for event operation
    */
    std::size_t link_id;

    /**
     * @details Offset for event operation (from link start point)
    */
    // ??? start 아니면 end 부터 offset인지
    double pos;

    /**
     * @details Lane ID for event operation
    */
    int lane;

    /**
     * @details Start time for event operation
    */
    double stime;

    /**
     * @details End time for event operation
    */
    double etime;

    /**
     * @details Event type
    */
    int type;

    /**
     * @details Event seriousness
    */
    // ??? 심각도로 쓸거면 severity 가 더 맞는 표현이라고 나옴
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
     * @param sern Event seriousness
    */
    InputEvent(int id, std::size_t link_id, double pos, int lane, double stime, double etime, int type, int sern);

    // access functions
    
    /**
     * @details Get event ID
     * @return Event ID
    */
    int getId()
    {
        return id;
    }

    /**
     * @details Get link ID
     * @return Link ID for event operation
    */
    std::size_t getLinkId()
    {
        return link_id;
    }

    /**
     * @details Get offset
     * @return Offset for event operation (from link start point)
    */
    double getPos()
    {
        return pos;
    }

    /**
     * @details Get lane ID
     * @return Lane ID for event operation
    */
    int getLane()
    {
        return lane;
    }

    /**
     * @details Get start time
     * @return Start time for event operation
    */
    double getStime()
    {
        return stime;
    }

    /**
     * @details Get end time
     * @return End time for event operation
    */
    double getEtime()
    {
        return etime;
    }

    /**
     * @details Get event type
     * @return Event type
    */
    int getType()
    {
        return type;
    }

    /**
     * @details Get event seriousness
     * @return Event seriousness
    */
    int getSern()
    {
        return sern;
    }
};

#endif