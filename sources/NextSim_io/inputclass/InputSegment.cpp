/**
 * NextSim Captain
 * @file : InputSegment.cpp
 * @version : 1.0
 * @author : ???
 */

#include <NextSim_io/inputclass/InputSegment.hpp>

namespace NextSimIO
{
InputSegment::InputSegment(std::size_t id, bool block, bool left_lc, bool right_lc,
                 double init_point, double end_point)
    : id(id), blocked(block), left_lc_allowed(left_lc), right_lc_allowed(right_lc),
      init_point(init_point), end_point(end_point) {};
} // namespace NextSimIO