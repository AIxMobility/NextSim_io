/**
 * NextSim Captain
 * @file : InputNode.hpp
 * @version : 1.0
 * @author : ???
 */

#include <NextSim_io/inputclass/InputNode.hpp>

namespace NextSimIO
{
InputNode::InputNode(int type, int id, int num_connection, 
                     int num_port, bool v2xActive)
    : type(type), id(id), numConnections(num_connection), 
      numLinks(num_port), v2xActive(v2xActive) {};
} // namespace NextSimIO