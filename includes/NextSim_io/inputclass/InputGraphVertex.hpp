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
 * @class InputGraphVertex
 * @brief Class for each graph vertex information
 */
class InputGraphVertex
{
public:
    /**
     * @details Constructor
     * @param id Vertex ID
     * @param heuristic Heuristic value of the vertex
     * @param rank Rank of the vertex
     */
    InputGraphVertex(int id, float heuristic, int rank);

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
     * @details Get vertex ID
     * @return vertex ID
     */
    int GetId() { return m_id; }

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
     * @details Free connected links vector
     */
    void FreeLinks() { std::vector<port>().swap(m_connectedLinks); }

private:
    /**
     * @details Vertex ID
     */
    int m_id; 

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

};
} // namespace NextSimIO

#endif