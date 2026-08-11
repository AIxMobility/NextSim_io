/**
 * NextSim Captain
 * @file PTGraphArr.cpp
 * @version 1.0
 * @author Yeonwoo Yu
 */

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <memory>
#include <set>
#include <cmath>
#include <utility> 
#include <vector>
#include <tuple>

#include <NextSim_io/parser/PTGraphArr.hpp>
#include <NextSim_io/inputclass/ptpath/footpath.hpp>
#include <NextSim_io/inputclass/ptpath/buspath.hpp>
#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

using namespace Captain;
namespace NextSimIO
{

// ### Helper functions ### ///
double convertToMinutes(const std::string& time) {
    try {
        if (time.empty()) {
            std::cerr << "Error: Empty time string" << std::endl;
            return -1.0;
        }

        size_t colonPos = time.find(':');
        if (colonPos == std::string::npos || colonPos == 0 || colonPos == time.length() - 1) {
            std::cerr << "Error: Invalid time format for '" << time << "'" << std::endl;
            return -1.0;
        }

        std::string hourStr = time.substr(0, colonPos);
        std::string minStr = time.substr(colonPos + 1);

        if (hourStr.empty() || minStr.empty()) {
            std::cerr << "Error: Empty hour or minute for '" << time << "'" << std::endl;
            return -1.0;
        }

        double hour = std::stod(hourStr);
        double minute = std::stod(minStr);

        if (minute < 0 || minute >= 60) {
            std::cerr << "Error: Invalid minute value for '" << time << "'" << std::endl;
            return -1.0;
        }

        if (hour < 0 || hour > 24) {
            std::cerr << "Error: Invalid hour value for '" << time << "'" << std::endl;
            return -1.0;
        }

        // 다음 날로 넘어가는 경우
        if (hour == 24) {
            return 1440.0 + minute; // 1440.0은 24시간을 double로 표현한 것
        }

        return hour * 60.0 + minute;

    } catch (const std::exception& e) {
        std::cerr << "Error: Exception in convertToMinutes for '" << time << "': " << e.what() << std::endl;
        return -1.0;
    }
}

std::string getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&current_time);
    std::stringstream ss;
    ss << std::put_time(&tm, "%H:%M");
    return ss.str();
}

double euclidDist(const std::pair<double, double>& p1, const std::pair<double, double>& p2) // Euclidean distance (flat coordinate)
{
    double dx = p1.first - p2.first;
    double dy = p1.second - p2.second;
    return std::sqrt(dx * dx + dy * dy);
}

void pairStations(const StationArr& roadStations,
                  const RailStationArr& railStations,
                  std::vector<std::tuple<int,int>>& pairs) {
    pairs.clear();

    const auto& road = roadStations.GetStations();
    for (size_t i = 0; i < road.size(); ++i) {
        for (size_t j = 0; j < road.size(); ++j) {
            if (i != j) {
                pairs.emplace_back(road[i].GetId(), road[j].GetId());
            }
        }
    }

    const auto& rail = railStations.GetRailStations();
    for (size_t i = 0; i < rail.size(); ++i) {
        for (size_t j = 0; j < rail.size(); ++j) {
            if (i != j) {
                pairs.emplace_back(rail[i].GetId(), rail[j].GetId());
            }
        }
    }

    for (const auto& rStation : road) {
        for (const auto& railStation : rail) {
            pairs.emplace_back(rStation.GetId(), railStation.GetId());
            pairs.emplace_back(railStation.GetId(), rStation.GetId());
        }
    }
}

//  ######## Constants for footpath/transfer logic ######## //
const double THRESHOLD_FOR_FOOTPATH = 10000.0; // meters
const double THRESHOLD_FOR_INTERMODAL_TRANSFER = 10000.0; // meters for intermodal transfer
const double TRANSFER_TURNAROUND_TIME = 1.0; // Fixed transfer time in minutes, to 1 min.

