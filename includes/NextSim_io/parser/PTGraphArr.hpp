/**
 * NextSim Captain
 * @file PTGraphArr.hpp
 * @version 1.0
 * @author Yeonwoo Yu
 */

#ifndef PTGRAPHARR_H
#define PTGRAPHARR_H

#include <vector>
#include <unordered_map>
#include <fstream>
#include <NextSim_io/inputclass/InputPTGraphVertex.hpp>
#include <NextSim_io/inputclass/InputPTGraphArc.hpp>
#include <NextSim_io/inputclass/InputStation.hpp>
#include <NextSim_io/parser/StationArr.hpp>
#include <NextSim_io/inputclass/InputRailStation.hpp>
#include <NextSim_io/parser/RailStationArr.hpp>
#include <NextSim_io/inputclass/InputPTline.hpp>
#include <NextSim_io/parser/PTlineArr.hpp>
#include <NextSim_io/inputclass/InputRailLine.hpp>
#include <NextSim_io/parser/RailLineArr.hpp>
#include <NextSim_io/inputclass/Railstation/Timetable.hpp>
#include <NextSim_io/inputclass/ptpath/footpath.hpp>

namespace NextSimIO
{
/**
 * @class PTVertexArr
 * @brief Class for public transit graph vertex array management
 */
class PTVertexArr
{
public:
    /**
     * @brief Default constructor
     */
    PTVertexArr();

    /**
     * @brief Constructor with station arrays
     * @param roadStations Road station array
     * @param railStations Rail station array  
     */
    PTVertexArr(const StationArr& roadStations, const RailStationArr& railStations,
                const PTlineArr& roadPTLines, const RailLineArr& railPTLines);

    /**
     * @brief Get vector of all PT vertices
     * @return Constant reference to the vector of PT vertices
     */
    const std::vector<InputPTGraphVertex>& GetPTVertices() const { return m_ptVertices; }

    /**
     * @brief Add a PT vertex to the array
     * @param vertex The vertex to add
     */
    void AddPTVertex(const InputPTGraphVertex& vertex);

    /**
     * @brief Get the number of vertices
     * @return Number of vertices in the array
     */
    size_t GetVertexCount() const { return m_ptVertices.size(); }

    /**
     * @brief Clear all vertices
     */
    void Clear();

private:
    /**
     * @brief Vector of PT vertices
     */
    std::vector<InputPTGraphVertex> m_ptVertices;

}; // class PTVertexArr

/**
 * @class PTArcArr
 * @brief Class for public transit graph arc array management
 */
class PTArcArr
{
public:
    /**
     * @brief Default constructor
     */
    PTArcArr();
    ~PTArcArr();

    /**
     * @brief Constructor with station arrays
     * @param roadStations Road station array
     * @param railStations Rail station array
     * @param roadPTLines Road public transport line data
     * @param railPTLines Rail public transport line data
     */
    PTArcArr(const StationArr& roadStations, const RailStationArr& railStations,
                const PTlineArr& roadPTLines, const RailLineArr& railPTLines);

    /**
     * @brief Get vector of all PT arcs
     * @return Constant reference to the vector of PT arcs
     */
    const std::vector<InputPTGraphArc>& GetPTArcs() const { return m_ptArcs; }

    /**
     * @brief Add a PT arc to the array
     * @param arc The arc to add
     */
    void AddPTArc(const InputPTGraphArc& arc);

    /**
     * @brief Get the number of arcs
     * @return Number of arcs in the array
     */
    size_t GetArcCount() const { return m_ptArcs.size(); }

    /**
     * @brief Clear all arcs
     */
    void Clear();

private:
    /**
     * @brief Vector of PT arcs
     */
    std::vector<InputPTGraphArc> m_ptArcs;

    std::ofstream m_arcLogFile; 

}; // class PTArcArr

/**
 * @class PTGraph
 * @brief Class for managing public transit graph with vertices and arcs
 */
class PTGraph
{
public:
    /**
     * @brief Constructor
     * @param arcArr Arc array
     * @param vertexArr Vertex array
     */
    PTGraph(const PTVertexArr& vertexArr, const PTArcArr& arcArr);

    /**
     * @brief Get vertex to arc mapping
     * @return Constant reference to vertex to arc map
     */
    const std::unordered_map<int, std::vector<int>>& GetVertexToArc() const { return m_vertexToArc; }
    
    /**
     * @brief Get arc to arc mapping
     * @return Constant reference to arc to arc map
     */
    const std::unordered_map<int, std::vector<int>>& GetArcToArc() const { return m_arcToArc; }

    /**
     * @brief Get PT vertices
     * @return Constant reference to vertex array
     */
    const PTVertexArr& GetVertices() const { return m_vertexArr; }

    /**
     * @brief Get PT arcs
     * @return Constant reference to arc array
     */
    const PTArcArr& GetArcs() const { return m_arcArr; }

private:
    /**
     * @brief Vertex to arc mapping - maps vertex ID to connected arc IDs
     */
    std::unordered_map<int, std::vector<int>> m_vertexToArc;

    /**
     * @brief Arc to arc mapping - maps arc ID to connected arc IDs
     */
    std::unordered_map<int, std::vector<int>> m_arcToArc;

    /**
     * @brief Reference to vertex array
     */
    const PTVertexArr& m_vertexArr;

    /**
     * @brief Reference to arc array
     */
    const PTArcArr& m_arcArr;

}; // class PTGraph

int convertToMinutes(const std::string& time);

void pairStations(const StationArr& roadStations, const RailStationArr& railStations, 
                    std::vector<std::tuple<int,int>>& pairs);

} // namespace NextSimIO

#endif