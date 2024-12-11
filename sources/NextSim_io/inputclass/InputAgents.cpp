/**
 * NextSim Captain
 * @file : InputAgents.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <sstream>

#include <NextSim_io/inputclass/InputAgents.hpp>

namespace NextSimIO
{
InputAgents::InputAgents(int id, int type, double dpt_time) 
                         : m_id(id), m_typeID(type), m_dptTime(dpt_time){};

void InputAgents::SetLinkSeq(std::string linkSeq)
{
    std::stringstream ss(linkSeq);
    int linkid;

    while (ss >> linkid)
        m_linkSeq.push_back(linkid);
}

void InputAgents::SetNodeSeq(std::string nodeSeq)
{
    std::stringstream ss(nodeSeq);
    int nodeid;

    while (ss >> nodeid)
        m_nodeSeq.push_back(nodeid);
}

void InputAgents::SetStationSeq(std::string stationSeq)
{
    std::stringstream ss(stationSeq);
    int stationid;

    while (ss >> stationid)
        m_stationSeq.push_back(stationid);
}

void InputAgents::SetStationDistanceSeq(std::string stationDistanceSeq)
{
    std::stringstream ss(stationDistanceSeq);
    double stationDistance;

    while (ss >> stationDistance)
        m_stationDistanceSeq.push_back(stationDistance);
}
} // namespace NextSimIO