/**
 * @file Footpath.hpp
 * @version 1.0
 * @author Yeonwoo Yu
 */

#ifndef Footpath_HPP
#define Footpath_HPP

#pragma once

#include <string>
#include <vector>
#include <map>
#include <queue>
#include <utility>
#include <limits>
#include <atomic>

#include <NextSim_io/inputclass/InputStation.hpp>

namespace Captain
{

/** 
 * @struct FootpathNode
 * @brief A node in the pedestrian footpath network.
 */
struct FootpathNode {
    std::string id;    /**< Unique node identifier */
    double x_coord;    /**< X coordinate */
    double y_coord;    /**< Y coordinate */
};

/** 
 * @struct FootpathEdge
 * @brief Directed edge connecting two nodes in the footpath network.
 */
struct FootpathEdge {
    std::string from_node_id; /**< Starting node ID */
    std::string to_node_id;   /**< Ending node ID */
    double length;            /**< Edge length */
    double travel_time;       /**< Estimated travel time */
};

/** 
 * @struct DijkstraState
 * @brief Helper struct for Dijkstra's algorithm.
 */
struct DijkstraState {
    std::string node_id;
    double distance;
    bool operator>(const DijkstraState& other) const {
        return distance > other.distance;
    }
};

/** 
 * @struct NearestLinkPoint
 * @brief Closest point on a footpath link to a given coordinate.
 */
struct NearestLinkPoint {
    std::string tempNodeId;
    double x_coord;
    double y_coord;
    std::string from_node_id;
    std::string to_node_id;
    double distance;
    bool found;
};

/**
 * @class Footpath
 * @brief Generates pedestrian footpath routes using Dijkstra's algorithm.
 */
class Footpath {
public:
    /** 
     * @brief Constructor 
    */
    Footpath();

    /** 
     * @brief Destructor 
    */
    ~Footpath() = default;

    /** 
     * @brief Load the pedestrian footpath network data
     */
    void LoadFootpathNetwork();

    /**
     * @brief Find the nearest point on a footpath link to given coordinates.
     * @param x X-coordinate
     * @param y Y-coordinate
     * @return NearestLinkPoint structure with details
     */
    NearestLinkPoint FindNearestFootpathLinkPoint(double x, double y) const;

    /** 
     * @brief Add a pedestrian node to the network. 
     */
    void AddFootpathNode(const FootpathNode& node);

    /** 
     * @brief Add a pedestrian edge to the network. 
     */
    void AddFootpathEdge(const FootpathEdge& edge);

    /**
     * @brief Get a footpath node by ID.
     * @param nodeId Node identifier
     * @return Reference to the FootpathNode
     */
    const FootpathNode& GetFootpathNode(const std::string& nodeId) const;

    /** 
     * @brief Remove temporary nodes and edges added during routing
     */
    void RemoveTempNodesAndEdges();

    /**
     * @brief Calculate Euclidean distance between two nodes.
     * @param n1 First node
     * @param n2 Second node
     * @return Distance value
     */
    double calculateDistance(const FootpathNode& n1, const FootpathNode& n2) const;

    /**
     * @brief Compute shortest path distance using Dijkstra's algorithm.
     * @param start_node_id Start node ID
     * @param end_node_id End node ID
     * @return Shortest travel time or -1 if no path
     */
    double Dijkstra(const std::string& start_node_id, const std::string& end_node_id);

    /**
     * @brief Calculate Euclidean distance between two points.
     * @param p1 First point (x,y)
     * @param p2 Second point (x,y)
     * @return Distance value
     */
    double GetDistance(const std::pair<double, double>& p1, const std::pair<double, double>& p2);

    // /**
    //  * @brief Export the network nodes, edges, and route to CSV files.
    //  * @param node_filepath Path for node CSV
    //  * @param edge_filepath Path for edge CSV
    //  * @param path_filepath Path for route CSV
    //  */
    // void ExportNetworkToCsv(const std::string& node_filepath, const std::string& edge_filepath, const std::string& path_filepath) const;

    /**
     * @brief Get the node ID list forming the last computed route.
     * @return Vector of node IDs
     */
    std::vector<std::string> GetFootpathRoute() const;

private:
    /** 
     * @brief Map of footpath nodes in the network
     */
    std::map<std::string, FootpathNode> m_footpathNodes;

    /** 
     * @brief Map of footpath edges in the network
     */
    std::map<std::string, std::vector<FootpathEdge>> m_footpathEdges;

    /** 
     * @brief Flag indicating whether the footpath network has been successfully loaded.
     */
    bool m_isNetworkLoaded = false;

    /** 
     * @brief The last computed footpath route as a sequence of node IDs.
     */
    std::vector<std::string> m_footpath;

    /** 
     * @brief Static atomic counter for generating unique temporary node IDs.
     */
    static std::atomic<long long> s_tempNodeCounter;
};

} // namespace Captain

#endif // Footpath_HPP
