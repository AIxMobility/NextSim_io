/**
 * NextSim Captain
 * @file : port.cpp
 * @version : 1.0
 * @author : ???
 */

#include <NextSim_io/inputclass/intersection/port.hpp>

namespace NextSimIO
{
port::port(int id, int dir, int type) 
    : m_linkId(id), m_direction(dir), m_type(type) {};
} // namespace NextSimIO