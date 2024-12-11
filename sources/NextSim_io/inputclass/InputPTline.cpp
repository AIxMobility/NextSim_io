/**
 * NextSim Captain
 * @file : InputPTline.cpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#include <sstream>

#include <NextSim_io/inputclass/InputPTline.hpp>

namespace NextSimIO
{
InputPTline::InputPTline(int id, double interval) 
    : m_id(id), m_interval(interval) {};

void InputPTline::SetLinkSeq(std::string linkSeq)
{
    std::stringstream ss(linkSeq);
    int linkid;

    while (ss >> linkid)
        m_linkSeq.push_back(linkid);
}

void InputPTline::SetNodeSeq(std::string nodeSeq)
{
    std::stringstream ss(nodeSeq);
    int nodeid;

    while (ss >> nodeid)
       m_nodeSeq.push_back(nodeid);
}

void InputPTline::SetStationSeq(std::string stationSeq)
{
    std::stringstream ss(stationSeq);
    int stationid;

    while (ss >> stationid)
        m_stationSeq.push_back(stationid);
}

void InputPTline::SetStationDistanceSeq(std::string stationDistanceSeq)
{
    std::stringstream ss(stationDistanceSeq);
    double stationDistance;

    while (ss >> stationDistance)
        m_stationDistanceSeq.push_back(stationDistance);
}
} // namespace NextSimIO