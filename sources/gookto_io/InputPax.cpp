#include <gookto_io/InputPax.hpp>


InputPax::InputPax(int id, int type, double dpt_time) :
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