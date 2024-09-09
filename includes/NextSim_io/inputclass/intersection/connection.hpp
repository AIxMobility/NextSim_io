/**
 * NextSim Captain
 * @file : connection.hpp
 * @version : 1.0
 * @author : ???
 */

#pragma once

#include <string>
#include <vector>

namespace NextSimIO
{
/**
 * @class connection
 * @brief Class for node connection information
 */
class connection
{
 private:
    
    /**
     * @details Connection ID
    */
    int connectionId;

    /**
     * @details Link ID that the connection is from
    */
    int from_link;

    /**
     * @details Lane ID that the connection is from
    */
    int from_lane;

    /**
     * @details Link ID that the connection is to
    */
    int to_link;

    /**
     * @details Lane ID that the connection is to
    */
    int to_lane;

    /**
     * @details Turning information (L(left turn), R(right turn), S(straight))
    */
    std::string turning;

    /**
     * @details Priority of the connection (0.1: R, 0.5: L, 1: S)
    */
    double priority;

    /**
     * @details Length [m]
    */
    double length;

    /**
     * @details Width [m]
    */
    double width;

    /**
     * @details Free flow speed [km/h]
    */
    double ffspeed;

 public:
    /** 
     * @details Constructor
     * @param id Connection ID
     * @param fromLink Link ID that the connection is from
     * @param fromLane Lane ID that the connection is from
     * @param toLink Link ID that the connection is to
     * @param toLane Lane ID that the connection is to
     * @param turning Turning information 
     * @param priority Priority of the connection
     * @param length Length
     * @param width Width
     * @param ffspeed Free flow speed
     */
    connection(int id, int fromLink, int fromLane, int toLink, int toLane,
               std::string turning, double priority, 
               double length, double width, double ffspeed);

    /**
     * @details Get connection ID
     * @return Connection ID
     */
    int getConnId() { return connectionId; }
    /**
     * @details Get link ID that the connection is from
     * @return Link ID
     */
    int getFromLink() { return from_link; }
    
    /**
     * @details Get lane ID that the connection is from
     * @return Lane ID
     */
    int getFromLane() { return from_lane; }
    
    /**
     * @details Get link ID that the connection is to
     * @return Link ID
     */
    int getToLink() { return to_link; }
    
    /**
     * @details Get lane ID that the connection is to
     * @return Lane ID
     */
    int getToLane() { return to_lane; }

    /**
     * @details Get turning information
     * @return Turning information (L(left turn), R(right turn), S(straight))
     */
    double getPriority() { return priority; }

    /**
     * @details Get priority of the connection
     * @return Priority (0.1: R, 0.5: L, 1: S)
     */
    double getLength() { return length; }

    /** @cond EXCLUDE */
    bool operator< (const connection& other) const
    {
        return to_lane < other.to_lane;
    }
    /** @endcond */
};
}  // namespace NextSimIO