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
    
   /**
     * @brief Push exit to the station
     * @param exit Exit of the station
     */
   void PushExit(Exit exit) { m_exit.push_back(exit); }
    
   /**
     * @brief Push timetable to the station
     * @param timetable Timetable of the station
     */
   void Pushtimetable(Timetable&& timetable) { m_timetable.push_back(std::move(timetable)); }

    /**
     * @details Get station ID
     * @return Station ID
    */
   int GetId() const { return m_id; }

    /**
     * @details Get transit mode of the station
     * @return Transit mode of the station (e.g., subway)
    */
   std::string GetTransitMode() const { return m_transitMode; }

    /**
     * @details Get address (name) of the station
     * @return Address (name) of the station
    */
   std::string GetAddress() const { return m_address; }
    
   /**
     * @details Get the coodinate center of the station
     * @return Coordinate center of the station
    */
   std::pair<double, double> GetCenter() const { return m_center; }
    
   /**
     * @details Get the type of the station, always StopType::Rail for this class
     * @return Type of the station (Rail)
    */
   StopType GetStopType() const { return m_type; }
    
   /**
     * @details Get the vector of exits
     * @return Vector of exits
    */
   std::vector<Exit> GetExits() const { return m_exit; }
    
   /**
     * @details Get the vector of timetables
     * @return Vector of timetables
    */
   std::vector<Timetable> GetTimetables() const { return m_timetable; }

private:
    /**
     * @details Station ID
    */
   int m_id;

   /**
    * @details Mode of the transit (subway)
   */
   std::string m_transitMode;

   /**
    * @details Name of the station
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
    * @details Vector of exits
   */
   std::vector<Exit> m_exit;

   /**
    * @details Vector of timetables
   */
   std::vector<Timetable> m_timetable;

};
}

#endif