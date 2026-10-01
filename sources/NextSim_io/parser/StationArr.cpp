/**
 * NextSim Captain
 * @file : StationArr.cpp
 * @version : 1.1
 * @author : Sujae Jeon, Yeonwoo Yu
 */

#include <filesystem>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

#include <NextSim_io/parser/StationArr.hpp>
#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
StationArr::StationArr()
{
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::RoadStationXMLPath.string().c_str());

    if (!loadSuccess)
    {
        std::cerr << "Loading failed (StationArr)" << std::endl;
        return;
    }

    TiXmlElement* root = doc.FirstChildElement();

    for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; 
        elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        if (elemName == "Stations")
        {
            for (TiXmlElement* e = elem->FirstChildElement(); e != NULL; 
                e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "station")
                {
                    const char *idStr = e->Attribute("id");
                    const char *linkStr = e->Attribute("link_ref");
                    const char *laneStr = e->Attribute("lane_ref");
                    const char *posStr = e->Attribute("pos");
                    
                    if (!idStr) throw std::runtime_error("Element should have 'id' attribute");
                    if (!linkStr) throw std::runtime_error("Element should have 'link_ref' attribute");
                    if (!laneStr) throw std::runtime_error("Element should have 'lane_ref' attribute");
                    if (!posStr) throw std::runtime_error("Element should have 'pos' attribute");

                    int id = atol(idStr);
                    int link = atol(linkStr);
                    int lane = atol(laneStr);
                    double pos = atof(posStr);

                    int parkingLots = 0;
                    if (e->Attribute("parkingLots"))
                        parkingLots = atol(e->Attribute("parkingLots"));
                    
                    std::string centerStr = e->Attribute("center");
                    std::stringstream ss(centerStr);
                    double x, y;
                    std::pair<double, double> center;
                    if (ss >> x >> y)
                    {
                        center = std::make_pair(x, y);
                    }

                    InputStation station(id, link, lane, pos, parkingLots, center);

                    TiXmlElement* lineElement = e->FirstChildElement("line");
                    if (lineElement && lineElement->Attribute("list"))
                    {
                        station.SetLineList(lineElement->Attribute("list"));
                    }

                    m_stations.push_back(station);
                    
                    // Form stop object and add to map for pt routing
                    Stop stop(id, station.GetStopType()); 
                    m_stopMap.emplace(id, stop);

                }
            }
        }
        else if (elemName == "Drt_Stations")
        {
            for (TiXmlElement* e = elem->FirstChildElement(); e != NULL; 
                e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "station")
                {
                    int id = atol(e->Attribute("id"));
                    int link = atol(e->Attribute("link_ref"));
                    int lane = atol(e->Attribute("lane_ref"));

                    InputDRTStation drtStation(id, link, lane);

                    // Parse position range (if exists)
                    if (e->Attribute("pos_range"))
                    {
                        drtStation.SetPosRange(e->Attribute("pos_range"));
                    }

                    m_drtStations.push_back(drtStation);
                }
            }
        }
    }
    doc.Clear();
}

bool StationArr::HasStop(int stopId) const {
    return m_stopMap.find(stopId) != m_stopMap.end();
}

const Stop& StationArr::GetStopById(int stopId) const {
    auto it = m_stopMap.find(stopId);
    if (it == m_stopMap.end()) {
        throw std::out_of_range("Stop ID " + std::to_string(stopId) + " not found.");
    }
    return it->second;
}

} // namespace NextSimIO
