/**
 * NextSim Captain
 * @file : turn.cpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#include <sstream>

#include <NextSim_io/inputclass/signal/turn.hpp>

namespace NextSimIO
{
turn::turn(int id, int turning, std::string type)
    : m_id(id), m_turning(turning), m_type(type) {};

void turn::SetConnList(std::string connString)
{
    std::stringstream ss(connString);
    int connId;

    while (ss >> connId)
        m_connList.push_back(connId);
}
} // namespace NextSimIO