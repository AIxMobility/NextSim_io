/**
 * NextSim Captain
 * @file : RailStation.cpp
 * @version : 1.1
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
            std::string dayOfWeek = timetableElem->Attribute("dayOfWeek");
            std::string routeId = timetableElem->Attribute("routeId");
            std::string type = timetableElem->Attribute("type");
            std::vector<std::string> times;

            std::istringstream timeStream(timetableElem->Attribute("time"));
            std::string time;
            while (timeStream >> time)
            {
                times.push_back(time);
            }
            Timetable timetable(dayOfWeek, routeId, type, times);

            station.Pushtimetable(timetable);
        }

        m_railstations.push_back(station);
        
        // Form stop object and add to map for pt routing
        Stop stop(id, station.GetStopType()); 
        m_stopMap.emplace(id, stop);

    }
    doc.Clear();

};

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