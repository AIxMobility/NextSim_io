/**
 * @file main.cpp
 * @brief FootpathRouteGenerator 테스트를 위한 임시 메인 함수
 */

#include "FootpathRouteGenerator.hpp"
#include <iostream>
#include <string> // For std::string
#include <vector> // For std::vector
#include <cmath>  // For std::sqrt

// Assume FootpathRouteGenerator.hpp includes FootpathNode, FootpathEdge, NearestLinkPoint
// and the necessary headers like <map>, <string>, <vector>, <limits>, <atomic>

using namespace Captain; // 가독성을 위해 main 함수 내에서 Captain 네임스페이스 사용

int main() {
    FootpathRouteGenerator generator;

    // 보행자 네트워크 XML 파일을 읽고 내부 구조로 변환
    generator.LoadFootpathNetwork();

    // --- Test FindNearestFootpathLinkPoint and Dijkstra with temp nodes ---
    double test_x_origin = 1800.0; // Example origin X coordinate (near a link)
    double test_y_origin = 1300.0; // Example origin Y coordinate (near a link)

    double test_x_dest = 2250.0;   // Example destination X coordinate (near another link)
    double test_y_dest = 1150.0;   // Example destination Y coordinate (near another link)

    // 다익스트라에 사용할 시작/종료 노드 ID (임시 노드 ID가 될 수 있음)
    std::string startNodeIdForDijkstra = "";
    std::string endNodeIdForDijkstra = "";

    // 1. 출발점에 가장 가까운 링크 위의 점 찾기 및 임시 노드/링크 생성
    std::cout << "\n--- Processing Origin Point ---\n";
    NearestLinkPoint originLinkPoint = generator.FindNearestFootpathLinkPoint(test_x_origin, test_y_origin);

    if (originLinkPoint.found) {
        std::cout << "Origin point (" << test_x_origin << ", " << test_y_origin << ") nearest link point: "
                  << originLinkPoint.tempNodeId << " at (" << originLinkPoint.x_coord << ", " << originLinkPoint.y_coord << ")\n"
                  << "  on link from " << originLinkPoint.from_node_id << " to " << originLinkPoint.to_node_id
                  << ", distance: " << originLinkPoint.distance << std::endl;

        // 임시 노드 생성
        FootpathNode tempOriginNode;
        tempOriginNode.id = originLinkPoint.tempNodeId;
        tempOriginNode.x_coord = originLinkPoint.x_coord;
        tempOriginNode.y_coord = originLinkPoint.y_coord;
        generator.AddFootpathNode(tempOriginNode); 

        // 임시 노드와 원본 링크를 연결하는 새 링크 생성
        const FootpathNode& originalFromNodeOrigin = generator.GetFootpathNode(originLinkPoint.from_node_id);
        double dist1_origin = generator.calculateDistance(originalFromNodeOrigin, tempOriginNode);
        generator.AddFootpathEdge({originalFromNodeOrigin.id, tempOriginNode.id, dist1_origin, dist1_origin});
        generator.AddFootpathEdge({tempOriginNode.id, originalFromNodeOrigin.id, dist1_origin, dist1_origin}); 

        const FootpathNode& originalToNodeOrigin = generator.GetFootpathNode(originLinkPoint.to_node_id);
        double dist2_origin = generator.calculateDistance(tempOriginNode, originalToNodeOrigin);
        generator.AddFootpathEdge({tempOriginNode.id, originalToNodeOrigin.id, dist2_origin, dist2_origin});
        generator.AddFootpathEdge({originalToNodeOrigin.id, tempOriginNode.id, dist2_origin, dist2_origin}); 
        
        startNodeIdForDijkstra = tempOriginNode.id; // 최종적으로 사용할 노드 ID
    } else {
        std::cerr << "Error: Could not find a nearest link point for origin (" << test_x_origin << ", " << test_y_origin << "). Dijkstra test might be skipped.\n";
    }

    // 2. 도착점에 가장 가까운 링크 위의 점 찾기 및 임시 노드/링크 생성
    std::cout << "\n--- Processing Destination Point ---\n";
    NearestLinkPoint destLinkPoint = generator.FindNearestFootpathLinkPoint(test_x_dest, test_y_dest);

    if (destLinkPoint.found) {
        std::cout << "Destination point (" << test_x_dest << ", " << test_y_dest << ") nearest link point: "
                  << destLinkPoint.tempNodeId << " at (" << destLinkPoint.x_coord << ", " << destLinkPoint.y_coord << ")\n"
                  << "  on link from " << destLinkPoint.from_node_id << " to " << destLinkPoint.to_node_id
                  << ", distance: " << destLinkPoint.distance << std::endl;

        // 임시 노드 생성
        FootpathNode tempDestNode;
        tempDestNode.id = destLinkPoint.tempNodeId;
        tempDestNode.x_coord = destLinkPoint.x_coord;
        tempDestNode.y_coord = destLinkPoint.y_coord;
        generator.AddFootpathNode(tempDestNode);

        // 임시 노드와 원본 링크를 연결하는 새 링크 생성
        const FootpathNode& originalFromNodeDest = generator.GetFootpathNode(destLinkPoint.from_node_id);
        double dist1_dest = generator.calculateDistance(originalFromNodeDest, tempDestNode);
        generator.AddFootpathEdge({originalFromNodeDest.id, tempDestNode.id, dist1_dest, dist1_dest});
        generator.AddFootpathEdge({tempDestNode.id, originalFromNodeDest.id, dist1_dest, dist1_dest}); 

        const FootpathNode& originalToNodeDest = generator.GetFootpathNode(destLinkPoint.to_node_id);
        double dist2_dest = generator.calculateDistance(tempDestNode, originalToNodeDest);
        generator.AddFootpathEdge({tempDestNode.id, originalToNodeDest.id, dist2_dest, dist2_dest});
        generator.AddFootpathEdge({originalToNodeDest.id, tempDestNode.id, dist2_dest, dist2_dest}); 

        endNodeIdForDijkstra = tempDestNode.id; // 최종적으로 사용할 노드 ID
    } else {
        std::cerr << "Error: Could not find a nearest link point for destination (" << test_x_dest << ", " << test_y_dest << "). Dijkstra test might be skipped.\n";
    }

    // 3. 다익스트라 수행 (이제 임시 노드 ID를 사용)
    double shortest_path_distance = -1.0; // 기본값으로 실패를 나타내는 값 설정
    if (!startNodeIdForDijkstra.empty() && !endNodeIdForDijkstra.empty()) {
        std::cout << "\n--- Performing Dijkstra Search ---\n";
        std::cout << "Attempting Dijkstra from (temp) node " << startNodeIdForDijkstra
                  << " to (temp) node " << endNodeIdForDijkstra << std::endl;
        shortest_path_distance = generator.Dijkstra(startNodeIdForDijkstra, endNodeIdForDijkstra);

        if (shortest_path_distance >= 0) {
            std::cout << "Shortest distance between (temp) nodes: " << shortest_path_distance << std::endl;
        } else {
            std::cout << "No path found between " << startNodeIdForDijkstra << " and " << endNodeIdForDijkstra << std::endl;
        }
    } else {
        std::cerr << "Dijkstra test skipped due to missing origin or destination link point after processing.\n";
    }

    // 4. GetDistance 함수 테스트: (이 함수도 임시 노드를 추가합니다)
    // GetDistance 함수는 자체적으로 FindNearestFootpathLinkPoint를 호출하고 임시 노드를 추가/제거하는 로직을
    // 포함해야 합니다. 만약 그렇지 않다면, 이 호출은 단순히 Dijkstra 호출 시 생성된 임시 노드를 사용할 것입니다.
    // 사용자가 '이 함수도 임시 노드를 추가합니다'라고 언급했으므로, GetDistance 내부에서
    // ExportNetworkToCsv 전에 임시 노드가 모두 생성되어 있음을 가정합니다.
    std::cout << "\n--- Testing GetDistance function ---\n";
    std::pair<double, double> origin_coords_test = {test_x_origin, test_y_origin};
    std::pair<double, double> dest_coords_test = {test_x_dest, test_y_dest};
    double calculated_dist = generator.GetDistance(origin_coords_test, dest_coords_test);

    if (calculated_dist >= 0) {
        std::cout << "Calculated total distance via GetDistance: " << calculated_dist << std::endl;
    } else {
        std::cout << "Failed to calculate distance via GetDistance. Check logs for details." << std::endl;
    }

    // !!!! 중요: 임시 노드 정보를 파일로 내보내는 부분 !!!!
    // ExportNetworkToCsv()는 RemoveTempNodesAndEdges() 호출 전에 실행되어야 합니다.
    // GetDistance() 호출로 인해 추가된 임시 노드들도 포함하여 내보내집니다.
    generator.ExportNetworkToCsv("footpath_nodes.csv", "footpath_edges.csv", "footpath_paths.csv");
    std::cout << "[FootpathRouteGenerator] Network exported to CSV files for visualization." << std::endl;


    // 임시 노드 및 링크 제거
    generator.RemoveTempNodesAndEdges(); // 이제 이 함수는 임시 노드들을 메모리에서 제거합니다.
    std::cout << "\nTemporary nodes and edges removed from the network after export." << std::endl;

    std::cout << "\n[FootpathRouteGenerator] 네트워크 로드 및 CSV 출력 완료." << std::endl;

    return 0;
}