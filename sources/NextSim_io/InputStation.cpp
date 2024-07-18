#include <string>
#include <iostream>
#include <sstream>

#include <NextSim_io/InputStation.hpp>

InputStation::InputStation(int id, int link_ref, int lane_ref, double pos, int parkingLots) : 
    id(id), link_ref(link_ref), lane_ref(lane_ref), pos(pos), parkingLots(parkingLots){};

void InputStation::setLineList(std::string line_list_str)
{
    std::stringstream ss(line_list_str);
    int line_id;

    while (ss >> line_id)
        line_list.push_back(line_id);
}


InputDRTStation::InputDRTStation(int id, int link_ref, int lane_ref) : 
    id(id), link_ref(link_ref), lane_ref(lane_ref) {};

void InputDRTStation::setPosRange(std::string pos_range_str)
{
    double start_pos;
    double end_pos;

    std::stringstream ss(pos_range_str);
    char delim;

    ss >> start_pos >> delim >> end_pos;

    if (delim == '-')
        pos_range = std::make_pair(start_pos, end_pos);
}