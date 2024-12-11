/**
 * NextSim Captain
 * @file : InputSegment.cpp
 * @version : 1.0
 * @author : ???
 */

#include <NextSim_io/inputclass/InputSegment.hpp>

namespace NextSimIO
{
InputSegment::InputSegment(std::size_t id, bool blocked, bool leftLc, bool rightLc,
                 double initPoint, double endPoint)
    : m_id(id), m_blocked(blocked), m_leftLcAllowed(leftLc), m_rightLcAllowed(rightLc),
      m_initPoint(initPoint), m_endPoint(endPoint) {};
} // namespace NextSimIO