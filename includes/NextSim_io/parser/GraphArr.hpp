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

    /**
     * @details Get vector of sink terminals
     */
    std::vector<int> GetSinkTerminals() { return m_sinkTerminals; }

    /**
     * @details Get vector of source terminals
     */
    std::vector<int> GetSourceTerminals() { return m_sourceTerminals; }

private:
    /**
     * @details Vector of vertices
     */
    std::vector<InputGraphVertex> m_vertices;

    /**
     * @details Vector of sink terminal ids
     */
    std::vector<int> m_sinkTerminals;

    /**
     * @details Vector of source terminal ids
     */
    std::vector<int> m_sourceTerminals;

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

    /**
     * @details Get vertex to arc map
     * @return Vertex to arc map
     */
    std::unordered_map<int, std::vector<int>> GetVertexToArc() { return m_vertexToArc; }
    
    /**
     * @details Get arc to arc map
     * @return Arc to arc map
     */
    std::unordered_map<int, std::vector<int>> GetArcToArc() { return m_arcToArc; }


private:
    /**
     * @details . 
     */
    std::unordered_map<int, std::vector<int>> m_vertexToArc;

    /**
     * @details .
     */
    std::unordered_map<int, std::vector<int>> m_arcToArc;

}; // class Graph

} // namespace NextSimIO

#endif