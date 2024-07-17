/**
 * NextSim Captain
 * @file : InputAgents.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <string>
#include <iostream>
#include <sstream>

#include <gookto_io/InputAgents.hpp>

InputAgents::InputAgents(int id, int type, double dpt_time) 
                         : id(id), typeId(type), dpt_time(dpt_time){};

void InputAgents::setLinkSeq(std::string linkSeq)
{
    std::stringstream ss(linkSeq);
    int linkid;

    while (ss >> linkid)
        link_seq.push_back(linkid);
}

void InputAgents::setNodeSeq(std::string nodeSeq)
{
    std::stringstream ss(nodeSeq);
    int nodeid;

    while (ss >> nodeid)
        node_seq.push_back(nodeid);
}

void InputAgents::setStationSeq(std::string stationSeq)
{
    std::stringstream ss(stationSeq);
    int stationid;

    while (ss >> stationid)
        station_seq.push_back(stationid);
}

void InputAgents::setStationDistanceSeq(std::string stationDistanceSeq)
{
    std::stringstream ss(stationDistanceSeq);
    double stationDistance;

    while (ss >> stationDistance)
        station_distance_seq.push_back(stationDistance);
}