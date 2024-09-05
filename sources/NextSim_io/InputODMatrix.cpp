#include <string>
#include <iostream>

#include <NextSim_io/InputODMatrix.hpp>

#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/tinyapi/tinystr.h>

namespace NextSimIO
{
InputODMatrix::InputODMatrix(int id, std::vector<Demand> demands)
    : id(id), demands(demands) {};
} // namespace NextSimIO