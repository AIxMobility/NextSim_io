/**
 * NextSim Captain
 * @file : InputSignal.cpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#include <NextSim_io/inputclass/InputSignal.hpp>

namespace NextSimIO
{
InputSignal::InputSignal(int type, int id, int numConnection, 
                         int numPort, bool v2xActive)
    : m_type(type), m_id(id), m_numConnections(numConnection), 
      m_numLinks(numPort), m_v2xActive(v2xActive) {};
} // namespace NextSimIO