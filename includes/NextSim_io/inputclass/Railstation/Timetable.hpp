/**
 * NextSim Captain
 * @file : Timetable.hpp
 * @version : 1.1
 * @author : Yuseock Hwang, Yeonwoo Yu
 */

 #pragma once
 #ifndef Timetable_H
 #define Timetable_H
 
 #include <string>
 #include <vector>
 
 namespace NextSimIO
 {
 /**
  * @class Timetable
  * @brief Class for Timetable information
  */
 class Timetable
 {
 public:
     /**
      * @details Constructor
      * @param dayOfWeek 
      * @param routeId (string)
      * @param type
      * @param time
      */
    Timetable(std::string dayOfWeek, std::string routeId, std::string type, std::vector<std::string> time);
 
     /**
      * @details Whether the timetable is for a weekday or weekend
      * @return weekdays / weekends
      */
    std::string GetDayOfWeek() const { return m_dayOfweek; }

     /**
      * @details Get route ID of the line
      * @return Route ID of the line (string)
      */
    std::string GetrouteId() const { return m_routeId; }

     /**
      * @details Direction of the line
      * @return terminal / start
      */
    std::string GetType() const { return m_type; }

      /**
      * @details List of times for the timetable (HH:MM)
      * @return  List of times for the timetable (HH:MM)
      */
    const std::vector<std::string>& GetTime() const { return m_time; }

 private:
     /**
      * @details Whether the timetable is for a weekday or weekend
     */
    std::string m_dayOfweek;

     /**
      * @details Route ID of the line
     */
    std::string m_routeId;

     /**
      * @details Direction of the line
     */
    std::string m_type;

     /**
      * @details Timetable times 
     */
    std::vector<std::string> m_time;

 };
 } // namespace NextSimIO
 
 #endif