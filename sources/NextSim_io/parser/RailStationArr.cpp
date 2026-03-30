/**
 * NextSim Captain
 * @file : RailStation.cpp
 * @version : 2.0
 * @author : Yuseock Hwang, Dongheon Lee
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
RailStationArr::RailStationArr()
{
    TiXmlDocument doc;
    const bool loadSuccess = doc.LoadFile(NextSimIO::RailStationXMLPath.string().c_str());

    if (!loadSuccess)
    {
        std::cout << "Loading failed (RailStationArr)" << std::endl;
        return;
    }

    TiXmlElement *root = doc.FirstChildElement("RailPublicTransit");
    if (root == nullptr)
    {
        std::cout << "Missing root element RailPublicTransit (RailStationArr)" << std::endl;
        return;
    }

    TiXmlElement *railStations = root->FirstChildElement("railStations");
    if (railStations == nullptr)
    {
        std::cout << "Missing railStations element (RailStationArr)" << std::endl;
        return;
    }

    for (TiXmlElement *stationElem = railStations->FirstChildElement("railStation");
        stationElem != nullptr;
        stationElem = stationElem->NextSiblingElement("railStation"))
    {
        const int id = std::stoi(stationElem->Attribute("id"));
        const std::string name = stationElem->Attribute("name");

        const std::string transitMode = stationElem->Attribute("transitMode");

        const std::string lineListStr = stationElem->Attribute("lineList");
        std::vector<std::string> lineList;
        std::istringstream lineStream(lineListStr);
        std::string line;
        while (std::getline(lineStream, line, ' '))
        {
            if (!line.empty())
            {
                lineList.push_back(line);
            }
        }

        InputRailStation station(id, name, transitMode, lineList);

        TiXmlElement *exitList = stationElem->FirstChildElement("exit");
        for (TiXmlElement *exitElem = exitList; exitElem != nullptr;
            exitElem = exitElem->NextSiblingElement("exit"))
        {
            int exitId = std::stoi(exitElem->Attribute("id"));
            int linkRef = std::stoi(exitElem->Attribute("linkRef"));
            int offset = std::stoi(exitElem->Attribute("offset"));
            int accessTime = std::stoi(exitElem->Attribute("accessTime"));

            exit stationExit(exitId, linkRef, offset, accessTime);
            station.PushExit(stationExit);
        }

        m_railstation.push_back(station);
    }
    doc.Clear();
};
} // namespace NextSimIO