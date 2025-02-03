/**
 * NextSim Captain
 * @file : plan.cpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#include <NextSim_io/inputclass/signal/plan.hpp>

namespace NextSimIO
{
plan::plan(int id, int cycle, int offset, std::vector<phase> phaseSeq) 
    : m_id(id), m_cycle(cycle), m_offset(offset), m_phaseSeq(phaseSeq) {};
} // namespace NextSimIO