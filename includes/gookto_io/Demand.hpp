#ifndef DEMAND_H
#define DEMAND_H

#include <vector>
#include <string>
#include <iostream>

class Demand
{
private:
    int type;  // 0: NV, 1: AV, 2: TR
    int flow;
    int sink;
    int source;
    int dist;

public:
    Demand(int type, int flow, int sink, int source, int dist);

    //access functions
    int getType() { return type; }
    int getFlow() { return flow; }
    int getSink() { return sink; }
    int getSource() { return source; }
    int getDist() { return dist; }
};
#endif