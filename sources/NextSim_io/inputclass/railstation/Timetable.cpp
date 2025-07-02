/**
 * NextSim Captain
 * @file : Timetable.cpp
 * @version : 1.1
 * @author : Yuseock Hwang, Yeonwoo Yu
 */

 #include <sstream>

 #include <NextSim_io/inputclass/Railstation/Timetable.hpp>
 
 namespace NextSimIO
 {
    Timetable::Timetable(std::string dayOfWeek, std::string routeId, std::string type, std::vector<std::string> time) 
    :  m_dayOfweek(dayOfWeek), m_routeId(routeId), m_type(type), m_time(std::move(time)) {};
 } // namespace NextSimIO