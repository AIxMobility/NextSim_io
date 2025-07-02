/**
 * NextSim Captain
 * @file : InputStation.cpp
 * @version : 1.1
 * @author : Sujae Jeon, Yeonwoo Yu
 */

#include <sstream>

#include <NextSim_io/inputclass/InputStation.hpp>

namespace NextSimIO
{
InputStation::InputStation(int id, int link, int lane, double pos, int parkingLots) : 
    m_id(id), m_link(link), m_lane(lane), m_pos(pos), m_parkingLots(parkingLots), m_center(0.0, 0.0), m_type(StopType::Road) {};

InputStation::InputStation(int id, int link, int lane, double pos, int parkingLots, std::pair<double, double> center)
    : m_id(id), m_link(link), m_lane(lane), m_pos(pos), m_parkingLots(parkingLots), m_center(center), m_type(StopType::Road) {};

    void InputStation::SetLineList(std::string lineList)
    {
        std::stringstream ss(lineList);
        std::string line_id;

        while (ss >> line_id)
            m_lineList.push_back(line_id);
    }

    void InputStation::SetParkingLots(int parkingLots)
    {
        m_parkingLots = parkingLots;
    }

    void InputStation::SetGarageList(std::string garageList)
    {
        m_garageList.clear();
        
        std::stringstream ss(garageList);
        std::string garage_id_str;
        
        while (ss >> garage_id_str) {
            try {
                int garage_id = std::stoi(garage_id_str);
                m_garageList.push_back(garage_id);
            } catch (const std::exception& e) {
                continue;
            }
        }
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