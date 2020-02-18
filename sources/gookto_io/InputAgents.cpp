#include <string>
#include <iostream>

#include <gookto_io/InputAgents.hpp>

#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/tinyapi/tinystr.h>

InputAgents::InputAgents(int id, int type, float dpt_time) :
id(id), type(type), dpt_time(dpt_time)
{};


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