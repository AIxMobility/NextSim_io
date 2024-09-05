#include <string>
#include <iostream>

#include <NextSim_io/intersection/port.hpp>

namespace NextSimIO
{
port::port(int id, int dir, int type) :
linkId(id), direction(dir), type(type)
{};
} // namespace NextSimIO