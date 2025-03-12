/**
 * NextSim Captain
 * @file : InputBackgroundTraffic.cpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#include <NextSim_io/inputclass/InputBackgroundTraffic.hpp>

namespace NextSimIO
{
InputBackgroundTraffic::InputBackgroundTraffic(int id, double avgSpd, double density)
    : m_id(id), m_avgSpd(avgSpd), m_density(density) {};
} // namespace NextSimIO