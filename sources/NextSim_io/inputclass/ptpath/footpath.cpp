/**
 * NextSim Captain
 * @file : footpath.cpp
 * @version : 1.0
 * @author : Yeonwoo Yu
 */

#include <iostream>
#include <limits>
#include <cmath> 
#include <fstream>
#include <sstream>
#include <map>
#include <atomic>
#include <algorithm>

#include <NextSim_io/inputclass/ptpath/footpath.hpp>
#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace Captain
{

footpath::footpath() {}

std::atomic<long long> footpath::s_tempNodeCounter(0);

void footpath::LoadFootpathNetwork() {
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::FootpathNetworkXMLPath.string().c_str());

    if (!loadSuccess) {
        std::cerr << "Loading failed (Footpath)\n";
        m_isNetworkLoaded = false;
        return;
    }

    TiXmlElement* pRoot = doc.RootElement();
    if (!pRoot) {
        std::cerr << "Error: Root element not found in network XML." << std::endl;
        m_isNetworkLoaded = false;
        return;
    }

    TiXmlElement* pNodesElem = pRoot->FirstChildElement("nodes");
    if (!pNodesElem) {
        std::cerr << "Warning: <nodes> element not found. Attempting to parse <node> elements directly under root." << std::endl;
        pNodesElem = pRoot;
    }

    int totalNodeCount = 0;
    int skippedNodeCount = 0;

    // ### Parsing nodes ###
    for (TiXmlElement* pNodeElem = pNodesElem->FirstChildElement("node"); 
         pNodeElem != nullptr; 
         pNodeElem = pNodeElem->NextSiblingElement("node")) {

        totalNodeCount++;
        
        std::string nodeId;
        if (pNodeElem->Attribute("id")) {
            nodeId = pNodeElem->Attribute("id");
        } else {
            std::cerr << "Warning: Node found without 'id' attribute. Skipping." << std::endl;
            skippedNodeCount++;
            continue;
        }

        double x_coord = 0.0, y_coord = 0.0;
        bool coordsFound = false;

        const char* center_attr = pNodeElem->Attribute("center");
        if (center_attr) {
            std::string centerStr(center_attr);
            std::istringstream iss(centerStr);
            
            if (iss >> x_coord >> y_coord) {
                coordsFound = true;
            } else {
                std::cerr << "Warning: Failed to parse center coordinates for node " << nodeId 
                          << ". Center value: '" << centerStr << "'" << std::endl;
            }
        }

        if (!coordsFound) {
            const char* x_attr = pNodeElem->Attribute("x_coord");
            const char* y_attr = pNodeElem->Attribute("y_coord");
            
            if (x_attr && y_attr) {
                try {
                    x_coord = std::stod(x_attr);
                    y_coord = std::stod(y_attr);
                    coordsFound = true;
                } catch (const std::exception& e) {
                    std::cerr << "Warning: Invalid coordinates for node " << nodeId 
                              << ". Error: " << e.what() << std::endl;
                }
            }
        }

        if (!coordsFound) {
            const char* x_attr = pNodeElem->Attribute("x");
            const char* y_attr = pNodeElem->Attribute("y");
            
            if (x_attr && y_attr) {
                try {
                    x_coord = std::stod(x_attr);
                    y_coord = std::stod(y_attr);
                    coordsFound = true;
                } catch (const std::exception& e) {
                    std::cerr << "Warning: Invalid x/y coordinates for node " << nodeId 
                              << ". Error: " << e.what() << std::endl;
                }
            }
        }

        if (!coordsFound) {
            std::cerr << "Warning: Node " << nodeId << " missing coordinate information. Skipping." << std::endl;
            skippedNodeCount++;
            continue;
        }

        FootpathNode fNode;
        fNode.id       = nodeId;
        fNode.x_coord  = x_coord;
        fNode.y_coord  = y_coord;

        m_footpathNodes[nodeId] = fNode;
    }

    // Summary of node parsing - For debugging
    // std::cout << "Node parsing summary:" << std::endl;
    // std::cout << "  Total nodes processed: " << totalNodeCount << std::endl;
    // std::cout << "  Nodes skipped: " << skippedNodeCount << std::endl;
    // std::cout << "  Nodes successfully loaded: " << m_footpathNodes.size() << std::endl;

    // ### Creating links between nodes ###
    int createdEdgeCount = 0;
    TiXmlElement* pLinksElem = pRoot->FirstChildElement("links");

    auto addEdgeIfMissing = [&](const std::string& fromNodeId,
                                const std::string& toNodeId,
                                double length) {
        auto& edges = m_footpathEdges[fromNodeId];
        auto edgeIt = std::find_if(
            edges.begin(), edges.end(),
            [&](const FootpathEdge& edge) {
                return edge.to_node_id == toNodeId;
            });
        if (edgeIt == edges.end()) {
            edges.push_back({fromNodeId, toNodeId, length, length});
            ++createdEdgeCount;
        } else if (length < edgeIt->length) {
            edgeIt->length = length;
            edgeIt->travel_time = length;
        }
    };

    if (pLinksElem) {
        for (TiXmlElement* pLinkElem = pLinksElem->FirstChildElement("link");
             pLinkElem != nullptr;
             pLinkElem = pLinkElem->NextSiblingElement("link")) {
            const char* fromNodeAttr = pLinkElem->Attribute("from_node");
            const char* toNodeAttr = pLinkElem->Attribute("to_node");
            if (!fromNodeAttr || !toNodeAttr) {
                std::cerr << "Warning: Footpath link is missing from_node or to_node. Skipping."
                          << std::endl;
                continue;
            }

            const std::string fromNodeId(fromNodeAttr);
            const std::string toNodeId(toNodeAttr);
            const auto fromNodeIt = m_footpathNodes.find(fromNodeId);
            const auto toNodeIt = m_footpathNodes.find(toNodeId);
            if (fromNodeIt == m_footpathNodes.end() ||
                toNodeIt == m_footpathNodes.end()) {
                std::cerr << "Warning: Footpath link references an unknown node ("
                          << fromNodeId << " -> " << toNodeId << "). Skipping."
                          << std::endl;
                continue;
            }

            double length = 0.0;
            if (const char* lengthAttr = pLinkElem->Attribute("length")) {
                try {
                    length = std::stod(lengthAttr);
                } catch (const std::exception&) {
                    length = 0.0;
                }
            }
            if (length <= 0.0) {
                length = calculateDistance(fromNodeIt->second, toNodeIt->second);
            }
            if (length <= 0.0) {
                continue;
            }

            // Road links are directional for vehicles, but the generated
            // pedestrian graph permits walking in both directions.
            addEdgeIfMissing(fromNodeId, toNodeId, length);
            addEdgeIfMissing(toNodeId, fromNodeId, length);
        }
    }

    // Legacy footpath files contain only nodes. Preserve their coordinate-
    // based inference, but never mix inferred shortcuts into an explicit road
    // topology.
    if (!pLinksElem) {
        constexpr double tolerance = 100.0;
        constexpr double verticalThreshold = 2000.0;
        constexpr double horizontalThreshold = 2000.0;

        for (const auto& [id1, node1] : m_footpathNodes) {
            for (const auto& [id2, node2] : m_footpathNodes) {
                if (id1 == id2) {
                    continue;
                }

                const double dx = std::abs(node1.x_coord - node2.x_coord);
                const double dy = std::abs(node1.y_coord - node2.y_coord);
                const bool isVerticalLink =
                    dx < tolerance && dy > 0 && dy <= verticalThreshold;
                const bool isHorizontalLink =
                    dy < tolerance && dx > 0 && dx <= horizontalThreshold;

                if (isVerticalLink || isHorizontalLink) {
                    const double length = std::sqrt(dx * dx + dy * dy);
                    addEdgeIfMissing(id1, id2, length);
                }
            }
        }
    }

    // std::cout << "[FOOTPATH NETWORK] Footpath network loading complete." << std::endl;

    size_t totalEdges = 0;
    for (const auto& pair : m_footpathEdges) {
        totalEdges += pair.second.size();
    }
    // std::cout << "Total Footpath Edges (bidirectional): " << totalEdges << std::endl;

    m_isNetworkLoaded = true;
}

