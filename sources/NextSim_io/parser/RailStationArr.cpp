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
RailStationArr::RailStationArr() {
    LoadRailStations();
}

RailStationArr::RailStationArr(const std::string& dayOfWeek) {
    LoadRailStations(dayOfWeek);
}

void RailStationArr::LoadRailStations(const std::optional<std::string>& dayOfWeekFilter) {
    TiXmlDocument doc;
    if (!doc.LoadFile(RailStationNewXMLPath.string().c_str())) {
        std::cerr << "Loading failed (RailStationArr)\n";
        return;
    }

    TiXmlElement* root = doc.FirstChildElement("RailPublicTransit");
    TiXmlElement* railStations = root ? root->FirstChildElement("railStations") : nullptr;

    for (TiXmlElement* stationElem = railStations ? railStations->FirstChildElement("railStation") : nullptr;
         stationElem != nullptr;
         stationElem = stationElem->NextSiblingElement("railStation"))
    {
        int id = std::stoi(stationElem->Attribute("id"));

        std::string transitMode = stationElem->Attribute("transitMode") ?: "";

        std::string lineListStr = stationElem->Attribute("lineList") ?: "";
        std::istringstream lineStream(lineListStr);
        std::vector<std::string> lineList;
        std::string line;
        while (lineStream >> line) lineList.push_back(line);
        
        std::string address = stationElem->Attribute("address") ?: "";

        std::string centerStr = stationElem->Attribute("center") ?: "";
        double x = 0, y = 0;
        std::stringstream(centerStr) >> x >> y;
        std::pair<double, double> center(x, y);

        InputRailStation station(id, transitMode, lineList, address, center);

        // Parse exits
        for (TiXmlElement* exitElem = stationElem->FirstChildElement("exit");
             exitElem != nullptr;
             exitElem = exitElem->NextSiblingElement("exit"))
        {
            int exitId = std::stoi(exitElem->Attribute("id"));
            int linkRef = std::stoi(exitElem->Attribute("linkRef"));
            double offset = std::stod(exitElem->Attribute("offset"));
            double accessTime = std::stod(exitElem->Attribute("accessTime"));
            station.PushExit(exit(exitId, linkRef, offset, accessTime));
        }

        // Parse timetables
        for (TiXmlElement* timetableElem = stationElem->FirstChildElement("timetable");
             timetableElem != nullptr;
             timetableElem = timetableElem->NextSiblingElement("timetable"))
        {
            std::string dayOfWeek = timetableElem->Attribute("dayOfWeek") ?: "";

            if (dayOfWeekFilter && *dayOfWeekFilter != dayOfWeek) {
                continue;
            }

            std::string lineId    = timetableElem->Attribute("lineId")    ?: "";
            std::string type = timetableElem->Attribute("type") ?: "";
            const char* rawTime   = timetableElem->Attribute("time");

            std::vector<std::string> times;
            if (rawTime) {
                std::istringstream timeStream(rawTime);
                std::string time;
                while (timeStream >> time) {
                    times.push_back(std::move(time));
                }
            }

            timetable timetable(dayOfWeek, lineId, type, std::move(times));
            station.Pushtimetable(std::move(timetable));
        }

        m_railstations.push_back(std::move(station));
        m_stopMap.emplace(id, Stop(id, m_railstations.back().GetStopType()));
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