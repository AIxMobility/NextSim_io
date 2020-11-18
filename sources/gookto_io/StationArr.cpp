#include <filesystem>
#include <iostream>
#include <string>
#include <cstdlib>

#include <gookto_io/tinyapi/tinystr.h>
#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/StationArr.hpp>
#include <gookto_io/InputStation.hpp>
#include <gookto_io/includes/gookto_io/FilePath.hpp>

LinkArr::LinkArr()
{
    std::filesystem::path cwd = std::filesystem::current_path();
    std::cout << cwd << std::endl;

    for (const auto &entry : std::filesystem::directory_iterator(cwd))
        std::cout << entry.path() << std::endl;

    std::filesystem::path netDir("network_xml");
    for (const auto &entry : std::filesystem::directory_iterator(cwd / netDir))
        std::cout << entry.path() << std::endl;

    TiXmlDocument doc("");
    bool loadOkay = doc.LoadFile(STSIO::NetworkXMLPath.string().c_str());

    std::cout << loadOkay << std::endl;

    std::cout << "Loading StationArr" << std::endl;

    if (!loadOkay)
    {
        std::cout << "loading failed" << std::endl;
        std::cerr << doc.ErrorDesc() << std::endl;
        exit(0);
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != nullptr;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        // const char *attr;
        if (elemName == "stations")
        {

            std::cout << "Got stations" << std::endl;
            std::cout << (elem->FirstChildElement())->Value() << std::endl;
            for (TiXmlElement *e = elem->FirstChildElement(); e != nullptr;
                 e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "station")
                {
                    InputStation demoStation(
                        static_cast<std::size_t>(atoll(e->Attribute("id"))),
                        atoi(e->Attribute("lane_ref")),
                        atof(e->Attribute("link_ref")),
                        atof(e->Attribute("pos")));

                    Stations.push_back(demoStation);
                }
            }
        }
    }
}