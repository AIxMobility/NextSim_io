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
    TiXmlDocument doc(STSIO::StationXMLPath.string().c_str());
    bool loadOkay = doc.LoadFile();

    if (!loadOkay)
    {
        std::cout << "Loading failed (StationArr)" << std::endl;
        // std::cerr << doc.ErrorDesc() << std::endl;
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
                    InputStation demo(atol(e->Attribute("id")),
                                      atol(e->Attribute("link_ref")),
                                      atol(e->Attribute("lane_ref")),
                                      atof(e->Attribute("pos")),
                                      atol(e->Attribute("parkingLots")));
                                      
                    auto ee = e->FirstChildElement();
                    auto line_list = ee->Attribute("list");
                    demo.setLineList(line_list);
                    
                    Stations.push_back(demo);
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
                    InputDRTStation demo(atol(e->Attribute("id")),
                                         atol(e->Attribute("link_ref")),
                                         atol(e->Attribute("lane_ref")));
                    
                    std::string pos_range = e->Attribute("pos_range");
                    demo.setPosRange(pos_range);
                    
                    DRTStations.push_back(demo);
                }
            }
        }
    }
    doc.Clear();
}