NearestLinkPoint footpath::FindNearestFootpathLinkPoint(double x, double y) const {
    NearestLinkPoint result;
    result.found = false;
    result.distance = std::numeric_limits<double>::max();

    if (m_footpathNodes.empty() || m_footpathEdges.empty()) {
        return result;
    }

    for (const auto& pair : m_footpathEdges) {
        for (const auto& edge : pair.second) {
            // Temporary routing edges must never become candidates for a later
            // nearest-link query.  Otherwise every GetDistance() call expands
            // the search space and subsequent queries become progressively
            // slower.
            if (edge.from_node_id.rfind("TEMP_NODE_", 0) == 0 ||
                edge.to_node_id.rfind("TEMP_NODE_", 0) == 0) {
                continue;
            }

            const FootpathNode& p1 = m_footpathNodes.at(edge.from_node_id);
            const FootpathNode& p2 = m_footpathNodes.at(edge.to_node_id);

            double line_dx = p2.x_coord - p1.x_coord;
            double line_dy = p2.y_coord - p1.y_coord;
            double line_length_sq = line_dx * line_dx + line_dy * line_dy;

            if (line_length_sq < std::numeric_limits<double>::epsilon()) {
                double dist_sq = (x - p1.x_coord) * (x - p1.x_coord) + (y - p1.y_coord) * (y - p1.y_coord);
                double current_distance = std::sqrt(dist_sq);

                if (current_distance < result.distance) {
                    result.distance = current_distance;
                    result.x_coord = p1.x_coord;
                    result.y_coord = p1.y_coord;
                    result.from_node_id = p1.id; 
                    result.to_node_id = p2.id;   
                    result.found = true;
                }
                continue;
            }
            double t = ((x - p1.x_coord) * line_dx + (y - p1.y_coord) * line_dy) / line_length_sq;

            double closest_x, closest_y;
            if (t < 0.0) {
                closest_x = p1.x_coord;
                closest_y = p1.y_coord;
            } else if (t > 1.0) {
                closest_x = p2.x_coord;
                closest_y = p2.y_coord;
            } else {
                closest_x = p1.x_coord + t * line_dx;
                closest_y = p1.y_coord + t * line_dy;
            }

            double dist_sq = (x - closest_x) * (x - closest_x) + (y - closest_y) * (y - closest_y);
            double current_distance = std::sqrt(dist_sq);

            if (current_distance < result.distance) {
                result.distance = current_distance;
                result.x_coord = closest_x;
                result.y_coord = closest_y;
                result.from_node_id = edge.from_node_id; 
                result.to_node_id = edge.to_node_id;    
                result.found = true;
            }
        }
    }

    // Allocate exactly one ID per query.  Previously an ID was consumed each
    // time a closer candidate edge was encountered during the scan.
    if (result.found) {
        result.tempNodeId = "TEMP_NODE_" + std::to_string(s_tempNodeCounter++);
    }

    return result;
}

