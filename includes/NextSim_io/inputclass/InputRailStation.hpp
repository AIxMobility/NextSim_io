/**
 * NextSim Captain
 * @file : InputrailStation.hpp
 * @version : 1.1
 * @author : Yuseock Hwang, Yeonwoo Yu
 */

#pragma once
#ifndef INPUTRAILSTATION_H
#define INPUTRAILSTATION_H

#include <vector>
#include <string>
#include <NextSim_io/inputclass/Railstation/Exit.hpp>
#include <NextSim_io/inputclass/Railstation/Timetable.hpp>
#include <NextSim_io/inputclass/InputPTGraphVertex.hpp>

namespace NextSimIO
{
/**
 * @class InputrailStaion
 * @brief Class for rail station information
 */
class InputRailStation
{
public:
    /**
     * @details Constructor
     * @param id Station ID
     * @param transitMode Type of transit 
     * @param address Station name
     * @param center Coordinate center of the station (Local Coordinate System)
     * @param type type of stop (default is Rail)
    */
   InputRailStation(int id, std::string transitMode, std::string address, std::pair<double, double> center);

   void PushExit(Exit exit) { m_exit.push_back(exit); }
   void Pushtimetable(Timetable timetable) { m_timetable.push_back(timetable); }

   int GetId() const { return m_id; }

   std::string GetTransitMode() const { return m_transitMode; }

   std::string GetAddress() const { return m_address; }

   std::pair<double, double> GetCenter() const { return m_center; }

   StopType GetStopType() const { return m_type; }

   std::vector<Exit> GetExits() const { return m_exit; }

   std::vector<Timetable> GetTimetables() const { return m_timetable; }

private:
 /**
     * @details Station ID
    */
   int m_id;

   /**
    * @details 
   */
   std::string m_transitMode;

   /**
    * @details 
   */
   std::string m_address;

    /**
     * @details Coordinate of the center of the station
    */
    std::pair<double, double> m_center;

   /**
    * @details Type of the station (Rail)
   */
   StopType m_type;

   /**
    * @details  
   */
   std::vector<Exit> m_exit;

   /**
    * @details  
   */
   std::vector<Timetable> m_timetable;

};
}

#endif