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

#include <NextSim_io/parser/PTGraphArr.hpp>
#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{

int convertTimeToMinutes(const std::string& time) {
    int h = 0, m = 0, s = 0;

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
        s = std::stoi(time.substr(i2 + 1));
    }

    return h * 60 + m;
}


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
        int accumulatedTravelTime = 0; 

            for (size_t i = 0; i < stationSeq.size(); ++i) {
                if (i > 0) {
                    accumulatedTravelTime += 5; // 이전 정류장에서 다음 정류장까지 5분 걸린다고 임시 가정
                }
                
                int arrivalMinute = startTime + accumulatedTravelTime;
                int departureMinute = arrivalMinute + 1; // 도착 후 1분 대기/환승 시간

                arrivalTimes.push_back(arrivalMinute);
                departureTimes.push_back(departureMinute);
            }
        } ////// 시간 계산 로직
        
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

    for (const auto& railLine : railPTLines.GetRailLine()) {
        int lineId = railLine.GetID();
        std::vector<int> stationSeq = railLine.GetTrailStationSeq(); 

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
                        int min = convertTimeToMinutes(t);
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
                departureTimes.push_back(arr + 1);  // 1분 대기
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

PTArcArr::PTArcArr(const StationArr& roadStations, const RailStationArr& railStations) 
{   

}


    void PTArcArr::AddPTArc(const InputPTGraphArc& arc)
    {
        m_ptArcs.push_back(arc);
    }

    void PTArcArr::Clear()
    {
        m_ptArcs.clear();
    }

// PTGraph Implementation
PTGraph::PTGraph(const PTArcArr& arcArr, const PTVertexArr& vertexArr)
    : m_arcArr(arcArr), m_vertexArr(vertexArr)
{
    // Clear existing mappings
    m_vertexToArc.clear();
    m_arcToArc.clear();

    // Build vertex to arc mapping
    const auto& vertices = m_vertexArr.GetPTVertices();
    const auto& arcs = m_arcArr.GetPTArcs();

    // Initialize vertex to arc mapping
    for (const auto& vertex : vertices) {
        int vertexId = vertex.GetStop().GetStopId();
        m_vertexToArc[vertexId] = std::vector<int>();
    }

    // Build mappings based on arcs
    for (size_t i = 0; i < arcs.size(); ++i) {
        const auto& arc = arcs[i];
        // Assuming InputPTGraphArc has methods to get source and destination vertex IDs
        // You'll need to implement these methods in InputPTGraphArc class
        /*
        int sourceVertexId = arc.GetSourceVertexId();
        int destVertexId = arc.GetDestVertexId();
        int arcId = arc.GetArcId();

        // Add arc to source vertex's outgoing arcs
        m_vertexToArc[sourceVertexId].push_back(arcId);

        // Build arc to arc connections
        // This would depend on your specific graph connectivity requirements
        if (m_arcToArc.find(arcId) == m_arcToArc.end()) {
            m_arcToArc[arcId] = std::vector<int>();
        }
        */
    }

    // For now, print the number of vertices and arcs created
    std::cout << "PTGraph built with " << vertices.size() << " vertices and " 
            << arcs.size() << " arcs." << std::endl;
}

} // namespace NextSimIO