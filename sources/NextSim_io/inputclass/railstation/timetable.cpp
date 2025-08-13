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
    timetable::timetable(std::string dayOfWeek, std::string lineId, std::vector<std::string> time) 
    :  m_dayOfweek(dayOfWeek), m_lineId(lineId), m_time(time) {};
 } // namespace NextSimIO