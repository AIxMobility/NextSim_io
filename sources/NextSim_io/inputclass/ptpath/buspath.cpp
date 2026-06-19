/**
 * NextSim Captain
 * @file : buspath.cpp
 * @version : 1.0
 * @author : Yeonwoo Yu
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <iomanip>

#include <NextSim_io/inputclass/ptpath/buspath.hpp>
#include <NextSim_io/inputclass/InputPTline.hpp>

namespace Captain
{
buspath::buspath(const PTlineArr& ptlinesArr, const StationArr& stationsArr, const LinkArr& linksArr)
{
    for (const auto& PTline : ptlinesArr.GetBusLines()) {
        try {
            BuildODMap(PTline, stationsArr, linksArr);
        } catch (const std::runtime_error& e) {
            std::cerr << "Error calculating OD for line " << PTline.GetID() << ": " << e.what() << std::endl;
        }
    }
}

void buspath::BuildODMap(const InputPTline& ptline, const StationArr& stationsArr, const LinkArr& linksArr)
{
    std::vector<LinkInfo> roadLinks;
    std::vector<StationInfo> roadStations;

    // 1. Link info processing 
    for (auto ptlink : ptline.GetLinkSeq()) {
        const NextSimIO::InputLink* l = nullptr;
        std::size_t linkId = ptlink.GetID();
        for (const auto& link : linksArr.GetLinks()) {
            if (link.GetID() == linkId) {
                l = &link;
                break;
            }
        }
        if (l == nullptr) {
            std::cerr << "Warning: Invalid link ID: " << linkId << " in line " << ptline.GetID() << ". Skipping." << std::endl;
            continue;
        }
        roadLinks.push_back({static_cast<int>(linkId), l->length});
    }

    // 2. Station info processing
    for (int stopId : ptline.GetStationSeq()) {
        if (!stationsArr.HasStop(stopId)) continue;
        auto it = std::find_if(stationsArr.GetStations().begin(), stationsArr.GetStations().end(),
                             [stopId](const NextSimIO::InputStation& s){ return s.GetId() == stopId; });
        if (it != stationsArr.GetStations().end()) {
            roadStations.push_back({it->GetId(), it->GetLink(), it->GetPos()});
        }
    }

    // 3. Compute OD maps
    if (roadLinks.empty() || roadStations.empty()) {
        std::cerr << "Error: Cannot build OD map for line " << ptline.GetID() << ". RoadLinks or RoadStations is empty." << std::endl;
        return;
    }

    std::map<std::pair<int, int>, double> currentLineODMap;

    for (size_t i = 0; i < roadStations.size(); ++i) {
        double dist = 0.0;
        for (size_t j = i + 1; j < roadStations.size(); ++j) {
            double segmentDist = 0.0;
            if (roadStations[j-1].link == roadStations[j].link) {
                // Distance within same link
                segmentDist = roadStations[j].pos - roadStations[j-1].pos;
            } else {
                // Distance across multiple links: start_link end + middle links + end_link start
                // Start link distance
                auto startLinkIt = std::find_if(roadLinks.begin(), roadLinks.end(),
                                                [&](const LinkInfo& l){ return l.id == roadStations[j-1].link; });
                if (startLinkIt == roadLinks.end()) { dist = -1; break; }
                segmentDist += startLinkIt->length - roadStations[j-1].pos;

                // Sum of lengths of middle links
                auto startIdx = std::distance(roadLinks.begin(), startLinkIt) + 1;
                auto endLinkIt = std::find_if(roadLinks.begin(), roadLinks.end(),
                                              [&](const LinkInfo& l){ return l.id == roadStations[j].link; });
                if (endLinkIt == roadLinks.end()) { dist = -1; break; }
                for (auto k = startIdx; k < std::distance(roadLinks.begin(), endLinkIt); ++k) {
                    segmentDist += roadLinks[k].length;
                }

                //End link distance
                segmentDist += roadStations[j].pos;
            }
            
            dist += segmentDist;
            
            // std::cout << std::fixed << std::setprecision(2)
            //           << "[OD Pair] " << roadStations[i].id << " -> " << roadStations[j].id
            //           << " | Distance: " << dist << " m" << std::endl;

            currentLineODMap[{roadStations[i].id, roadStations[j].id}] = dist;
        }
    }

    // Store current line's OD map to the main map
    busODMaps[ptline.GetID()] = currentLineODMap;
    // std::cout << "--------------------------------------------------------" << std::endl;
    // std::cout << "[OD Summary] Line " << line.GetID() << " has "
    //           << currentLineODMap.size() << " OD pairs." << std::endl;
    // std::cout << "--------------------------------------------------------" << std::endl;
}

double buspath::GetBusTravelDistance(const std::string& lineId, int fromStationId, int toStationId)
{
    auto itLine = busODMaps.find(lineId);
    if (itLine == busODMaps.end()) {
        std::cerr << "Error: Line ID " << lineId << " not found in OD map." << std::endl;
        return -1.0; 
    }
    
    auto& lineODMap = itLine->second;
    auto itOD = lineODMap.find({fromStationId, toStationId});
    if (itOD == lineODMap.end()) {
        std::cerr << "Error: OD pair " << fromStationId << " -> " << toStationId << " not found for line " << lineId << "." << std::endl;
        return -1.0;
    }
    
    return itOD->second;
}

double buspath::GetBusTravelTime(const std::string& lineId, int fromStationId, int toStationId, double busSpeedMps)
{
    double distance = GetBusTravelDistance(lineId, fromStationId, toStationId);
    
    if (distance <= 0) {
        std::cerr << "Warning: Invalid distance for " << fromStationId << " -> " << toStationId << " on line " << lineId << "." << std::endl;
        return -1.0;
    }
    if (busSpeedMps <= 0) {
        std::cerr << "Error: Bus speed must be positive." << std::endl;
        return -1.0;
    }
    
    double travelTimeInSeconds = distance / busSpeedMps;
    double travelTimeInMinutes = travelTimeInSeconds / 60.0;
    
    // std::cout << std::fixed << std::setprecision(2)
    //           << "[TravelTime] Line " << lineId << ": " << fromStationId << " -> " << toStationId
    //           << " | Distance: " << distance << " m, Speed: " << busSpeedMps << " m/s"
    //           << " | Travel Time: " << travelTimeInMinutes << " min" << std::endl;
    
    return travelTimeInMinutes;
}

} // namespace Captain