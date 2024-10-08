/**
 * NextSim Captain
 * @file : InputPax.cpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#include <NextSim_io/inputclass/InputPax.hpp>

namespace NextSimIO
{
InputODPax::InputODPax(int origin, int dest, int flow, std::string dist) 
    : origin(origin), dest(dest), flow(flow), dist(dist) {};

InputAgentPax::InputAgentPax(int id, int origin_station, int dest_station, 
                             double dpt_time, std::string type) 
    : id(id), origin_station(origin_station), 
      dest_station(dest_station), dpt_time(dpt_time), type(type) {};
} // namespace NextSimIO