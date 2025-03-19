/**
 * NextSim Captain
 * @file GraphArr.hpp
 * @version 1.0
 * @author Dongheon Lee
 */

#ifndef GRAPHARR_H
#define GRAPHARR_H

#include <unordered_map>
#include <NextSim_io/inputclass/InputGraphVertex.hpp>
#include <NextSim_io/inputclass/InputGraphArc.hpp>

namespace NextSimIO
{
/**
 * @class VertexArr
 * @brief Class for whole graph vertex information from network.xml
 */
class VertexArr
{
public:
    /**
     * @details Constructor (Parse graph information from network.xml)
     */
    VertexArr();

    /**
     * @details Get vector of all vertices
     */
    std::vector<InputGraphVertex> GetVertices() { return m_vertices; }

private:
    /**
     * @details Vector of vertices
     */
    std::vector<InputGraphVertex> m_vertices;
}; // class VertexArr

/**
 * @class ArcArr
 * @brief Class for whole graph arc information from network.xml
 */
class ArcArr
{
public:
    /**
     * @details Constructor (Parse graph information from network.xml)
     */
    ArcArr();

    /**
     * @details Get vector of all arcs
     */
    std::vector<InputGraphArc> GetArcs() { return m_arcs; }

private:
    /**
     * @details Vector of arcs
     */
    std::vector<InputGraphArc> m_arcs;
    
}; // class ArcArr

/**
 * @class Graph
 * @brief Class for graph used in route generation
 */
class Graph
{
public:
    /**
     * @details Constructor
     * @param arcArr Arc vectors
     * @param vertexArr Vertex vectors
     */
    Graph(ArcArr arcArr, VertexArr vertexArr);

private:
    /**
     * @details . 
     */
    std::unordered_map<int, std::vector<int>> m_vertexToArc;

    /**
     * @details .
     */
    std::unordered_map<int, int> m_arcToVertex;

    /**
     * @details .
     */
    std::unordered_map<int, std::vector<int>> m_arcToArc;

}; // class Graph

} // namespace NextSimIO

#endif