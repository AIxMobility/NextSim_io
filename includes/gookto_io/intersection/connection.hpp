#pragma once
#include <iostream>
#include <string>
#include <vector>

class connection
{
 private:
    int connectionId;
    int from_link;
    int from_lane;
    int to_link;
    int to_lane;
    double priority;
    double length;

 public:
    connection(int id, int fromLink, int fromLane, int toLink, int toLane,
               double priority, double length);

    // access functions
    int getConnId()
    {
        return connectionId;
    }
    int getFromLink()
    {
        return from_link;
    }
    int getFromLane()
    {
        return from_lane;
    }
    int getToLink()
    {
        return to_link;
    }
    int getToLane()
    {
        return to_lane;
    }
    double getPriority()
    {
        return priority;
    }
    double getLength()
    {
        return length;
    }
};