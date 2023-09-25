#include <gookto_io/InputPax.hpp>


ODPax::ODPax(int origin, int dest, int flow, std::string dist) :
    origin(origin), dest(dest), flow(flow), dist(dist)
{
};


AgentPax::AgentPax(int origin_link, double origin_pos, 
         int dest_link, double dest_pos, 
         int num_pax, double time, std::string type) :
    origin_link(origin_link), origin_pos(origin_pos),
    dest_link(dest_link), dest_pos(dest_pos),
    num_pax(num_pax), time(time), type(type)
{
};