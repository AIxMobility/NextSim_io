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
     * @param address Station name
    */
    InputRailStation(int id, std::string transitMode, std::string address);

    void PushExit(Exit exit) { m_exit.push_back(exit); }
    
    void Pushtimetable(timetable timetable) { m_timetable.push_back(timetable); }

    int GetId() { return m_id; }

    std::string GetTransitMode() { return m_transitMode; }

    std::string GetAddress() { return m_address; }

    std::vector<Exit> GetExits() const { return m_exit; }

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
     * @details  Station address
     */
    std::string m_address;

    /**
     * @details Exits of railstation.
     */
    std::vector<Exit> m_exit;

    /**
     * @details Timetable of railstation.
    */
    std::vector<timetable> m_timetable;

};
}

#endif