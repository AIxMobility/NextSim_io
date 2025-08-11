/**
 * NextSim Captain
 * @file : timetable.cpp
 * @version : 1.0
 * @author : Yuseock Hwang
 */

 #include <sstream>

 #include <NextSim_io/inputclass/Railstation/timetable.hpp>
 
 namespace NextSimIO
 {
    timetable::timetable(std::string dayOfWeek, int routeId, std::string type, std::vector<std::string> time) 
    :  m_dayOfweek(dayOfWeek), m_routeId(routeId), m_direction(type), m_time(time) {};
 } // namespace NextSimIO