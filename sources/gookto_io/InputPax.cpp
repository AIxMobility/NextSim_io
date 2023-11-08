#include <gookto_io/InputPax.hpp>


ODPax::ODPax(int origin, int dest, int flow, std::string dist) :
    origin(origin), dest(dest), flow(flow), dist(dist)
{
};


AgentPax::AgentPax(int id, int origin_link, double origin_pos, 
                   int dest_link, double dest_pos, 
                   double dpt_time, std::string type) :
    id(id), origin_link(origin_link), origin_pos(origin_pos),
    dest_link(dest_link), dest_pos(dest_pos),
    dpt_time(dpt_time), type(type)
{
};