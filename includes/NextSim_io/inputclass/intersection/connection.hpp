/**
 * NextSim Captain
 * @file : connection.hpp
 * @version : 1.0
 * @author : ???
 */

#pragma once
#ifndef CONNECTION_H
#define CONNECTION_H

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
     * @param ffSpeed Free flow speed
     * @param shapePoints Ordered connection shape points
     */
    connection(int id, int fromLink, int fromLane, int toLink, int toLane,
               std::string turning, double priority, 
               double length, double width, double ffSpeed,
               std::vector<std::pair<double, double>> shapePoints = {});

    /**
     * @details Get connection ID
     * @return Connection ID
     */
    int GetConnId() { return m_connectionId; }
    /**
     * @details Get link ID that the connection is from
     * @return Link ID
     */
    int GetFromLink() { return m_fromLink; }
    
    /**
     * @details Get lane ID that the connection is from
     * @return Lane ID
     */
    int GetFromLane() { return m_fromLane; }
    
    /**
     * @details Get link ID that the connection is to
     * @return Link ID
     */
    int GetToLink() { return m_toLink; }
    
    /**
     * @details Get lane ID that the connection is to
     * @return Lane ID
     */
    int GetToLane() { return m_toLane; }

    /**
     * @details Get turning information
     * @return Turning information (L(left turn), R(right turn), S(straight))
     */
    std::string GetTurning() { return m_turning; }

    /**
     * @details Get priority of the connection
     * @return Priority (0.1: R, 0.5: L, 1: S)
     */
    double GetPriority() { return m_priority; }

    /**
     * @details Get length of the connection
     * @return Length [m]
     */
    double GetLength() { return m_length; }

    /**
     * @details Get width of the connection
     * @return Width [m]
     */
    double GetWidth() { return m_width; }

    /**
     * @details Get free flow speed of the connection
     * @return Free flow speed [km/h]
     */
    double GetFreeFlowSpeed() { return m_ffSpeed; }

    /**
     * @details Get connection shape points.
     * @return Ordered shape points of the connection centerline.
     */
    const std::vector<std::pair<double, double>>& GetShapePoints() const
    {
        return m_shapePoints;
    }

    /** @cond EXCLUDE */
    bool operator< (const connection& other) const
    {
        return m_toLane < other.m_toLane;
    }
    /** @endcond */

private:
    /**
     * @details Connection ID
    */
    int m_connectionId;

    /**
     * @details Link ID that the connection is from
    */
    int m_fromLink;

    /**
     * @details Lane ID that the connection is from
    */
    int m_fromLane;

    /**
     * @details Link ID that the connection is to
    */
    int m_toLink;

    /**
     * @details Lane ID that the connection is to
    */
    int m_toLane;

    /**
     * @details Turning information (L(left turn), R(right turn), S(straight))
    */
    std::string m_turning;

    /**
     * @details Priority of the connection (0.1: R, 0.5: L, 1: S)
    */
    double m_priority;

    /**
     * @details Length [m]
    */
    double m_length;

    /**
     * @details Width [m]
    */
    double m_width;

    /**
     * @details Free flow speed [km/h]
    */
    double m_ffSpeed;

    /**
     * @details Ordered connection shape points.
    */
    std::vector<std::pair<double, double>> m_shapePoints;
};
}  // namespace NextSimIO

#endif