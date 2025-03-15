/**
 * NextSim Captain
 * @file : Exit.cpp
 * @version : 1.0
 * @author : Yuseock Hwang
 */

 #include <sstream>

 #include <NextSim_io/inputclass/Railstation/Timetable.hpp>
 
 namespace NextSimIO
 {
    Timetable::Timetable(std::string dayOfWeek, std::string routeId, std::vector<std::string> time) 
    :  m_dayOfweek(dayOfWeek), m_routeId(routeId), m_time(time) {};
 } // namespace NextSimIO