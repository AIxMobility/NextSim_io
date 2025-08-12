/**
 * NextSim Captain
 * @file : RailStation.cpp
 * @version : 1.2
 * @author : Yuseock Hwang, Yeonwoo Yu
 */
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

#include <NextSim_io/parser/RailStationArr.hpp>

#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
RailStationArr::RailStationArr()
{
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::RailStationNewXMLPath.string().c_str());

    if (!loadSuccess)
    {
        std::cout << "Loading failed (RailStationArr)" << std::endl;
        return;
    }

    TiXmlElement *root = doc.FirstChildElement("RailPublicTransit");

    TiXmlElement *railStations = root->FirstChildElement("railStations");

    for (TiXmlElement *stationElem = railStations->FirstChildElement("railStation");
    stationElem != NULL;
    stationElem = stationElem->NextSiblingElement("railStation"))
    {
        const int id = std::stoi(stationElem->Attribute("id"));
        const std::string transitMode = stationElem->Attribute("transitMode");
        const std::string address = stationElem->Attribute("address");

        std::string centerStr = stationElem->Attribute("center");
        std::stringstream ss(centerStr);
        double x, y;
        std::pair<double, double> center;
        if (ss >> x >> y)
        {
            center = std::make_pair(x, y);
        }

        InputRailStation station(id, transitMode, address, center);

        TiXmlElement *exitList = stationElem->FirstChildElement("exit");
        for (TiXmlElement *exitElem = exitList; exitElem != nullptr;
            exitElem = exitElem->NextSiblingElement("exit"))
       {
           int exitId = std::stoi(exitElem->Attribute("id"));
           int linkRef = std::stoi(exitElem->Attribute("linkRef"));
           int offset = std::stod(exitElem->Attribute("offset"));
           double accessTime = std::stoi(exitElem->Attribute("accessTime"));

           Exit exit(exitId, linkRef, offset, accessTime);
           station.PushExit(exit);
       }

        TiXmlElement *timetableList = stationElem->FirstChildElement("timetable");
        for (TiXmlElement *timetableElem = timetableList; timetableElem != nullptr;
            timetableElem = timetableElem->NextSiblingElement("timetable"))
        {
            // NULL 포인터 체크를 더 안전하게
            const char* dayOfWeekAttr = timetableElem->Attribute("dayOfWeek");
            const char* routeIdAttr = timetableElem->Attribute("routeId");
            const char* typeAttr = timetableElem->Attribute("type");
            const char* rawTime = timetableElem->Attribute("time");

            std::string dayOfWeek = dayOfWeekAttr ? std::string(dayOfWeekAttr) : "";
            std::string routeId = routeIdAttr ? std::string(routeIdAttr) : "";
            std::string type = typeAttr ? std::string(typeAttr) : "";

            // std::cerr << "  [XML] Parsing timetable - routeId=" << routeId 
            //         << ", type=" << type << ", dayOfWeek=" << dayOfWeek << std::endl;

            if (!rawTime) {
                std::cerr << "  Warning: timetable with no time attribute for routeId=" << routeId << "\n";
                continue;
            }

            // 안전한 길이 체크
            size_t timeAttrLength = 0;
            try {
                timeAttrLength = strlen(rawTime);
            } catch (...) {
                std::cerr << "  Error: Failed to get length of time attribute\n";
                continue;
            }

            // std::cerr << "  [XML] Raw time attribute length: " << timeAttrLength << std::endl;

            // 너무 긴 문자열 처리
            const size_t MAX_TIME_ATTR_LENGTH = 20000; // 더 보수적으로 설정
            if (timeAttrLength > MAX_TIME_ATTR_LENGTH) {
                std::cerr << "  Warning: time attribute too long (" << timeAttrLength
                        << " chars) for routeId=" << routeId << ". Truncating.\n";
                timeAttrLength = MAX_TIME_ATTR_LENGTH;
            }

            // 안전한 string 생성
            std::string timeAttr;
            try {
                timeAttr.reserve(timeAttrLength + 100); // 여유분 추가
                timeAttr.assign(rawTime, timeAttrLength);
                // std::cerr << "  [XML] Time string created successfully, length: " << timeAttr.length() << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "  Error: Failed to create time string for routeId=" << routeId 
                        << ", error: " << e.what() << "\n";
                continue;
            }

            // 시간 문자열 샘플 출력 (처음 100자만)
            std::string sample = timeAttr.length() > 100 ? timeAttr.substr(0, 100) + "..." : timeAttr;
            // std::cerr << "  [XML] Time sample: " << sample << std::endl;

            std::vector<std::string> times;
            times.reserve(500); // 예상되는 시간 개수만큼 미리 예약

            try {
                std::istringstream timeStream(timeAttr);
                std::string time;
                const size_t maxTokens = 300; // 더 보수적으로 설정
                size_t tokenCount = 0;

                while (timeStream >> time && tokenCount < maxTokens) {
                    // 시간 형식 더 엄격하게 검증
                    if (time.length() >= 4 && time.length() <= 5) {
                        size_t colonPos = time.find(':');
                        if (colonPos != std::string::npos && colonPos > 0 && colonPos < time.length() - 1) {
                            // 시간과 분이 숫자인지 확인
                            std::string hourStr = time.substr(0, colonPos);
                            std::string minStr = time.substr(colonPos + 1);
                            
                            bool validHour = !hourStr.empty() && std::all_of(hourStr.begin(), hourStr.end(), ::isdigit);
                            bool validMin = !minStr.empty() && std::all_of(minStr.begin(), minStr.end(), ::isdigit);
                            
                            if (validHour && validMin) {
                                times.emplace_back(std::move(time));
                                tokenCount++;
                            } else {
                                std::cerr << "    Warning: Invalid time digits: " << time << "\n";
                            }
                        } else {
                            std::cerr << "    Warning: Invalid colon position: " << time << "\n";
                        }
                    } else {
                        std::cerr << "    Warning: Invalid time length: " << time << "\n";
                    }
                }

                if (tokenCount >= maxTokens) {
                    std::cerr << "Warning: too many time tokens (" << tokenCount 
                            << ") for routeId=" << routeId << ", truncating.\n";
                }

                // std::cerr << "  [XML] Parsed " << times.size() << " valid time entries\n";

                // Timetable 객체 생성 - 더 안전하게
                try {
                    Timetable timetable(std::move(dayOfWeek), std::move(routeId), std::move(type), std::move(times));
                    station.Pushtimetable(std::move(timetable));
                    // std::cerr << "  [XML] Timetable added successfully\n";
                } catch (const std::exception& e) {
                    std::cerr << "  Error: Failed to create/add timetable: " << e.what() << "\n";
                }

            } catch (const std::exception& e) {
                std::cerr << "  Error: Exception while parsing times for routeId=" << routeId 
                        << ", error: " << e.what() << "\n";
                continue;
            }
        }

        m_railstations.push_back(station);
        
        // Form stop object and add to map for pt routing
        Stop stop(id, station.GetStopType()); 
        m_stopMap.emplace(id, stop);

    }
    doc.Clear();

};

