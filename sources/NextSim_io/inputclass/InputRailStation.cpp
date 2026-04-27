/**
 * NextSim Captain
 * @file : InputrailStation.cpp
 * @version : 1.2
 * @author : Yuseock Hwang, Yeonwoo Yu, Sujae Jeon
 */

 #include <NextSim_io/inputclass/InputRailStation.hpp>

 namespace NextSimIO
{
InputRailStation::InputRailStation(int id, const std::string transitMode,
    std::vector<std::string> lineList, const std::string name, std::pair<double, double> center) :
    m_id(id), m_transitMode(transitMode), m_lineList(std::move(lineList)), m_name(name), m_center(center), m_type(StopType::Rail) {};
}