/**
 * NextSim Captain
 * @file : InputMessage.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <NextSim_io/inputclass/InputMessage.hpp>

namespace NextSimIO
{
InputMessage::InputMessage(int id, double sTime, double eTime, 
                           int msgType, int value) 
    : m_id(id), m_sTime(sTime), m_eTime(eTime), 
      m_msgType(msgType), m_value(value) {}
} // namespace NextSimIO