inline double KMPtoMPS(double kph) { return kph * 1000.0 / 3600.0; }
const double FOOTPATH_SPEED = 4;      // 4 km/h (approximately 1.11 m/s)
const double FOOTPATH_SPEED_MPS = KMPtoMPS(FOOTPATH_SPEED); // 11.1111 mps
const double BUS_SPEED = 20;       // 20 km/h (approximately 5.56 m/s)
const double BUS_SPEED_MPS = KMPtoMPS(BUS_SPEED); // 5.5556 mps


PTVertexArr::PTVertexArr(const StationArr& roadStations, const RailStationArr& railStations,
                            const PTlineArr& roadPTLines, const RailLineArr& railPTLines)
{
    m_ptVertices.clear();

    // road station
    LinkArr roadLinks;
    buspath buspathGenerator(roadPTLines, roadStations, roadLinks); 

    for (const auto& roadLine : roadPTLines.GetBusLines()) {
        std::vector<double> arrivalTimes;
        std::vector<double> departureTimes;
        std::string lineId = roadLine.GetID();
        std::vector<int> stationSeq = roadLine.GetStationSeq(); 
        double interval = roadLine.GetInterval();

        const double startMinuteOfDay = 6 * 60;   // 06:00
        const double endMinuteOfDay = 24 * 60;    // 24:00 (다음 날 00:00)
        const double dwellTime = 1; // 정류장에서의 대기 시간 (1분)

        for (double startTime = startMinuteOfDay; startTime < endMinuteOfDay; startTime += interval) {
            double currentTime = startTime;

            for (size_t i = 0; i < stationSeq.size(); ++i) {
                arrivalTimes.push_back(currentTime);
                departureTimes.push_back(currentTime + dwellTime);

                if (i + 1 < stationSeq.size()) {
                    int originStopId = stationSeq[i];
                    int destStopId = stationSeq[i + 1];

                    double busTravelTime = buspathGenerator.GetBusTravelTime(lineId, originStopId, destStopId, BUS_SPEED_MPS);

                    if (busTravelTime < 0) {
                        std::cerr << "Failed to compute for: " << lineId << ", " << originStopId << " -> " << destStopId << "\n";
                        busTravelTime = 2.0; 
                    }

                    currentTime += dwellTime + busTravelTime;
                }
            }
        }
        
        std::shared_ptr<Line> currentLine = 
            std::make_shared<Line>(lineId, stationSeq, arrivalTimes, departureTimes);
        
        size_t arrivals = stationSeq.size();
        size_t runCount = arrivalTimes.empty() ? 0 : arrivalTimes.size() / arrivals; 

        for (size_t run = 0; run < runCount; ++run) {
            for (size_t stopIdx = 0; stopIdx < arrivals; ++stopIdx) {
                int stopId = stationSeq[stopIdx];
                const Stop* realStop = nullptr;

                if (roadStations.HasStop(stopId)) { 
                    realStop = &roadStations.GetStopById(stopId);
                } 

                if (realStop) {
                    InputPTGraphVertex vertex(*realStop, currentLine); 
                    m_ptVertices.push_back(vertex);
                } 
            }
        }
    }

    // rail station: use departureTime + stationSeq.timeOffset to generate arrivals
    for (const auto& railLine : railPTLines.GetRailLines()) {
        std::string lineId = railLine.GetID();
        const auto stationSeqObjs = railLine.GetRailStationSeq();

        // build station id vector
        std::vector<int> stationSeqIds;
        for (const auto& s : stationSeqObjs) stationSeqIds.push_back(s.GetId());

        // build arrivals per stop from departures and offsets
        std::map<int, std::vector<double>> arrivalsPerStop;
        const auto departures = railLine.GetDepartureTime();
        for (const auto& dep : departures) {
            double base = convertToMinutes(dep);
            if (base < 0) continue;
            for (const auto& s : stationSeqObjs) {
                double arr = base + static_cast<double>(s.GetTimeOffset());
                if (arr >= 24*60) arr -= 24*60;
                arrivalsPerStop[s.GetId()].push_back(arr);
            }
        }

        if (stationSeqIds.empty()) continue;

        // determine number of runs (min available per stop)
        size_t numRuns = SIZE_MAX;
        for (int sid : stationSeqIds) {
            if (!arrivalsPerStop.count(sid)) { numRuns = 0; break; }
            numRuns = std::min(numRuns, arrivalsPerStop[sid].size());
        }
        if (numRuns == 0 || numRuns == SIZE_MAX) {
            std::cerr << "  [SKIP] No runs found for line " << lineId << ".\n";
            continue;
        }

        // create Line object and vertices
        std::vector<double> arrivalTimes, departureTimes;
        for (size_t run = 0; run < numRuns; ++run) {
            for (int sid : stationSeqIds) {
                double arr = arrivalsPerStop[sid][run];
                arrivalTimes.push_back(arr);
                departureTimes.push_back(arr + 1.0);
            }
        }

        std::shared_ptr<Line> currentLine = std::make_shared<Line>(lineId, stationSeqIds, arrivalTimes, departureTimes);

        size_t arrivals = stationSeqIds.size();
        size_t runCount = numRuns;
        for (size_t run = 0; run < runCount; ++run) {
            for (size_t stopIdx = 0; stopIdx < arrivals; ++stopIdx) {
                int stopId = stationSeqIds[stopIdx];
                if (railStations.HasStop(stopId)) {
                    const Stop* realStop = &railStations.GetStopById(stopId);
                    InputPTGraphVertex vertex(*realStop, currentLine);
                    m_ptVertices.push_back(vertex);
                }
            }
        }
    }
}

