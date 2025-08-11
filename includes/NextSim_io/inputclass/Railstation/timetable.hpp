/**
 * NextSim Captain
 * @file : timetable.hpp
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
 * @class timetable
 * @brief Class for timetable information
 */
class timetable
{
public:
    /**
     * @details Constructor
     * @param dayOfWeek Day of the week for the timetable
     * @param routeId Route ID for the timetable
     * @param type Type of the timetable
     * @param time Time schedule for the timetable
     */
    timetable(std::string dayOfWeek, int routeId, std::string type, std::vector<std::string> time);

    /**
     * @details Gets the day of the week for the timetable.
     * @return The day of the week as a string.
     */
    std::string GetDayOfWeek() const { return m_dayOfweek; }

    /**
     * @details Gets the route ID for the timetable.
     * @return The route ID as an integer.
     */
    int GetRouteId() const { return m_routeId; }

    /**
     * @details Gets the type of the timetable.
     * @return The type of the timetable as a string.
     */
    std::string GetDirection() const { return m_direction; }

    /**
     * @details Gets the time schedule for the timetable.
     * @return The time schedule for the timetable as a vector of strings.
     */
    std::vector<std::string> GetTime() const { return m_time; }

    /**
     * @return The type of the timetable as a string.
     */
    std::string GetType() const { return m_direction; }

private:
    /**
     * @details 
     */
    std::string m_dayOfweek;

    /**
     * @details 
     */
    int m_routeId;

    /**
     * @details 
     */
    std::string m_direction;

    /**
     * @details 
     */
    std::vector<std::string> m_time;
};
} // namespace NextSimIO

#endif