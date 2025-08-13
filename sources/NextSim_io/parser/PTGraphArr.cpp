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
#include <NextSim_io/inputclass/footpath/footpath.hpp>
#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>
#include <captain/Util/RouteGenerator.hpp>

using namespace Captain;
namespace NextSimIO
{

// ### Helper functions ### ///
int convertToMinutes(const std::string& time) {
    try {
        if (time.empty()) {
            std::cerr << "Error: Empty time string" << std::endl;
            return -1;
        }

        size_t colonPos = time.find(':');
        if (colonPos == std::string::npos || colonPos == 0 || colonPos == time.length() - 1) {
            std::cerr << "Error: Invalid time format for '" << time << "'" << std::endl;
            return -1;
        }

        std::string hourStr = time.substr(0, colonPos);
        std::string minStr = time.substr(colonPos + 1);

        if (hourStr.empty() || minStr.empty()) {
            std::cerr << "Error: Empty hour or minute for '" << time << "'" << std::endl;
            return -1;
        }

        int hour = std::stoi(hourStr);
        int minute = std::stoi(minStr);

        if (minute < 0 || minute >= 60) {
            std::cerr << "Error: Invalid minute value for '" << time << "'" << std::endl;
            return -1;
        }

        if (hour < 0 || hour > 24) {
            std::cerr << "Error: Invalid hour value for '" << time << "'" << std::endl;
            return -1;
        }

        // Next day
        if (hour == 24) {
            return 1440 + minute;
        }

        return hour * 60 + minute;

    } catch (const std::exception& e) {
        std::cerr << "Error: Exception in convertToMinutes for '" << time << "': " << e.what() << std::endl;
        return -1;
    }
}

double euclidDist(const std::pair<double, double>& p1, const std::pair<double, double>& p2) // Euclidean distance (flat coordinate)
{
    double dx = p1.first - p2.first;
    double dy = p1.second - p2.second;
    return std::sqrt(dx * dx + dy * dy);
}

double GetBusTravelTime(int originLinkID, int destLinkID, double avgSpeedMps) {
    RouteGenerator routeGen;

    // 최단 경로 실행
    std::vector<int> path = routeGen.ExecuteDijkstraForSinglePair(originLinkID, destLinkID, false);
    if (path.empty()) {
        std::cerr << "경로를 찾을 수 없습니다.\n";
        return -1.0;
    }

    // 경로 추출 및 거리 계산
    VehicleRoute route = routeGen.ExtractRoutesForSinglePair(path, {false, 0});
    double totalDistance = route.GetDistance();  // meters

    // 시간 계산 (초 -> 분)
    double timeSec = totalDistance / avgSpeedMps;
    double timeMin = timeSec / 60.0;

    return timeMin;
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

// Constants for footpath/transfer logic
const double THRESHOLD_FOR_FOOTPATH = 10000.0; // meters
const double FOOTPATH_SPEED_MPS = 1.11;      // meters per second (approximately 67m per minute, or 4 km/h)
const double THRESHOLD_FOR_INTERMODAL_TRANSFER = 1000.0; // meters for intermodal transfer
const double TRANSFER_TIME_MINUTES = 1.0; // Fixed transfer time in minutes, to 1 min.
const double avgBusSpeed = 20.0;

PTVertexArr::PTVertexArr() {}

PTVertexArr::PTVertexArr(const StationArr& roadStations, const RailStationArr& railStations,
                            const PTlineArr& roadPTLines, const RailLineArr& railPTLines)
{
    m_ptVertices.clear();

    // road station
    for (const auto& roadLine : roadPTLines.GetPTLines()) {
        std::vector<int> arrivalTimes;
        std::vector<int> departureTimes;
        std::string lineId = roadLine.GetID();
        std::vector<int> stationSeq = roadLine.GetStationSeq(); 
        double interval = roadLine.GetInterval();

        const int startMinuteOfDay = 6 * 60;   // 06:00
        const int endMinuteOfDay = 24 * 60;    // 24:00 (다음 날 00:00)
        const int dwellTime = 1; // 정류장에서의 대기 시간 (1분)

        for (int startTime = startMinuteOfDay; startTime < endMinuteOfDay; startTime += static_cast<int>(interval)) {
            int currentTime = startTime;

            for (size_t i = 0; i < stationSeq.size(); ++i) {
                arrivalTimes.push_back(currentTime);
                departureTimes.push_back(currentTime + dwellTime);

                if (i + 1 < stationSeq.size()) {
                    int originStopId = stationSeq[i];
                    int destStopId = stationSeq[i + 1];

                    // auto findInputStation = [](const std::vector<InputStation>& stations, int stopId) -> const InputStation* {
                    //     for (const auto& station : stations) {
                    //         if (station.GetId() == stopId) {
                    //             return &station;
                    //         }
                    //     }
                    //     return nullptr;
                    // };

                    // const std::vector<InputStation>& stationList = roadStations.GetStations();
                    // const InputStation* originStation = findInputStation(stationList, originStopId);
                    // const InputStation* destStation = findInputStation(stationList, destStopId);

                    // if (!roadStations.HasStop(originStopId) || !roadStations.HasStop(destStopId)) {
                    //     std::cerr << "정류장 정보가 없습니다.\n";
                    //     continue;
                    // }

                    // int originLinkID = originStation->GetLink();
                    // int destLinkID = destStation->GetLink();

                    // double travelTimeMin = GetBusTravelTime(originLinkID, destLinkID, avgBusSpeed);

                    // if (travelTimeMin < 0) {
                    //     std::cerr << "경로 계산 실패: " << originLinkID << " -> " << destLinkID << "\n";
                    //     continue;
                    // }

                    double travelTimeMin = 2.0;

                    currentTime += dwellTime + static_cast<int>(std::round(travelTimeMin));
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

    // rail station
    for (const auto& railLine : railPTLines.GetRailLines()) {
        std::string lineId = railLine.GetID();
        std::vector<int> stationSeq = railLine.GetRailStationSeq(); 

        // std::cerr << "[LINE] Processing line: " << lineId << ", stations count: " << stationSeq.size() << "\n";

        std::map<int, std::vector<int>> arrivalsPerStop;  // stopId → 도착 시각 목록
        bool isValidLine = true;

        for (int stopId : stationSeq) {
            // std::cerr << "  [STOP] Checking stopId: " << stopId << "\n";

            const InputRailStation* station = nullptr;
            for (const auto& s : railStations.GetRailStations()) {
                if (s.GetId() == stopId) {
                    station = &s;
                    break;
                }
            }

            if (!station) {
                std::cerr << "  [ERROR] Stop " << stopId << " not found for line " << lineId << ". Skipping line.\n";
                isValidLine = false;
                break;
            }

            bool found = false;
            for (const auto& tt : station->GetTimetables()) {
                // std::cerr << "      [CHECK] timetable.routeId = " << tt.GetrouteId()
                //         << ", type = " << tt.GetType()
                //         << ", times = " << tt.GetTime().size() << " entries\n";

                if (tt.GetrouteId() == lineId) {
                    const auto& times = tt.GetTime();
                    for (const auto& t : times) {
                        // std::cerr << "        [TIME] Raw: '" << t << "'\n";
                        int min = convertToMinutes(t);
                        if (min != -1) {
                            arrivalsPerStop[stopId].push_back(min);
                            // std::cerr << "        [TIME] Converted to min: " << min << "\n";
                        } else {
                            std::cerr << "        [WARN] Invalid time string: '" << t << "'\n";
                        }
                    }
                    found = true;
                    break;
                }
            }

            if (!found) {
                std::cerr << "    [WARN] No timetable found for stop " << stopId << " and line " << lineId << "\n";
                isValidLine = false;
                break;
            }
        }

        if (!isValidLine) {
            std::cerr << "  [SKIP] Line " << lineId << " skipped due to missing data.\n";
            continue;
        }

        size_t numRuns;

        if (stationSeq.empty()) {
            numRuns = 0;
        } else {
            numRuns = std::numeric_limits<size_t>::max();
            for (int stopId : stationSeq) {
                if (!arrivalsPerStop.count(stopId)) {
                    std::cerr << "  [WARN] No arrivals recorded for stopId=" << stopId << "\n";
                    numRuns = 0;
                    break;  // 정류장 하나라도 없으면 0으로 처리
                }

                size_t stopRuns = arrivalsPerStop[stopId].size();
                // std::cerr << "  [INFO] stopId=" << stopId << ", arrivals count=" << stopRuns << "\n";

                if (stopRuns == 0) {
                    std::cerr << "  [WARN] Stop " << stopId << " has zero arrivals.\n";
                    numRuns = 0;
                    break;
                }

                numRuns = std::min(numRuns, stopRuns);
            }
        }

        // std::cerr << "  [RUNS] Number of runs for line " << lineId << ": " << numRuns << "\n";

        if (numRuns == 0) {
            std::cerr << "  [SKIP] No runs found for line " << lineId << ".\n";
            continue;
        }

        std::vector<int> arrivalTimes, departureTimes;
        bool isConsistent = true;

        for (size_t i = 0; i < numRuns; ++i) {
            // std::cerr << "  [RUN] Processing run #" << i << "\n";
            for (int stopId : stationSeq) {
                if (!arrivalsPerStop.count(stopId)) {
                    std::cerr << "    [ERR] No arrivals for stop " << stopId << " in run " << i << "\n";
                    isConsistent = false;
                    break;
                }

                if (arrivalsPerStop[stopId].size() <= i) {
                    std::cerr << "    [ERR] arrivalsPerStop[" << stopId << "].size() = "
                            << arrivalsPerStop[stopId].size() << " <= " << i << "\n";
                    isConsistent = false;
                    break;
                }

                int arr = arrivalsPerStop[stopId][i];
                arrivalTimes.push_back(arr);
                departureTimes.push_back(arr + 1);
                // std::cerr << "    [TIME] stopId=" << stopId << " arr=" << arr << " dep=" << (arr + 1) << "\n";
            }

            if (!isConsistent) break;
        }

        if (!isConsistent) {
            std::cerr << "  [SKIP] Inconsistent timetable for line " << lineId << "\n";
            continue;
        }

        std::shared_ptr<Line> currentLine = 
            std::make_shared<Line>(lineId, stationSeq, arrivalTimes, departureTimes);

        // std::cerr << "  [LINE OBJECT] Created Line object: lineId=" << lineId
        //         << ", arrivalTimes.size=" << arrivalTimes.size()
        //         << ", departureTimes.size=" << departureTimes.size() << "\n";

        size_t arrivals = stationSeq.size();
        size_t runCount = numRuns;

        // std::cerr << "  [VERTEX] Creating vertices: runs=" << runCount << ", stops per run=" << arrivals << "\n";

        for (size_t run = 0; run < runCount; ++run) {
            for (size_t stopIdx = 0; stopIdx < arrivals; ++stopIdx) {
                int stopId = stationSeq[stopIdx];
                const Stop* realStop = nullptr;

                if (railStations.HasStop(stopId)) {
                    realStop = &railStations.GetStopById(stopId);
                    // std::cerr << "    [FOUND] Stop " << stopId << " found in railStations\n";
                } else {
                    std::cerr << "    [WARN] Stop " << stopId << " not found in railStations\n";
                }

                if (realStop) {
                    InputPTGraphVertex vertex(*realStop, currentLine);
                    m_ptVertices.push_back(vertex);
                    // std::cerr << "    [VERTEX CREATED] stopId=" << stopId << " run=" << run << "\n";
                } else {
                    std::cerr << "    [SKIP] Could not create vertex for stopId=" << stopId << "\n";
                }
            }
        }

        // std::cerr << "[DONE] Line " << lineId << " processed with " << m_ptVertices.size() << " total vertices.\n";
    }
}

    void PTVertexArr::AddPTVertex(const InputPTGraphVertex& vertex)
    {
        m_ptVertices.push_back(vertex);
    }

    void PTVertexArr::Clear()
    {
        m_ptVertices.clear();
    }


// PTArcArr Implementation
PTArcArr::PTArcArr() {}

PTArcArr::PTArcArr(const StationArr& roadStations, const RailStationArr& railStations,
                            const PTlineArr& roadPTLines, const RailLineArr& railPTLines) 
{   
    m_ptArcs.clear();

    //// 로그 ////
    m_arcLogFile.open("arc_log.txt", std::ios::out | std::ios::trunc); 
    if (!m_arcLogFile.is_open()) {
        std::cerr << "Error: Could not open arc_log.txt for writing!" << std::endl;
    } else {
        m_arcLogFile << "Arc_ID,From_Stop_ID,From_Line_ID,To_Stop_ID,To_Line_ID,Departure_Time,Arc_Type,Time_Cost,Distance_Cost,Count_Cost\n";
    }
    //////////////

    size_t arcIdCounter = 0; 
    
    // 1.1. Road Line (버스) InVehicle 아크 생성
    for (const auto& roadLine : roadPTLines.GetPTLines()) {
        std::string lineId = roadLine.GetID(); // string으로 유지
        
        // lineId 유효성 검사 (빈 문자열 체크)
        if (lineId.empty()) {
            std::cerr << "Invalid line ID: empty string" << std::endl;
            continue;
        }

        std::vector<int> stationSeq = roadLine.GetStationSeq(); 
        double interval = roadLine.GetInterval();
        
        const int startMinuteOfDay = 6 * 60;
        const int endMinuteOfDay = 24 * 60;
        const int dwellTime = 1;

        // 각 '운행(run)'에 대해 InVehicle 아크 생성
        for (int startTime = startMinuteOfDay; startTime < endMinuteOfDay; startTime += static_cast<int>(interval)) {
            std::vector<int> arrivalTimes;
            std::vector<int> departureTimes;

            int currentTime = startTime;

            for (size_t i = 0; i < stationSeq.size(); ++i) {
                arrivalTimes.push_back(currentTime);
                departureTimes.push_back(currentTime + dwellTime);

                if (i + 1 < stationSeq.size()) {
                    int originStopId = stationSeq[i];
                    int destStopId = stationSeq[i + 1];

                    // auto findInputStation = [](const std::vector<InputStation>& stations, int stopId) -> const InputStation* {
                    //     for (const auto& station : stations) {
                    //         if (station.GetId() == stopId) {
                    //             return &station;
                    //         }
                    //     }
                    //     return nullptr;
                    // };

                    // const std::vector<InputStation>& stationList = roadStations.GetStations();
                    // const InputStation* originStation = findInputStation(stationList, originStopId);
                    // const InputStation* destStation = findInputStation(stationList, destStopId);

                    // if (!roadStations.HasStop(originStopId) || !roadStations.HasStop(destStopId)) {
                    //     std::cerr << "정류장 정보가 없습니다.\n";
                    //     continue;
                    // }

                    // int originLinkID = originStation->GetLink();
                    // int destLinkID = destStation->GetLink();

                    // double travelTimeMin = GetBusTravelTime(originLinkID, destLinkID, avgBusSpeed);

                    // if (travelTimeMin < 0) {
                    //     std::cerr << "경로 계산 실패: " << originLinkID << " -> " << destLinkID << "\n";
                    //     continue;
                    // }
                    double travelTimeMin = 2.0; // 임시로 2분으로 설정

                    currentTime += dwellTime + static_cast<int>(std::round(travelTimeMin));
                }
            }

            // 이 run의 InVehicle 아크들을 생성
            for (size_t i = 0; i < stationSeq.size() - 1; ++i) { // 마지막 정류장 전까지
                int fromStopId = stationSeq[i];
                int toStopId = stationSeq[i+1];

                double timeCost = 0.0;
                if (i < departureTimes.size() && (i + 1) < arrivalTimes.size()) {
                    int fromTime = departureTimes[i];
                    int toTime = arrivalTimes[i + 1];
                    timeCost = static_cast<double>(toTime - fromTime);
                    if (timeCost < 0) {
                        timeCost += 24 * 60; // 다음 날로 넘어가는 경우
                    }
                } else {
                    std::cerr << "Warning: Road Line " << lineId << " run " << (startTime/static_cast<int>(interval))
                              << ": Time data out of bounds for segment " << fromStopId << " to " << toStopId << ". Skipping." << std::endl;
                    continue;
                }

                PTCost inVehicleCost(timeCost, 0, 0);
                AddPTArc(InputPTGraphArc(arcIdCounter++, fromStopId, lineId, toStopId, lineId, departureTimes[i], ArcType::InVehicle, inVehicleCost));
            }
        }
    }
    
    // 1.2. Rail Line (철도) InVehicle 아크 생성
    for (const auto& railLine : railPTLines.GetRailLines()) {
        std::string lineId = railLine.GetID(); // int를 string으로 변환
        std::vector<int> stationSeq = railLine.GetRailStationSeq(); 

        std::map<int, std::vector<int>> startTimes;
        std::map<int, std::vector<int>> terminalTimes;

        // std::cerr << "[DEBUG] Processing rail line " << lineId << " with " << stationSeq.size() << " stations.\n";

        if (stationSeq.size() < 2) {
            std::cerr << "Warning: rail line " << lineId << " has less than 2 stations.\n";
            continue;
}

        // 시작역과 종착역 ID
        int startStationId = stationSeq.front();
        int terminalStationId = stationSeq.back();

        const InputRailStation* startStation = nullptr;
        const InputRailStation* terminalStation = nullptr;

        // 시작/종착역 객체 찾기
        for (const auto& s : railStations.GetRailStations()) {
            if (s.GetId() == startStationId) startStation = &s;
            if (s.GetId() == terminalStationId) terminalStation = &s;
        }

        if (!startStation || !terminalStation) {
            std::cerr << "Error: Start or terminal station not found for line " << lineId << "\n";
            continue;
        }

        bool hasStart = false, hasTerminal = false;

        // 시작역의 start timetable 파싱
        for (const auto& tt : startStation->GetTimetables()) {
            if (tt.GetrouteId() != railLine.GetID()) continue;
            if (tt.GetType() == "start") {
                for (const auto& t : tt.GetTime()) {
                    int min = convertToMinutes(t);
                    if (min != -1) startTimes[startStationId].push_back(min);
                }
                hasStart = true;
            }
        }

        // 종착역의 terminal timetable 파싱
        for (const auto& tt : terminalStation->GetTimetables()) {
            if (tt.GetrouteId() != railLine.GetID()) continue;
            if (tt.GetType() == "terminal") {
                for (const auto& t : tt.GetTime()) {
                    int min = convertToMinutes(t);
                    if (min != -1) terminalTimes[terminalStationId].push_back(min);
                }
                hasTerminal = true;
            }
        }

        if (!hasStart || !hasTerminal) {
            std::cerr << "Warning: Missing start or terminal timetable for line " << lineId << "\n";
            continue;
        }

        // 타임 수 확인
        size_t startCount = startTimes[startStationId].size();
        size_t terminalCount = terminalTimes[terminalStationId].size();
        size_t numRuns = std::min(startCount, terminalCount);

        // std::cerr << "[DEBUG] startStationId=" << startStationId << ", startTimes=" << startCount
        //         << ", terminalStationId=" << terminalStationId << ", terminalTimes=" << terminalCount << "\n";

        if (numRuns == 0) {
            std::cerr << "[DEBUG] No valid runs found for line " << lineId << ". numRuns=0\n";
            continue;
        }

        // std::cerr << "[DEBUG] Number of runs for line " << lineId << ": " << numRuns << "\n"; !! 냅두기

        // Arc 생성
        for (size_t runIdx = 0; runIdx < numRuns; ++runIdx) {
            // std::cerr << "[DEBUG] Processing run index " << runIdx << "\n";

            int departure = startTimes[startStationId][runIdx];
            int arrival = terminalTimes[terminalStationId][runIdx];

            double timeCostTotal = static_cast<double>(arrival - departure);
            if (timeCostTotal < 0) timeCostTotal += 24 * 60;

            for (size_t i = 0; i < stationSeq.size() - 1; ++i) {
                int fromStop = stationSeq[i];
                int toStop = stationSeq[i + 1];

                int departure = startTimes[fromStop][runIdx];
                int arrival = terminalTimes[toStop][runIdx];

                double timeCost = static_cast<double>(arrival - departure);
                if (timeCost < 0) timeCost += 24 * 60;  // 다음날 도착 보정

                // std::cerr << "[DEBUG] Arc from " << fromStop << " to " << toStop
                //         << ", dep=" << departure << ", arr=" << arrival
                //         << ", cost=" << timeCost << "\n";

                PTCost inVehicleCost(timeCost, 0, 0);
                AddPTArc(InputPTGraphArc(
                    arcIdCounter++, fromStop, lineId, toStop, lineId, departure, ArcType::InVehicle, inVehicleCost));
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

                    PTCost transferCost(TRANSFER_TIME_MINUTES, 0.0, 1);
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
        for (const auto& tt : railInputStation.GetTimetables()) {
            railLines.insert(tt.GetrouteId());
        }
        long long arcsForCurrentStation = 0; // 현재 정류장의 아크 카운터

        if (railLines.size() > 1) {
            // std::cout << "[DEBUG_TRANSFER_ARC_GENERATION] Rail Station ID: " << railInputStation.GetId() << ", Lines: ";

            // std::cout << "(" << railLines.size() << " unique lines)" << std::endl;

            for (const std::string& fromLineId : railLines) {
                for (const std::string& toLineId : railLines) {
                    if (fromLineId == toLineId) continue;

                    PTCost transferCost(TRANSFER_TIME_MINUTES, 0.0, 1);
                    AddPTArc(InputPTGraphArc(arcIdCounter++, railInputStation.GetId(), fromLineId, railInputStation.GetId(), toLineId, 0, ArcType::Transfer, transferCost));
                    // 주석 처리: 각 아크 생성 시마다 출력하면 로그가 너무 길어질 수 있습니다.
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
    #define LOG_FOOTPATH_ARC(arc_id, from_id, to_id, distance, time_cost, type) \
    std::cout << "[DEBUG_ARC_GENERATION] Type: " << type << ", Arc ID: " << arc_id \
              << ", From Stop: " << from_id << ", To Stop: " << to_id \
              << ", Distance: " << std::fixed << std::setprecision(2) << distance << " m" \
              << ", Time Cost: " << std::fixed << std::setprecision(4) << time_cost << " min" \
              << std::endl;

    // Initialize counters for each section
    int road_to_road_footpath_count = 0;
    int rail_to_rail_footpath_count = 0;
    int intermodal_footpath_count = 0;

    // 3. 도보(Footpath) 아크 생성
    Captain::Footpath generator; // Genarate footpath arcs using the Footpath
    generator.LoadFootpathNetwork(); // Load the footpath network

    // 3.1. 로드 정류장 간 도보 (InputStation의 Location 사용)
    // std::cout << "\n--- Generating Road-to-Road Footpath Arcs ---" << std::endl;
    for (size_t i = 0; i < roadStations.GetStations().size(); ++i) {
        for (size_t j = i + 1; j < roadStations.GetStations().size(); ++j) {
            const auto& fromInputStation = roadStations.GetStations()[i];
            const auto& toInputStation = roadStations.GetStations()[j];
            
            double distance = generator.GetDistance(fromInputStation.GetCenter(), toInputStation.GetCenter());
            if (distance <= THRESHOLD_FOR_FOOTPATH) {
                double timeCost = distance / FOOTPATH_SPEED_MPS / 60.0; // 초 -> 분
                PTCost footpathCost(timeCost, distance, 0);

                // Add first direction
                AddPTArc(InputPTGraphArc(arcIdCounter, fromInputStation.GetId(), "", toInputStation.GetId(), "", 0, ArcType::Footpath, footpathCost));
                // LOG_FOOTPATH_ARC(arcIdCounter, fromInputStation.GetId(), toInputStation.GetId(), distance, timeCost, "Road-Road Footpath (Forward)");
                arcIdCounter++;
                road_to_road_footpath_count++;

                // Add reverse direction
                AddPTArc(InputPTGraphArc(arcIdCounter, toInputStation.GetId(), "", fromInputStation.GetId(), "", 0, ArcType::Footpath, footpathCost)); // 양방향
                // LOG_FOOTPATH_ARC(arcIdCounter, toInputStation.GetId(), fromInputStation.GetId(), distance, timeCost, "Road-Road Footpath (Reverse)");
                arcIdCounter++;
                road_to_road_footpath_count++;
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

            double distance = generator.GetDistance(fromInputRailStation.GetCenter(), toInputRailStation.GetCenter());
            if (distance <= THRESHOLD_FOR_FOOTPATH) {
                double timeCost = distance / FOOTPATH_SPEED_MPS / 60.0;
                PTCost footpathCost(timeCost, distance, 0);

                // Add first direction
                AddPTArc(InputPTGraphArc(arcIdCounter, fromInputRailStation.GetId(), "", toInputRailStation.GetId(), "", 0, ArcType::Footpath, footpathCost));
                // LOG_FOOTPATH_ARC(arcIdCounter, fromInputRailStation.GetId(), toInputRailStation.GetId(), distance, timeCost, "Rail-Rail Footpath (Forward)");
                arcIdCounter++;
                rail_to_rail_footpath_count++;

                // Add reverse direction
                AddPTArc(InputPTGraphArc(arcIdCounter, toInputRailStation.GetId(), "", fromInputRailStation.GetId(), "", 0, ArcType::Footpath, footpathCost));
                // LOG_FOOTPATH_ARC(arcIdCounter, toInputRailStation.GetId(), fromInputRailStation.GetId(), distance, timeCost, "Rail-Rail Footpath (Reverse)");
                arcIdCounter++;
                rail_to_rail_footpath_count++;
            }
        }
    }
    // std::cout << "--- Total Rail-to-Rail Footpath Arcs Generated: " << rail_to_rail_footpath_count << " ---" << std::endl;


    // 3.3. 로드 정류장과 철도 정류장 간 도보 (Intermodal)
    // std::cout << "\n--- Generating Intermodal (Road-to-Rail) Footpath Arcs ---" << std::endl;
    for (const auto& roadInputStation : roadStations.GetStations()) {
        for (const auto& railInputStation : railStations.GetRailStations()) {

            double distance = generator.GetDistance(roadInputStation.GetCenter(), railInputStation.GetCenter());
            if (distance) {
                double timeCost = distance / FOOTPATH_SPEED_MPS / 60.0;
                PTCost footpathCost(timeCost, distance, 0);

                // Add Road to Rail
                AddPTArc(InputPTGraphArc(arcIdCounter, roadInputStation.GetId(), "", railInputStation.GetId(), "", 0, ArcType::Footpath, footpathCost));
                // LOG_FOOTPATH_ARC(arcIdCounter, roadInputStation.GetId(), railInputStation.GetId(), distance, timeCost, "Intermodal Footpath (Road->Rail)");
                arcIdCounter++;
                intermodal_footpath_count++;

                // Add Rail to Road
                AddPTArc(InputPTGraphArc(arcIdCounter, railInputStation.GetId(), "", roadInputStation.GetId(), "", 0, ArcType::Footpath, footpathCost));
                // LOG_FOOTPATH_ARC(arcIdCounter, railInputStation.GetId(), roadInputStation.GetId(), distance, timeCost, "Intermodal Footpath (Rail->Road)");
                arcIdCounter++;
                intermodal_footpath_count++;
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
    /////// 로그 ///////
    // PTArcArr 소멸자
    PTArcArr::~PTArcArr() {
        if (m_arcLogFile.is_open()) {
            m_arcLogFile.close();
        }
    }

    void PTArcArr::AddPTArc(const InputPTGraphArc& arc)
    {
        m_ptArcs.push_back(arc);

            // 파일에 아크 정보 기록
        if (m_arcLogFile.is_open()) {
            m_arcLogFile << arc.GetArcId() << ","
                        << arc.GetFromStopId() << ","
                        << arc.GetFromLineId() << ","
                        << arc.GetToStopId() << ","
                        << arc.GetToLineId() << ","
                        << arc.GetDepTime() << ","
                        << static_cast<int>(arc.GetType()) << "," // ArcType을 int로 변환하여 저장
                        << std::fixed << std::setprecision(4) << arc.GetCost()[0].GetTimeCost() << ","
                        << std::fixed << std::setprecision(2) << arc.GetCost()[0].GetFootpathCost() << ","
                        << arc.GetCost()[0].GetTransferCost() << "\n";
        }
        ////////////////
    }
    
    void PTArcArr::Clear()
    {
        m_ptArcs.clear();
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