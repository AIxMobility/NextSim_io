/**
 * NextSim Captain
 * @file : InputStation.cpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#include <sstream>

#include <algorithm>
#include <NextSim_io/inputclass/InputStation.hpp>

namespace NextSimIO
{
InputStation::InputStation(int id, int link, int lane, double pos, int parkingLots, std::string globalPos) : 
    m_id(id), m_link(link), m_lane(lane), m_pos(pos), m_parkingLots(parkingLots)
{
    std::replace(globalPos.begin(), globalPos.end(), ',', ' ');
    std::stringstream ss(globalPos);
    double x, y;
    if (ss >> x >> y)
    {
        m_globalPos = {x, y};
    }
};

void InputStation::SetLineList(std::string lineList)
{
    std::stringstream ss(lineList);
    std::string line_id;

    while (ss >> line_id)
        m_lineList.push_back(line_id);
}


InputDRTStation::InputDRTStation(int id, int link, int lane) : 
    m_id(id), m_link(link), m_lane(lane) {};

void InputDRTStation::SetPosRange(std::string posRange)
{
    double start_pos;
    double end_pos;

    std::stringstream ss(posRange);
    char delim;

    ss >> start_pos >> delim >> end_pos;

    if (delim == '-')
        m_posRange = std::make_pair(start_pos, end_pos);
}
} // namespace NextSimIO