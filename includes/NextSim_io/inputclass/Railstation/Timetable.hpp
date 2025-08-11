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
      * @param type
      * @param time
      */
    Timetable(std::string dayOfWeek, int routeId, std::string type, std::vector<std::string> time);
 
     /**
      * @details 
      * @return 
      */
    std::string GetDayOfWeek() const { return m_dayOfweek; }

     /**
      * @details 
      * @return 
      */
    int GetRouteId() const { return m_routeId; }

     /**
      * @details 
      * @return 
      */
    std::string GetType() const { return m_type; }

      /**
      * @details 
      * @return 
      */
    std::vector<std::string> GetTime() const { return m_time; }

 private:
     /**
      * @details Exit ID
     */
    std::string m_dayOfweek;

     /**
      * @details 
     */
    int m_routeId;

     /**
      * @details 
     */
    std::string m_type;

     /**
      * @details 
     */
    std::vector<std::string> m_time;

 };
 } // namespace NextSimIO
 
 #endif