RailStationArr::RailStationArr(const std::string& dayOfWeekFilter)
{
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::RailStationNewXMLPath.string().c_str());

    if (!loadSuccess)
    {
        std::cout << "Loading failed (RailStationArr with filter)" << std::endl;
        return;
    }

    TiXmlElement *root = doc.FirstChildElement("RailPublicTransit");
    TiXmlElement *railStations = root->FirstChildElement("railStations");

    for (TiXmlElement *stationElem = railStations->FirstChildElement("railStation");
        stationElem != nullptr;
        stationElem = stationElem->NextSiblingElement("railStation"))
    {
        const int id = std::stoi(stationElem->Attribute("id"));
        const std::string transitMode = stationElem->Attribute("transitMode");
        const std::string address = stationElem->Attribute("address");

        std::string centerStr = stationElem->Attribute("center");
        std::stringstream ss(centerStr);
        double x, y;
        std::pair<double, double> center;
        if (ss >> x >> y)
        {
            center = std::make_pair(x, y);
        }

        InputRailStation station(id, transitMode, address, center);

        TiXmlElement *exitList = stationElem->FirstChildElement("exit");
        for (TiXmlElement *exitElem = exitList; exitElem != nullptr;
            exitElem = exitElem->NextSiblingElement("exit"))
        {
            int exitId = std::stoi(exitElem->Attribute("id"));
            int linkRef = std::stoi(exitElem->Attribute("linkRef"));
            int offset = std::stod(exitElem->Attribute("offset"));
            double accessTime = std::stoi(exitElem->Attribute("accessTime"));

            Exit exit(exitId, linkRef, offset, accessTime);
            station.PushExit(exit);
        }

        // timetable 파싱 (요일 필터 적용)
        TiXmlElement *timetableList = stationElem->FirstChildElement("timetable");
        for (TiXmlElement *timetableElem = timetableList; timetableElem != nullptr;
            timetableElem = timetableElem->NextSiblingElement("timetable"))
        {
            const char* dayOfWeekAttr = timetableElem->Attribute("dayOfWeek");
            if (!dayOfWeekAttr || dayOfWeekFilter != dayOfWeekAttr)
                continue;  // 필터링

            const char* routeIdAttr = timetableElem->Attribute("routeId");
            const char* typeAttr = timetableElem->Attribute("type");
            const char* rawTime = timetableElem->Attribute("time");

            std::string dayOfWeek = std::string(dayOfWeekAttr);
            std::string routeId = routeIdAttr ? std::string(routeIdAttr) : "";
            std::string type = typeAttr ? std::string(typeAttr) : "";
            
            // std::cerr << "  [XML] Parsing timetable - routeId=" << routeId 
            //         << ", type=" << type << ", dayOfWeek=" << dayOfWeek << std::endl;

            if (!rawTime) continue;

            size_t timeAttrLength = strlen(rawTime);
            if (timeAttrLength > 20000) timeAttrLength = 20000;

            std::string timeAttr(rawTime, timeAttrLength);
            std::vector<std::string> times;
            std::istringstream timeStream(timeAttr);
            std::string time;
            size_t tokenCount = 0;
            const size_t maxTokens = 300;

            while (timeStream >> time && tokenCount < maxTokens)
            {
                if (time.length() >= 4 && time.length() <= 5) {
                    size_t colonPos = time.find(':');
                    if (colonPos != std::string::npos) {
                        std::string hourStr = time.substr(0, colonPos);
                        std::string minStr = time.substr(colonPos + 1);

                        if (std::all_of(hourStr.begin(), hourStr.end(), ::isdigit) &&
                            std::all_of(minStr.begin(), minStr.end(), ::isdigit)) {
                            times.emplace_back(std::move(time));
                            tokenCount++;
                        }
                    }
                }
            }

            try {
                Timetable timetable(std::move(dayOfWeek), std::move(routeId), std::move(type), std::move(times));
                station.Pushtimetable(std::move(timetable));
            } catch (...) {
                // ignore bad timetable
            }
        }

        m_railstations.push_back(station);
        m_stopMap.emplace(id, Stop(id, station.GetStopType()));
    }

    doc.Clear();
}


bool RailStationArr::HasStop(int stopId) const {
    return m_stopMap.find(stopId) != m_stopMap.end();
}

const Stop& RailStationArr::GetStopById(int stopId) const {
    auto it = m_stopMap.find(stopId);
    if (it == m_stopMap.end()) {
        throw std::out_of_range("Stop ID " + std::to_string(stopId) + " not found.");
    }
    return it->second;
}

} // namespace NextSimIO