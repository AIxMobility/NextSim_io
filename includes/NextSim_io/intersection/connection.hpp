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
    std::string turning;
    double priority;
    double length;
    double width;
    double ffspeed;

 public:
    connection(int id, int fromLink, int fromLane, int toLink, int toLane,
               std::string turning, double priority, 
               double length, double width, double ffspeed);

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

    bool operator< (const connection& other) const
    {
        return to_lane < other.to_lane;
    }
};