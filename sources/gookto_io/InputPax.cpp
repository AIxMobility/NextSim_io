#include <gookto_io/InputPax.hpp>

#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/tinyapi/tinystr.h>

#include <string>
#include <iostream>

InputPax::InputPax(int id, int type, float dpt_time) :
id(id), type(type), dpt_time(dpt_time)
{};

void InputPax::addLink(int val)
{
    link_seq.push_back(val);
};

void InputPax::addNode(int val)
{
    node_seq.push_back(val);
};