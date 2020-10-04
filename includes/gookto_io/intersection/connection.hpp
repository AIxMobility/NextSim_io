#pragma once
#include <vector>
#include <string>
#include <iostream>

class connection
{
private:
    long int connectionId;
    long int from_link;
    long int from_lane;
    long int to_link;
    long int to_lane;
    float priority;

public:
    connection(long int id, long int fromLink, long int fromLane, long int toLink, long int toLane, float priority);

    //access functions
    long int getConnId() { return connectionId; }
    long int getFromLink() { return from_link; }
    long int getFromLane() { return from_lane; }
    long int getToLink() { return to_link; }
    long int getToLane() { return to_lane; }
    float getPriority() { return priority; }

};