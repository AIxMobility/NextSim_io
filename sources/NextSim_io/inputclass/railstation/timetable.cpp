/**
 * NextSim Captain
 * @file : timetable.cpp
 * @version : 1.2
 * @author : Yuseock Hwang, Yeonwoo Yu, Sujae Jeon
 */

 #include <sstream>

 #include <NextSim_io/inputclass/Railstation/timetable.hpp>
 
 namespace NextSimIO
 {
    timetable::timetable(std::string dayOfWeek, std::string lineId, std::string direction, std::vector<std::string> time) 
    :  m_dayOfweek(dayOfWeek), m_lineId(lineId), m_direction(direction), m_time(std::move(time)) {};
    
 } // namespace NextSimIO