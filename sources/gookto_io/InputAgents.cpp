/**
 * STS19 Captain
 * @file : InputAgents.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <string>
#include <iostream>

#include <gookto_io/InputAgents.hpp>

InputAgents::InputAgents(int id, int type, double dpt_time) 
                         : id(id), typeId(type), dpt_time(dpt_time){};

void InputAgents::addLink(int val)
{
    link_seq.push_back(val);
};

void InputAgents::addNode(int val)
{
    node_seq.push_back(val);
};

void InputAgents::addPaxList(int val)
{
    pax_list.push_back(val);
};

void InputAgents::addPaxOrigin(int val)
{
    pax_origin.push_back(val);
};

void InputAgents::addPaxDest(int val)
{
    pax_dest.push_back(val);
};

void InputAgents::addStation(int val)
{
    station_seq.push_back(val);
};

void InputAgents::addStationDwellTime(double val)
{
    station_dwell_time.push_back(val);
};

void InputAgents::addStationIn(int val)
{
    station_in.push_back(val);
};

void InputAgents::addStationOut(int val)
{
    station_out.push_back(val);
};