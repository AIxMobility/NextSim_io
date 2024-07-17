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

class InputEvent
{
private:

    int id;
    std::size_t link_id;
    double pos;
    int lane;
    double stime;
    double etime;
    int type;
    int sern;

public:
    // Constructor
    InputEvent(int id, std::size_t link_id, double pos, int lane, double stime, double etime, int type, int sern);

    // access functions
    int getId()
    {
        return id;
    }
    std::size_t getLinkId()
    {
        return link_id;
    }
    double getPos()
    {
        return pos;
    }
    int getLane()
    {
        return lane;
    }
    double getStime()
    {
        return stime;
    }
    double getEtime()
    {
        return etime;
    }
    int getType()
    {
        return type;
    }
    int getSern()
    {
        return sern;
    }
};

#endif