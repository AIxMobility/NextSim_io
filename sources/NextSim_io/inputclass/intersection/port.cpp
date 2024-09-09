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
    : linkId(id), direction(dir), type(type) {};
} // namespace NextSimIO