#include <string>
#include <iostream>

#include <gookto_io/Demand.hpp>

#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/tinyapi/tinystr.h>

NVdemand::NVdemand(int flow, int sink, int source, int dist) : 
    flow(flow), sink(sink), source(source), dist(dist) {};

PVdemand::PVdemand(int route, int sink, int source) :
    route(route), sink(sink), source(source) {};