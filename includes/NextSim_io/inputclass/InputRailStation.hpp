/**
 * NextSim Captain
 * @file : InputrailStation.hpp
 * @version : 2.0
 * @author : Yuseock Hwang, Dongheon Lee
 */

#pragma once
#ifndef INPUTRAILSTATION_H
#define INPUTRAILSTATION_H

#include <vector>
#include <string>
#include <NextSim_io/inputclass/Railstation/exit.hpp>
#include <NextSim_io/inputclass/Railstation/timetable.hpp>

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
     * @param name Station name
     * @param transitMode Type of transit
     * @param lineList List of lines serving the station
    */
    InputRailStation(int id, std::string name, std::string transitMode, 
                    std::vector<std::string> lineList);
    
    /**
     * @details Adds an exit to the station
     */
    void PushExit(exit exit) { m_exit.push_back(exit); }
    
    /**
     * @details Gets the station ID
     */
    int GetId() { return m_id; }

    /**
     * @details Gets the transit mode
     */
    std::string GetTransitMode() { return m_transitMode; }

    /**
    * @details Gets the station name
    */
    std::string GetName() { return m_name; }

    /**
     * @details Gets the list of lines serving the station
     */
    std::vector<std::string> GetLineList() { return m_lineList; }

    /**
     * @details Gets the exits of the station
     */
    std::vector<exit> GetExits() const { return m_exit; }

private:
    /**
     * @details Station ID
     */
    int m_id;

    /**
     * @details  Station name
     */
    std::string m_name;

    /**
     * @details  Type of transit
     */
    std::string m_transitMode;

    /**
     * @details List of lines serving the station
     */
    std::vector<std::string> m_lineList;

    /**
     * @details Exits of railstation.
     */
    std::vector<exit> m_exit;

};
}

#endif