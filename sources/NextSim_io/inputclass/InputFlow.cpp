/**
 * NextSim Captain
 * @file : InputFlow.cpp
 * @version : 1.0
 * @author : ???
 */

#include <NextSim_io/inputclass/InputFlow.hpp>

namespace NextSimIO
{
InputFlow::InputFlow(int type, int flow, int sink, int source, int dist) : 
    type(type), flow(flow), sink(sink), source(source), dist(dist) {};
} // namespace NextSimIO