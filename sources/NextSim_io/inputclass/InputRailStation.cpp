/**
 * NextSim Captain
 * @file : InputrailStation.cpp
 * @version : 1.1
 * @author : Yuseock Hwang, Yeonwoo Yu
 */

 #include <NextSim_io/inputclass/InputRailStation.hpp>

 namespace NextSimIO
{
InputRailStation::InputRailStation(int id, const std::string transitMode, const std::string address, std::pair<double, double> center) : 
    m_id(id), m_transitMode(transitMode), m_address(address), m_center(center), m_type(StopType::Rail) {};
}