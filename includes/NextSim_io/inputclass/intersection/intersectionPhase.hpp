/**
 * NextSim Captain
 * @file : intersectinoPhase.hpp
 * @version : 1.0
 * @author : ???
 */

#pragma once
#ifndef INTERSECTIONPHASE_H
#define INTERSECTIONPHASE_H

#include <vector>
#include <string>

namespace NextSimIO
{
/**
 * @class intersectionPhase
 * @brief Class for intersection phase information
 */
class intersectionPhase
{
public:
    /**
     * @details Constructor
     * @param id Intersection phase ID
     */
    intersectionPhase(int id);
    /**
     * @details Push connection to the vector
     * @param conn Connection
     */
    void PushConnection(int conn);
    
    /**
     * @details Push priority to the vector
     * @param priority Priority
     */
    void PushPriority(double priority);

    /**
     * @details Get intersection phase ID
     * @return Intersection phase ID
     */
    int GetId() { return m_id; }

    /**
     * @details Get vector of connection
     * @return Vector of connection
     */
    std::vector<int> GetConnectionVector() { return m_connectionVector; }

    /**
     * @details Get vector of priority
     * @return Vector of priority
     */
    std::vector<double> GetPriorityVector() { return m_priorityVector; }

private:

    /**
     * @details Intersection phase ID
    */
    int m_id;

    /**
     * @details Vector of connection that the phase includes
    */
    std::vector<int> m_connectionVector; 

    /**
     * @details Priority of the connections in the phase
    */
    std::vector<double> m_priorityVector;
};
} // namespace NextSimIO

#endif