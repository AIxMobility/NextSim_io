/**
 * NextSim Captain
 * @file : RailStation.cpp
 * @version : 1.0
 * @author : Yuseock Hwang
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
    bool loadSuccess = doc.LoadFile(NextSimIO::RailStationXMLPath.string().c_str());

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

        const std::string lineLisStr = stationElem->Attribute("lineList");
        std::vector<std::string> lineList;
        std::istringstream lineStream(lineLisStr);
        std::string line;
        while (std::getline(lineStream, line, ' ')) {
            lineList.push_back(line);
        }

        const std::string address = stationElem->Attribute("address");

        InputRailStation station(id, transitMode, lineList, address);


        TiXmlElement *exitList = stationElem->FirstChildElement("exit");
        for (TiXmlElement *exitElem = exitList; exitElem != nullptr;
            exitElem = exitElem->NextSiblingElement("exit"))
        {
            int exitId = std::stoi(exitElem->Attribute("id"));
            int linkRef = std::stoi(exitElem->Attribute("linkRef"));
            int offset = std::stod(exitElem->Attribute("offset"));
            double accessTime = std::stoi(exitElem->Attribute("accessTime"));

            exit exit(exitId, linkRef, offset, accessTime);
            station.PushExit(exit);
        }

        TiXmlElement *timetableList = stationElem->FirstChildElement("timetable");
        for (TiXmlElement *timetableElem = timetableList; timetableElem != nullptr;
        timetableElem = timetableElem->NextSiblingElement("timetable"))
        {
            std::string dayOfWeek = timetableElem->Attribute("dayOfWeek");
            std::string lineId = timetableElem->Attribute("lineId");
            std::vector<std::string> times;
            std::istringstream timeStream(timetableElem->Attribute("time"));
            std::string time;
            while (timeStream >> time)
            {
                times.push_back(time);
            }
            timetable timetable(dayOfWeek, lineId, times);

            station.Pushtimetable(timetable);
        }

        m_railstation.push_back(station);
    }
    doc.Clear();
};
} // namespace NextSimIO