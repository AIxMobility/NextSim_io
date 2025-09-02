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

InputAgentPax::InputAgentPax(int id, int originLink, int originOffset, int destLink, int destOffset, double time)
    : m_id(id), m_originLink(originLink), m_originOffset(originOffset), 
      m_destLink(destLink), m_destOffset(destOffset), 
      m_time(time) {}

void InputAgentPax::AddTrip(int origin, int dest, std::string mode, int lineID) {
  m_trips.push_back(InputAgentPaxTrip(origin, dest, mode, lineID)); }
} // namespace NextSimIO