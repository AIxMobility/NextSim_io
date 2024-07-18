#include <NextSim_io/InputPax.hpp>


ODPax::ODPax(int origin, int dest, int flow, std::string dist) :
    origin(origin), dest(dest), flow(flow), dist(dist)
{
};


AgentPax::AgentPax(int id, int origin_station, int dest_station, 
                   double dpt_time, std::string type) :
    id(id), origin_station(origin_station), 
    dest_station(dest_station), dpt_time(dpt_time), type(type)
{
};