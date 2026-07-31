/**
 * NextSim Captain
 * @file : InputNode.hpp
 * @version : 1.0
 * @author : ???
 */

#include <NextSim_io/inputclass/InputNode.hpp>

namespace NextSimIO
{
InputNode::InputNode(int type, int id, int numConnection, int numPort)
    : m_type(type), m_id(id), m_numConnections(numConnection), 
      m_numLinks(numPort) {};
} // namespace NextSimIO
