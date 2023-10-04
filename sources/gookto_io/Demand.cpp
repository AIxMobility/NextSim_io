#include <string>
#include <iostream>

#include <gookto_io/Demand.hpp>

#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/tinyapi/tinystr.h>

NVdemand::NVdemand(int flow, int sink, int source, int dist) : 
    flow(flow), sink(sink), source(source), dist(dist) {};

PVdemand::PVdemand(int line, int sink, int source) :
    line(line), sink(sink), source(source) {};