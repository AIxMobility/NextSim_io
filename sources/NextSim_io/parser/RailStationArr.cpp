/**
 * NextSim Captain
 * @file : RailStation.cpp
 * @version : 2.0
 * @author : Yuseock Hwang, Yeonwoo Yu, Dongheon Lee
 */
#include <iostream>
#include <sstream>
#include <string>

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
        const char* idAttr = stationElem->Attribute("id");
        if (!idAttr) {
            std::cerr << "[WARN] Skipping railStation: missing id attribute\n";
            continue;
        }
        int id = std::stoi(idAttr);

        std::string transitMode = stationElem->Attribute("transitMode") ? stationElem->Attribute("transitMode") : "";

        std::string lineListStr = stationElem->Attribute("lineList") ? stationElem->Attribute("lineList") : "";
        std::istringstream lineStream(lineListStr);
        std::vector<std::string> lineList;
        std::string line;
        while (lineStream >> line) lineList.push_back(line);

        // prefer 'name' attribute; fall back to 'address' for older files
        std::string name = stationElem->Attribute("name") ? stationElem->Attribute("name") : "";
        if (name.empty() && stationElem->Attribute("address")) name = stationElem->Attribute("address");

        std::string centerStr = stationElem->Attribute("center") ? stationElem->Attribute("center") : "";
        double x = 0.0, y = 0.0;
        if (!centerStr.empty()) {
            std::istringstream ss(centerStr);
            ss >> x >> y;
        }
        std::pair<double, double> center(x, y);

        InputRailStation station(id, transitMode, lineList, name, center);

        // Parse exits
        for (TiXmlElement* exitElem = stationElem->FirstChildElement("exit");
             exitElem != nullptr;
             exitElem = exitElem->NextSiblingElement("exit"))
        {
            const char* exitIdAttr = exitElem->Attribute("id");
            const char* linkRefAttr = exitElem->Attribute("linkRef");
            if (!exitIdAttr || !linkRefAttr) continue;
            int exitId = std::stoi(exitIdAttr);
            int linkRef = std::stoi(linkRefAttr);
            int offset = exitElem->Attribute("offset") ? std::stoi(exitElem->Attribute("offset")) : 0;
            int accessTime = exitElem->Attribute("accessTime") ? std::stoi(exitElem->Attribute("accessTime")) : 0;
            station.PushExit(exit(exitId, linkRef, offset, accessTime));
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