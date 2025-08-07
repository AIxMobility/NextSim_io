/**
 * NextSim Captain
 * @file : InputrailStation.cpp
 * @version : 1.0
 * @author : Yuseock Hwang
 */

 #include <NextSim_io/inputclass/InputRailStation.hpp>

 namespace NextSimIO
{
InputRailStation::InputRailStation(int id, const std::string transitMode, const std::string address) : 
    m_id(id), m_transitMode(transitMode), m_address(address) {};
}