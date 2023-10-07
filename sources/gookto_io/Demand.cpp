#include <string>
#include <iostream>

#include <gookto_io/Demand.hpp>

#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/tinyapi/tinystr.h>

Demand::Demand(int type, int flow, int sink, int source, int dist) : 
    type(type), flow(flow), sink(sink), source(source), dist(dist) {};