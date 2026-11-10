/**
 * NextSim Captain
 * @file : InputPax.cpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#include <NextSim_io/inputclass/InputPax.hpp>

namespace NextSimIO
{
InputODPax::InputODPax(int origin, int dest, int flow, std::string dist, int matrixId)
    : m_origin(origin), m_dest(dest), m_flow(flow), m_dist(dist), m_matrixId(matrixId) {};

InputAgentPax::InputAgentPax(int id, int originLink, int originOffset, int destLink, int destOffset, double time)
    : m_id(id), m_originLink(originLink), m_originOffset(originOffset), 
      m_destLink(destLink), m_destOffset(destOffset), 
      m_time(time) {}

void InputAgentPax::AddTrip(int origin, int dest, std::string mode, std::string lineID, double time) {
  m_trips.push_back(InputAgentPaxTrip(origin, dest, mode, lineID, time)); }

void InputAgentPax::SetNodeTrip(int originNode, int destNode, std::string mode)
{
    m_originNode = originNode;
    m_destNode = destNode;
    m_mode = std::move(mode);
}

void InputAgentPax::SetTripKey(std::string personId, int tourNo, int stopNo)
{
    m_personId = std::move(personId);
    m_tourNo = tourNo;
    m_stopNo = stopNo;
}
} // namespace NextSimIO