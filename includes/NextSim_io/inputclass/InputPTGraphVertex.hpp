/**
 * NextSim Captain
 * @file InputPTGraphVertex.hpp
 * @version 1.0
 * @author Yeonwoo Yu
 */

 #pragma once
 #ifndef INPUTPTGRAPHVERTEX_H
 #define INPUTPTGRAPHVERTEX_H
 
 #include <vector>
 #include <string>
 #include <utility>
 #include <memory>

namespace NextSimIO
{
class InputPTGraphVertex;

/**
 * @enum StopType
 * @brief Enum to classify stop types (e.g., road or rail)
 */
enum class StopType {
    Road,
    Rail
};

/**
 * @class Stop
 * @brief Class for each stop information
 */
class Stop {
public:
    /**
     * @brief Constructor
     * @param stopId Unique ID of the stop
     * @param type Type of the stop
     */
    Stop(int stopId, StopType type);
    Stop(const Stop&) = default;
    Stop& operator=(const Stop&) = default;
    /**
     * @brief Get stop ID
     * @return Stop ID
     */
    int GetStopId() const;

    /**
     * @brief Get the type of the stop
     * @return Stop type (Road or Rail)
     */
    StopType GetStopType() const;

private:
    /**
     * @details Stop ID
     */
    int m_stopId;
    
    /**
     * @details Stop type
     */
    StopType m_stopType;
};
    
/**
 * @class Line
 * @brief Class for each line information
 */
class Line {
public:
    /**
     * @brief Constructor
     * @param lineId Line ID
     * @param stops List of stop IDs included in the line
     * @param arrivalTimes List of arrival times at each stop
     * @param departureTimes List of departure times from each stop
     */
    Line(std::string lineId, const std::vector<int> &stops, const std::vector<double> &arrivalTimes, const std::vector<double> &departureTimes);

    /**
     * @brief Get line ID
     * @return Line ID.
     */
    std::string GetLineId() const;

    /**
     * @brief Get list of stops in the line
     * @return Constant reference to the list of stop IDs
     */
    const std::vector<int>& GetStops() const;

    /**
     * @brief Get list of arrival times at each stop.
     * @return Constant reference to the list of arrival times
     */
    const std::vector<double>& GetArrivalTimes() const;

    /**
     * @brief Get list of departure times from each stop.
     * @return Cconstant reference to the list of departure times
     */
    const std::vector<double>& GetDepartureTimes() const;

private:
    /**
     * @details line ID
     */
    std::string m_lineId;
    /**
     * @details List of stops in the line
     */
    std::vector<int> m_stops;
    /**
     * @details List of arrival times at each stop
     */
    std::vector<double> m_arrivalTimes;
    /**
     * @details List of departure times from each stop
     */
    std::vector<double> m_departureTimes;
};

/**
 * @class InputPTGraphVertex
 * @brief Represents a vertex in the public transport graph.
 */
class InputPTGraphVertex
{
public:
    /**
     * @details Constructor for InputPTGraphVertex.
     * @param stop The stop associated with this vertex.
     * @param line The line associated with this vertex.
     */
    InputPTGraphVertex(const Stop& stop, std::shared_ptr<Line> line = nullptr);

    /**
     * @details Get the stop associated with this vertex.
     * @return A constant reference to the Stop object.
     */
    const Stop& GetStop() const;

    /**
     * @details Get the line associated with this vertex.
     * @return A shared pointer to the Line object.
     */
    std::shared_ptr<Line> GetLine() const;

private:
    /**
     * @brief The stop associated with this vertex.
     */
    Stop m_stop;

    /**
     * @brief The line associated with this vertex.
     */
    std::shared_ptr<Line> m_line;
    
}; 
} // namespace NextSimIO
#endif