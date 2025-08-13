/**
 * NextSim Captain
 * @file : InputrailStation.hpp
 * @version : 1.0
 * @author : Yuseock Hwang
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
     * @param transitMode Type of transit
     * @param lineList List of lines serving the station
     * @param address Station name
    */
    InputRailStation(int id, std::string transitMode, 
                     std::vector<std::string> lineList, std::string address);
    
    /**
     * @details Adds an exit to the station
     */
    void PushExit(exit exit) { m_exit.push_back(exit); }

    /**
     * @details Adds a timetable to the station
     */
    void Pushtimetable(timetable timetable) { m_timetable.push_back(timetable); }
    
    /**
     * @details Gets the station ID
     */
    int GetId() { return m_id; }

    /**
     * @details Gets the transit mode
     */
    std::string GetTransitMode() { return m_transitMode; }

    /**
     * @details Gets the list of lines serving the station
     */
    std::vector<std::string> GetLineList() { return m_lineList; }

    /**
     * @details Gets the station address
     */
    std::string GetAddress() { return m_address; }

    /**
     * @details Gets the exits of the station
     */
    std::vector<exit> GetExits() const { return m_exit; }

    /**
     * @details Gets the timetables of the station
     */
    std::vector<timetable> GetTimetables() const { return m_timetable; }

private:
    /**
     * @details Station ID
     */
    int m_id;

    /**
     * @details  Type of transit
     */
    std::string m_transitMode;

    /**
     * @details List of lines serving the station
     */
    std::vector<std::string> m_lineList;

    /**
     * @details  Station address
     */
    std::string m_address;

    /**
     * @details Exits of railstation.
     */
    std::vector<exit> m_exit;

    /**
     * @details Timetable of railstation.
    */
    std::vector<timetable> m_timetable;

};
}

#endif