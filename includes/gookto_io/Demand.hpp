#ifndef DEMAND_H
#define DEMAND_H

#include <vector>
#include <string>
#include <iostream>

class NVdemand
{
private:
    int flow;
    int sink;
    int source;
    int dist;

public:
    NVdemand(int flow, int sink, int source, int dist);

    //access functions
    int getFlow() { return flow; }
    int getSink() { return sink; }
    int getSource() { return source; }
    int getDist() { return dist; }
};

class PVdemand
{
private:
    int route;
    int sink;
    int source;

public:
    PVdemand(int route, int sink, int source);

    //access functions
    int getRoute() { return route; }
    int getSink() { return sink; }
    int getSource() { return source; }
};
#endif