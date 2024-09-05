#include <string>
#include <iostream>

#include <NextSim_io/InputFlow.hpp>

#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/tinyapi/tinystr.h>

namespace NextSimIO
{
InputFlow::InputFlow(int type, int flow, int sink, int source, int dist) : 
    type(type), flow(flow), sink(sink), source(source), dist(dist) {};
} // namespace NextSimIO