/**
 * NextSim Captain
 * @file : InputFlow.cpp
 * @version : 1.0
 * @author : ???
 */

#include <NextSim_io/inputclass/InputFlow.hpp>

namespace NextSimIO
{
InputFlow::InputFlow(int type, int flow, int sink, int source, int dist, bool v2xActive) :
    m_type(type), m_flow(flow), m_sink(sink), m_source(source), m_dist(dist), m_v2xActive(v2xActive) {}
} // namespace NextSimIO
