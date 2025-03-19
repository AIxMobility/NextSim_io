/**
 * NextSim Captain
 * @file InputGraphVertex.hpp
 * @version 1.0
 * @author Dongheon Lee
 */

#pragma once
#ifndef INPUTGRAPHVERTEX_H
#define INPUTGRAPHVERTEX_H

#include <vector>
#include <string>
#include "intersection/port.hpp"

namespace NextSimIO
{
/**
 * @class VertexCord
 * @brief Class for each vertex coordinate information
 */
class VertexCoord
{
public:
    /**
     * @details Constructor
     * @param x X coordinate of the vertex
     * @param y Y coordinate of the vertex
     */
    VertexCoord(float x, float y);

    /**
     * @details Set X coordinate of the vertex
     * @param x X coordinate of the vertex
     */
    void SetX(float x) { m_x = x; }

    /**
     * @details Set Y coordinate of the vertex
     * @param y Y coordinate of the vertex
     */
    void SetY(float y) { m_y = y; }

    /**
     * @details Get X coordinate of the vertex
     * @return X coordinate of the vertex
     */
    float GetX() { return m_x; }

    /**
     * @details Get Y coordinate of the vertex
     * @return Y coordinate of the vertex
     */
    float GetY() { return m_y; }

private:
    /**
     * @details X coordinate of the vertex
     */
    float m_x;

    /**
     * @details Y coordinate of the vertex
     */
    float m_y;
}; // class VertexCoord

/**
 * @class ConnectionInfo
 * @brief Class for link connection information
 */
class ConnectionInfo
{
public:
    /**
     * @details Constructor
     * @param fromLink Link ID that the connection is from
     * @param toLink Link ID that the connection is to
     * @param length Length of the subArc
     */
    ConnectionInfo(int fromLink, int toLink, double length);

    /**
     * @details Get link ID that the connection is from
     * @return Link ID
     */
    int GetFromLink() { return m_fromLink; }

    /**
     * @details Get link ID that the connection is to
     * @return Link ID
     */
    int GetToLink() { return m_toLink; }

    /**
     * @details Get length of the subArc
     * @return Length of the subArc
     */
    double GetLength() { return m_length; }

private:
    /**
     * @details Link ID that the connection is from
     */
    int m_fromLink;

    /**
     * @details Link ID that the connection is to
     */
    int m_toLink;

    /**
     * @details length of the subArc [m]
     */
    double m_length;
}; // class ConnectionInfo

/**
 * @class InputGraphVertex
 * @brief Class for each graph vertex information
 */
class InputGraphVertex
{
public:
    /**
     * @details Constructor
     * @param id Vertex ID
     * @param type Node type
     * @param heuristic Heuristic value of the vertex
     * @param rank Rank of the vertex
     */
    InputGraphVertex(int id, int type, float heuristic, int rank);

    /**
     * @details Set physical coordinates of the vertex
     * @param coordinates Physical coordinates of the vertex
     */
    void SetCoordinates(std::vector<VertexCoord> coordinates) { m_coordinates = coordinates; }

    /**
     * @details Set Heuristic value of the vertex
     * @param heuristic Heuristic value of the vertex
     */
    void SetHeuristic(float heuristic) { m_heuristic = heuristic; }

    /**
     * @details Set Rank of the vertex
     * @param rank Rank of the vertex
     */
    void SetRank(int rank) { m_rank = rank; }

    /**
     * @details Add connected link into vector
     * @param link Connected link
     */
    void pushLink(port link);

    /**
     * @details Add connection information into vector
     * @param connectionInfo Connection information
     */
    void pushConnectionInfo(ConnectionInfo connectionInfo) { m_connectionInfo.push_back(connectionInfo); }

    /**
     * @details Get vertex ID
     * @return vertex ID
     */
    int GetId() { return m_id; }

    /**
     * @details Get node type
     * @return Node type 
     */
    int GetType() { return m_type; }

    /**
     * @details Get physical coordinates of the vertex
     * @return Physical coordinates of the vertex
     */
    std::vector<VertexCoord> GetCoordinates() { return m_coordinates; }
    
    /**
     * @details Get Heuristic value of the vertex
     * @return Heuristic value of the vertex
     */
    float GetHeuristic() { return m_heuristic; }

    /**
     * @details Get Rank of the vertex
     * @return Rank of the vertex
     */
    int GetRank() { return m_rank; }

    /**
     * @details Get connected links
     * @return Vector of connected links
     */
    std::vector<port> GetLinks() { return m_connectedLinks; }

    /**
     * @details Get connection information
     * @return Vector of connection information
     */
    std::vector<ConnectionInfo> GetConnectionInfo() { return m_connectionInfo; }

    /**
     * @details Free connected links vector
     */
    void FreeLinks() { std::vector<port>().swap(m_connectedLinks); }

    /**
     * @details calculate heuristic value
     * @param departVertex Departure vertex
     * @param destVertex Destination vertex
     * @return Heuristic value
     */
    float CalHeuristic (InputGraphVertex departVertex, InputGraphVertex destVertex);

private:
    /**
     * @details Vertex ID
     */
    int m_id; 

    /**
     * @details Node type (0: Intersection, 1: Normal, 2: Diverging, 3: Terminal, 4: Garage)
     */
    int m_type;

    /**
     * @details Physical coordinates of the vertex
     */
    std::vector<VertexCoord> m_coordinates;

    /**
     * @details Heuristic value of the vertex (used for A* algorithm)
     */
    double m_heuristic;

    /**
     * @details Rank of the vertex (used for CH or CCH algorithm)
     */
    int m_rank;

    /**
     * @details Vector of connected links
    */
    std::vector<port> m_connectedLinks;

    /**
     * @details Vector of connection information
     */
    std::vector<ConnectionInfo> m_connectionInfo;

};
} // namespace NextSimIO

#endif