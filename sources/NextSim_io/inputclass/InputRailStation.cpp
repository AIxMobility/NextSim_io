/**
 * NextSim Captain
 * @file : InputrailStation.cpp
 * @version : 1.0
 * @author : Yuseock Hwang
 */

 #include <NextSim_io/inputclass/InputRailStation.hpp>

 namespace NextSimIO
{
InputRailStation::InputRailStation(int id, std::string name, std::string transitMode, 
    std::vector<std::string> lineList) : 
    m_id(id), m_name(name), m_transitMode(transitMode), m_lineList(std::move(lineList)) {};
}