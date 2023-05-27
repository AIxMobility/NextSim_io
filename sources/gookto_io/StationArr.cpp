#include <filesystem>
#include <iostream>
#include <string>
#include <cstdlib>

#include <gookto_io/tinyapi/tinystr.h>
#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/StationArr.hpp>
#include <gookto_io/InputStation.hpp>
#include <gookto_io/FilePath.hpp>

StationArr::StationArr()
{
    TiXmlDocument doc("");
    bool loadOkay = doc.LoadFile(STSIO::NetworkXMLPath.string().c_str());
    // std::cout << "Loading StationArr" << std::endl;

    if (!loadOkay)
    {
        std::cout << "Loading failed (StationArr)" << std::endl;
        std::cerr << doc.ErrorDesc() << std::endl;
        exit(0);
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != nullptr;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        if (elemName == "stations")
        {
            for (TiXmlElement *e = elem->FirstChildElement(); e != nullptr;
                 e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "station")
                {
                    const char *id = e->Attribute("id");
                    const char *lane_ref = e->Attribute("lane_ref");
                    const char *link_ref = e->Attribute("link_ref");
                    const char *pos = e->Attribute("pos");

                    if (!id) throw std::runtime_error ("Element should have 'id' attribute");
                    if (!lane_ref) throw std::runtime_error ("Element should have 'lane_ref' attribute");
                    if (!link_ref) throw std::runtime_error ("Element should have 'link_ref' attribute");
                    if (!pos) throw std::runtime_error ("Element should have 'pos' attribute");

                    InputStation demoStation(
                        static_cast<std::size_t>(atoll(id)),
                        atoi(lane_ref),
                        atof(link_ref),
                        atof(pos));

                    Stations.push_back(demoStation);
                }
            }
        }
    }
}