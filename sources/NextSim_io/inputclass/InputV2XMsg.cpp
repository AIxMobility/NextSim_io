/**
 * NextSim Captain
 * @file : InputMessage.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <NextSim_io/inputclass/InputV2XMsg.hpp>
 // Wait, I haven't renamed the file yet. I'll keep the include as is for now or update it later.

namespace NextSimIO
{
InputV2XMsg::InputV2XMsg(int id, double sTime, double eTime, 
                             int msgType, int value)
    : m_id(id), m_sTime(sTime), m_eTime(eTime), 
    m_msgType(msgType), m_value(value)
{
}
}
 // namespace NextSimIO