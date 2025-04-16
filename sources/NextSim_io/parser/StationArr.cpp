/**
 * NextSim Captain
 * @file : StationArr.cpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#include <filesystem>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>

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
                    int id = atol(e->Attribute("id"));
                    int link = atol(e->Attribute("link_ref"));
                    int lane = atol(e->Attribute("lane_ref"));
                    double pos = atof(e->Attribute("pos"));

                    // Handle optional `parkingLots`
                    int parkingLots = 0;
                    if (e->Attribute("parkingLots"))
                        parkingLots = atol(e->Attribute("parkingLots"));

                    InputStation station(id, link, lane, pos, parkingLots);

                    // Parse <line list="...">
                    TiXmlElement* lineElement = e->FirstChildElement("line");
                    if (lineElement && lineElement->Attribute("list"))
                    {
                        station.SetLineList(lineElement->Attribute("list"));
                    }

                    m_stations.push_back(station);
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

} // namespace NextSimIO
