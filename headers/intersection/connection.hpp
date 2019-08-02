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
    float priority;

public:
    connection(int id, int fromLink, int fromLane, int toLink, int toLane, int priority);

    //access functions
    int getConnId() { return connectionId; }
    int getFromLink() { return from_link; }
    int getFromLane() { return from_lane; }
    int getToLink() { return to_link; }
    int getToLane() { return to_lane; }
    float getPriority() { return priority; }

};