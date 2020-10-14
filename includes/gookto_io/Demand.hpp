#ifndef DEMAND_H
#define DEMAND_H

#include <vector>
#include <string>
#include <iostream>

class Demand
{
private:
    int flow;
    int sink;
    int source;
    int dist;

public:
    Demand(int flow, int sink, int source, int dist);

    //access functions
    int getFlow() { return flow; }
    int getSink() { return sink; }
    int getSource() { return source; }
    int getDist() { return dist; }
};

#endif