/**
 * NextSim Captain
 * @file : RailLineArr.cpp
 * @version : 1.0
 * @author : Yuseock Hwang
 */
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

#include <NextSim_io/parser/RailLineArr.hpp>

#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
RailLineArr::RailLineArr()
{
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::RailStationNewXMLPath.string().c_str());

    if (!loadSuccess)
    {
        std::cout << "Loading failed (RailStationArr)" << std::endl;
        return;
    }

    TiXmlElement *modeElem = doc.FirstChildElement("Mode");

    TiXmlElement *routesElem = modeElem->FirstChildElement("routes");

    for (TiXmlElement *routeElem = routesElem->FirstChildElement("route");
             routeElem != nullptr;
             routeElem = routeElem->NextSiblingElement("route"))
    {
        std::string routeId = routeElem->Attribute("id");
        std::string stationSeqStr = routeElem->Attribute("railStationSeq");

        std::vector<int> stationSeq;
        std::istringstream stationStream(stationSeqStr);
        int station;
        while (stationStream >> station)
        {
            stationSeq.push_back(station);
        }

        InputRailLine route(routeId, stationSeq);
        m_railline.push_back(route);
    }
    doc.Clear();


};
} // namespace NextSimIO