PTArcArr::PTArcArr(const StationArr& roadStations, const RailStationArr& railStations,
                   const PTlineArr& roadPTLines, const RailLineArr& railPTLines)
{
    m_ptArcs.clear();
    size_t arcIdCounter = 0;
    
    // 1.1. Road Line (버스) InVehicle 아크 생성
    LinkArr roadLinks;
    buspath buspathGenerator(roadPTLines, roadStations, roadLinks);
    //✨ 총 아크 수
    size_t totalArcsCreated = 0;
    // ✨ 각 OD 쌍의 아크 수를 저장할 맵
    std::map<std::string, std::map<std::pair<int, int>, size_t>> lineODPairCounts;

    for (const auto& roadLine : roadPTLines.GetBusLines()) {
        std::string lineId = roadLine.GetID();

        if (lineId.empty()) {
            std::cerr << "Invalid line ID: empty string" << std::endl;
            continue;
        }

        std::vector<int> stationSeq = roadLine.GetStationSeq();
        double interval = roadLine.GetInterval();
        double fee = roadLine.GetFee();
        
        const double startMinuteOfDay = 6 * 60;
        const double endMinuteOfDay = 24 * 60;
        const double dwellTime = 1;

        // ✨ 노선 당 아크 수
        size_t arcsInThisLine = 0;

        for (double startTime = startMinuteOfDay; startTime < endMinuteOfDay; startTime += interval) {
            std::vector<double> arrivalTimes;
            std::vector<double> departureTimes;
            double currentTime = startTime;

            for (size_t i = 0; i < stationSeq.size(); ++i) {
                arrivalTimes.push_back(currentTime);
                departureTimes.push_back(currentTime + dwellTime);

                if (i + 1 < stationSeq.size()) {
                    int originStopId = stationSeq[i];
                    int destStopId = stationSeq[i + 1];

                    double busTravelTime = buspathGenerator.GetBusTravelTime(lineId, originStopId, destStopId, BUS_SPEED_MPS);

                    if (busTravelTime < 0) {
                        std::cerr << "Failed to compute for: " << lineId << ", " << originStopId << " -> " << destStopId << "\n";
                        busTravelTime = 2.0;
                    }
                    currentTime += dwellTime + busTravelTime;
                }
            }

            for (size_t i = 0; i < stationSeq.size() - 1; ++i) {
                int fromStopId = stationSeq[i];
                int toStopId = stationSeq[i+1];
                double timeCost = 0.0;
                if (i < departureTimes.size() && (i + 1) < arrivalTimes.size()) {
                    double fromTime = departureTimes[i];
                    double toTime = arrivalTimes[i + 1];
                    timeCost = static_cast<double>(toTime - fromTime);
                    if (timeCost < 0) {
                        timeCost += 24 * 60; // 다음 날로 넘어가는 경우
                    }
                } else {
                    std::cerr << "Warning: Road Line " << lineId << " run " << (startTime/interval)
                                << ": Time data out of bounds for segment " << fromStopId << " to " << toStopId << ". Skipping." << std::endl;
                    continue;
                }
                PTCost inVehicleCost(timeCost, 0, 0, fee);
                AddPTArc(InputPTGraphArc(arcIdCounter++, fromStopId, lineId, toStopId, lineId, departureTimes[i], ArcType::InVehicle, inVehicleCost));
                arcsInThisLine++; // ✨ 아크가 생성될 때마다 카운트 증가
                lineODPairCounts[lineId][{fromStopId, toStopId}]++; // ✨ OD 쌍 카운트 증가
            }
        }
        totalArcsCreated += arcsInThisLine; // ✨ 총 아크 수에 누적
    }
    // ✨ 모든 루프가 끝난 후, OD 쌍별 아크 수 출력
    // std::cout << "\n------------------------------------------" << std::endl;
    // std::cout << "Total InVehicle arcs created: " << totalArcsCreated << std::endl;
    // std::cout << "------------------------------------------" << std::endl;

    // for (const auto& linePair : lineODPairCounts) {
    //     const std::string& lineId = linePair.first;
    //     const auto& odMap = linePair.second;
    //     std::cout << "OD Pair specific arc counts for Line: " << lineId << std::endl;
        
    //     for (const auto& odPair : odMap) {
    //         std::cout << "  OD Pair (" << odPair.first.first << " -> " << odPair.first.second << "): "
    //                 << odPair.second << " arcs" << std::endl;
    //     }
    //     std::cout << "------------------------------------------" << std::endl;
    // }
    
    // 1.2. Rail Line (철도) InVehicle 아크 생성
    for (const auto& railLine : railPTLines.GetRailLines()) {
        std::string lineId = railLine.GetID();
        const auto stationSeqObjs = railLine.GetRailStationSeq();
        double fee = railLine.GetFee();

        if (stationSeqObjs.size() < 2) continue;

        // build station ids
        std::vector<int> stationSeqIds;
        for (const auto& s : stationSeqObjs) stationSeqIds.push_back(s.GetId());

        // build arrivals per stop from departures and offsets
        std::map<int, std::vector<double>> arrivalsPerStop;
        const auto departures = railLine.GetDepartureTime();
        for (const auto& dep : departures) {
            double base = convertToMinutes(dep);
            if (base < 0) continue;
            for (const auto& s : stationSeqObjs) {
                double arr = base + static_cast<double>(s.GetTimeOffset());
                if (arr >= 24*60) arr -= 24*60;
                arrivalsPerStop[s.GetId()].push_back(arr);
            }
        }

        // determine number of runs
        size_t numRuns = SIZE_MAX;
        for (int sid : stationSeqIds) {
            if (!arrivalsPerStop.count(sid)) { numRuns = 0; break; }
            numRuns = std::min(numRuns, arrivalsPerStop[sid].size());
        }
        if (numRuns == 0 || numRuns == SIZE_MAX) continue;

        // for each run, create segment arcs
        for (size_t run = 0; run < numRuns; ++run) {
            for (size_t i = 0; i < stationSeqIds.size() - 1; ++i) {
                int fromStop = stationSeqIds[i];
                int toStop = stationSeqIds[i+1];
                double t1 = arrivalsPerStop[fromStop][run];
                double t2 = arrivalsPerStop[toStop][run];
                double timeCost = t2 - t1;
                if (timeCost < 0) timeCost += 24*60;
                PTCost inVehicleCost(timeCost, 0, 0, fee);
                AddPTArc(InputPTGraphArc(arcIdCounter++, fromStop, lineId, toStop, lineId, t1, ArcType::InVehicle, inVehicleCost));
            }
        }
    }

    // 2. 환승(Transfer) 아크 생성

    // std::cout << "--- Generating Transfer Arcs ---" << std::endl;

    // 2.1. 같은 로드 정류장 내에서 다른 노선으로의 환승
    // std::cout << "[DEBUG_TRANSFER_ARC_GENERATION] Processing Road Stations for Transfers..." << std::endl;
    for (const auto& inputStation : roadStations.GetStations()) {
        const std::vector<std::string>& lineIds = inputStation.GetLineList();
        long long arcsForCurrentStation = 0; // 현재 정류장의 아크 카운터

        if (lineIds.size() > 1) {
            // std::cout << "[DEBUG_TRANSFER_ARC_GENERATION] Station ID: " << inputStation.GetId() << ", Lines: ";
            for (size_t i = 0; i < lineIds.size(); ++i) {
                for (size_t j = 0; j < lineIds.size(); ++j) {
                    if (i == j) continue; // 같은 라인은 스킵

                    const std::string& fromLineId = lineIds[i];
                    const std::string& toLineId = lineIds[j];

                    // 빈 문자열 체크
                    if (fromLineId.empty() || toLineId.empty()) {
                        std::cerr << "Error: Empty line ID found for transfer arc at station " << inputStation.GetId() << std::endl;
                        continue;
                    }

                    PTCost transferCost(TRANSFER_TURNAROUND_TIME, 0.0, 1, 0);
                    AddPTArc(InputPTGraphArc(arcIdCounter++, inputStation.GetId(), fromLineId, inputStation.GetId(), toLineId, 0, ArcType::Transfer, transferCost));
                    // 주석 처리: 각 아크 생성 시마다 출력하면 로그가 너무 길어질 수 있습니다.
                    // std::cout << "[DEBUG_TRANSFER_ARC_GENERATION] Generated Road Transfer Arc ID: " << (arcIdCounter - 1)
                    //           << ", From Station: " << inputStation.GetId() << ", From Line: " << fromLineId
                    //           << ", To Station: " << inputStation.GetId() << ", To Line: " << toLineId << std::endl;
                    arcsForCurrentStation++;
                }
            }
            // std::cout << "[DEBUG_TRANSFER_ARC_GENERATION] -> Total " << arcsForCurrentStation << " Road Transfer Arcs generated for Station ID: " << inputStation.GetId() << std::endl;
        } else {
            // std::cout << "[DEBUG_TRANSFER_ARC_GENERATION] Station ID: " << inputStation.GetId()
            //           << " has " << lineIds.size() << " line(s). No transfer arcs generated." << std::endl;
        }
    }
    
    // 2.2. 같은 철도 정류장 내에서 다른 노선으로의 환승
    // std::cout << "[DEBUG_TRANSFER_ARC_GENERATION] Processing Rail Stations for Transfers..." << std::endl;
    for (const auto& railInputStation : railStations.GetRailStations()) {
        std::set<std::string> railLines;
        const auto& lines = railInputStation.GetLineList();
        for (const auto& lid : lines) if (!lid.empty()) railLines.insert(lid);
        long long arcsForCurrentStation = 0; // 현재 정류장의 아크 카운터

        if (railLines.size() > 1) {
            // std::cout << "[DEBUG_TRANSFER_ARC_GENERATION] Rail Station ID: " << railInputStation.GetId() << ", Lines: ";

            // std::cout << "(" << railLines.size() << " unique lines)" << std::endl;

            for (const std::string& fromLineId : railLines) {
                for (const std::string& toLineId : railLines) {
                    if (fromLineId == toLineId) continue;

                    PTCost transferCost(TRANSFER_TURNAROUND_TIME, 0.0, 1, 0);
                    AddPTArc(InputPTGraphArc(arcIdCounter++, railInputStation.GetId(), fromLineId, railInputStation.GetId(), toLineId, 0, ArcType::Transfer, transferCost));
                    // std::cout << "[DEBUG_TRANSFER_ARC_GENERATION] Generated Rail Transfer Arc ID: " << (arcIdCounter - 1)
                    //           << ", From Station: " << railInputStation.GetId() << ", From Line: " << fromLineId
                    //           << ", To Station: " << railInputStation.GetId() << ", To Line: " << toLineId << std::endl;
                    arcsForCurrentStation++;
                }
            }
            // std::cout << "[DEBUG_TRANSFER_ARC_GENERATION] -> Total " << arcsForCurrentStation << " Rail Transfer Arcs generated for Rail Station ID: " << railInputStation.GetId() << std::endl;
        } else {
            // std::cout << "[DEBUG_TRANSFER_ARC_GENERATION] Rail Station ID: " << railInputStation.GetId()
            //           << " has " << railLines.size() << " unique line(s). No transfer arcs generated." << std::endl;
        }
    }
    // std::cout << "--- Finished Generating Transfer Arcs ---" << std::endl;
    // std::cout << "Total Transfer Arcs Generated Across All Stations: " << (arcIdCounter - initialArcCounter) << std::endl;

    // 3. 도보(Footpath) 아크 생성

    // Initialize counters for each section
    // int road_to_road_footpath_count = 0;
    // int rail_to_rail_footpath_count = 0;
    // int intermodal_footpath_count = 0;

    // 3. 도보(Footpath) 아크 생성
    Captain::footpath footpathGenerator; // Genarate footpath arcs using the Footpath
    footpathGenerator.LoadFootpathNetwork(); // Load the footpath network

    // 3.1. 로드 정류장 간 도보 (InputStation의 Location 사용)
    // std::cout << "\n--- Generating Road-to-Road Footpath Arcs ---" << std::endl;
    for (size_t i = 0; i < roadStations.GetStations().size(); ++i) {
        for (size_t j = i + 1; j < roadStations.GetStations().size(); ++j) {
            const auto& fromInputStation = roadStations.GetStations()[i];
            const auto& toInputStation = roadStations.GetStations()[j];
            
            double distance = footpathGenerator.GetDistance(fromInputStation.GetCenter(), toInputStation.GetCenter());
            if (distance >= 0.0 && distance <= THRESHOLD_FOR_FOOTPATH) {
                double timeCost = distance / FOOTPATH_SPEED_MPS / 60.0; // 초 -> 분
                PTCost footpathCost(timeCost, distance, 0, 0);

                AddPTArc(InputPTGraphArc(arcIdCounter, fromInputStation.GetId(), "", toInputStation.GetId(), "", 0, ArcType::Footpath, footpathCost));
                arcIdCounter++;

                AddPTArc(InputPTGraphArc(arcIdCounter, toInputStation.GetId(), "", fromInputStation.GetId(), "", 0, ArcType::Footpath, footpathCost)); // 양방향
                arcIdCounter++;
                // road_to_road_footpath_count++;
            }
        }
    }
    // std::cout << "--- Total Road-to-Road Footpath Arcs Generated: " << road_to_road_footpath_count << " ---" << std::endl;

    // 3.2. 철도 정류장 간 도보 (InputRailStation의 Location 사용)
    // std::cout << "\n--- Generating Rail-to-Rail Footpath Arcs ---" << std::endl;
    for (size_t i = 0; i < railStations.GetRailStations().size(); ++i) {
        for (size_t j = i + 1; j < railStations.GetRailStations().size(); ++j) {
            const auto& fromInputRailStation = railStations.GetRailStations()[i];
            const auto& toInputRailStation = railStations.GetRailStations()[j];

            double distance = footpathGenerator.GetDistance(fromInputRailStation.GetCenter(), toInputRailStation.GetCenter());
            if (distance >= 0.0 && distance <= THRESHOLD_FOR_FOOTPATH) {
                double timeCost = distance / FOOTPATH_SPEED_MPS / 60.0;
                PTCost footpathCost(timeCost, distance, 0, 0);

                AddPTArc(InputPTGraphArc(arcIdCounter, fromInputRailStation.GetId(), "", toInputRailStation.GetId(), "", 0, ArcType::Footpath, footpathCost));
                arcIdCounter++;

                AddPTArc(InputPTGraphArc(arcIdCounter, toInputRailStation.GetId(), "", fromInputRailStation.GetId(), "", 0, ArcType::Footpath, footpathCost));
                arcIdCounter++;
            }
        }
    }
    // std::cout << "--- Total Rail-to-Rail Footpath Arcs Generated: " << rail_to_rail_footpath_count << " ---" << std::endl;


    // 3.3. 로드 정류장과 철도 정류장 간 도보 (Intermodal)
    // std::cout << "\n--- Generating Intermodal (Road-to-Rail) Footpath Arcs ---" << std::endl;
    for (const auto& roadInputStation : roadStations.GetStations()) {
        for (const auto& railInputStation : railStations.GetRailStations()) {

            double distance = footpathGenerator.GetDistance(roadInputStation.GetCenter(), railInputStation.GetCenter());
            if (distance >= 0.0 && distance <= THRESHOLD_FOR_FOOTPATH) {
                double timeCost = distance / FOOTPATH_SPEED_MPS / 60.0;
                PTCost footpathCost(timeCost, distance, 0, 0);

                // Add Road to Rail
                AddPTArc(InputPTGraphArc(arcIdCounter, roadInputStation.GetId(), "", railInputStation.GetId(), "", 0, ArcType::Footpath, footpathCost));
                // LOG_FOOTPATH_ARC(arcIdCounter, roadInputStation.GetId(), railInputStation.GetId(), distance, timeCost, "Intermodal Footpath (Road->Rail)");
                arcIdCounter++;
                // intermodal_footpath_count++;

                // Add Rail to Road
                AddPTArc(InputPTGraphArc(arcIdCounter, railInputStation.GetId(), "", roadInputStation.GetId(), "", 0, ArcType::Footpath, footpathCost));
                // LOG_FOOTPATH_ARC(arcIdCounter, railInputStation.GetId(), roadInputStation.GetId(), distance, timeCost, "Intermodal Footpath (Rail->Road)");
                arcIdCounter++;
                // intermodal_footpath_count++;
            }
        }
    }
    // std::cout << "--- Total Intermodal Footpath Arcs Generated: " << intermodal_footpath_count << " ---" << std::endl;

    // // Final total count
    // std::cout << "\n=== Footpath Arc Generation Summary ===" << std::endl;
    // std::cout << "Total Footpath Arcs (Road-to-Road): " << road_to_road_footpath_count << std::endl;
    // std::cout << "Total Footpath Arcs (Rail-to-Rail): " << rail_to_rail_footpath_count << std::endl;
    // std::cout << "Total Footpath Arcs (Intermodal): " << intermodal_footpath_count << std::endl;
    // std::cout << "Grand Total Footpath Arcs Generated: " << (arcIdCounter - initial_arc_id_counter) << std::endl;
}


PTGraph::PTGraph(const PTVertexArr& vertexArr, const PTArcArr& arcArr)
    : m_vertexArr(vertexArr),m_arcArr(arcArr)
{
    m_vertexToArc.clear();
    m_arcToArc.clear();

    [[maybe_unused]] const auto& vertices = m_vertexArr.GetPTVertices();
    const auto& arcs = m_arcArr.GetPTArcs();

    std::unordered_map<int, std::vector<int>> arcsFromStop;

    for (const auto& arc : arcs) {
        int fromStopId = arc.GetFromStopId();
        int arcId = arc.GetArcId();

        m_vertexToArc[fromStopId].emplace_back(arcId);
        arcsFromStop[fromStopId].emplace_back(arcId);
        m_arcToArc.emplace(arcId, std::vector<int>());
    }

    for (const auto& arc : arcs) {
        int currentArcId = arc.GetArcId();
        int destinationStopId = arc.GetToStopId();

        const auto& nextArcs = arcsFromStop[destinationStopId];
        for (int nextArcId : nextArcs) {
            if (nextArcId != currentArcId) {
                m_arcToArc[currentArcId].push_back(nextArcId);
            }
        }
    }
}

} // namespace NextSimIO
