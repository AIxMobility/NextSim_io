/**
 * NextSim Captain
 * @file : InputMessage.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <NextSim_io/inputclass/InputMessage.hpp>

namespace NextSimIO
{
InputMessage::InputMessage(int id, double stime, double etime, 
                           int msg_type, int value) 
    : id(id), stime(stime), etime(etime), 
      msg_type(msg_type), value(value) {};
} // namespace NextSimIO