void footpath::AddFootpathNode(const FootpathNode& node) {
    m_footpathNodes[node.id] = node;
}

void footpath::AddFootpathEdge(const FootpathEdge& edge) {
    m_footpathEdges[edge.from_node_id].push_back(edge);
}

const FootpathNode& footpath::GetFootpathNode(const std::string& nodeId) const {
    auto it = m_footpathNodes.find(nodeId);
    if (it != m_footpathNodes.end()) {
        return it->second;
    }
    std::cerr << "Error: Node " << nodeId << " not found in GetFootpathNode" << std::endl;
    static FootpathNode dummyNode = {"", 0.0, 0.0};
    return dummyNode;
}

void footpath::RemoveTempNodesAndEdges() {
    std::vector<std::string> tempNodeIdsToRemove;
    for (const auto& pair : m_footpathNodes) {
        if (pair.first.rfind("TEMP_NODE_", 0) == 0) {
            tempNodeIdsToRemove.push_back(pair.first);
        }
    }

    for (const std::string& id : tempNodeIdsToRemove) {
        m_footpathNodes.erase(id);
    }
    for (const std::string& id : tempNodeIdsToRemove) {
        m_footpathEdges.erase(id);
    }

    for (auto it = m_footpathEdges.begin(); it != m_footpathEdges.end(); /* no increment here */) {
        std::vector<FootpathEdge>& edges = it->second;
        edges.erase(std::remove_if(edges.begin(), edges.end(), 
            [&](const FootpathEdge& edge) {
                return edge.to_node_id.rfind("TEMP_NODE_", 0) == 0 || edge.from_node_id.rfind("TEMP_NODE_", 0) == 0;
            }), 
            edges.end());
        if (edges.empty()) {
            it = m_footpathEdges.erase(it);
        } else {
            ++it;
        }
    }
}

double Captain::footpath::calculateDistance(const FootpathNode& n1, const FootpathNode& n2) const {
    return std::sqrt(std::pow(n1.x_coord - n2.x_coord, 2) + std::pow(n1.y_coord - n2.y_coord, 2));
}

