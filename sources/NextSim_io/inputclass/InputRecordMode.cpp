/**
 * NextSim Captain
 * @file : InputRecordMode.cpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#include <NextSim_io/inputclass/InputRecordMode.hpp>

namespace NextSimIO
{
InputRecordMode::InputRecordMode(int id, bool activated)
    : m_id(id), m_activated(activated) {};
} // namespace NextSimIO