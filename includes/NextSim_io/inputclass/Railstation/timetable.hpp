/**
 * NextSim Captain
 * @file : timetable.hpp
 * @version : 1.2
 * @author : Yuseock Hwang, Yeonwoo Yu, Sujae Jeon
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
     * @param lineId line ID for the timetable
     * @param type Direction type of the timetable (e.g., terminal, start)
     * @param time Time schedule for the timetable
     */
    timetable(std::string dayOfWeek, std::string lineId, std::string type, std::vector<std::string> time);

    /**
     * @details Gets the day of the week for the timetable.
     * @return The day of the week as a string.
     */
    std::string GetDayOfWeek() const { return m_dayOfweek; }

    /**
     * @details Gets the line ID for the timetable.
     * @return The line ID as a string.
     */
    std::string GetLineId() const { return m_lineId; }

    /**
      * @details Get direction type of the line
      * @return Direction of the line. (e.g., terminal / start)
      */
    std::string GetType() const { return m_type; }

    /**
     * @details Gets the time schedule for the timetable. (HH:MM)
     * @return The time schedule for the timetable as a vector of strings. (HH:MM)
     */
    std::vector<std::string> GetTime() const { return m_time; }

private:
    /**
     * @details Day of the week for the timetable
     */
    std::string m_dayOfweek;

    /**
     * @details The unique ID of the transit line
     */
    std::string m_lineId;

    /**
      * @details Direction type of the line
     */
    std::string m_type;

    /**
     * @details The time schedule for the timetable
     */
    std::vector<std::string> m_time;
};
} // namespace NextSimIO

#endif