double footpath::Dijkstra(const std::string& start_node_id, const std::string& end_node_id) {
    if (start_node_id.empty() || end_node_id.empty() ||
        m_footpathNodes.find(start_node_id) == m_footpathNodes.end() ||
        m_footpathNodes.find(end_node_id) == m_footpathNodes.end()) {
        std::cerr << "Error: Invalid start or end node ID for Dijkstra. (IDs: " << start_node_id << ", " << end_node_id << ")" << std::endl;
        return -1.0;
    }

    std::priority_queue<DijkstraState, std::vector<DijkstraState>, std::greater<DijkstraState>> pq;
    std::map<std::string, double> distances;
    std::map<std::string, std::string> predecessors;
    
    for (const auto& pair : m_footpathNodes) {
        distances[pair.first] = std::numeric_limits<double>::max();
    }

    distances[start_node_id] = 0.0;
    pq.push({start_node_id, 0.0});

     while (!pq.empty()) {
        DijkstraState current = pq.top();
        pq.pop();

        std::string u_id = current.node_id;
        double dist_u = current.distance;

        if (dist_u > distances[u_id]) {
            continue;
        }

        if (u_id == end_node_id) {
            std::vector<std::string> path;
            std::string current_path_node = end_node_id;
            while (current_path_node != start_node_id) {
                path.insert(path.begin(), current_path_node);
                current_path_node = predecessors[current_path_node];
            }
            path.insert(path.begin(), start_node_id);

            m_footpath = path; // Store the node IDs in the path

            return dist_u;
        }

        if (m_footpathEdges.count(u_id)) {
            for (const FootpathEdge& edge : m_footpathEdges.at(u_id)) {
                std::string v_id = edge.to_node_id;
                double edge_weight = edge.length;

                double new_dist = dist_u + edge_weight;

                if (new_dist < distances[v_id]) {
                    distances[v_id] = new_dist;
                    predecessors[v_id] = u_id; 
                    pq.push({v_id, new_dist});
                }
            }
        }
    }
    return -1.0;
}

double footpath::GetDistance(const std::pair<double, double>& origin_coords, const std::pair<double, double>& dest_coords) {
    // Step 1: Find nearest link point for origin
    NearestLinkPoint originLinkPoint = FindNearestFootpathLinkPoint(origin_coords.first, origin_coords.second);
    if (!originLinkPoint.found) {
        std::cerr << "GetDistance Error: Could not find nearest link point for origin ("
                  << origin_coords.first << ", " << origin_coords.second << ")\n";
        return -1.0;
    }

    // Step 2: Find nearest link point for destination
    NearestLinkPoint destLinkPoint = FindNearestFootpathLinkPoint(dest_coords.first, dest_coords.second);
    if (!destLinkPoint.found) {
        std::cerr << "GetDistance Error: Could not find nearest link point for destination ("
                  << dest_coords.first << ", " << dest_coords.second << ")\n";
        return -1.0;
    }

    // Step 3: Add temporary nodes
    FootpathNode tempOriginNode = {originLinkPoint.tempNodeId, originLinkPoint.x_coord, originLinkPoint.y_coord};
    AddFootpathNode(tempOriginNode);

    const FootpathNode& originFrom = GetFootpathNode(originLinkPoint.from_node_id);
    const FootpathNode& originTo = GetFootpathNode(originLinkPoint.to_node_id);

    AddFootpathEdge({originFrom.id, tempOriginNode.id, calculateDistance(originFrom, tempOriginNode), calculateDistance(originFrom, tempOriginNode)});
    AddFootpathEdge({tempOriginNode.id, originFrom.id, calculateDistance(originFrom, tempOriginNode), calculateDistance(originFrom, tempOriginNode)});

    AddFootpathEdge({originTo.id, tempOriginNode.id, calculateDistance(originTo, tempOriginNode), calculateDistance(originTo, tempOriginNode)});
    AddFootpathEdge({tempOriginNode.id, originTo.id, calculateDistance(originTo, tempOriginNode), calculateDistance(originTo, tempOriginNode)});

    FootpathNode tempDestNode = {destLinkPoint.tempNodeId, destLinkPoint.x_coord, destLinkPoint.y_coord};
    AddFootpathNode(tempDestNode);

    const FootpathNode& destFrom = GetFootpathNode(destLinkPoint.from_node_id);
    const FootpathNode& destTo = GetFootpathNode(destLinkPoint.to_node_id);

    AddFootpathEdge({destFrom.id, tempDestNode.id, calculateDistance(destFrom, tempDestNode), calculateDistance(destFrom, tempDestNode)});
    AddFootpathEdge({tempDestNode.id, destFrom.id, calculateDistance(destFrom, tempDestNode), calculateDistance(destFrom, tempDestNode)});

    AddFootpathEdge({destTo.id, tempDestNode.id, calculateDistance(destTo, tempDestNode), calculateDistance(destTo, tempDestNode)});
    AddFootpathEdge({tempDestNode.id, destTo.id, calculateDistance(destTo, tempDestNode), calculateDistance(destTo, tempDestNode)});

    // Step 4: Run Dijkstra
    double network_distance = Dijkstra(tempOriginNode.id, tempDestNode.id);

    // Step 5: Add perpendicular offset distances
    double origin_offset = std::sqrt(std::pow(origin_coords.first - originLinkPoint.x_coord, 2) +
                                     std::pow(origin_coords.second - originLinkPoint.y_coord, 2));

    double dest_offset = std::sqrt(std::pow(dest_coords.first - destLinkPoint.x_coord, 2) +
                                   std::pow(dest_coords.second - destLinkPoint.y_coord, 2));

    double total_distance = -1.0;
    if (network_distance >= 0.0) {
        total_distance = origin_offset + network_distance + dest_offset;
    }

    // GetDistance() is invoked for every station pair.  Keeping these nodes
    // and edges would make both nearest-link search and Dijkstra operate on a
    // graph that grows with every pair (quadratic station pairs compounded by
    // a linearly growing graph).
    RemoveTempNodesAndEdges();

    // std::cout << "Origin offset distance: " << origin_offset << std::endl;
    // std::cout << "Footpath network distance (Dijkstra): " << network_distance << std::endl;
    // std::cout << "Destination offset distance: " << dest_offset << std::endl;
    // std::cout << ">>> Total distance (with offset): " << total_distance << std::endl;

    return total_distance;
}

