/**
 * NextSim Captain
 * @file : InputNode.hpp
 * @version : 1.0
 * @author : ???
 */

#include <NextSim_io/inputclass/InputNode.hpp>

namespace NextSimIO
{
InputNode::InputNode(int type, int id, int numConnection, 
                     int numPort, bool v2xActive)
    : m_type(type), m_id(id), m_numConnections(numConnection), 
      m_numLinks(numPort), m_v2xActive(v2xActive) {};
} // namespace NextSimIO