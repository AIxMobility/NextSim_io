/**
 * NextSim Captain
 * @file : InputrailStation.hpp
 * @version : 2.0
 * @author : Yuseock Hwang, Yeonwoo Yu, Sujae Jeon, Dongheon Lee
 */

#pragma once
#ifndef INPUTRAILSTATION_H
#define INPUTRAILSTATION_H

#include <vector>
#include <string>
#include <NextSim_io/inputclass/Railstation/exit.hpp>
#include <NextSim_io/inputclass/Railstation/timetable.hpp>
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
   * @param lineList List of lines serving the station
   * @param name Station name
   * @param center Coordinate center of the station (Local Coordinate System)
   * @param type type of stop (default is Rail)
  */
  InputRailStation(int id, std::string transitMode, std::vector<std::string> lineList, std::string name, std::pair<double, double> center);
  
  /**
   * @brief Add exit to the station
   */
  void PushExit(exit exit) { m_exit.push_back(exit); }

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
   * @details Gets the list of lines serving the station
   */
  std::vector<std::string> GetLineList() const { return m_lineList; }

  /**
   * @details Get address (name) of the station
   * @return Address (name) of the station
  */
  std::string GetName() const { return m_name; }

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
  std::vector<exit> GetExits() const { return m_exit; }

private:
  /**
   * @details Station ID
  */
  int m_id;
   
  /**
  * @details Name of the station
  */
  std::string m_name;

  /**
  * @details Mode of the transit (subway)
  */
  std::string m_transitMode;

  /**
   * @details List of lines serving the station
  */
  std::vector<std::string> m_lineList;

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
  std::vector<exit> m_exit;
};
}

#endif