// void Footpath::ExportNetworkToCsv(const std::string& node_filepath, const std::string& edge_filepath, const std::string& path_filepath) const {
//     // Save nodes to CSV (footpath_nodes.csv)
//     std::ofstream nodes_ofs(node_filepath);
//     if (!nodes_ofs.is_open()) {
//         std::cerr << "[Footpath::ExportNetworkToCsv][Error] Failed to open node file for writing: " << node_filepath << std::endl;
//         return;
//     }
//     nodes_ofs << "id,x,y\n";

//     for (const auto& pair : m_footpathNodes) {
//         const FootpathNode& node = pair.second;
//         nodes_ofs << node.id << ","
//                   << std::fixed << std::setprecision(3) << node.x_coord << "," // 소수점 3자리까지 고정
//                   << std::fixed << std::setprecision(3) << node.y_coord << "\n";
//     }
//     nodes_ofs.close();
//     std::cout << "\n[Footpath::ExportNetworkToCsv][Info] Exported " << m_footpathNodes.size() << " nodes to " << node_filepath << std::endl;

//     // Save edges to CSV (footpath_edges.csv)
//     std::ofstream edges_ofs(edge_filepath);
//     if (!edges_ofs.is_open()) {
//         std::cerr << "[Footpath::ExportNetworkToCsv][Error] Failed to open edge file for writing: " << edge_filepath << std::endl;
//         return;
//     }
//     edges_ofs << "from_node,to_node,length\n";

//     for (const auto& pair : m_footpathEdges) {
//         for (const auto& edge : pair.second) {
//             edges_ofs << edge.from_node_id << ","
//                       << edge.to_node_id << ","
//                       << std::fixed << std::setprecision(3) << edge.length << "\n";
//         }
//     }
//     edges_ofs.close();
//     std::cout << "[Footpath::ExportNetworkToCsv][Info] Exported " << m_footpathEdges.size() << " edge lists to " << edge_filepath << std::endl;

//     // Save paths to CSV (footpath_paths.csv)
//     std::ofstream paths_ofs(path_filepath);
//     if (!paths_ofs.is_open()) {
//         std::cerr << "[Footpath::ExportNetworkToCsv][Error] Failed to open path file for writing: " << path_filepath << std::endl;
//         return;
//     }
//     paths_ofs << "node_id\n";

//     for (const auto& nodeId : m_footpath) {
//         paths_ofs << nodeId << "\n";
//     }
//     paths_ofs.close();
//     std::cout << "[Footpath::ExportNetworkToCsv][Info] Exported " << m_footpath.size() << " path nodes to " << path_filepath << std::endl;
// }

} // namespace Captain
