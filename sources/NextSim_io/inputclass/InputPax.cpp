/**
 * NextSim Captain
 * @file : InputPax.cpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#include <NextSim_io/inputclass/InputPax.hpp>

namespace NextSimIO
{
InputODPax::InputODPax(int origin, int dest, int flow, std::string dist) 
    : m_origin(origin), m_dest(dest), m_flow(flow), m_dist(dist) {};

InputAgentPax::InputAgentPax(int id, int originStation, int destStation, 
                             double dptTime, std::string type) 
    : m_id(id), m_originStation(originStation), m_destStation(destStation), 
      m_dptTime(dptTime), m_type(type) {};
} // namespace NextSimIO