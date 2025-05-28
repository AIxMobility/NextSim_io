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
 * @class Trip
 * @brief Class for each trip information
 */
class Trip {
public:
    /**
     * @brief Constructor
     * @param tripId Trip ID
     * @param stops List of stop IDs included in the trip
     * @param arrivalTimes List of arrival times at each stop
     * @param departureTimes List of departure times from each stop
     */
    Trip(int tripId, const std::vector<int> &stops, const std::vector<int> &arrivalTimes, const std::vector<int> &departureTimes);

    /**
     * @brief Get trip ID
     * @return Trip ID.
     */
    int GetTripId() const;

    /**
     * @brief Get list of stops in the trip
     * @return Constant reference to the list of stop IDs
     */
    const std::vector<int>& GetStops() const;

    /**
     * @brief Get list of arrival times at each stop.
     * @return Constant reference to the list of arrival times
     */
    const std::vector<int>& GetArrivalTimes() const;

    /**
     * @brief Get list of departure times from each stop.
     * @return Cconstant reference to the list of departure times
     */
    const std::vector<int>& GetDepartureTimes() const;

private:
    /**
     * @details Trip ID
     */
    int m_tripId;
    /**
     * @details List of stops in the trip
     */
    std::vector<int> m_stops;
    /**
     * @details List of arrival times at each stop
     */
    std::vector<int> m_arrivalTimes;
    /**
     * @details List of departure times from each stop
     */
    std::vector<int> m_departureTimes;
};

/**
 * @brief Structure to hold connection information between graph vertices.
 */
struct ConnectionInfo {
    InputPTGraphVertex* toVertex;
    std::string type; // "trip", "transfer", "footpath"
    int arrivalTime = -1;   // trip
    int departureTime = -1; // trip
    int tripId = -1;        // trip, transfer
    int duration = -1;      // trip?, transfer, footpath

    /**
     * @details Constructor for ConnectionInfo.
     * @param toVertex The destination vertex of the connection.
     * @param type The type of the connection ("trip", "transfer", "footpath").
     */
    ConnectionInfo(InputPTGraphVertex* toVertex, std::string type): toVertex(toVertex), type(type) {};
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
     * @param trip The trip associated with this vertex.
     */
    InputPTGraphVertex(const Stop& stop, std::shared_ptr<Trip> trip = nullptr);

    /**
     * @details Get the stop associated with this vertex.
     * @return A constant reference to the Stop object.
     */
    const Stop& GetStop() const;

    /**
     * @details Get the trip associated with this vertex.
     * @return A shared pointer to the Trip object.
     */
    std::shared_ptr<Trip> GetTrip() const;

    /**
     * @details Add a connection from this vertex to another.
     * @param connectionInfo The information about the connection to add.
     */
    void AddConnection(ConnectionInfo connectionInfo);

    /**
     * @details Get the list of connections originating from this vertex.
     * @return A constant reference to the vector of ConnectionInfo objects.
     */
    const std::vector<ConnectionInfo>& GetConnections() const;

private:
    /**
     * @brief The stop associated with this vertex.
     */
    const Stop& m_stop;

    /**
     * @brief The trip associated with this vertex.
     */
    std::shared_ptr<Trip> m_trip;

    /**
     * @brief List of connections originating from this vertex.
     */
    std::vector<ConnectionInfo> m_connections;
}; 

} // namespace NextSimIO

#endif