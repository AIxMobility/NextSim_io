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

#include <NextSim_io/parser/PTGraphArr.hpp>
#include <NextSim_io/inputclass/footpath/footpath.hpp>
#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{

// ### Helper functions ### ///
int convertToMinutes(const std::string& time) {
    int h = 0, m = 0;

    size_t i1 = time.find(':');
    if (i1 == std::string::npos) {
        std::cerr << "Error: Invalid time format (no colon) for '" << time << "'" << std::endl;
        return -1;
    }

    h = std::stoi(time.substr(0, i1));
    size_t i2 = time.find(':', i1 + 1);

    if (i2 == std::string::npos) {
        m = std::stoi(time.substr(i1 + 1));
    } else {
        m = std::stoi(time.substr(i1 + 1, i2 - i1 - 1));
    }

    return h * 60 + m;
}

double euclidDist(const std::pair<double, double>& p1, const std::pair<double, double>& p2) // Euclidean distance (flat coordinate)
{
    double dx = p1.first - p2.first;
    double dy = p1.second - p2.second;
    return std::sqrt(dx * dx + dy * dy);
}

// Constants for footpath/transfer logic
const double THRESHOLD_FOR_FOOTPATH = 1000.0; // meters
const double FOOTPATH_SPEED_MPS = 1.11;      // meters per second (approximately 67m per minute, or 4 km/h)
const double THRESHOLD_FOR_INTERMODAL_TRANSFER = 1000.0; // meters for intermodal transfer
const double TRANSFER_TIME_MINUTES = 1.0; // Fixed transfer time in minutes, to 1 min.


PTVertexArr::PTVertexArr() {}

