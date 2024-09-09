/**
 * NextSim Captain
 * @file : intersectinoPhase.hpp
 * @version : 1.0
 * @author : ???
 */

#pragma once
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
private:

    /**
     * @details Intersection phase ID
    */
    int id;

    /**
     * @details Vector of connection that the phase includes
    */
    std::vector<int> connectionRef; 

    /**
     * @details Priority of the connections in the phase
    */
    std::vector<double> priority;

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
    void pushConnectionRef(int conn);
    
    /**
     * @details Push priority to the vector
     * @param priority Priority
     */
    void pushPriority(double priority);

    /**
     * @details Get intersection phase ID
     * @return Intersection phase ID
     */
    int getId() { return id; }

    /**
     * @details Get vector of connection
     * @return Vector of connection
     */
    std::vector<int> getConnRef() { return connectionRef; }

    /**
     * @details Get vector of priority
     * @return Vector of priority
     */
    std::vector<double> getPriority() { return priority; }
};
} // namespace NextSimIO