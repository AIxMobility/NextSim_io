#include <string>
#include <iostream>

#include <NextSim_io/Demand.hpp>

#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/tinyapi/tinystr.h>

Demand::Demand(int type, int flow, int sink, int source, int dist) : 
    type(type), flow(flow), sink(sink), source(source), dist(dist) {};