PTVertexArr::PTVertexArr(const StationArr& roadStations, const RailStationArr& railStations,
                            const PTlineArr& roadPTLines, const RailLineArr& railPTLines)
{
    m_ptVertices.clear();

    for (const auto& roadLine : roadPTLines.GetPTLines()) {
        std::string lineId = roadLine.GetID();
        std::vector<int> stationSeq = roadLine.GetStationSeq(); 
        double interval = roadLine.GetInterval();

        std::vector<int> arrivalTimes;
        std::vector<int> departureTimes;

        // road pt 시간 계산 업데이트 필요!!! /////
        const int startMinuteOfDay = 6 * 60;   // 06:00
        const int endMinuteOfDay = 24 * 60;    // 24:00 (다음 날 00:00)

        for (int startTime = startMinuteOfDay; startTime < endMinuteOfDay; startTime += static_cast<int>(interval)) {
        int accTravelTime = 0; 

            for (size_t i = 0; i < stationSeq.size(); ++i) {
                if (i > 0) {
                    accTravelTime += interval; // 이전 정류장에서 다음 정류장까지 interval 만큼 걸린다고 임시 가정
                }
                
                int arrivalMinute = startTime + accTravelTime;
                int departureMinute = arrivalMinute + 1; // 도착 후 1분 대기/환승 시간

                arrivalTimes.push_back(arrivalMinute);
                departureTimes.push_back(departureMinute);
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


    // rail station 처리 
    for (const auto& railLine : railPTLines.GetRailLine()) {
        std::string lineId = railLine.GetID();
        std::vector<int> stationSeq = railLine.GetRailStationSeq(); 

        std::map<int, std::vector<int>> arrivalsPerStop;  // stopId → 도착 시각 목록
        bool isValidLine = true;

        for (int stopId : stationSeq) {
            const InputRailStation* station = nullptr;
            for (const auto& s : railStations.GetRailStations()) {
                if (s.GetId() == stopId) {
                    station = &s;
                    break;
                }
            }

            if (!station) {
                std::cerr << "Error: Stop " << stopId << " not found for line " << lineId << ". Skipping.\n";
                isValidLine = false;
                break;
            }

            bool found = false;
            for (const auto& tt : station->GetTimetables()) {
                if (tt.GetrouteId() == lineId) {
                    for (const auto& t : tt.GetTime()) {
                        int min = convertToMinutes(t);
                        if (min != -1) arrivalsPerStop[stopId].push_back(min);
                        else std::cerr << "Warning: Invalid time '" << t << "' for line " << lineId << " at stop " << stopId << "\n";
                    }
                    found = true;
                    break;
                }
            }

            if (!found) {
                std::cerr << "Warning: No timetable for line " << lineId << " at stop " << stopId << ". Skipping.\n";
                isValidLine = false;
                break;
            }
        }

        if (!isValidLine) {
            std::cerr << "Warning: Line " << lineId << " skipped due to missing data.\n";
            continue;
        }

        size_t numRuns = stationSeq.empty() || !arrivalsPerStop.count(stationSeq[0]) 
                        ? 0 : arrivalsPerStop[stationSeq[0]].size();

        if (numRuns == 0) {
            std::cerr << "Warning: No runs found for line " << lineId << ". Skipping.\n";
            continue;
        }

        std::vector<int> arrivalTimes, departureTimes;
        bool isConsistent = true;

        for (size_t i = 0; i < numRuns; ++i) {
            for (int stopId : stationSeq) {
                if (!arrivalsPerStop.count(stopId) || arrivalsPerStop[stopId].size() <= i) {
                    std::cerr << "Error: Inconsistent data for line " << lineId 
                            << ", stop " << stopId << ", run " << i << ". Skipping.\n";
                    isConsistent = false;
                    break;
                }
                int arr = arrivalsPerStop[stopId][i];
                arrivalTimes.push_back(arr);
                departureTimes.push_back(arr + 1);  
            }
            if (!isConsistent) break;
        }

        if (!isConsistent) {
            std::cerr << "Warning: Line " << lineId << " skipped due to inconsistent timetable.\n";
            continue;
        }
        
        std::shared_ptr<Line> currentLine = 
            std::make_shared<Line>(lineId, stationSeq, arrivalTimes, departureTimes);

        size_t arrivals = stationSeq.size();
        size_t runCount = numRuns; 

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
        int intInterval = static_cast<int>(interval);
        if (intInterval <= 0) intInterval = 1;

        // 각 '운행(run)'에 대해 InVehicle 아크 생성
        for (int startTime = startMinuteOfDay; startTime < endMinuteOfDay; startTime += intInterval) {
            std::vector<int> arrivalTimes;
            std::vector<int> departureTimes;
            int accTravelTime = 0; // accumulated travel time in minutes

            for (size_t i = 0; i < stationSeq.size(); ++i) {
                if (i > 0) {
                    accTravelTime += interval;
                }
                arrivalTimes.push_back(startTime + accTravelTime);
                departureTimes.push_back(startTime + accTravelTime + 1);
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
                    std::cerr << "Warning: Road Line " << lineId << " run " << (startTime/intInterval)
                              << ": Time data out of bounds for segment " << fromStopId << " to " << toStopId << ". Skipping." << std::endl;
                    continue;
                }

                PTCost inVehicleCost(timeCost, 0, 0);
                AddPTArc(InputPTGraphArc(arcIdCounter++, fromStopId, lineId, toStopId, lineId, ArcType::InVehicle, inVehicleCost));
            }
        }
    }
    
    // 1.2. Rail Line (철도) InVehicle 아크 생성
    for (const auto& railLine : railPTLines.GetRailLine()) {
        std::string lineId = railLine.GetID(); // int를 string으로 변환
        std::vector<int> stationSeq = railLine.GetRailStationSeq(); 

        std::map<int, std::vector<int>> arrivalsPerStop; // stopId → 해당 stop의 모든 run에 대한 도착 시각 목록
        bool isValidLine = true;

        for (int stopId : stationSeq) {
            const InputRailStation* station = nullptr;
            for (const auto& s : railStations.GetRailStations()) {
                if (s.GetId() == stopId) {
                    station = &s;
                    break;
                }
            }

            if (!station) {
                std::cerr << "Error: Rail Stop " << stopId << " not found for line " << lineId << ". Skipping InVehicle arc generation for this line.\n";
                isValidLine = false;
                break;
            }

            bool foundTimetable = false;
            for (const auto& tt : station->GetTimetables()) {
                if (tt.GetrouteId() == railLine.GetID()) { // 원래 int ID와 비교
                    for (const auto& t : tt.GetTime()) {
                        int min = convertToMinutes(t);
                        if (min != -1) arrivalsPerStop[stopId].push_back(min);
                        else std::cerr << "Warning: Invalid time '" << t << "' for rail line " << lineId << " at stop " << stopId << "\n";
                    }
                    foundTimetable = true;
                    break;
                }
            }
            if (!foundTimetable) {
                std::cerr << "Warning: No timetable for rail line " << lineId << " at stop " << stopId << ". Skipping InVehicle arc generation for this line.\n";
                isValidLine = false;
                break;
            }
        }
        if (!isValidLine) { continue; }

        size_t numRuns = stationSeq.empty() || !arrivalsPerStop.count(stationSeq[0]) 
                         ? 0 : arrivalsPerStop[stationSeq[0]].size();
        if (numRuns == 0) {
            std::cerr << "Warning: No runs found for rail line " << lineId << ". Skipping InVehicle arc generation.\n";
            continue;
        }

        // 각 '운행(run)'에 대해 InVehicle 아크 생성
        for (size_t runIdx = 0; runIdx < numRuns; ++runIdx) {
            std::vector<int> arrivalTimes, departureTimes;
            bool isConsistentRun = true;

            for (int stopId : stationSeq) {
                if (!arrivalsPerStop.count(stopId) || arrivalsPerStop[stopId].size() <= runIdx) {
                    std::cerr << "Error: Rail Line " << lineId << " run " << runIdx 
                              << ": Inconsistent data for stop " << stopId << ". Skipping this run for InVehicle arcs." << std::endl;
                    isConsistentRun = false;
                    break;
                }
                int arr = arrivalsPerStop[stopId][runIdx];
                arrivalTimes.push_back(arr);
                departureTimes.push_back(arr + 1); // 1분 대기 (임시)
            }
            if (!isConsistentRun) continue;

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
                    std::cerr << "Warning: Rail Line " << lineId << " run " << runIdx
                              << ": Time data out of bounds for segment " << fromStopId << " to " << toStopId << ". Skipping." << std::endl;
                    continue;
                }

                PTCost inVehicleCost(timeCost, 0, 0);
                AddPTArc(InputPTGraphArc(arcIdCounter++, fromStopId, lineId, toStopId, lineId, ArcType::InVehicle, inVehicleCost));
            }
        }
    }

    // 2. 환승(Transfer) 아크 생성

    // 2.1. 같은 로드 정류장 내에서 다른 노선으로의 환승
    for (const auto& inputStation : roadStations.GetStations()) {
        const std::vector<std::string>& lineIds = inputStation.GetLineList();

        if (lineIds.size() > 1) {
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
                    AddPTArc(InputPTGraphArc(arcIdCounter++, inputStation.GetId(), fromLineId, inputStation.GetId(), toLineId, ArcType::Transfer, transferCost));
                }
            }
        }
    }
    
    // 2.2. 같은 철도 정류장 내에서 다른 노선으로의 환승
    for (const auto& railInputStation : railStations.GetRailStations()) {
        std::set<std::string> railLines;
        for (const auto& tt : railInputStation.GetTimetables()) {
            railLines.insert(tt.GetrouteId());
        }

        if (railLines.size() > 1) {
            for (const std::string& fromLineId : railLines) {
                for (const std::string& toLineId : railLines) {
                    if (fromLineId == toLineId) continue;

                    PTCost transferCost(TRANSFER_TIME_MINUTES, 0.0, 1);
                    AddPTArc(InputPTGraphArc(arcIdCounter++, railInputStation.GetId(), fromLineId, railInputStation.GetId(), toLineId, ArcType::Transfer, transferCost));
                }
            }
        }
    }

    // 3. 도보(Footpath) 아크 생성
    Captain::Footpath generator; // Genarate footpath arcs using the Footpath
    generator.LoadFootpathNetwork(); // Load the footpath network

    // 3.1. 로드 정류장 간 도보 (InputStation의 Location 사용)
    for (size_t i = 0; i < roadStations.GetStations().size(); ++i) {
        for (size_t j = i + 1; j < roadStations.GetStations().size(); ++j) {
            const auto& fromInputStation = roadStations.GetStations()[i];
            const auto& toInputStation = roadStations.GetStations()[j];
 
            double distance = generator.GetDistance(fromInputStation.GetCenter(), toInputStation.GetCenter());
            if (distance <= THRESHOLD_FOR_FOOTPATH) {
                double timeCost = distance / FOOTPATH_SPEED_MPS / 60.0; // 초 -> 분
                PTCost footpathCost(timeCost, distance, 0);
                AddPTArc(InputPTGraphArc(arcIdCounter++, fromInputStation.GetId(), "", toInputStation.GetId(), "", ArcType::Footpath, footpathCost));
                AddPTArc(InputPTGraphArc(arcIdCounter++, toInputStation.GetId(), "", fromInputStation.GetId(), "", ArcType::Footpath, footpathCost)); // 양방향
            }
        }
    }

    // 3.2. 철도 정류장 간 도보 (InputRailStation의 Location 사용)
    for (size_t i = 0; i < railStations.GetRailStations().size(); ++i) {
        for (size_t j = i + 1; j < railStations.GetRailStations().size(); ++j) {
            const auto& fromInputRailStation = railStations.GetRailStations()[i];
            const auto& toInputRailStation = railStations.GetRailStations()[j];

            double distance = generator.GetDistance(fromInputRailStation.GetCenter(), toInputRailStation.GetCenter());
            if (distance <= THRESHOLD_FOR_FOOTPATH) {
                double timeCost = distance / FOOTPATH_SPEED_MPS / 60.0;
                PTCost footpathCost(timeCost, distance, 0);
                AddPTArc(InputPTGraphArc(arcIdCounter++, fromInputRailStation.GetId(), "", toInputRailStation.GetId(), "", ArcType::Footpath, footpathCost));
                AddPTArc(InputPTGraphArc(arcIdCounter++, toInputRailStation.GetId(), "", fromInputRailStation.GetId(), "", ArcType::Footpath, footpathCost));
            }
        }
    }

    // 3.3. 로드 정류장과 철도 정류장 간 도보 (Intermodal)
    for (const auto& roadInputStation : roadStations.GetStations()) {
        for (const auto& railInputStation : railStations.GetRailStations()) {

            double distance = generator.GetDistance(roadInputStation.GetCenter(), railInputStation.GetCenter());
            if (distance <= THRESHOLD_FOR_INTERMODAL_TRANSFER) {
                double timeCost = distance / FOOTPATH_SPEED_MPS / 60.0;
                PTCost footpathCost(timeCost, distance, 0);
                AddPTArc(InputPTGraphArc(arcIdCounter++, roadInputStation.GetId(), "", railInputStation.GetId(), "", ArcType::Footpath, footpathCost));
                AddPTArc(InputPTGraphArc(arcIdCounter++, railInputStation.GetId(), "", roadInputStation.GetId(), "", ArcType::Footpath, footpathCost));
            }
        }
    }
}

    void PTArcArr::AddPTArc(const InputPTGraphArc& arc)
    {
        m_ptArcs.push_back(arc);
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

#ifdef DEBUG_PTGRAPH
    std::cout << "PTGraph built with " << vertices.size() << " vertices and "
              << arcs.size() << " arcs.\n";
    std::cout << "Vertex to Arc mapping: " << m_vertexToArc.size() << " entries.\n";
    std::cout << "Arc to Arc mapping: " << m_arcToArc.size() << " entries.\n";
#endif
}

} // namespace NextSimIO