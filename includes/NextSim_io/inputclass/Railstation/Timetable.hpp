/**
 * NextSim Captain
 * @file : Timetable.hpp
 * @version : 1.0
 * @author : YuseockHwang
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
      * @param routeId
      * @param time
      */
    Timetable(std::string dayOfWeek, std::string routeId, std::vector<std::string> time);
 
     /**
      * @details 
      * @return 
      */
    std::string GetDayOfWeek() { return m_dayOfweek; }

     /**
      * @details 
      * @return 
      */
    std::string GetrouteId() { return m_routeId; }

      /**
      * @details 
      * @return 
      */
    std::vector<std::string> GetTime() { return m_time; }

 private:
     /**
      * @details Exit ID
     */
    std::string m_dayOfweek;

     /**
      * @details 
     */
    std::string m_routeId;

     /**
      * @details 
     */
    std::vector<std::string> m_time;

 };
 } // namespace NextSimIO
 
 #endif