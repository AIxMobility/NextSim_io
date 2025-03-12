/**
 * NextSim Captain
 * @file : table.hpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#pragma once
#ifndef TABLE_H
#define TABLE_H

namespace NextSimIO
{
/**
 * @class table
 * @brief Class for TOD plan table of each node
*/
class table
{
public:
    /**
     * @details Constructor
     * @param planId Plan ID
     * @param startTime Start time
     * @param endTime End time
    */
    table(int planId, int startTime, int endTime);

    /**
     * @details Get Plan ID
     * @return Plan ID
    */
    int GetPlanId() const { return m_planId; }

    /**
     * @details Get start time
     * @return Start time
    */
    int GetStartTime() const { return m_startTime; }

    /**
     * @details Get end time
     * @return End time
    */
    int GetEndTime() const { return m_endTime; }

private:
    /**
     * @details Plan ID
    */
    int m_planId;

    /**
     * @details Start time
    */
    int m_startTime;

    /**
     * @details End time
    */
    int m_endTime;
};
} // namespace NextSimIO

#endif