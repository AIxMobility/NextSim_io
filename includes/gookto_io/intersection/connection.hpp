#pragma once
#include <vector>
#include <string>
#include <iostream>

class connection
{
private:
    int connectionId;
    int from_link;
    int from_lane;
    int to_link;
    int to_lane;
    double priority;

public:
    connection(int id, int fromLink, int fromLane, int toLink, int toLane, double priority);

    //access functions
    int getConnId() { return connectionId; }
    int getFromLink() { return from_link; }
    int getFromLane() { return from_lane; }
    int getToLink() { return to_link; }
    int getToLane() { return to_lane; }
    double getPriority() { return priority; }

};